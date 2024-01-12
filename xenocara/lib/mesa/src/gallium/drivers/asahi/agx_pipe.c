/*
 * Copyright 2010 Red Hat Inc.
 * Copyright 2014-2017 Broadcom
 * Copyright 2019-2020 Collabora, Ltd.
 * Copyright 2006 VMware, Inc.
 * SPDX-License-Identifier: MIT
 */
#include <errno.h>
#include <stdio.h>
#include <xf86drm.h>
#include "asahi/compiler/agx_compile.h"
#include "asahi/layout/layout.h"
#include "asahi/lib/agx_formats.h"
#include "asahi/lib/decode.h"
#include "drm-uapi/drm_fourcc.h"
#include "frontend/sw_winsys.h"
#include "frontend/winsys_handle.h"
#include "gallium/auxiliary/renderonly/renderonly.h"
#include "gallium/auxiliary/util/u_debug_cb.h"
#include "gallium/auxiliary/util/u_framebuffer.h"
#include "gallium/auxiliary/util/u_surface.h"
#include "gallium/auxiliary/util/u_transfer.h"
#include "gallium/auxiliary/util/u_transfer_helper.h"
#include "pipe/p_context.h"
#include "pipe/p_defines.h"
#include "pipe/p_screen.h"
#include "pipe/p_state.h"
#include "util/format/u_format.h"
#include "util/half_float.h"
#include "util/u_drm.h"
#include "util/u_gen_mipmap.h"
#include "util/u_inlines.h"
#include "util/u_memory.h"
#include "util/u_screen.h"
#include "util/u_upload_mgr.h"
#include "agx_device.h"
#include "agx_disk_cache.h"
#include "agx_fence.h"
#include "agx_public.h"
#include "agx_state.h"

/* Fake values, pending UAPI upstreaming */
#ifndef DRM_FORMAT_MOD_APPLE_TWIDDLED
#define DRM_FORMAT_MOD_APPLE_TWIDDLED (2)
#endif
#ifndef DRM_FORMAT_MOD_APPLE_TWIDDLED_COMPRESSED
#define DRM_FORMAT_MOD_APPLE_TWIDDLED_COMPRESSED (3)
#endif

/* clang-format off */
static const struct debug_named_value agx_debug_options[] = {
   {"trace",     AGX_DBG_TRACE,    "Trace the command stream"},
   {"deqp",      AGX_DBG_DEQP,     "Hacks for dEQP"},
   {"no16",      AGX_DBG_NO16,     "Disable 16-bit support"},
   {"perf",      AGX_DBG_PERF,     "Print performance warnings"},
#ifndef NDEBUG
   {"dirty",     AGX_DBG_DIRTY,    "Disable dirty tracking"},
#endif
   {"precompile",AGX_DBG_PRECOMPILE,"Precompile shaders for shader-db"},
   {"nocompress",AGX_DBG_NOCOMPRESS,"Disable lossless compression"},
   {"nocluster", AGX_DBG_NOCLUSTER,"Disable vertex clustering"},
   {"sync",      AGX_DBG_SYNC,     "Synchronously wait for all submissions"},
   {"stats",     AGX_DBG_STATS,    "Show command execution statistics"},
   {"resource",  AGX_DBG_RESOURCE, "Log resource operations"},
   DEBUG_NAMED_VALUE_END
};
/* clang-format on */

uint64_t agx_best_modifiers[] = {
   DRM_FORMAT_MOD_APPLE_TWIDDLED_COMPRESSED,
   DRM_FORMAT_MOD_APPLE_TWIDDLED,
   DRM_FORMAT_MOD_LINEAR,
};

void agx_init_state_functions(struct pipe_context *ctx);

/*
 * resource
 */

static enum ail_tiling
ail_modifier_to_tiling(uint64_t modifier)
{
   switch (modifier) {
   case DRM_FORMAT_MOD_LINEAR:
      return AIL_TILING_LINEAR;
   case DRM_FORMAT_MOD_APPLE_TWIDDLED:
      return AIL_TILING_TWIDDLED;
   case DRM_FORMAT_MOD_APPLE_TWIDDLED_COMPRESSED:
      return AIL_TILING_TWIDDLED_COMPRESSED;
   default:
      unreachable("Unsupported modifier");
   }
}

const static char *s_tiling[] = {
   [AIL_TILING_LINEAR] = "LINR",
   [AIL_TILING_TWIDDLED] = "TWID",
   [AIL_TILING_TWIDDLED_COMPRESSED] = "COMP",
};

#define rsrc_debug(res, ...)                                                   \
   do {                                                                        \
      if (agx_device((res)->base.screen)->debug & AGX_DBG_RESOURCE)            \
         agx_msg(__VA_ARGS__);                                                 \
   } while (0)

static void
agx_resource_debug(struct agx_resource *res, const char *msg)
{
   if (!(agx_device(res->base.screen)->debug & AGX_DBG_RESOURCE))
      return;

   int ino = -1;
   if (res->bo->prime_fd >= 0) {
      struct stat sb;
      if (!fstat(res->bo->prime_fd, &sb))
         ino = sb.st_ino;
   }

   agx_msg(
      "%s%s %dx%dx%d %dL %d/%dM %dS M:%llx %s %s%s S:0x%llx LS:0x%llx CS:0x%llx "
      "Base=0x%llx Size=0x%llx Meta=0x%llx/0x%llx (%s) %s%s%s%s%s%sfd:%d(%d) @ %p\n",
      msg ?: "", util_format_short_name(res->base.format), res->base.width0,
      res->base.height0, res->base.depth0, res->base.array_size,
      res->base.last_level, res->layout.levels, res->layout.sample_count_sa,
      (long long)res->modifier, s_tiling[res->layout.tiling],
      res->layout.mipmapped_z ? "MZ " : "",
      res->layout.page_aligned_layers ? "PL " : "",
      (long long)res->layout.linear_stride_B,
      (long long)res->layout.layer_stride_B,
      (long long)res->layout.compression_layer_stride_B,
      (long long)res->bo->ptr.gpu, (long long)res->layout.size_B,
      res->layout.metadata_offset_B
         ? ((long long)res->bo->ptr.gpu + res->layout.metadata_offset_B)
         : 0,
      (long long)res->layout.metadata_offset_B, res->bo->label,
      res->bo->flags & AGX_BO_SHARED ? "SH " : "",
      res->bo->flags & AGX_BO_LOW_VA ? "LO " : "",
      res->bo->flags & AGX_BO_EXEC ? "EX " : "",
      res->bo->flags & AGX_BO_WRITEBACK ? "WB " : "",
      res->bo->flags & AGX_BO_SHAREABLE ? "SA " : "",
      res->bo->flags & AGX_BO_READONLY ? "RO " : "", res->bo->prime_fd, ino,
      res);
}

static void
agx_resource_setup(struct agx_device *dev, struct agx_resource *nresource)
{
   struct pipe_resource *templ = &nresource->base;

   nresource->layout = (struct ail_layout){
      .tiling = ail_modifier_to_tiling(nresource->modifier),
      .mipmapped_z = templ->target == PIPE_TEXTURE_3D,
      .format = templ->format,
      .width_px = templ->width0,
      .height_px = templ->height0,
      .depth_px = templ->depth0 * templ->array_size,
      .sample_count_sa = MAX2(templ->nr_samples, 1),
      .levels = templ->last_level + 1,
   };
}

static struct pipe_resource *
agx_resource_from_handle(struct pipe_screen *pscreen,
                         const struct pipe_resource *templat,
                         struct winsys_handle *whandle, unsigned usage)
{
   struct agx_device *dev = agx_device(pscreen);
   struct agx_resource *rsc;
   struct pipe_resource *prsc;

   assert(whandle->type == WINSYS_HANDLE_TYPE_FD);

   rsc = CALLOC_STRUCT(agx_resource);
   if (!rsc)
      return NULL;

   rsc->modifier = whandle->modifier == DRM_FORMAT_MOD_INVALID
                      ? DRM_FORMAT_MOD_LINEAR
                      : whandle->modifier;

   /* We need strides to be aligned. ail asserts this, but we want to fail
    * gracefully so the app can handle the error.
    */
   if (rsc->modifier == DRM_FORMAT_MOD_LINEAR && (whandle->stride % 16) != 0) {
      FREE(rsc);
      return false;
   }

   prsc = &rsc->base;

   *prsc = *templat;

   pipe_reference_init(&prsc->reference, 1);
   prsc->screen = pscreen;

   rsc->bo = agx_bo_import(dev, whandle->handle);
   /* Sometimes an import can fail e.g. on an invalid buffer fd, out of
    * memory space to mmap it etc.
    */
   if (!rsc->bo) {
      FREE(rsc);
      return NULL;
   }

   agx_resource_setup(dev, rsc);

   if (rsc->layout.tiling == AIL_TILING_LINEAR) {
      rsc->layout.linear_stride_B = whandle->stride;
   } else if (whandle->stride != ail_get_wsi_stride_B(&rsc->layout, 0)) {
      FREE(rsc);
      return NULL;
   }

   assert(whandle->offset == 0);

   ail_make_miptree(&rsc->layout);

   if (prsc->target == PIPE_BUFFER) {
      assert(rsc->layout.tiling == AIL_TILING_LINEAR);
      util_range_init(&rsc->valid_buffer_range);
   }

   agx_resource_debug(rsc, "Import: ");

   return prsc;
}

