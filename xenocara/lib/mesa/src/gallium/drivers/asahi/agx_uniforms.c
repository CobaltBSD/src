/*
 * Copyright 2021 Alyssa Rosenzweig
 * SPDX-License-Identifier: MIT
 */
#include <stdio.h>
#include "asahi/lib/agx_pack.h"
#include "agx_state.h"

static uint64_t
agx_const_buffer_ptr(struct agx_batch *batch, struct pipe_constant_buffer *cb)
{
   if (cb->buffer) {
      struct agx_resource *rsrc = agx_resource(cb->buffer);
      agx_batch_reads(batch, rsrc);

      return rsrc->bo->ptr.gpu + cb->buffer_offset;
   } else {
      return 0;
   }
}

static uint64_t
agx_shader_buffer_ptr(struct agx_batch *batch, struct pipe_shader_buffer *sb)
{
   if (sb->buffer) {
      struct agx_resource *rsrc = agx_resource(sb->buffer);

      /* Assume SSBOs are written. TODO: Optimize read-only SSBOs */
      agx_batch_writes(batch, rsrc);

      return rsrc->bo->ptr.gpu + sb->buffer_offset;
   } else {
      return 0;
   }
}

static uint64_t
agx_vertex_buffer_ptr(struct agx_batch *batch, unsigned vbo)
{
   struct pipe_vertex_buffer vb = batch->ctx->vertex_buffers[vbo];
   assert(!vb.is_user_buffer);

   if (vb.buffer.resource) {
      struct agx_resource *rsrc = agx_resource(vb.buffer.resource);
      agx_batch_reads(batch, rsrc);

      return rsrc->bo->ptr.gpu + vb.buffer_offset;
   } else {
      return 0;
   }
}

uint64_t
agx_upload_uniforms(struct agx_batch *batch, uint64_t textures,
                    enum pipe_shader_type stage)
{
   struct agx_context *ctx = batch->ctx;
   struct agx_stage *st = &ctx->stage[stage];

   struct agx_ptr root_ptr = agx_pool_alloc_aligned(
      &batch->pool, sizeof(struct agx_draw_uniforms), 16);

   struct agx_draw_uniforms uniforms = {
      .tables =
         {
            [AGX_SYSVAL_TABLE_ROOT] = root_ptr.gpu,
         },
      .texture_base = textures,
   };

   u_foreach_bit(s, st->valid_samplers) {
      uniforms.lod_bias[s] = st->samplers[s]->lod_bias_as_fp16;
   }

   u_foreach_bit(cb, st->cb_mask) {
      uniforms.ubo_base[cb] = agx_const_buffer_ptr(batch, &st->cb[cb]);
   }

   u_foreach_bit(cb, st->ssbo_mask) {
      uniforms.ssbo_base[cb] = agx_shader_buffer_ptr(batch, &st->ssbo[cb]);
      uniforms.ssbo_size[cb] = st->ssbo[cb].buffer_size;
   }

   if (stage == PIPE_SHADER_VERTEX) {
      u_foreach_bit(vbo, ctx->vb_mask) {
         uniforms.vs.vbo_base[vbo] = agx_vertex_buffer_ptr(batch, vbo);
      }
   } else if (stage == PIPE_SHADER_FRAGMENT) {
      memcpy(uniforms.fs.blend_constant, &ctx->blend_color,
             sizeof(ctx->blend_color));
   }

   memcpy(root_ptr.cpu, &uniforms, sizeof(uniforms));
   return root_ptr.gpu;
}
