
/* Copyright © 2022 Collabora, Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
/* This file generated from vk_format_info_gen.py, don't edit directly. */

#ifndef VK_FORMAT_INFO_H
#define VK_FORMAT_INFO_H

#include <vulkan/vulkan_core.h>

#ifdef __cplusplus
extern "C" {
#endif

enum vk_format_class {
   MESA_VK_FORMAT_CLASS_UNKNOWN,
   MESA_VK_FORMAT_CLASS_8_BIT,
   MESA_VK_FORMAT_CLASS_16_BIT,
   MESA_VK_FORMAT_CLASS_24_BIT,
   MESA_VK_FORMAT_CLASS_32_BIT,
   MESA_VK_FORMAT_CLASS_48_BIT,
   MESA_VK_FORMAT_CLASS_64_BIT,
   MESA_VK_FORMAT_CLASS_96_BIT,
   MESA_VK_FORMAT_CLASS_128_BIT,
   MESA_VK_FORMAT_CLASS_192_BIT,
   MESA_VK_FORMAT_CLASS_256_BIT,
   MESA_VK_FORMAT_CLASS_D16,
   MESA_VK_FORMAT_CLASS_D24,
   MESA_VK_FORMAT_CLASS_D32,
   MESA_VK_FORMAT_CLASS_S8,
   MESA_VK_FORMAT_CLASS_D16S8,
   MESA_VK_FORMAT_CLASS_D24S8,
   MESA_VK_FORMAT_CLASS_D32S8,
   MESA_VK_FORMAT_CLASS_BC1_RGB,
   MESA_VK_FORMAT_CLASS_BC1_RGBA,
   MESA_VK_FORMAT_CLASS_BC2,
   MESA_VK_FORMAT_CLASS_BC3,
   MESA_VK_FORMAT_CLASS_BC4,
   MESA_VK_FORMAT_CLASS_BC5,
   MESA_VK_FORMAT_CLASS_BC6H,
   MESA_VK_FORMAT_CLASS_BC7,
   MESA_VK_FORMAT_CLASS_ETC2_RGB,
   MESA_VK_FORMAT_CLASS_ETC2_RGBA,
   MESA_VK_FORMAT_CLASS_ETC2_EAC_RGBA,
   MESA_VK_FORMAT_CLASS_EAC_R,
   MESA_VK_FORMAT_CLASS_EAC_RG,
   MESA_VK_FORMAT_CLASS_ASTC_4X4,
   MESA_VK_FORMAT_CLASS_ASTC_5X4,
   MESA_VK_FORMAT_CLASS_ASTC_5X5,
   MESA_VK_FORMAT_CLASS_ASTC_6X5,
   MESA_VK_FORMAT_CLASS_ASTC_6X6,
   MESA_VK_FORMAT_CLASS_ASTC_8X5,
   MESA_VK_FORMAT_CLASS_ASTC_8X6,
   MESA_VK_FORMAT_CLASS_ASTC_8X8,
   MESA_VK_FORMAT_CLASS_ASTC_10X5,
   MESA_VK_FORMAT_CLASS_ASTC_10X6,
   MESA_VK_FORMAT_CLASS_ASTC_10X8,
   MESA_VK_FORMAT_CLASS_ASTC_10X10,
   MESA_VK_FORMAT_CLASS_ASTC_12X10,
   MESA_VK_FORMAT_CLASS_ASTC_12X12,
   MESA_VK_FORMAT_CLASS_32_BIT_G8B8G8R8,
   MESA_VK_FORMAT_CLASS_32_BIT_B8G8R8G8,
   MESA_VK_FORMAT_CLASS_8_BIT_3_PLANE_420,
   MESA_VK_FORMAT_CLASS_8_BIT_2_PLANE_420,
   MESA_VK_FORMAT_CLASS_8_BIT_3_PLANE_422,
   MESA_VK_FORMAT_CLASS_8_BIT_2_PLANE_422,
   MESA_VK_FORMAT_CLASS_8_BIT_3_PLANE_444,
   MESA_VK_FORMAT_CLASS_64_BIT_R10G10B10A10,
   MESA_VK_FORMAT_CLASS_64_BIT_G10B10G10R10,
   MESA_VK_FORMAT_CLASS_64_BIT_B10G10R10G10,
   MESA_VK_FORMAT_CLASS_10_BIT_3_PLANE_420,
   MESA_VK_FORMAT_CLASS_10_BIT_2_PLANE_420,
   MESA_VK_FORMAT_CLASS_10_BIT_3_PLANE_422,
   MESA_VK_FORMAT_CLASS_10_BIT_2_PLANE_422,
   MESA_VK_FORMAT_CLASS_10_BIT_3_PLANE_444,
   MESA_VK_FORMAT_CLASS_64_BIT_R12G12B12A12,
   MESA_VK_FORMAT_CLASS_64_BIT_G12B12G12R12,
   MESA_VK_FORMAT_CLASS_64_BIT_B12G12R12G12,
   MESA_VK_FORMAT_CLASS_12_BIT_3_PLANE_420,
   MESA_VK_FORMAT_CLASS_12_BIT_2_PLANE_420,
   MESA_VK_FORMAT_CLASS_12_BIT_3_PLANE_422,
   MESA_VK_FORMAT_CLASS_12_BIT_2_PLANE_422,
   MESA_VK_FORMAT_CLASS_12_BIT_3_PLANE_444,
   MESA_VK_FORMAT_CLASS_64_BIT_G16B16G16R16,
   MESA_VK_FORMAT_CLASS_64_BIT_B16G16R16G16,
   MESA_VK_FORMAT_CLASS_16_BIT_3_PLANE_420,
   MESA_VK_FORMAT_CLASS_16_BIT_2_PLANE_420,
   MESA_VK_FORMAT_CLASS_16_BIT_3_PLANE_422,
   MESA_VK_FORMAT_CLASS_16_BIT_2_PLANE_422,
   MESA_VK_FORMAT_CLASS_16_BIT_3_PLANE_444,
   MESA_VK_FORMAT_CLASS_PVRTC1_2BPP,
   MESA_VK_FORMAT_CLASS_PVRTC1_4BPP,
   MESA_VK_FORMAT_CLASS_PVRTC2_2BPP,
   MESA_VK_FORMAT_CLASS_PVRTC2_4BPP,
   MESA_VK_FORMAT_CLASS_8_BIT_2_PLANE_444,
   MESA_VK_FORMAT_CLASS_10_BIT_2_PLANE_444,
   MESA_VK_FORMAT_CLASS_12_BIT_2_PLANE_444,
   MESA_VK_FORMAT_CLASS_16_BIT_2_PLANE_444,
};

struct vk_format_class_info {
   const VkFormat *formats;
   uint32_t format_count;
};

const struct vk_format_class_info *
vk_format_class_get_info(enum vk_format_class class);

const struct vk_format_class_info *
vk_format_get_class_info(VkFormat format);

#ifdef __cplusplus
}
#endif

#endif