static bool
agx_resource_get_handle(struct pipe_screen *pscreen, struct pipe_context *ctx,
                        struct pipe_resource *pt, struct winsys_handle *handle,
                        unsigned usage)
{
   struct agx_device *dev = agx_device(pscreen);
   struct pipe_resource *cur = pt;

   /* Even though asahi doesn't support multi-planar formats, we
    * can get here through GBM, which does. Walk the list of planes
    * to find the right one.
    */
   for (int i = 0; i < handle->plane; i++) {
      cur = cur->next;
      if (!cur)
         return false;
   }

   struct agx_resource *rsrc = agx_resource(cur);

   if (handle->type == WINSYS_HANDLE_TYPE_KMS && dev->ro) {
      rsrc_debug(rsrc, "Get handle: %p (KMS RO)\n", rsrc);

      if (!rsrc->scanout && dev->ro && (rsrc->base.bind & PIPE_BIND_SCANOUT)) {
         rsrc->scanout =
            renderonly_scanout_for_resource(&rsrc->base, dev->ro, NULL);
      }

      if (!rsrc->scanout)
         return false;

      return renderonly_get_handle(rsrc->scanout, handle);
   } else if (handle->type == WINSYS_HANDLE_TYPE_KMS) {
      rsrc_debug(rsrc, "Get handle: %p (KMS)\n", rsrc);

      handle->handle = rsrc->bo->handle;
   } else if (handle->type == WINSYS_HANDLE_TYPE_FD) {
      int fd = agx_bo_export(rsrc->bo);

      if (fd < 0)
         return false;

      handle->handle = fd;
      if (dev->debug & AGX_DBG_RESOURCE) {
         struct stat sb;
         fstat(rsrc->bo->prime_fd, &sb);
         agx_msg("Get handle: %p (FD %d/%ld)\n", rsrc, fd, (long)sb.st_ino);
      }
   } else {
      /* Other handle types not supported */
      return false;
   }

   handle->stride = ail_get_wsi_stride_B(&rsrc->layout, 0);
   handle->size = rsrc->layout.size_B;
   handle->offset = rsrc->layout.level_offsets_B[0];
   handle->format = rsrc->layout.format;
   handle->modifier = rsrc->modifier;

   return true;
}

static bool
agx_resource_get_param(struct pipe_screen *pscreen, struct pipe_context *pctx,
                       struct pipe_resource *prsc, unsigned plane,
                       unsigned layer, unsigned level,
                       enum pipe_resource_param param, unsigned usage,
                       uint64_t *value)
{
   struct agx_resource *rsrc = (struct agx_resource *)prsc;
   struct pipe_resource *cur;
   unsigned count;

   switch (param) {
   case PIPE_RESOURCE_PARAM_STRIDE:
      *value = ail_get_wsi_stride_B(&rsrc->layout, level);
      return true;
   case PIPE_RESOURCE_PARAM_OFFSET:
      *value = rsrc->layout.level_offsets_B[level];
      return true;
   case PIPE_RESOURCE_PARAM_MODIFIER:
      *value = rsrc->modifier;
      return true;
   case PIPE_RESOURCE_PARAM_NPLANES:
      /* We don't support multi-planar formats, but we should still handle
       * this case for GBM shared resources.
       */
      for (count = 0, cur = prsc; cur; cur = cur->next)
         count++;
      *value = count;
      return true;
   default:
      return false;
   }
}

static bool
agx_is_2d(enum pipe_texture_target target)
{
   return (target == PIPE_TEXTURE_2D || target == PIPE_TEXTURE_RECT);
}

static bool
agx_linear_allowed(const struct agx_resource *pres)
{
   /* Mipmapping not allowed with linear */
   if (pres->base.last_level != 0)
      return false;

   /* Depth/stencil buffers must not be linear */
   if (pres->base.bind & PIPE_BIND_DEPTH_STENCIL)
      return false;

   switch (pres->base.target) {
   /* 1D is always linear */
   case PIPE_BUFFER:
   case PIPE_TEXTURE_1D:
   case PIPE_TEXTURE_1D_ARRAY:

   /* Linear textures require specifying their strides explicitly, which only
    * works for 2D textures. Rectangle textures are a special case of 2D.
    */
   case PIPE_TEXTURE_2D:
   case PIPE_TEXTURE_2D_ARRAY:
   case PIPE_TEXTURE_RECT:
      break;

   /* No other texture type can specify a stride */
   default:
      return false;
   }

   return true;
}

static bool
agx_twiddled_allowed(const struct agx_resource *pres)
{
   /* Certain binds force linear */
   if (pres->base.bind & (PIPE_BIND_DISPLAY_TARGET | PIPE_BIND_LINEAR))
      return false;

   /* Buffers must be linear */
   if (pres->base.target == PIPE_BUFFER)
      return false;

   /* Anything else may be twiddled */
   return true;
}

static bool
agx_compression_allowed(const struct agx_resource *pres)
{
   /* Allow disabling compression for debugging */
   if (agx_device(pres->base.screen)->debug & AGX_DBG_NOCOMPRESS) {
      rsrc_debug(pres, "No compression: disabled\n");
      return false;
   }

   /* Limited to renderable */
   if (pres->base.bind &
       ~(PIPE_BIND_SAMPLER_VIEW | PIPE_BIND_RENDER_TARGET |
         PIPE_BIND_DEPTH_STENCIL | PIPE_BIND_SHARED | PIPE_BIND_SCANOUT)) {
      rsrc_debug(pres, "No compression: not renderable\n");
      return false;
   }

   /* We use the PBE for compression via staging blits, so we can only compress
    * renderable formats. As framebuffer compression, other formats don't make a
    * ton of sense to compress anyway.
    */
   if (!agx_pixel_format[pres->base.format].renderable &&
       !util_format_is_depth_or_stencil(pres->base.format)) {
      rsrc_debug(pres, "No compression: format not renderable\n");
      return false;
   }

   /* Lossy-compressed texture formats cannot be compressed */
   assert(!util_format_is_compressed(pres->base.format) &&
          "block-compressed formats are not renderable");

   /* TODO: Compression of arrays/cubes currently fails because it would require
    * arrayed linear staging resources, which the hardware doesn't support. This
    * could be worked around with more sophisticated blit code.
    */
   if (pres->base.target != PIPE_TEXTURE_2D &&
       pres->base.target != PIPE_TEXTURE_RECT) {
      rsrc_debug(pres, "No compression: array/cube\n");
      return false;
   }

   /* Small textures cannot (should not?) be compressed */
   if (pres->base.width0 < 16 || pres->base.height0 < 16) {
      rsrc_debug(pres, "No compression: too small\n");
      return false;
   }

   return true;
}

static uint64_t
agx_select_modifier_from_list(const struct agx_resource *pres,
                              const uint64_t *modifiers, int count)
{
   if (agx_twiddled_allowed(pres) && agx_compression_allowed(pres) &&
       drm_find_modifier(DRM_FORMAT_MOD_APPLE_TWIDDLED_COMPRESSED, modifiers,
                         count))
      return DRM_FORMAT_MOD_APPLE_TWIDDLED_COMPRESSED;

   if (agx_twiddled_allowed(pres) &&
       drm_find_modifier(DRM_FORMAT_MOD_APPLE_TWIDDLED, modifiers, count))
      return DRM_FORMAT_MOD_APPLE_TWIDDLED;

   if (agx_linear_allowed(pres) &&
       drm_find_modifier(DRM_FORMAT_MOD_LINEAR, modifiers, count))
      return DRM_FORMAT_MOD_LINEAR;

   /* We didn't find anything */
   return DRM_FORMAT_MOD_INVALID;
}

static uint64_t
agx_select_best_modifier(const struct agx_resource *pres)
{
   /* Prefer linear for staging resources, which should be as fast as possible
    * to write from the CPU.
    */
   if (agx_linear_allowed(pres) && pres->base.usage == PIPE_USAGE_STAGING)
      return DRM_FORMAT_MOD_LINEAR;

   /* For SCANOUT resources with no explicit modifier selection, assume we need
    * linear.
    */
   if (pres->base.bind & PIPE_BIND_SCANOUT) {
      assert(agx_linear_allowed(pres));
      return DRM_FORMAT_MOD_LINEAR;
   }

   if (agx_twiddled_allowed(pres)) {
      if (agx_compression_allowed(pres))
         return DRM_FORMAT_MOD_APPLE_TWIDDLED_COMPRESSED;
      else
         return DRM_FORMAT_MOD_APPLE_TWIDDLED;
   }

   assert(agx_linear_allowed(pres));
   return DRM_FORMAT_MOD_LINEAR;
}

static struct pipe_resource *
agx_resource_create_with_modifiers(struct pipe_screen *screen,
                                   const struct pipe_resource *templ,
                                   const uint64_t *modifiers, int count)
{
   struct agx_device *dev = agx_device(screen);
   struct agx_resource *nresource;

   nresource = CALLOC_STRUCT(agx_resource);
   if (!nresource)
      return NULL;

   nresource->base = *templ;
   nresource->base.screen = screen;

   if (modifiers) {
      nresource->modifier =
         agx_select_modifier_from_list(nresource, modifiers, count);

      /* There may not be a matching modifier, bail if so */
      if (nresource->modifier == DRM_FORMAT_MOD_INVALID) {
         free(nresource);
         return NULL;
      }
   } else {
      nresource->modifier = agx_select_best_modifier(nresource);

      assert(nresource->modifier != DRM_FORMAT_MOD_INVALID);
   }

   nresource->mipmapped = (templ->last_level > 0);

   assert(templ->format != PIPE_FORMAT_Z24X8_UNORM &&
          templ->format != PIPE_FORMAT_Z24_UNORM_S8_UINT &&
          "u_transfer_helper should have lowered");

   agx_resource_setup(dev, nresource);

   pipe_reference_init(&nresource->base.reference, 1);

   struct sw_winsys *winsys = ((struct agx_screen *)screen)->winsys;

   ail_make_miptree(&nresource->layout);

   if (templ->target == PIPE_BUFFER) {
      assert(nresource->layout.tiling == AIL_TILING_LINEAR);
      util_range_init(&nresource->valid_buffer_range);
   }

   if (winsys && templ->bind & PIPE_BIND_DISPLAY_TARGET) {
      unsigned width = templ->width0;
      unsigned height = templ->height0;

      if (nresource->layout.tiling == AIL_TILING_TWIDDLED) {
         width = ALIGN_POT(width, 64);
         height = ALIGN_POT(height, 64);
      }

      nresource->dt = winsys->displaytarget_create(
         winsys, templ->bind, templ->format, width, height, 64,
         NULL /*map_front_private*/, &nresource->dt_stride);

      if (nresource->layout.tiling == AIL_TILING_LINEAR)
         nresource->layout.linear_stride_B = nresource->dt_stride;

      if (nresource->dt == NULL) {
         FREE(nresource);
         return NULL;
      }
   }

   /* Guess a label based on the bind */
   unsigned bind = templ->bind;

   const char *label = (bind & PIPE_BIND_INDEX_BUFFER)     ? "Index buffer"
                       : (bind & PIPE_BIND_SCANOUT)        ? "Scanout"
                       : (bind & PIPE_BIND_DISPLAY_TARGET) ? "Display target"
                       : (bind & PIPE_BIND_SHARED)         ? "Shared resource"
                       : (bind & PIPE_BIND_RENDER_TARGET)  ? "Render target"
                       : (bind & PIPE_BIND_DEPTH_STENCIL)
                          ? "Depth/stencil buffer"
                       : (bind & PIPE_BIND_SAMPLER_VIEW)    ? "Texture"
                       : (bind & PIPE_BIND_VERTEX_BUFFER)   ? "Vertex buffer"
                       : (bind & PIPE_BIND_CONSTANT_BUFFER) ? "Constant buffer"
                       : (bind & PIPE_BIND_GLOBAL)          ? "Global memory"
                       : (bind & PIPE_BIND_SHADER_BUFFER)   ? "Shader buffer"
                       : (bind & PIPE_BIND_SHADER_IMAGE)    ? "Shader image"
                                                            : "Other resource";

   uint32_t create_flags = 0;

   /* Default to write-combine resources, but use writeback if that is expected
    * to be beneficial.
    */
   if (nresource->base.usage == PIPE_USAGE_STAGING ||
       (nresource->base.flags & PIPE_RESOURCE_FLAG_MAP_COHERENT)) {

      create_flags |= AGX_BO_WRITEBACK;
   }

   /* Create buffers that might be shared with the SHAREABLE flag */
   if (bind & (PIPE_BIND_SCANOUT | PIPE_BIND_DISPLAY_TARGET | PIPE_BIND_SHARED))
      create_flags |= AGX_BO_SHAREABLE;

   nresource->bo =
      agx_bo_create(dev, nresource->layout.size_B, create_flags, label);

   if (!nresource->bo) {
      FREE(nresource);
      return NULL;
   }

   agx_resource_debug(nresource, "New: ");
   return &nresource->base;
}

static struct pipe_resource *
agx_resource_create(struct pipe_screen *screen,
                    const struct pipe_resource *templ)
{
   return agx_resource_create_with_modifiers(screen, templ, NULL, 0);
}

static void
agx_resource_destroy(struct pipe_screen *screen, struct pipe_resource *prsrc)
{
   struct agx_resource *rsrc = (struct agx_resource *)prsrc;
   struct agx_screen *agx_screen = (struct agx_screen *)screen;

   agx_resource_debug(rsrc, "Destroy: ");

   if (prsrc->target == PIPE_BUFFER)
      util_range_destroy(&rsrc->valid_buffer_range);

   if (rsrc->dt) {
      /* display target */
      struct sw_winsys *winsys = agx_screen->winsys;
      winsys->displaytarget_destroy(winsys, rsrc->dt);
   }

   if (rsrc->scanout)
      renderonly_scanout_destroy(rsrc->scanout, agx_screen->dev.ro);

   agx_bo_unreference(rsrc->bo);
   FREE(rsrc);
}

/*
 * transfer
 */

static void
agx_transfer_flush_region(struct pipe_context *pipe,
                          struct pipe_transfer *transfer,
                          const struct pipe_box *box)
{
}

/* Reallocate the backing buffer of a resource, returns true if successful */
static bool
agx_shadow(struct agx_context *ctx, struct agx_resource *rsrc)
{
   struct agx_device *dev = agx_device(ctx->base.screen);
   struct agx_bo *old = rsrc->bo;
   struct agx_bo *new_ = agx_bo_create(dev, old->size, old->flags, old->label);

   /* If allocation failed, we can fallback on a flush gracefully*/
   if (new_ == NULL)
      return false;

   /* Swap the pointers, dropping a reference */
   agx_bo_unreference(rsrc->bo);
   rsrc->bo = new_;

   /* Reemit descriptors using this resource */
   agx_dirty_all(ctx);
   return true;
}

/*
 * Perform the required synchronization before a transfer_map operation can
 * complete. This may require syncing batches.
 */
static void
agx_prepare_for_map(struct agx_context *ctx, struct agx_resource *rsrc,
                    unsigned level,
                    unsigned usage, /* a combination of PIPE_MAP_x */
                    const struct pipe_box *box)
{
   /* Upgrade DISCARD_RANGE to WHOLE_RESOURCE if the whole resource is
    * being mapped.
    */
   if ((usage & PIPE_MAP_DISCARD_RANGE) &&
       !(rsrc->base.flags & PIPE_RESOURCE_FLAG_MAP_PERSISTENT) &&
       rsrc->base.last_level == 0 &&
       util_texrange_covers_whole_level(&rsrc->base, 0, box->x, box->y, box->z,
                                        box->width, box->height, box->depth)) {

      usage |= PIPE_MAP_DISCARD_WHOLE_RESOURCE;
   }

   /* Shadowing doesn't work separate stencil or shared resources */
   if (rsrc->separate_stencil || (rsrc->bo->flags & AGX_BO_SHARED))
      usage &= ~PIPE_MAP_DISCARD_WHOLE_RESOURCE;

   /* If the access is unsynchronized, there's nothing to do */
   if (usage & PIPE_MAP_UNSYNCHRONIZED)
      return;

   /* Everything after this needs the context, which is not safe for
    * unsynchronized transfers when we claim
    * PIPE_CAP_MAP_UNSYNCHRONIZED_THREAD_SAFE.
    */
   assert(!(usage & PIPE_MAP_UNSYNCHRONIZED));

   /* Both writing and reading need writers synced */
   agx_sync_writer(ctx, rsrc, "Unsynchronized transfer");

   /* Additionally, writing needs readers synced */
   if (!(usage & PIPE_MAP_WRITE))
      return;

   /* If the range being written is uninitialized, we do not need to sync. */
   if (rsrc->base.target == PIPE_BUFFER && !(rsrc->bo->flags & AGX_BO_SHARED) &&
       !util_ranges_intersect(&rsrc->valid_buffer_range, box->x,
                              box->x + box->width))
      return;

   /* If there are no readers, we're done. We check at the start to
    * avoid expensive shadowing paths or duplicated checks in this hapyp path.
    */
   if (!agx_any_batch_uses_resource(ctx, rsrc))
      return;

   /* There are readers. Try to shadow the resource to avoid a sync */
   if ((usage & PIPE_MAP_DISCARD_WHOLE_RESOURCE) && agx_shadow(ctx, rsrc))
      return;

   /* Otherwise, we need to sync */
   agx_sync_readers(ctx, rsrc, "Unsynchronized write");
}

/* Most of the time we can do CPU-side transfers, but sometimes we need to use
 * the 3D pipe for this. Let's wrap u_blitter to blit to/from staging textures.
 * Code adapted from panfrost */

static struct agx_resource *
agx_alloc_staging(struct pipe_screen *screen, struct agx_resource *rsc,
                  unsigned level, const struct pipe_box *box)
{
   struct pipe_resource tmpl = rsc->base;

   tmpl.width0 = box->width;
   tmpl.height0 = box->height;

   /* for array textures, box->depth is the array_size, otherwise for 3d
    * textures, it is the depth.
    */
   if (tmpl.array_size > 1) {
      if (tmpl.target == PIPE_TEXTURE_CUBE)
         tmpl.target = PIPE_TEXTURE_2D_ARRAY;
      tmpl.array_size = box->depth;
      tmpl.depth0 = 1;
   } else {
      tmpl.array_size = 1;
      tmpl.depth0 = box->depth;
   }
   tmpl.last_level = 0;
   tmpl.bind |= PIPE_BIND_LINEAR;

   struct pipe_resource *pstaging = screen->resource_create(screen, &tmpl);
   if (!pstaging)
      return NULL;

   return agx_resource(pstaging);
}

static void
agx_blit_from_staging(struct pipe_context *pctx, struct agx_transfer *trans)
{
   struct pipe_resource *dst = trans->base.resource;
   struct pipe_blit_info blit = {0};

   blit.dst.resource = dst;
   blit.dst.format = dst->format;
   blit.dst.level = trans->base.level;
   blit.dst.box = trans->base.box;
   blit.src.resource = trans->staging.rsrc;
   blit.src.format = trans->staging.rsrc->format;
   blit.src.level = 0;
   blit.src.box = trans->staging.box;
   blit.mask = util_format_get_mask(blit.src.format);
   blit.filter = PIPE_TEX_FILTER_NEAREST;

   agx_blit(pctx, &blit);
}

static void
agx_blit_to_staging(struct pipe_context *pctx, struct agx_transfer *trans)
{
   struct pipe_resource *src = trans->base.resource;
   struct pipe_blit_info blit = {0};

   blit.src.resource = src;
   blit.src.format = src->format;
   blit.src.level = trans->base.level;
   blit.src.box = trans->base.box;
   blit.dst.resource = trans->staging.rsrc;
   blit.dst.format = trans->staging.rsrc->format;
   blit.dst.level = 0;
   blit.dst.box = trans->staging.box;
   blit.mask = util_format_get_mask(blit.dst.format);
   blit.filter = PIPE_TEX_FILTER_NEAREST;

   agx_blit(pctx, &blit);
}

static void *
agx_transfer_map(struct pipe_context *pctx, struct pipe_resource *resource,
                 unsigned level,
                 unsigned usage, /* a combination of PIPE_MAP_x */
                 const struct pipe_box *box,
                 struct pipe_transfer **out_transfer)
{
   struct agx_context *ctx = agx_context(pctx);
   struct agx_resource *rsrc = agx_resource(resource);

   /* Can't map tiled/compressed directly */
   if ((usage & PIPE_MAP_DIRECTLY) && rsrc->modifier != DRM_FORMAT_MOD_LINEAR)
      return NULL;

   /* Can't transfer out of bounds mip levels */
   if (level >= rsrc->layout.levels)
      return NULL;

   agx_prepare_for_map(ctx, rsrc, level, usage, box);

   /* Track the written buffer range */
   if (resource->target == PIPE_BUFFER) {
      /* Note the ordering: DISCARD|WRITE is valid, so clear before adding. */
      if (usage & PIPE_MAP_DISCARD_WHOLE_RESOURCE)
         util_range_set_empty(&rsrc->valid_buffer_range);
      if (usage & PIPE_MAP_WRITE) {
         util_range_add(resource, &rsrc->valid_buffer_range, box->x,
                        box->x + box->width);
      }
   }

   struct agx_transfer *transfer = CALLOC_STRUCT(agx_transfer);
   transfer->base.level = level;
   transfer->base.usage = usage;
   transfer->base.box = *box;

   pipe_resource_reference(&transfer->base.resource, resource);
   *out_transfer = &transfer->base;

   /* For compression, we use a staging blit as we do not implement AGX
    * compression in software. In some cases, we could use this path for
    * twiddled too, but we don't have a use case for that yet.
    */
   if (rsrc->modifier == DRM_FORMAT_MOD_APPLE_TWIDDLED_COMPRESSED) {
      /* Should never happen for buffers, and it's not safe */
      assert(resource->target != PIPE_BUFFER);

      struct agx_resource *staging =
         agx_alloc_staging(pctx->screen, rsrc, level, box);
      assert(staging);

      /* Staging resources have one LOD: level 0. Query the strides
       * on this LOD.
       */
      transfer->base.stride = ail_get_linear_stride_B(&staging->layout, 0);
      transfer->base.layer_stride = staging->layout.layer_stride_B;
      transfer->staging.rsrc = &staging->base;

      transfer->staging.box = *box;
      transfer->staging.box.x = 0;
      transfer->staging.box.y = 0;
      transfer->staging.box.z = 0;

      assert(transfer->staging.rsrc != NULL);

      if ((usage & PIPE_MAP_READ) && agx_resource_valid(rsrc, level)) {
         agx_blit_to_staging(pctx, transfer);
         agx_sync_writer(ctx, staging, "GPU read staging blit");
      }

      agx_bo_mmap(staging->bo);
      return staging->bo->ptr.cpu;
   }

   agx_bo_mmap(rsrc->bo);

   if (rsrc->modifier == DRM_FORMAT_MOD_APPLE_TWIDDLED) {
      /* Should never happen for buffers, and it's not safe */
      assert(resource->target != PIPE_BUFFER);

      transfer->base.stride =
         util_format_get_stride(rsrc->layout.format, box->width);

      transfer->base.layer_stride = util_format_get_2d_size(
         rsrc->layout.format, transfer->base.stride, box->height);

      transfer->map = calloc(transfer->base.layer_stride, box->depth);

      if ((usage & PIPE_MAP_READ) && agx_resource_valid(rsrc, level)) {
         for (unsigned z = 0; z < box->depth; ++z) {
            uint8_t *map = agx_map_texture_cpu(rsrc, level, box->z + z);
            uint8_t *dst =
               (uint8_t *)transfer->map + transfer->base.layer_stride * z;

            ail_detile(map, dst, &rsrc->layout, level, transfer->base.stride,
                       box->x, box->y, box->width, box->height);
         }
      }

      return transfer->map;
   } else {
      assert(rsrc->modifier == DRM_FORMAT_MOD_LINEAR);

      transfer->base.stride = ail_get_linear_stride_B(&rsrc->layout, level);
      transfer->base.layer_stride = rsrc->layout.layer_stride_B;

      /* Be conservative for direct writes */
      if ((usage & PIPE_MAP_WRITE) &&
          (usage &
           (PIPE_MAP_DIRECTLY | PIPE_MAP_PERSISTENT | PIPE_MAP_COHERENT))) {
         BITSET_SET(rsrc->data_valid, level);
      }

      uint32_t offset =
         ail_get_linear_pixel_B(&rsrc->layout, level, box->x, box->y, box->z);

      return ((uint8_t *)rsrc->bo->ptr.cpu) + offset;
   }
}

static void
agx_transfer_unmap(struct pipe_context *pctx, struct pipe_transfer *transfer)
{
   /* Gallium expects writeback here, so we tile */

   struct agx_transfer *trans = agx_transfer(transfer);
   struct pipe_resource *prsrc = transfer->resource;
   struct agx_resource *rsrc = (struct agx_resource *)prsrc;

   if (trans->staging.rsrc && (transfer->usage & PIPE_MAP_WRITE)) {
      assert(prsrc->target != PIPE_BUFFER);
      agx_blit_from_staging(pctx, trans);
      agx_flush_readers(agx_context(pctx), agx_resource(trans->staging.rsrc),
                        "GPU write staging blit");
   } else if (trans->map && (transfer->usage & PIPE_MAP_WRITE)) {
      assert(rsrc->modifier == DRM_FORMAT_MOD_APPLE_TWIDDLED);

      for (unsigned z = 0; z < transfer->box.depth; ++z) {
         uint8_t *map =
            agx_map_texture_cpu(rsrc, transfer->level, transfer->box.z + z);
         uint8_t *src = (uint8_t *)trans->map + transfer->layer_stride * z;

         ail_tile(map, src, &rsrc->layout, transfer->level, transfer->stride,
                  transfer->box.x, transfer->box.y, transfer->box.width,
                  transfer->box.height);
      }
   }

   /* The level we wrote is now initialized. We do this at the end so
    * blit_from_staging can avoid reloading existing contents.
    */
   if (transfer->usage & PIPE_MAP_WRITE)
      BITSET_SET(rsrc->data_valid, transfer->level);

   /* Free the transfer */
   free(trans->map);
   pipe_resource_reference(&trans->staging.rsrc, NULL);
   pipe_resource_reference(&transfer->resource, NULL);
   FREE(transfer);
}

static bool
agx_generate_mipmap(struct pipe_context *pctx, struct pipe_resource *prsrc,
                    enum pipe_format format, unsigned base_level,
                    unsigned last_level, unsigned first_layer,
                    unsigned last_layer)
{
   struct agx_resource *rsrc = agx_resource(prsrc);

   /* Generating a mipmap invalidates the written levels. Make that
    * explicit so we don't reload the previous contents.
    */
   for (unsigned l = base_level + 1; l <= last_level; ++l)
      BITSET_CLEAR(rsrc->data_valid, l);

   /* For now we use util_gen_mipmap, but this has way too much overhead */
   perf_debug_ctx(agx_context(pctx), "Unoptimized mipmap generation");

   return util_gen_mipmap(pctx, prsrc, format, base_level, last_level,
                          first_layer, last_layer, PIPE_TEX_FILTER_LINEAR);
}

/*
 * clear/copy
 */
static void
agx_clear(struct pipe_context *pctx, unsigned buffers,
          const struct pipe_scissor_state *scissor_state,
          const union pipe_color_union *color, double depth, unsigned stencil)
{
   struct agx_context *ctx = agx_context(pctx);
   struct agx_batch *batch = agx_get_batch(ctx);

   if (unlikely(!agx_render_condition_check(ctx)))
      return;

   unsigned fastclear = buffers & ~(batch->draw | batch->load);
   unsigned slowclear = buffers & ~fastclear;

   assert(scissor_state == NULL && "we don't support PIPE_CAP_CLEAR_SCISSORED");

   /* Fast clears configure the batch */
   for (unsigned rt = 0; rt < PIPE_MAX_COLOR_BUFS; ++rt) {
      if (!(fastclear & (PIPE_CLEAR_COLOR0 << rt)))
         continue;

      static_assert(sizeof(color->f) == 16, "mismatched structure");

      batch->uploaded_clear_color[rt] =
         agx_pool_upload_aligned(&batch->pool, color->f, sizeof(color->f), 16);
   }

   if (fastclear & PIPE_CLEAR_DEPTH)
      batch->clear_depth = depth;

   if (fastclear & PIPE_CLEAR_STENCIL)
      batch->clear_stencil = stencil;

   /* Slow clears draw a fullscreen rectangle */
   if (slowclear) {
      agx_blitter_save(ctx, ctx->blitter, false /* render cond */);
      util_blitter_clear(
         ctx->blitter, ctx->framebuffer.width, ctx->framebuffer.height,
         util_framebuffer_get_num_layers(&ctx->framebuffer), slowclear, color,
         depth, stencil,
         util_framebuffer_get_num_samples(&ctx->framebuffer) > 1);
   }

   batch->clear |= fastclear;
   batch->resolve |= buffers;
   assert((batch->draw & slowclear) == slowclear);
}

static void
agx_flush_resource(struct pipe_context *pctx, struct pipe_resource *pres)
{
   struct agx_resource *rsrc = agx_resource(pres);

   /* flush_resource is used to prepare resources for sharing, so if this is not
    * already a shareabe resource, make it so
    */
   struct agx_bo *old = rsrc->bo;
   if (!(old->flags & AGX_BO_SHAREABLE)) {
      assert(rsrc->layout.levels == 1 &&
             "Shared resources must not be mipmapped");
      assert(rsrc->layout.sample_count_sa == 1 &&
             "Shared resources must not be multisampled");
      assert(rsrc->bo);
      assert(!(pres->bind & PIPE_BIND_SHARED));

      struct pipe_resource templ = *pres;
      templ.bind |= PIPE_BIND_SHARED;

      /* Create a new shareable resource */
      struct agx_resource *new_res =
         agx_resource(pctx->screen->resource_create(pctx->screen, &templ));

      assert(new_res);

      /* Blit it over */
      struct pipe_blit_info blit = {0};

      u_box_3d(0, 0, 0, rsrc->layout.width_px, rsrc->layout.height_px,
               rsrc->layout.depth_px, &blit.dst.box);
      blit.src.box = blit.dst.box;

      blit.dst.resource = &new_res->base;
      blit.dst.format = new_res->base.format;
      blit.dst.level = 0;
      blit.src.resource = pres;
      blit.src.format = pres->format;
      blit.src.level = 0;
      blit.mask = util_format_get_mask(blit.src.format);
      blit.filter = PIPE_TEX_FILTER_NEAREST;
      agx_blit(pctx, &blit);

      /* Flush the blit out, to make sure the old resource is no longer used */
      agx_flush_writer(agx_context(pctx), new_res, "flush_resource");

      /* Copy the bind flags and swap the BOs */
      rsrc->base.bind = new_res->base.bind;
      rsrc->bo = new_res->bo;
      new_res->bo = old;

      /* Free the new resource, which now owns the old BO */
      pipe_resource_reference((struct pipe_resource **)&new_res, NULL);
   } else {
      /* Otherwise just claim it's already shared */
      pres->bind |= PIPE_BIND_SHARED;
      agx_flush_writer(agx_context(pctx), rsrc, "flush_resource");
   }
}

/*
 * context
 */
static void
agx_flush(struct pipe_context *pctx, struct pipe_fence_handle **fence,
          unsigned flags)
{
   struct agx_context *ctx = agx_context(pctx);

   agx_flush_all(ctx, "Gallium flush");

   /* At this point all pending work has been submitted. Since jobs are
    * started and completed sequentially from a UAPI perspective, and since
    * we submit all jobs with compute+render barriers on the prior job,
    * waiting on the last submitted job is sufficient to guarantee completion
    * of all GPU work thus far, so we can create a fence out of the latest
    * syncobj.
    *
    * See this page for more info on how the GPU/UAPI queueing works:
    * https://github.com/AsahiLinux/docs/wiki/SW:AGX-driver-notes#queues
    */

   if (fence) {
      struct pipe_fence_handle *f = agx_fence_create(ctx);
      pctx->screen->fence_reference(pctx->screen, fence, NULL);
      *fence = f;
   }
}

void
agx_flush_batch(struct agx_context *ctx, struct agx_batch *batch)
{
   struct agx_device *dev = agx_device(ctx->base.screen);

   assert(agx_batch_is_active(batch));
   assert(!agx_batch_is_submitted(batch));

   /* Make sure there's something to submit. */
   if (!batch->clear && !batch->any_draws) {
      agx_batch_reset(ctx, batch);
      return;
   }

   /* Finalize the encoder */
   uint8_t stop[5 + 64] = {0x00, 0x00, 0x00, 0xc0, 0x00};
   memcpy(batch->encoder_current, stop, sizeof(stop));

   uint64_t pipeline_background = agx_build_meta(batch, false, false);
   uint64_t pipeline_background_partial = agx_build_meta(batch, false, true);
   uint64_t pipeline_store = agx_build_meta(batch, true, false);

   bool clear_pipeline_textures = false;

   for (unsigned i = 0; i < batch->key.nr_cbufs; ++i) {
      struct pipe_surface *surf = batch->key.cbufs[i];

      if (surf && surf->texture) {
         struct agx_resource *rt = agx_resource(surf->texture);
         BITSET_SET(rt->data_valid, surf->u.tex.level);

         if (!(batch->clear & (PIPE_CLEAR_COLOR0 << i)))
            clear_pipeline_textures = true;
      }
   }

   struct agx_resource *zbuf =
      batch->key.zsbuf ? agx_resource(batch->key.zsbuf->texture) : NULL;

   if (zbuf) {
      unsigned level = batch->key.zsbuf->u.tex.level;
      BITSET_SET(zbuf->data_valid, level);

      if (zbuf->separate_stencil)
         BITSET_SET(zbuf->separate_stencil->data_valid, level);
   }

   /* Scissor and depth bias arrays are staged to dynamic arrays on the CPU. At
    * submit time, they're done growing and are uploaded to GPU memory attached
    * to the batch.
    */
   uint64_t scissor = agx_pool_upload_aligned(&batch->pool, batch->scissor.data,
                                              batch->scissor.size, 64);
   uint64_t zbias = agx_pool_upload_aligned(
      &batch->pool, batch->depth_bias.data, batch->depth_bias.size, 64);

   /* BO list for a given batch consists of:
    *  - BOs for the batch's pools
    *  - BOs for the encoder
    *  - BO for internal shaders
    *  - BOs added to the batch explicitly
    */
   agx_batch_add_bo(batch, batch->encoder);

   /* Occlusion queries are allocated as a contiguous pool */
   unsigned oq_count =
      util_dynarray_num_elements(&batch->occlusion_queries, struct agx_query *);
   size_t oq_size = oq_count * sizeof(uint64_t);

   if (oq_size) {
      batch->occlusion_buffer =
         agx_pool_alloc_aligned(&batch->pool, oq_size, 64);
      memset(batch->occlusion_buffer.cpu, 0, oq_size);
   } else {
      batch->occlusion_buffer.gpu = 0;
   }

   unsigned handle_count = agx_batch_num_bo(batch) +
                           agx_pool_num_bos(&batch->pool) +
                           agx_pool_num_bos(&batch->pipeline_pool);

   uint32_t *handles = calloc(sizeof(uint32_t), handle_count);
   unsigned handle = 0, handle_i = 0;

   AGX_BATCH_FOREACH_BO_HANDLE(batch, handle) {
      handles[handle_i++] = handle;
   }

   agx_pool_get_bo_handles(&batch->pool, handles + handle_i);
   handle_i += agx_pool_num_bos(&batch->pool);

   agx_pool_get_bo_handles(&batch->pipeline_pool, handles + handle_i);
   handle_i += agx_pool_num_bos(&batch->pipeline_pool);

   /* Size calculation should've been exact */
   assert(handle_i == handle_count);

   /* TODO: Linux UAPI submission */
   (void)dev;
   (void)zbias;
   (void)scissor;
   (void)clear_pipeline_textures;
   (void)pipeline_store;
   (void)pipeline_background;
   (void)pipeline_background_partial;

   unreachable("Linux UAPI not yet upstream");
   agx_batch_submit(ctx, batch, 0, 0, NULL);
}

static void
agx_destroy_context(struct pipe_context *pctx)
{
   struct agx_device *dev = agx_device(pctx->screen);
   struct agx_context *ctx = agx_context(pctx);

   /* Batch state needs to be freed on completion, and we don't want to yank
    * buffers out from in-progress GPU jobs to avoid faults, so just wait until
    * everything in progress is actually done on context destroy. This will
    * ensure everything is cleaned up properly.
    */
   agx_sync_all(ctx, "destroy context");

   if (pctx->stream_uploader)
      u_upload_destroy(pctx->stream_uploader);

   if (ctx->blitter)
      util_blitter_destroy(ctx->blitter);

   util_unreference_framebuffer_state(&ctx->framebuffer);

   agx_meta_cleanup(&ctx->meta);

   agx_bo_unreference(ctx->result_buf);

   drmSyncobjDestroy(dev->fd, ctx->in_sync_obj);
   drmSyncobjDestroy(dev->fd, ctx->dummy_syncobj);
   if (ctx->in_sync_fd != -1)
      close(ctx->in_sync_fd);

   for (unsigned i = 0; i < AGX_MAX_BATCHES; ++i) {
      if (ctx->batches.slots[i].syncobj)
         drmSyncobjDestroy(dev->fd, ctx->batches.slots[i].syncobj);
   }

   ralloc_free(ctx);
}

static void
agx_invalidate_resource(struct pipe_context *pctx,
                        struct pipe_resource *resource)
{
   struct agx_context *ctx = agx_context(pctx);
   struct agx_batch *batch = agx_get_batch(ctx);

   /* Handle the glInvalidateFramebuffer case */
   if (batch->key.zsbuf && batch->key.zsbuf->texture == resource)
      batch->resolve &= ~PIPE_CLEAR_DEPTHSTENCIL;

   for (unsigned i = 0; i < batch->key.nr_cbufs; ++i) {
      struct pipe_surface *surf = batch->key.cbufs[i];

      if (surf && surf->texture == resource)
         batch->resolve &= ~(PIPE_CLEAR_COLOR0 << i);
   }
}

static struct pipe_context *
agx_create_context(struct pipe_screen *screen, void *priv, unsigned flags)
{
   struct agx_context *ctx = rzalloc(NULL, struct agx_context);
   struct pipe_context *pctx = &ctx->base;
   int ret;

   if (!ctx)
      return NULL;

   pctx->screen = screen;
   pctx->priv = priv;

   util_dynarray_init(&ctx->writer, ctx);

   pctx->stream_uploader = u_upload_create_default(pctx);
   if (!pctx->stream_uploader) {
      FREE(pctx);
      return NULL;
   }
   pctx->const_uploader = pctx->stream_uploader;

   pctx->destroy = agx_destroy_context;
   pctx->flush = agx_flush;
   pctx->clear = agx_clear;
   pctx->resource_copy_region = util_resource_copy_region;
   pctx->blit = agx_blit;
   pctx->generate_mipmap = agx_generate_mipmap;
   pctx->flush_resource = agx_flush_resource;

   pctx->buffer_map = u_transfer_helper_transfer_map;
   pctx->buffer_unmap = u_transfer_helper_transfer_unmap;
   pctx->texture_map = u_transfer_helper_transfer_map;
   pctx->texture_unmap = u_transfer_helper_transfer_unmap;
   pctx->transfer_flush_region = u_transfer_helper_transfer_flush_region;

   pctx->buffer_subdata = u_default_buffer_subdata;
   pctx->texture_subdata = u_default_texture_subdata;
   pctx->set_debug_callback = u_default_set_debug_callback;
   pctx->invalidate_resource = agx_invalidate_resource;

   agx_init_state_functions(pctx);
   agx_init_query_functions(pctx);

   agx_meta_init(&ctx->meta, agx_device(screen));

   ctx->blitter = util_blitter_create(pctx);

   ctx->result_buf = agx_bo_create(
      agx_device(screen), sizeof(union agx_batch_result) * AGX_MAX_BATCHES,
      AGX_BO_WRITEBACK, "Batch result buffer");
   assert(ctx->result_buf);

   /* Sync object/FD used for NATIVE_FENCE_FD. */
   ctx->in_sync_fd = -1;
   ret = drmSyncobjCreate(agx_device(screen)->fd, 0, &ctx->in_sync_obj);
   assert(!ret);

   /* Dummy sync object used before any work has been submitted. */
   ret = drmSyncobjCreate(agx_device(screen)->fd, DRM_SYNCOBJ_CREATE_SIGNALED,
                          &ctx->dummy_syncobj);
   assert(!ret);
   ctx->syncobj = ctx->dummy_syncobj;

   return pctx;
}

static void
agx_flush_frontbuffer(struct pipe_screen *_screen, struct pipe_context *pctx,
                      struct pipe_resource *prsrc, unsigned level,
                      unsigned layer, void *context_private,
                      struct pipe_box *box)
{
   struct agx_resource *rsrc = (struct agx_resource *)prsrc;
   struct agx_screen *agx_screen = (struct agx_screen *)_screen;
   struct sw_winsys *winsys = agx_screen->winsys;

   /* Dump the framebuffer */
   assert(rsrc->dt);
   void *map = winsys->displaytarget_map(winsys, rsrc->dt, PIPE_USAGE_DEFAULT);
   assert(map != NULL);

   if (rsrc->modifier == DRM_FORMAT_MOD_APPLE_TWIDDLED) {
      ail_detile(rsrc->bo->ptr.cpu, map, &rsrc->layout, 0, rsrc->dt_stride, 0,
                 0, rsrc->base.width0, rsrc->base.height0);
   } else {
      assert(rsrc->modifier == DRM_FORMAT_MOD_LINEAR);
      memcpy(map, rsrc->bo->ptr.cpu, rsrc->dt_stride * rsrc->base.height0);
   }

   winsys->displaytarget_display(winsys, rsrc->dt, context_private, box);
}

static const char *
agx_get_vendor(struct pipe_screen *pscreen)
{
   return "Mesa";
}

static const char *
agx_get_device_vendor(struct pipe_screen *pscreen)
{
   return "Apple";
}

static const char *
agx_get_name(struct pipe_screen *pscreen)
{
   struct agx_device *dev = agx_device(pscreen);

   return dev->name;
}

static int
agx_get_param(struct pipe_screen *pscreen, enum pipe_cap param)
{
   bool is_deqp = agx_device(pscreen)->debug & AGX_DBG_DEQP;

   switch (param) {
   case PIPE_CAP_NPOT_TEXTURES:
   case PIPE_CAP_SHADER_STENCIL_EXPORT:
   case PIPE_CAP_MIXED_COLOR_DEPTH_BITS:
   case PIPE_CAP_FRAGMENT_SHADER_TEXTURE_LOD:
   case PIPE_CAP_VERTEX_COLOR_UNCLAMPED:
   case PIPE_CAP_DEPTH_CLIP_DISABLE:
   case PIPE_CAP_MIXED_FRAMEBUFFER_SIZES:
   case PIPE_CAP_FRAGMENT_SHADER_DERIVATIVES:
   case PIPE_CAP_FRAMEBUFFER_NO_ATTACHMENT:
   case PIPE_CAP_SHADER_PACK_HALF_FLOAT:
   case PIPE_CAP_FS_FINE_DERIVATIVE:
   case PIPE_CAP_TEXTURE_BARRIER:
      return 1;

   /* We could support ARB_clip_control by toggling the clip control bit for
    * the render pass. Because this bit is for the whole render pass,
    * switching clip modes necessarily incurs a flush. This should be ok, from
    * the ARB_clip_control spec:
    *
    *         Some implementations may introduce a flush when changing the
    *         clip control state.  Hence frequent clip control changes are
    *         not recommended.
    *
    * However, this would require tuning to ensure we don't flush unnecessary
    * when using u_blitter clears, for example. As we don't yet have a use case,
    * don't expose the feature.
    */
   case PIPE_CAP_CLIP_HALFZ:
      return 0;

   case PIPE_CAP_MAX_RENDER_TARGETS:
   case PIPE_CAP_FBFETCH:
   case PIPE_CAP_FBFETCH_COHERENT:
      return 8;

   case PIPE_CAP_MAX_DUAL_SOURCE_RENDER_TARGETS:
      return 0;

   case PIPE_CAP_OCCLUSION_QUERY:
   case PIPE_CAP_GENERATE_MIPMAP:
   case PIPE_CAP_PRIMITIVE_RESTART:
   case PIPE_CAP_PRIMITIVE_RESTART_FIXED_INDEX:
   case PIPE_CAP_ANISOTROPIC_FILTER:
   case PIPE_CAP_NATIVE_FENCE_FD:
      return true;

   case PIPE_CAP_SAMPLER_VIEW_TARGET:
   case PIPE_CAP_TEXTURE_SWIZZLE:
   case PIPE_CAP_BLEND_EQUATION_SEPARATE:
   case PIPE_CAP_INDEP_BLEND_ENABLE:
   case PIPE_CAP_INDEP_BLEND_FUNC:
   case PIPE_CAP_ACCELERATED:
   case PIPE_CAP_UMA:
   case PIPE_CAP_TEXTURE_FLOAT_LINEAR:
   case PIPE_CAP_TEXTURE_HALF_FLOAT_LINEAR:
   case PIPE_CAP_TEXTURE_MIRROR_CLAMP_TO_EDGE:
   case PIPE_CAP_SHADER_ARRAY_COMPONENTS:
   case PIPE_CAP_PACKED_UNIFORMS:
   case PIPE_CAP_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION:
   case PIPE_CAP_VS_INSTANCEID:
   case PIPE_CAP_VERTEX_ELEMENT_INSTANCE_DIVISOR:
   case PIPE_CAP_CONDITIONAL_RENDER:
   case PIPE_CAP_CONDITIONAL_RENDER_INVERTED:
   case PIPE_CAP_SEAMLESS_CUBE_MAP:
   case PIPE_CAP_LOAD_CONSTBUF:
   case PIPE_CAP_SEAMLESS_CUBE_MAP_PER_TEXTURE:
   case PIPE_CAP_TEXTURE_BUFFER_OBJECTS:
   case PIPE_CAP_NULL_TEXTURES:
      return 1;

   case PIPE_CAP_TEXTURE_MULTISAMPLE:
   case PIPE_CAP_SURFACE_SAMPLE_COUNT:
   case PIPE_CAP_SAMPLE_SHADING:
   case PIPE_CAP_IMAGE_LOAD_FORMATTED:
   case PIPE_CAP_IMAGE_STORE_FORMATTED:
   case PIPE_CAP_COMPUTE:
   case PIPE_CAP_INT64:
      return is_deqp;

   case PIPE_CAP_COPY_BETWEEN_COMPRESSED_AND_PLAIN_FORMATS:
      return 0;

   case PIPE_CAP_MAX_STREAM_OUTPUT_BUFFERS:
      return is_deqp ? PIPE_MAX_SO_BUFFERS : 0;

   case PIPE_CAP_MAX_STREAM_OUTPUT_SEPARATE_COMPONENTS:
   case PIPE_CAP_MAX_STREAM_OUTPUT_INTERLEAVED_COMPONENTS:
      return is_deqp ? PIPE_MAX_SO_OUTPUTS : 0;

   case PIPE_CAP_STREAM_OUTPUT_PAUSE_RESUME:
   case PIPE_CAP_STREAM_OUTPUT_INTERLEAVE_BUFFERS:
      return is_deqp ? 1 : 0;

   case PIPE_CAP_MAX_TEXTURE_ARRAY_LAYERS:
      return 2048;

   case PIPE_CAP_GLSL_FEATURE_LEVEL:
   case PIPE_CAP_GLSL_FEATURE_LEVEL_COMPATIBILITY:
      return is_deqp ? 330 : 130;
   case PIPE_CAP_ESSL_FEATURE_LEVEL:
      return is_deqp ? 320 : 120;

   case PIPE_CAP_CONSTANT_BUFFER_OFFSET_ALIGNMENT:
      return 16;

   case PIPE_CAP_MAX_TEXEL_BUFFER_ELEMENTS_UINT:
      return AGX_TEXTURE_BUFFER_MAX_SIZE;

   case PIPE_CAP_TEXTURE_BUFFER_OFFSET_ALIGNMENT:
      return 64;

   case PIPE_CAP_VERTEX_ATTRIB_ELEMENT_ALIGNED_ONLY:
      return 1;

   case PIPE_CAP_MAX_TEXTURE_2D_SIZE:
      return 16384;
   case PIPE_CAP_MAX_TEXTURE_3D_LEVELS:
   case PIPE_CAP_MAX_TEXTURE_CUBE_LEVELS:
      return 13;

   case PIPE_CAP_FS_COORD_ORIGIN_UPPER_LEFT:
   case PIPE_CAP_FS_COORD_PIXEL_CENTER_HALF_INTEGER:
   case PIPE_CAP_TGSI_TEXCOORD:
   case PIPE_CAP_FS_FACE_IS_INTEGER_SYSVAL:
   case PIPE_CAP_FS_POSITION_IS_SYSVAL:
      return true;
   case PIPE_CAP_FS_COORD_ORIGIN_LOWER_LEFT:
   case PIPE_CAP_FS_COORD_PIXEL_CENTER_INTEGER:
   case PIPE_CAP_FS_POINT_IS_SYSVAL:
      return false;

   case PIPE_CAP_MAX_VERTEX_ELEMENT_SRC_OFFSET:
      return 0xffff;

   case PIPE_CAP_TEXTURE_TRANSFER_MODES:
      return PIPE_TEXTURE_TRANSFER_BLIT;

   case PIPE_CAP_ENDIANNESS:
      return PIPE_ENDIAN_LITTLE;

   case PIPE_CAP_MAX_TEXTURE_GATHER_COMPONENTS:
      return 4;
   case PIPE_CAP_MIN_TEXTURE_GATHER_OFFSET:
      return -8;
   case PIPE_CAP_MAX_TEXTURE_GATHER_OFFSET:
      return 7;
   case PIPE_CAP_DRAW_INDIRECT:
      return true;

   case PIPE_CAP_VIDEO_MEMORY: {
      uint64_t system_memory;

      if (!os_get_total_physical_memory(&system_memory))
         return 0;

      return (int)(system_memory >> 20);
   }

   case PIPE_CAP_SHADER_BUFFER_OFFSET_ALIGNMENT:
      return 4;

   case PIPE_CAP_MAX_VARYINGS:
      return 16;

   case PIPE_CAP_FLATSHADE:
   case PIPE_CAP_TWO_SIDED_COLOR:
   case PIPE_CAP_ALPHA_TEST:
   case PIPE_CAP_POINT_SIZE_FIXED:
   case PIPE_CAP_CLIP_PLANES:
   case PIPE_CAP_NIR_IMAGES_AS_DEREF:
      return 0;

   case PIPE_CAP_TEXTURE_BORDER_COLOR_QUIRK:
      return PIPE_QUIRK_TEXTURE_BORDER_COLOR_SWIZZLE_FREEDRENO;

   case PIPE_CAP_SUPPORTED_PRIM_MODES:
   case PIPE_CAP_SUPPORTED_PRIM_MODES_WITH_RESTART:
      return BITFIELD_BIT(PIPE_PRIM_POINTS) | BITFIELD_BIT(PIPE_PRIM_LINES) |
             BITFIELD_BIT(PIPE_PRIM_LINE_STRIP) |
             BITFIELD_BIT(PIPE_PRIM_LINE_LOOP) |
             BITFIELD_BIT(PIPE_PRIM_TRIANGLES) |
             BITFIELD_BIT(PIPE_PRIM_TRIANGLE_STRIP) |
             BITFIELD_BIT(PIPE_PRIM_TRIANGLE_FAN) |
             BITFIELD_BIT(PIPE_PRIM_QUADS) | BITFIELD_BIT(PIPE_PRIM_QUAD_STRIP);

   case PIPE_CAP_MAP_UNSYNCHRONIZED_THREAD_SAFE:
      return 1;

   default:
      return u_pipe_screen_get_param_defaults(pscreen, param);
   }
}

static float
agx_get_paramf(struct pipe_screen *pscreen, enum pipe_capf param)
{
   switch (param) {
   case PIPE_CAPF_MIN_LINE_WIDTH:
   case PIPE_CAPF_MIN_LINE_WIDTH_AA:
   case PIPE_CAPF_MIN_POINT_SIZE:
   case PIPE_CAPF_MIN_POINT_SIZE_AA:
      return 1;

   case PIPE_CAPF_POINT_SIZE_GRANULARITY:
   case PIPE_CAPF_LINE_WIDTH_GRANULARITY:
      return 0.1;

   case PIPE_CAPF_MAX_LINE_WIDTH:
   case PIPE_CAPF_MAX_LINE_WIDTH_AA:
      return 16.0; /* Off-by-one fixed point 4:4 encoding */

   case PIPE_CAPF_MAX_POINT_SIZE:
   case PIPE_CAPF_MAX_POINT_SIZE_AA:
      return 511.95f;

   case PIPE_CAPF_MAX_TEXTURE_ANISOTROPY:
      return 16.0;

   case PIPE_CAPF_MAX_TEXTURE_LOD_BIAS:
      return 16.0; /* arbitrary */

   case PIPE_CAPF_MIN_CONSERVATIVE_RASTER_DILATE:
   case PIPE_CAPF_MAX_CONSERVATIVE_RASTER_DILATE:
   case PIPE_CAPF_CONSERVATIVE_RASTER_DILATE_GRANULARITY:
      return 0.0f;

   default:
      debug_printf("Unexpected PIPE_CAPF %d query\n", param);
      return 0.0;
   }
}

static int
agx_get_shader_param(struct pipe_screen *pscreen, enum pipe_shader_type shader,
                     enum pipe_shader_cap param)
{
   bool is_no16 = agx_device(pscreen)->debug & AGX_DBG_NO16;
   bool is_deqp = agx_device(pscreen)->debug & AGX_DBG_DEQP;

   if (shader != PIPE_SHADER_VERTEX && shader != PIPE_SHADER_FRAGMENT &&
       !(shader == PIPE_SHADER_COMPUTE && is_deqp))
      return 0;

   /* Don't allow side effects with vertex processing. The APIs don't require it
    * and it may be problematic on our hardware.
    */
   bool allow_side_effects = (shader != PIPE_SHADER_VERTEX);

   /* this is probably not totally correct.. but it's a start: */
   switch (param) {
   case PIPE_SHADER_CAP_MAX_INSTRUCTIONS:
   case PIPE_SHADER_CAP_MAX_ALU_INSTRUCTIONS:
   case PIPE_SHADER_CAP_MAX_TEX_INSTRUCTIONS:
   case PIPE_SHADER_CAP_MAX_TEX_INDIRECTIONS:
      return 16384;

   case PIPE_SHADER_CAP_MAX_CONTROL_FLOW_DEPTH:
      return 1024;

   case PIPE_SHADER_CAP_MAX_INPUTS:
      return 16;

   case PIPE_SHADER_CAP_MAX_OUTPUTS:
      return shader == PIPE_SHADER_FRAGMENT ? 8 : 16;

   case PIPE_SHADER_CAP_MAX_TEMPS:
      return 256; /* GL_MAX_PROGRAM_TEMPORARIES_ARB */

   case PIPE_SHADER_CAP_MAX_CONST_BUFFER0_SIZE:
      return 16 * 1024 * sizeof(float);

   case PIPE_SHADER_CAP_MAX_CONST_BUFFERS:
      return 16;

   case PIPE_SHADER_CAP_CONT_SUPPORTED:
      return 0;

   case PIPE_SHADER_CAP_INDIRECT_INPUT_ADDR:
   case PIPE_SHADER_CAP_INDIRECT_OUTPUT_ADDR:
   case PIPE_SHADER_CAP_INDIRECT_TEMP_ADDR:
   case PIPE_SHADER_CAP_SUBROUTINES:
   case PIPE_SHADER_CAP_TGSI_SQRT_SUPPORTED:
      return 0;

   case PIPE_SHADER_CAP_INDIRECT_CONST_ADDR:
   case PIPE_SHADER_CAP_INTEGERS:
      return true;

   case PIPE_SHADER_CAP_FP16:
   case PIPE_SHADER_CAP_GLSL_16BIT_CONSTS:
   case PIPE_SHADER_CAP_FP16_DERIVATIVES:
   case PIPE_SHADER_CAP_FP16_CONST_BUFFERS:
      return !is_no16;
   case PIPE_SHADER_CAP_INT16:
      /* GLSL compiler is broken. Flip this on when Panfrost does. */
      return false;

   case PIPE_SHADER_CAP_INT64_ATOMICS:
   case PIPE_SHADER_CAP_DROUND_SUPPORTED:
   case PIPE_SHADER_CAP_TGSI_ANY_INOUT_DECL_RANGE:
      return 0;

   case PIPE_SHADER_CAP_MAX_TEXTURE_SAMPLERS:
   case PIPE_SHADER_CAP_MAX_SAMPLER_VIEWS:
      return 16; /* XXX: How many? */

   case PIPE_SHADER_CAP_PREFERRED_IR:
      return PIPE_SHADER_IR_NIR;

   case PIPE_SHADER_CAP_SUPPORTED_IRS:
      return (1 << PIPE_SHADER_IR_NIR);

   case PIPE_SHADER_CAP_MAX_SHADER_BUFFERS:
      return (is_deqp && allow_side_effects) ? PIPE_MAX_SHADER_BUFFERS : 0;

   case PIPE_SHADER_CAP_MAX_SHADER_IMAGES:
      return (is_deqp && allow_side_effects) ? PIPE_MAX_SHADER_IMAGES : 0;

   case PIPE_SHADER_CAP_MAX_HW_ATOMIC_COUNTERS:
   case PIPE_SHADER_CAP_MAX_HW_ATOMIC_COUNTER_BUFFERS:
      return 0;

   default:
      /* Other params are unknown */
      return 0;
   }

   return 0;
}

static int
agx_get_compute_param(struct pipe_screen *pscreen, enum pipe_shader_ir ir_type,
                      enum pipe_compute_cap param, void *ret)
{
   if (!(agx_device(pscreen)->debug & AGX_DBG_DEQP))
      return 0;

#define RET(x)                                                                 \
   do {                                                                        \
      if (ret)                                                                 \
         memcpy(ret, x, sizeof(x));                                            \
      return sizeof(x);                                                        \
   } while (0)

   switch (param) {
   case PIPE_COMPUTE_CAP_ADDRESS_BITS:
      RET((uint32_t[]){64});

   case PIPE_COMPUTE_CAP_IR_TARGET:
      if (ret)
         sprintf(ret, "agx");
      return strlen("agx") * sizeof(char);

   case PIPE_COMPUTE_CAP_GRID_DIMENSION:
      RET((uint64_t[]){3});

   case PIPE_COMPUTE_CAP_MAX_GRID_SIZE:
      RET(((uint64_t[]){65535, 65535, 65535}));

   case PIPE_COMPUTE_CAP_MAX_BLOCK_SIZE:
      RET(((uint64_t[]){256, 256, 256}));

   case PIPE_COMPUTE_CAP_MAX_THREADS_PER_BLOCK:
      RET((uint64_t[]){256});

   case PIPE_COMPUTE_CAP_MAX_GLOBAL_SIZE:
      RET((uint64_t[]){1024 * 1024 * 512 /* Maybe get memory */});

   case PIPE_COMPUTE_CAP_MAX_LOCAL_SIZE:
      RET((uint64_t[]){32768});

   case PIPE_COMPUTE_CAP_MAX_PRIVATE_SIZE:
   case PIPE_COMPUTE_CAP_MAX_INPUT_SIZE:
      RET((uint64_t[]){4096});

   case PIPE_COMPUTE_CAP_MAX_MEM_ALLOC_SIZE:
      RET((uint64_t[]){1024 * 1024 * 512 /* Maybe get memory */});

   case PIPE_COMPUTE_CAP_MAX_CLOCK_FREQUENCY:
      RET((uint32_t[]){800 /* MHz -- TODO */});

   case PIPE_COMPUTE_CAP_MAX_COMPUTE_UNITS:
      RET((uint32_t[]){4 /* TODO */});

   case PIPE_COMPUTE_CAP_IMAGES_SUPPORTED:
      RET((uint32_t[]){1});

   case PIPE_COMPUTE_CAP_SUBGROUP_SIZE:
      RET((uint32_t[]){32});

   case PIPE_COMPUTE_CAP_MAX_VARIABLE_THREADS_PER_BLOCK:
      RET((uint64_t[]){1024}); // TODO
   }

   return 0;
}

static bool
agx_is_format_supported(struct pipe_screen *pscreen, enum pipe_format format,
                        enum pipe_texture_target target, unsigned sample_count,
                        unsigned storage_sample_count, unsigned usage)
{
   assert(target == PIPE_BUFFER || target == PIPE_TEXTURE_1D ||
          target == PIPE_TEXTURE_1D_ARRAY || target == PIPE_TEXTURE_2D ||
          target == PIPE_TEXTURE_2D_ARRAY || target == PIPE_TEXTURE_RECT ||
          target == PIPE_TEXTURE_3D || target == PIPE_TEXTURE_CUBE ||
          target == PIPE_TEXTURE_CUBE_ARRAY);

   bool is_deqp = agx_device(pscreen)->debug & AGX_DBG_DEQP;

   if (sample_count > 1 && !(sample_count == 4 && is_deqp))
      return false;

   if (MAX2(sample_count, 1) != MAX2(storage_sample_count, 1))
      return false;

   if ((usage & PIPE_BIND_VERTEX_BUFFER) && !agx_vbo_supports_format(format))
      return false;

   /* For framebuffer_no_attachments, fake support for "none" images */
   if (format == PIPE_FORMAT_NONE)
      return true;

   if (usage & (PIPE_BIND_RENDER_TARGET | PIPE_BIND_SAMPLER_VIEW)) {
      enum pipe_format tex_format = format;

      /* Mimic the fixup done in create_sampler_view and u_transfer_helper so we
       * advertise GL_OES_texture_stencil8. Alternatively, we could make mesa/st
       * less stupid?
       */
      if (tex_format == PIPE_FORMAT_X24S8_UINT)
         tex_format = PIPE_FORMAT_S8_UINT;

      struct agx_pixel_format_entry ent = agx_pixel_format[tex_format];

      if (!agx_is_valid_pixel_format(tex_format))
         return false;

      /* RGB32 is emulated for texture buffers only */
      if (ent.channels == AGX_CHANNELS_R32G32B32_EMULATED &&
          target != PIPE_BUFFER)
         return false;

      if ((usage & PIPE_BIND_RENDER_TARGET) && !ent.renderable)
         return false;
   }

   if (usage & PIPE_BIND_DEPTH_STENCIL) {
      switch (format) {
      /* natively supported
       * TODO: we could also support Z16_UNORM */
      case PIPE_FORMAT_Z32_FLOAT:
      case PIPE_FORMAT_S8_UINT:

      /* lowered by u_transfer_helper to one of the above */
      case PIPE_FORMAT_Z24X8_UNORM:
      case PIPE_FORMAT_Z24_UNORM_S8_UINT:
      case PIPE_FORMAT_Z32_FLOAT_S8X24_UINT:
         break;

      default:
         return false;
      }
   }

   return true;
}

static void
agx_query_dmabuf_modifiers(struct pipe_screen *screen, enum pipe_format format,
                           int max, uint64_t *modifiers,
                           unsigned int *external_only, int *out_count)
{
   int i;

   if (max == 0) {
      *out_count = ARRAY_SIZE(agx_best_modifiers);
      return;
   }

   for (i = 0; i < ARRAY_SIZE(agx_best_modifiers) && i < max; i++) {
      if (external_only)
         external_only[i] = 0;

      modifiers[i] = agx_best_modifiers[i];
   }

   /* Return the number of modifiers copied */
   *out_count = i;
}

static bool
agx_is_dmabuf_modifier_supported(struct pipe_screen *screen, uint64_t modifier,
                                 enum pipe_format format, bool *external_only)
{
   if (external_only)
      *external_only = false;

   for (unsigned i = 0; i < ARRAY_SIZE(agx_best_modifiers); ++i) {
      if (agx_best_modifiers[i] == modifier)
         return true;
   }

   return false;
}

static void
agx_destroy_screen(struct pipe_screen *pscreen)
{
   struct agx_screen *screen = agx_screen(pscreen);

   if (screen->dev.ro)
      screen->dev.ro->destroy(screen->dev.ro);

   u_transfer_helper_destroy(pscreen->transfer_helper);
   agx_close_device(&screen->dev);
   disk_cache_destroy(screen->disk_cache);
   ralloc_free(screen);
}

static const void *
agx_get_compiler_options(struct pipe_screen *pscreen, enum pipe_shader_ir ir,
                         enum pipe_shader_type shader)
{
   return &agx_nir_options;
}

static void
agx_resource_set_stencil(struct pipe_resource *prsrc,
                         struct pipe_resource *stencil)
{
   agx_resource(prsrc)->separate_stencil = agx_resource(stencil);
}

static struct pipe_resource *
agx_resource_get_stencil(struct pipe_resource *prsrc)
{
   return (struct pipe_resource *)agx_resource(prsrc)->separate_stencil;
}

static enum pipe_format
agx_resource_get_internal_format(struct pipe_resource *prsrc)
{
   return agx_resource(prsrc)->layout.format;
}

static struct disk_cache *
agx_get_disk_shader_cache(struct pipe_screen *pscreen)
{
   return agx_screen(pscreen)->disk_cache;
}

static const struct u_transfer_vtbl transfer_vtbl = {
   .resource_create = agx_resource_create,
   .resource_destroy = agx_resource_destroy,
   .transfer_map = agx_transfer_map,
   .transfer_unmap = agx_transfer_unmap,
   .transfer_flush_region = agx_transfer_flush_region,
   .get_internal_format = agx_resource_get_internal_format,
   .set_stencil = agx_resource_set_stencil,
   .get_stencil = agx_resource_get_stencil,
};

static int
agx_screen_get_fd(struct pipe_screen *pscreen)
{
   return agx_device(pscreen)->fd;
}

struct pipe_screen *
agx_screen_create(int fd, struct renderonly *ro, struct sw_winsys *winsys)
{
   struct agx_screen *agx_screen;
   struct pipe_screen *screen;

   agx_screen = rzalloc(NULL, struct agx_screen);
   if (!agx_screen)
      return NULL;

   screen = &agx_screen->pscreen;
   agx_screen->winsys = winsys;

   /* Set debug before opening */
   agx_screen->dev.debug =
      debug_get_flags_option("ASAHI_MESA_DEBUG", agx_debug_options, 0);

   agx_screen->dev.fd = fd;
   agx_screen->dev.ro = ro;

   /* Try to open an AGX device */
   if (!agx_open_device(screen, &agx_screen->dev)) {
      ralloc_free(agx_screen);
      return NULL;
   }

   if (agx_screen->dev.debug & AGX_DBG_DEQP) {
      /* You're on your own. */
      static bool warned_about_hacks = false;

      if (!warned_about_hacks) {
         agx_msg("\n------------------\n"
                 "Unsupported debug parameter set. Expect breakage.\n"
                 "Do not report bugs.\n"
                 "------------------\n\n");
         warned_about_hacks = true;
      }
   }

   screen->destroy = agx_destroy_screen;
   screen->get_screen_fd = agx_screen_get_fd;
   screen->get_name = agx_get_name;
   screen->get_vendor = agx_get_vendor;
   screen->get_device_vendor = agx_get_device_vendor;
   screen->get_param = agx_get_param;
   screen->get_shader_param = agx_get_shader_param;
   screen->get_compute_param = agx_get_compute_param;
   screen->get_paramf = agx_get_paramf;
   screen->is_format_supported = agx_is_format_supported;
   screen->query_dmabuf_modifiers = agx_query_dmabuf_modifiers;
   screen->is_dmabuf_modifier_supported = agx_is_dmabuf_modifier_supported;
   screen->context_create = agx_create_context;
   screen->resource_from_handle = agx_resource_from_handle;
   screen->resource_get_handle = agx_resource_get_handle;
   screen->resource_get_param = agx_resource_get_param;
   screen->resource_create_with_modifiers = agx_resource_create_with_modifiers;
   screen->flush_frontbuffer = agx_flush_frontbuffer;
   screen->get_timestamp = u_default_get_timestamp;
   screen->fence_reference = agx_fence_reference;
   screen->fence_finish = agx_fence_finish;
   screen->fence_get_fd = agx_fence_get_fd;
   screen->get_compiler_options = agx_get_compiler_options;
   screen->get_disk_shader_cache = agx_get_disk_shader_cache;

   screen->resource_create = u_transfer_helper_resource_create;
   screen->resource_destroy = u_transfer_helper_resource_destroy;
   screen->transfer_helper = u_transfer_helper_create(
      &transfer_vtbl,
      U_TRANSFER_HELPER_SEPARATE_Z32S8 | U_TRANSFER_HELPER_SEPARATE_STENCIL |
         U_TRANSFER_HELPER_MSAA_MAP | U_TRANSFER_HELPER_Z24_IN_Z32F);

   agx_disk_cache_init(agx_screen);

   return screen;
}
