/*
 * Copyright (C) 2016 Intel Corporation
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


/* Instructions, enums and structures for SKL.
 *
 * This file has been generated, do not hand edit.
 */

#ifndef GFX9_SKL_PACK_H
#define GFX9_SKL_PACK_H

#include <stdio.h>

#include "util/bitpack_helpers.h"

#ifndef __gen_validate_value
#define __gen_validate_value(x)
#endif

#ifndef __intel_field_functions
#define __intel_field_functions

#ifdef NDEBUG
#define NDEBUG_UNUSED __attribute__((unused))
#else
#define NDEBUG_UNUSED
#endif

static inline __attribute__((always_inline)) uint64_t
__gen_offset(uint64_t v, NDEBUG_UNUSED uint32_t start, NDEBUG_UNUSED uint32_t end)
{
   __gen_validate_value(v);
#ifndef NDEBUG
   uint64_t mask = (~0ull >> (64 - (end - start + 1))) << start;

   assert((v & ~mask) == 0);
#endif

   return v;
}

static inline __attribute__((always_inline)) uint64_t
__gen_offset_nonzero(uint64_t v, uint32_t start, uint32_t end)
{
   assert(v != 0ull);
   return __gen_offset(v, start, end);
}

static inline __attribute__((always_inline)) uint64_t
__gen_address(__gen_user_data *data, void *location,
              __gen_address_type address, uint32_t delta,
              __attribute__((unused)) uint32_t start, uint32_t end)
{
   uint64_t addr_u64 = __gen_combine_address(data, location, address, delta);
   if (end == 31) {
      return addr_u64;
   } else if (end < 63) {
      const unsigned shift = 63 - end;
      return (addr_u64 << shift) >> shift;
   } else {
      return addr_u64;
   }
}

#ifndef __gen_address_type
#error #define __gen_address_type before including this file
#endif

#ifndef __gen_user_data
#error #define __gen_combine_address before including this file
#endif

#undef NDEBUG_UNUSED

#endif


enum GFX9_3D_Color_Buffer_Blend_Factor {
   BLENDFACTOR_ONE                      =      1,
   BLENDFACTOR_SRC_COLOR                =      2,
   BLENDFACTOR_SRC_ALPHA                =      3,
   BLENDFACTOR_DST_ALPHA                =      4,
   BLENDFACTOR_DST_COLOR                =      5,
   BLENDFACTOR_SRC_ALPHA_SATURATE       =      6,
   BLENDFACTOR_CONST_COLOR              =      7,
   BLENDFACTOR_CONST_ALPHA              =      8,
   BLENDFACTOR_SRC1_COLOR               =      9,
   BLENDFACTOR_SRC1_ALPHA               =     10,
   BLENDFACTOR_ZERO                     =     17,
   BLENDFACTOR_INV_SRC_COLOR            =     18,
   BLENDFACTOR_INV_SRC_ALPHA            =     19,
   BLENDFACTOR_INV_DST_ALPHA            =     20,
   BLENDFACTOR_INV_DST_COLOR            =     21,
   BLENDFACTOR_INV_CONST_COLOR          =     23,
   BLENDFACTOR_INV_CONST_ALPHA          =     24,
   BLENDFACTOR_INV_SRC1_COLOR           =     25,
   BLENDFACTOR_INV_SRC1_ALPHA           =     26,
};

enum GFX9_3D_Color_Buffer_Blend_Function {
   BLENDFUNCTION_ADD                    =      0,
   BLENDFUNCTION_SUBTRACT               =      1,
   BLENDFUNCTION_REVERSE_SUBTRACT       =      2,
   BLENDFUNCTION_MIN                    =      3,
   BLENDFUNCTION_MAX                    =      4,
};

enum GFX9_3D_Compare_Function {
   COMPAREFUNCTION_ALWAYS               =      0,
   COMPAREFUNCTION_NEVER                =      1,
   COMPAREFUNCTION_LESS                 =      2,
   COMPAREFUNCTION_EQUAL                =      3,
   COMPAREFUNCTION_LEQUAL               =      4,
   COMPAREFUNCTION_GREATER              =      5,
   COMPAREFUNCTION_NOTEQUAL             =      6,
   COMPAREFUNCTION_GEQUAL               =      7,
};

enum GFX9_3D_Logic_Op_Function {
   LOGICOP_CLEAR                        =      0,
   LOGICOP_NOR                          =      1,
   LOGICOP_AND_INVERTED                 =      2,
   LOGICOP_COPY_INVERTED                =      3,
   LOGICOP_AND_REVERSE                  =      4,
   LOGICOP_INVERT                       =      5,
   LOGICOP_XOR                          =      6,
   LOGICOP_NAND                         =      7,
   LOGICOP_AND                          =      8,
   LOGICOP_EQUIV                        =      9,
   LOGICOP_NOOP                         =     10,
   LOGICOP_OR_INVERTED                  =     11,
   LOGICOP_COPY                         =     12,
   LOGICOP_OR_REVERSE                   =     13,
   LOGICOP_OR                           =     14,
   LOGICOP_SET                          =     15,
};

enum GFX9_3D_Prim_Topo_Type {
   _3DPRIM_POINTLIST                    =      1,
   _3DPRIM_LINELIST                     =      2,
   _3DPRIM_LINESTRIP                    =      3,
   _3DPRIM_TRILIST                      =      4,
   _3DPRIM_TRISTRIP                     =      5,
   _3DPRIM_TRIFAN                       =      6,
   _3DPRIM_QUADLIST                     =      7,
   _3DPRIM_QUADSTRIP                    =      8,
   _3DPRIM_LINELIST_ADJ                 =      9,
   _3DPRIM_LINESTRIP_ADJ                =     10,
   _3DPRIM_TRILIST_ADJ                  =     11,
   _3DPRIM_TRISTRIP_ADJ                 =     12,
   _3DPRIM_TRISTRIP_REVERSE             =     13,
   _3DPRIM_POLYGON                      =     14,
   _3DPRIM_RECTLIST                     =     15,
   _3DPRIM_LINELOOP                     =     16,
   _3DPRIM_POINTLIST_BF                 =     17,
   _3DPRIM_LINESTRIP_CONT               =     18,
   _3DPRIM_LINESTRIP_BF                 =     19,
   _3DPRIM_LINESTRIP_CONT_BF            =     20,
   _3DPRIM_TRIFAN_NOSTIPPLE             =     22,
   _3DPRIM_PATCHLIST_1                  =     32,
   _3DPRIM_PATCHLIST_2                  =     33,
   _3DPRIM_PATCHLIST_3                  =     34,
   _3DPRIM_PATCHLIST_4                  =     35,
   _3DPRIM_PATCHLIST_5                  =     36,
   _3DPRIM_PATCHLIST_6                  =     37,
   _3DPRIM_PATCHLIST_7                  =     38,
   _3DPRIM_PATCHLIST_8                  =     39,
   _3DPRIM_PATCHLIST_9                  =     40,
   _3DPRIM_PATCHLIST_10                 =     41,
   _3DPRIM_PATCHLIST_11                 =     42,
   _3DPRIM_PATCHLIST_12                 =     43,
   _3DPRIM_PATCHLIST_13                 =     44,
   _3DPRIM_PATCHLIST_14                 =     45,
   _3DPRIM_PATCHLIST_15                 =     46,
   _3DPRIM_PATCHLIST_16                 =     47,
   _3DPRIM_PATCHLIST_17                 =     48,
   _3DPRIM_PATCHLIST_18                 =     49,
   _3DPRIM_PATCHLIST_19                 =     50,
   _3DPRIM_PATCHLIST_20                 =     51,
   _3DPRIM_PATCHLIST_21                 =     52,
   _3DPRIM_PATCHLIST_22                 =     53,
   _3DPRIM_PATCHLIST_23                 =     54,
   _3DPRIM_PATCHLIST_24                 =     55,
   _3DPRIM_PATCHLIST_25                 =     56,
   _3DPRIM_PATCHLIST_26                 =     57,
   _3DPRIM_PATCHLIST_27                 =     58,
   _3DPRIM_PATCHLIST_28                 =     59,
   _3DPRIM_PATCHLIST_29                 =     60,
   _3DPRIM_PATCHLIST_30                 =     61,
   _3DPRIM_PATCHLIST_31                 =     62,
   _3DPRIM_PATCHLIST_32                 =     63,
};

enum GFX9_3D_Stencil_Operation {
   STENCILOP_KEEP                       =      0,
   STENCILOP_ZERO                       =      1,
   STENCILOP_REPLACE                    =      2,
   STENCILOP_INCRSAT                    =      3,
   STENCILOP_DECRSAT                    =      4,
   STENCILOP_INCR                       =      5,
   STENCILOP_DECR                       =      6,
   STENCILOP_INVERT                     =      7,
};

enum GFX9_3D_Vertex_Component_Control {
   VFCOMP_NOSTORE                       =      0,
   VFCOMP_STORE_SRC                     =      1,
   VFCOMP_STORE_0                       =      2,
   VFCOMP_STORE_1_FP                    =      3,
   VFCOMP_STORE_1_INT                   =      4,
   VFCOMP_STORE_PID                     =      7,
};

enum GFX9_Atomic_OPCODE {
   MI_ATOMIC_OP_AND                     =      1,
   MI_ATOMIC_OP_OR                      =      2,
   MI_ATOMIC_OP_XOR                     =      3,
   MI_ATOMIC_OP_MOVE                    =      4,
   MI_ATOMIC_OP_INC                     =      5,
   MI_ATOMIC_OP_DEC                     =      6,
   MI_ATOMIC_OP_ADD                     =      7,
   MI_ATOMIC_OP_SUB                     =      8,
   MI_ATOMIC_OP_RSUB                    =      9,
   MI_ATOMIC_OP_IMAX                    =     10,
   MI_ATOMIC_OP_IMIN                    =     11,
   MI_ATOMIC_OP_UMAX                    =     12,
   MI_ATOMIC_OP_UMIN                    =     13,
   MI_ATOMIC_OP_CMP_WR                  =     14,
   MI_ATOMIC_OP_PREDEC                  =     15,
   MI_ATOMIC_OP_AND8B                   =     33,
   MI_ATOMIC_OP_OR8B                    =     34,
   MI_ATOMIC_OP_XOR8B                   =     35,
   MI_ATOMIC_OP_MOVE8B                  =     36,
   MI_ATOMIC_OP_INC8B                   =     37,
   MI_ATOMIC_OP_DEC8B                   =     38,
   MI_ATOMIC_OP_ADD8B                   =     39,
   MI_ATOMIC_OP_SUB8B                   =     40,
   MI_ATOMIC_OP_RSUB8B                  =     41,
   MI_ATOMIC_OP_IMAX8B                  =     42,
   MI_ATOMIC_OP_IMIN8B                  =     43,
   MI_ATOMIC_OP_UMAX8B                  =     44,
   MI_ATOMIC_OP_UMIN8B                  =     45,
   MI_ATOMIC_OP_CMP_WR8B                =     46,
   MI_ATOMIC_OP_PREDEC8B                =     47,
   MI_ATOMIC_OP_CMP_WR16B               =     78,
};

enum GFX9_Attribute_Component_Format {
   ACF_DISABLED                         =      0,
   ACF_XY                               =      1,
   ACF_XYZ                              =      2,
   ACF_XYZW                             =      3,
};

enum GFX9_COMPONENT_ENABLES {
   CE_NONE                              =      0,
   CE_X                                 =      1,
   CE_Y                                 =      2,
   CE_XY                                =      3,
   CE_Z                                 =      4,
   CE_XZ                                =      5,
   CE_YZ                                =      6,
   CE_XYZ                               =      7,
   CE_W                                 =      8,
   CE_XW                                =      9,
   CE_YW                                =     10,
   CE_XYW                               =     11,
   CE_ZW                                =     12,
   CE_XZW                               =     13,
   CE_YZW                               =     14,
   CE_XYZW                              =     15,
};

enum GFX9_ShaderChannelSelect {
   SCS_ZERO                             =      0,
   SCS_ONE                              =      1,
   SCS_RED                              =      4,
   SCS_GREEN                            =      5,
   SCS_BLUE                             =      6,
   SCS_ALPHA                            =      7,
};

enum GFX9_TextureCoordinateMode {
   TCM_WRAP                             =      0,
   TCM_MIRROR                           =      1,
   TCM_CLAMP                            =      2,
   TCM_CUBE                             =      3,
   TCM_CLAMP_BORDER                     =      4,
   TCM_MIRROR_ONCE                      =      5,
   TCM_HALF_BORDER                      =      6,
};

enum GFX9_WRAP_SHORTEST_ENABLE {
   WSE_X                                =      1,
   WSE_Y                                =      2,
   WSE_XY                               =      3,
   WSE_Z                                =      4,
   WSE_XZ                               =      5,
   WSE_YZ                               =      6,
   WSE_XYZ                              =      7,
   WSE_W                                =      8,
   WSE_XW                               =      9,
   WSE_YW                               =     10,
   WSE_XYW                              =     11,
   WSE_ZW                               =     12,
   WSE_XZW                              =     13,
   WSE_YZW                              =     14,
   WSE_XYZW                             =     15,
};

#define GFX9_3DSTATE_CONSTANT_BODY_length     10
struct GFX9_3DSTATE_CONSTANT_BODY {
   uint32_t                             ReadLength[4];
   __gen_address_type                   Buffer[4];
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_CONSTANT_BODY_pack(__attribute__((unused)) __gen_user_data *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GFX9_3DSTATE_CONSTANT_BODY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->ReadLength[0], 0, 15) |
      util_bitpack_uint(values->ReadLength[1], 16, 31);

   dw[1] =
      util_bitpack_uint(values->ReadLength[2], 0, 15) |
      util_bitpack_uint(values->ReadLength[3], 16, 31);

   const uint64_t v2_address =
      __gen_address(data, &dw[2], values->Buffer[0], 0, 5, 63);
   dw[2] = v2_address;
   dw[3] = v2_address >> 32;

   const uint64_t v4_address =
      __gen_address(data, &dw[4], values->Buffer[1], 0, 5, 63);
   dw[4] = v4_address;
   dw[5] = v4_address >> 32;

   const uint64_t v6_address =
      __gen_address(data, &dw[6], values->Buffer[2], 0, 5, 63);
   dw[6] = v6_address;
   dw[7] = v6_address >> 32;

   const uint64_t v8_address =
      __gen_address(data, &dw[8], values->Buffer[3], 0, 5, 63);
   dw[8] = v8_address;
   dw[9] = v8_address >> 32;
}

#define GFX9_BINDING_TABLE_EDIT_ENTRY_length      1
struct GFX9_BINDING_TABLE_EDIT_ENTRY {
   uint64_t                             SurfaceStatePointer;
   uint32_t                             BindingTableIndex;
};

static inline __attribute__((always_inline)) void
GFX9_BINDING_TABLE_EDIT_ENTRY_pack(__attribute__((unused)) __gen_user_data *data,
                                   __attribute__((unused)) void * restrict dst,
                                   __attribute__((unused)) const struct GFX9_BINDING_TABLE_EDIT_ENTRY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      __gen_offset(values->SurfaceStatePointer, 0, 15) |
      util_bitpack_uint(values->BindingTableIndex, 16, 23);
}

#define GFX9_BINDING_TABLE_STATE_length        1
struct GFX9_BINDING_TABLE_STATE {
   uint64_t                             SurfaceStatePointer;
};

static inline __attribute__((always_inline)) void
GFX9_BINDING_TABLE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_BINDING_TABLE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      __gen_offset(values->SurfaceStatePointer, 6, 31);
}

#define GFX9_BLEND_STATE_ENTRY_length          2
struct GFX9_BLEND_STATE_ENTRY {
   bool                                 WriteDisableBlue;
   bool                                 WriteDisableGreen;
   bool                                 WriteDisableRed;
   bool                                 WriteDisableAlpha;
   enum GFX9_3D_Color_Buffer_Blend_Function AlphaBlendFunction;
   enum GFX9_3D_Color_Buffer_Blend_Factor DestinationAlphaBlendFactor;
   enum GFX9_3D_Color_Buffer_Blend_Factor SourceAlphaBlendFactor;
   enum GFX9_3D_Color_Buffer_Blend_Function ColorBlendFunction;
   enum GFX9_3D_Color_Buffer_Blend_Factor DestinationBlendFactor;
   enum GFX9_3D_Color_Buffer_Blend_Factor SourceBlendFactor;
   bool                                 ColorBufferBlendEnable;
   bool                                 PostBlendColorClampEnable;
   bool                                 PreBlendColorClampEnable;
   uint32_t                             ColorClampRange;
#define COLORCLAMP_UNORM                         0
#define COLORCLAMP_SNORM                         1
#define COLORCLAMP_RTFORMAT                      2
   bool                                 PreBlendSourceOnlyClampEnable;
   enum GFX9_3D_Logic_Op_Function       LogicOpFunction;
   bool                                 LogicOpEnable;
};

static inline __attribute__((always_inline)) void
GFX9_BLEND_STATE_ENTRY_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_BLEND_STATE_ENTRY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->WriteDisableBlue, 0, 0) |
      util_bitpack_uint(values->WriteDisableGreen, 1, 1) |
      util_bitpack_uint(values->WriteDisableRed, 2, 2) |
      util_bitpack_uint(values->WriteDisableAlpha, 3, 3) |
      util_bitpack_uint(values->AlphaBlendFunction, 5, 7) |
      util_bitpack_uint(values->DestinationAlphaBlendFactor, 8, 12) |
      util_bitpack_uint(values->SourceAlphaBlendFactor, 13, 17) |
      util_bitpack_uint(values->ColorBlendFunction, 18, 20) |
      util_bitpack_uint(values->DestinationBlendFactor, 21, 25) |
      util_bitpack_uint(values->SourceBlendFactor, 26, 30) |
      util_bitpack_uint(values->ColorBufferBlendEnable, 31, 31);

   dw[1] =
      util_bitpack_uint(values->PostBlendColorClampEnable, 0, 0) |
      util_bitpack_uint(values->PreBlendColorClampEnable, 1, 1) |
      util_bitpack_uint(values->ColorClampRange, 2, 3) |
      util_bitpack_uint(values->PreBlendSourceOnlyClampEnable, 4, 4) |
      util_bitpack_uint(values->LogicOpFunction, 27, 30) |
      util_bitpack_uint(values->LogicOpEnable, 31, 31);
}

#define GFX9_BLEND_STATE_length                1
struct GFX9_BLEND_STATE {
   uint32_t                             YDitherOffset;
   uint32_t                             XDitherOffset;
   bool                                 ColorDitherEnable;
   enum GFX9_3D_Compare_Function        AlphaTestFunction;
   bool                                 AlphaTestEnable;
   bool                                 AlphaToCoverageDitherEnable;
   bool                                 AlphaToOneEnable;
   bool                                 IndependentAlphaBlendEnable;
   bool                                 AlphaToCoverageEnable;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_BLEND_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                      __attribute__((unused)) void * restrict dst,
                      __attribute__((unused)) const struct GFX9_BLEND_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->YDitherOffset, 19, 20) |
      util_bitpack_uint(values->XDitherOffset, 21, 22) |
      util_bitpack_uint(values->ColorDitherEnable, 23, 23) |
      util_bitpack_uint(values->AlphaTestFunction, 24, 26) |
      util_bitpack_uint(values->AlphaTestEnable, 27, 27) |
      util_bitpack_uint(values->AlphaToCoverageDitherEnable, 28, 28) |
      util_bitpack_uint(values->AlphaToOneEnable, 29, 29) |
      util_bitpack_uint(values->IndependentAlphaBlendEnable, 30, 30) |
      util_bitpack_uint(values->AlphaToCoverageEnable, 31, 31);
}

#define GFX9_CC_VIEWPORT_length                2
struct GFX9_CC_VIEWPORT {
   float                                MinimumDepth;
   float                                MaximumDepth;
};

static inline __attribute__((always_inline)) void
GFX9_CC_VIEWPORT_pack(__attribute__((unused)) __gen_user_data *data,
                      __attribute__((unused)) void * restrict dst,
                      __attribute__((unused)) const struct GFX9_CC_VIEWPORT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_float(values->MinimumDepth);

   dw[1] =
      util_bitpack_float(values->MaximumDepth);
}

#define GFX9_COLOR_CALC_STATE_length           6
struct GFX9_COLOR_CALC_STATE {
   uint32_t                             AlphaTestFormat;
#define ALPHATEST_UNORM8                         0
#define ALPHATEST_FLOAT32                        1
   bool                                 RoundDisableFunctionDisable;
   uint32_t                             AlphaReferenceValueAsUNORM8;
   float                                AlphaReferenceValueAsFLOAT32;
   float                                BlendConstantColorRed;
   float                                BlendConstantColorGreen;
   float                                BlendConstantColorBlue;
   float                                BlendConstantColorAlpha;
};

static inline __attribute__((always_inline)) void
GFX9_COLOR_CALC_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_COLOR_CALC_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->AlphaTestFormat, 0, 0) |
      util_bitpack_uint(values->RoundDisableFunctionDisable, 15, 15);

   dw[1] =
      util_bitpack_uint(values->AlphaReferenceValueAsUNORM8, 0, 31) |
      util_bitpack_float(values->AlphaReferenceValueAsFLOAT32);

   dw[2] =
      util_bitpack_float(values->BlendConstantColorRed);

   dw[3] =
      util_bitpack_float(values->BlendConstantColorGreen);

   dw[4] =
      util_bitpack_float(values->BlendConstantColorBlue);

   dw[5] =
      util_bitpack_float(values->BlendConstantColorAlpha);
}

#define GFX9_EXECUTION_UNIT_EXTENDED_MESSAGE_DESCRIPTOR_length      1
struct GFX9_EXECUTION_UNIT_EXTENDED_MESSAGE_DESCRIPTOR {
   uint32_t                             TargetFunctionID;
   uint32_t                             EndOfThread;
#define NoTermination                            0
#define EOT                                      1
   uint32_t                             ExtendedMessageLength;
};

static inline __attribute__((always_inline)) void
GFX9_EXECUTION_UNIT_EXTENDED_MESSAGE_DESCRIPTOR_pack(__attribute__((unused)) __gen_user_data *data,
                                                     __attribute__((unused)) void * restrict dst,
                                                     __attribute__((unused)) const struct GFX9_EXECUTION_UNIT_EXTENDED_MESSAGE_DESCRIPTOR * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->TargetFunctionID, 0, 3) |
      util_bitpack_uint(values->EndOfThread, 5, 5) |
      util_bitpack_uint(values->ExtendedMessageLength, 6, 9);
}

#define GFX9_FILTER_COEFFICIENT_length         1
struct GFX9_FILTER_COEFFICIENT {
   float                                FilterCoefficient;
};

static inline __attribute__((always_inline)) void
GFX9_FILTER_COEFFICIENT_pack(__attribute__((unused)) __gen_user_data *data,
                             __attribute__((unused)) void * restrict dst,
                             __attribute__((unused)) const struct GFX9_FILTER_COEFFICIENT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_sfixed(values->FilterCoefficient, 0, 7, 6);
}

#define GFX9_FRAMEDELTAQP_length               2
struct GFX9_FRAMEDELTAQP {
   int32_t                              FrameDeltaQP[8];
};

static inline __attribute__((always_inline)) void
GFX9_FRAMEDELTAQP_pack(__attribute__((unused)) __gen_user_data *data,
                       __attribute__((unused)) void * restrict dst,
                       __attribute__((unused)) const struct GFX9_FRAMEDELTAQP * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_sint(values->FrameDeltaQP[0], 0, 7) |
      util_bitpack_sint(values->FrameDeltaQP[1], 8, 15) |
      util_bitpack_sint(values->FrameDeltaQP[2], 16, 23) |
      util_bitpack_sint(values->FrameDeltaQP[3], 24, 31);

   dw[1] =
      util_bitpack_sint(values->FrameDeltaQP[4], 0, 7) |
      util_bitpack_sint(values->FrameDeltaQP[5], 8, 15) |
      util_bitpack_sint(values->FrameDeltaQP[6], 16, 23) |
      util_bitpack_sint(values->FrameDeltaQP[7], 24, 31);
}

#define GFX9_FRAMEDELTAQPRANGE_length          2
struct GFX9_FRAMEDELTAQPRANGE {
   uint32_t                             FrameDeltaQPRange[8];
};

static inline __attribute__((always_inline)) void
GFX9_FRAMEDELTAQPRANGE_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_FRAMEDELTAQPRANGE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->FrameDeltaQPRange[0], 0, 7) |
      util_bitpack_uint(values->FrameDeltaQPRange[1], 8, 15) |
      util_bitpack_uint(values->FrameDeltaQPRange[2], 16, 23) |
      util_bitpack_uint(values->FrameDeltaQPRange[3], 24, 31);

   dw[1] =
      util_bitpack_uint(values->FrameDeltaQPRange[4], 0, 7) |
      util_bitpack_uint(values->FrameDeltaQPRange[5], 8, 15) |
      util_bitpack_uint(values->FrameDeltaQPRange[6], 16, 23) |
      util_bitpack_uint(values->FrameDeltaQPRange[7], 24, 31);
}

#define GFX9_GATHER_CONSTANT_ENTRY_length      1
struct GFX9_GATHER_CONSTANT_ENTRY {
   uint32_t                             BindingTableIndexOffset;
   uint32_t                             ChannelMask;
   uint64_t                             ConstantBufferOffset;
};

static inline __attribute__((always_inline)) void
GFX9_GATHER_CONSTANT_ENTRY_pack(__attribute__((unused)) __gen_user_data *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GFX9_GATHER_CONSTANT_ENTRY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->BindingTableIndexOffset, 0, 3) |
      util_bitpack_uint(values->ChannelMask, 4, 7) |
      __gen_offset(values->ConstantBufferOffset, 8, 15);
}

#define GFX9_MEMORYADDRESSATTRIBUTES_length      1
struct GFX9_MEMORYADDRESSATTRIBUTES {
   uint32_t                             MOCS;
   uint32_t                             ArbitrationPriorityControl;
#define Highestpriority                          0
#define Secondhighestpriority                    1
#define Thirdhighestpriority                     2
#define Lowestpriority                           3
   bool                                 MemoryCompressionEnable;
   uint32_t                             RowStoreScratchBufferCacheSelect;
#define LLC                                      0
#define InternalMediaStorage                     1
   uint32_t                             TiledResourceMode;
#define TRMODE_NONE                              0
#define TRMODE_TILEYF                            1
#define TRMODE_TILEYS                            2
};

static inline __attribute__((always_inline)) void
GFX9_MEMORYADDRESSATTRIBUTES_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_MEMORYADDRESSATTRIBUTES * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint_nonzero(values->MOCS, 1, 6) |
      util_bitpack_uint(values->ArbitrationPriorityControl, 7, 8) |
      util_bitpack_uint(values->MemoryCompressionEnable, 9, 9) |
      util_bitpack_uint(values->RowStoreScratchBufferCacheSelect, 12, 12) |
      util_bitpack_uint(values->TiledResourceMode, 13, 14);
}

#define GFX9_HCP_PAK_INSERT_OBJECT_INDIRECT_PAYLOAD_length      4
struct GFX9_HCP_PAK_INSERT_OBJECT_INDIRECT_PAYLOAD {
   uint32_t                             IndirectPayloadDataSizeinbits;
   __gen_address_type                   IndirectPayloadBaseAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  IndirectPayloadBaseAddress2;
};

static inline __attribute__((always_inline)) void
GFX9_HCP_PAK_INSERT_OBJECT_INDIRECT_PAYLOAD_pack(__attribute__((unused)) __gen_user_data *data,
                                                 __attribute__((unused)) void * restrict dst,
                                                 __attribute__((unused)) const struct GFX9_HCP_PAK_INSERT_OBJECT_INDIRECT_PAYLOAD * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->IndirectPayloadDataSizeinbits, 0, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->IndirectPayloadBaseAddress, 0, 0, 63);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[3], &values->IndirectPayloadBaseAddress2);
}

#define GFX9_HCP_REF_LIST_ENTRY_length         1
struct GFX9_HCP_REF_LIST_ENTRY {
   uint32_t                             ReferencePicturetbValue;
   uint32_t                             ListEntry;
   uint32_t                             ChromaWeightedPrediction;
#define Default                                  0
#define Explicit                                 1
   uint32_t                             LumaWeightedPrediction;
#define Default                                  0
#define Explicit                                 1
   bool                                 LongTermReference;
   bool                                 FieldPic;
   bool                                 TopField;
};

static inline __attribute__((always_inline)) void
GFX9_HCP_REF_LIST_ENTRY_pack(__attribute__((unused)) __gen_user_data *data,
                             __attribute__((unused)) void * restrict dst,
                             __attribute__((unused)) const struct GFX9_HCP_REF_LIST_ENTRY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->ReferencePicturetbValue, 0, 7) |
      util_bitpack_uint(values->ListEntry, 8, 10) |
      util_bitpack_uint(values->ChromaWeightedPrediction, 11, 11) |
      util_bitpack_uint(values->LumaWeightedPrediction, 12, 12) |
      util_bitpack_uint(values->LongTermReference, 13, 13) |
      util_bitpack_uint(values->FieldPic, 14, 14) |
      util_bitpack_uint(values->TopField, 15, 15);
}

#define GFX9_HCP_TILE_POSITION_IN_CTB_length      1
struct GFX9_HCP_TILE_POSITION_IN_CTB {
   uint32_t                             CtbPos0i;
   uint32_t                             CtbPos1i;
   uint32_t                             CtbPos2i;
   uint32_t                             CtbPos3i;
};

static inline __attribute__((always_inline)) void
GFX9_HCP_TILE_POSITION_IN_CTB_pack(__attribute__((unused)) __gen_user_data *data,
                                   __attribute__((unused)) void * restrict dst,
                                   __attribute__((unused)) const struct GFX9_HCP_TILE_POSITION_IN_CTB * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->CtbPos0i, 0, 7) |
      util_bitpack_uint(values->CtbPos1i, 8, 15) |
      util_bitpack_uint(values->CtbPos2i, 16, 23) |
      util_bitpack_uint(values->CtbPos3i, 24, 31);
}

#define GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_length      1
struct GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY {
   int32_t                              DeltaChromaWeightLX0;
   uint32_t                             ChromaOffsetLX0;
   int32_t                              DeltaChromaWeightLX1;
   uint32_t                             ChromaOffsetLX1;
};

static inline __attribute__((always_inline)) void
GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(__attribute__((unused)) __gen_user_data *data,
                                        __attribute__((unused)) void * restrict dst,
                                        __attribute__((unused)) const struct GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_sint(values->DeltaChromaWeightLX0, 0, 7) |
      util_bitpack_uint(values->ChromaOffsetLX0, 8, 15) |
      util_bitpack_sint(values->DeltaChromaWeightLX1, 16, 23) |
      util_bitpack_uint(values->ChromaOffsetLX1, 24, 31);
}

#define GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_length      1
struct GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY {
   int32_t                              DeltaLumaWeightLX;
   uint32_t                             LumaOffsetLX;
};

static inline __attribute__((always_inline)) void
GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(__attribute__((unused)) __gen_user_data *data,
                                      __attribute__((unused)) void * restrict dst,
                                      __attribute__((unused)) const struct GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_sint(values->DeltaLumaWeightLX, 0, 7) |
      util_bitpack_uint(values->LumaOffsetLX, 8, 15);
}

#define GFX9_HEVC_ARBITRATION_PRIORITY_length      1
struct GFX9_HEVC_ARBITRATION_PRIORITY {
   uint32_t                             Priority;
#define Highestpriority                          0
#define Secondhighestpriority                    1
#define Thirdhighestpriority                     2
#define Lowestpriority                           3
};

static inline __attribute__((always_inline)) void
GFX9_HEVC_ARBITRATION_PRIORITY_pack(__attribute__((unused)) __gen_user_data *data,
                                    __attribute__((unused)) void * restrict dst,
                                    __attribute__((unused)) const struct GFX9_HEVC_ARBITRATION_PRIORITY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->Priority, 0, 1);
}

#define GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_length      1
struct GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS {
   uint32_t                             LambdaValue0;
   uint32_t                             LambdaValue1;
};

static inline __attribute__((always_inline)) void
GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(__attribute__((unused)) __gen_user_data *data,
                                      __attribute__((unused)) void * restrict dst,
                                      __attribute__((unused)) const struct GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->LambdaValue0, 0, 15) |
      util_bitpack_uint(values->LambdaValue1, 16, 31);
}

#define GFX9_HUC_VIRTUAL_ADDR_REGION_length      3
struct GFX9_HUC_VIRTUAL_ADDR_REGION {
   __gen_address_type                   Address;
   struct GFX9_MEMORYADDRESSATTRIBUTES  MemoryAddressAttributes;
};

static inline __attribute__((always_inline)) void
GFX9_HUC_VIRTUAL_ADDR_REGION_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_HUC_VIRTUAL_ADDR_REGION * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0_address =
      __gen_address(data, &dw[0], values->Address, 0, 0, 63);
   dw[0] = v0_address;
   dw[1] = v0_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[2], &values->MemoryAddressAttributes);
}

#define GFX9_INLINE_DATA_DESCRIPTION_FOR_MFD_AVC_BSD_OBJECT_length      3
struct GFX9_INLINE_DATA_DESCRIPTION_FOR_MFD_AVC_BSD_OBJECT {
   bool                                 MBErrorConcealmentPSliceWeightPredictionDisable;
   bool                                 MBErrorConcealmentPSliceMotionVectorsOverrideDisable;
   bool                                 MBErrorConcealmentBSpatialWeightPredictionDisable;
   bool                                 MBErrorConcealmentBSpatialMotionVectorsOverrideDisable;
   uint32_t                             MBErrorConcealmentBSpatialPredictionMode;
   bool                                 MBHeaderErrorHandling;
   bool                                 EntropyErrorHandling;
   bool                                 MPRErrorHandling;
   bool                                 BSDPrematureCompleteErrorHandling;
   uint32_t                             ConcealmentPictureID;
   bool                                 MBErrorConcealmentBTemporalWeightPredictionDisable;
   bool                                 MBErrorConcealmentBTemporalMotionVectorsOverrideEnable;
   uint32_t                             MBErrorConcealmentBTemporalPredictionMode;
   uint32_t                             IntraPredMode4x48x8LumaErrorControl;
   bool                                 InitCurrentMBNumber;
   uint32_t                             ConcealmentMethod;
   uint32_t                             FirstMBBitOffset;
   bool                                 LastSlice;
   bool                                 EmulationPreventionBytePresent;
   bool                                 FixPrevMBSkipped;
   uint32_t                             FirstMBByteOffsetofSliceDataorSliceHeader;
   bool                                 IntraPredictionErrorControl;
   bool                                 Intra8x84x4PredictionErrorConcealmentControl;
   uint32_t                             BSliceTemporalInterConcealmentMode;
   uint32_t                             BSliceSpatialInterConcealmentMode;
   uint32_t                             BSliceInterDirectTypeConcealmentMode;
   uint32_t                             BSliceConcealmentMode;
#define IntraConcealment                         1
#define InterConcealment                         0
   uint32_t                             PSliceInterConcealmentMode;
   uint32_t                             PSliceConcealmentMode;
#define IntraConcealment                         1
#define InterConcealment                         0
   uint32_t                             ConcealmentReferencePictureFieldBit;
   uint32_t                             ISliceConcealmentMode;
#define IntraConcealment                         1
#define InterConcealment                         0
};

static inline __attribute__((always_inline)) void
GFX9_INLINE_DATA_DESCRIPTION_FOR_MFD_AVC_BSD_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                                                         __attribute__((unused)) void * restrict dst,
                                                         __attribute__((unused)) const struct GFX9_INLINE_DATA_DESCRIPTION_FOR_MFD_AVC_BSD_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->MBErrorConcealmentPSliceWeightPredictionDisable, 0, 0) |
      util_bitpack_uint(values->MBErrorConcealmentPSliceMotionVectorsOverrideDisable, 1, 1) |
      util_bitpack_uint(values->MBErrorConcealmentBSpatialWeightPredictionDisable, 3, 3) |
      util_bitpack_uint(values->MBErrorConcealmentBSpatialMotionVectorsOverrideDisable, 4, 4) |
      util_bitpack_uint(values->MBErrorConcealmentBSpatialPredictionMode, 6, 7) |
      util_bitpack_uint(values->MBHeaderErrorHandling, 8, 8) |
      util_bitpack_uint(values->EntropyErrorHandling, 10, 10) |
      util_bitpack_uint(values->MPRErrorHandling, 12, 12) |
      util_bitpack_uint(values->BSDPrematureCompleteErrorHandling, 14, 14) |
      util_bitpack_uint(values->ConcealmentPictureID, 16, 21) |
      util_bitpack_uint(values->MBErrorConcealmentBTemporalWeightPredictionDisable, 24, 24) |
      util_bitpack_uint(values->MBErrorConcealmentBTemporalMotionVectorsOverrideEnable, 25, 25) |
      util_bitpack_uint(values->MBErrorConcealmentBTemporalPredictionMode, 27, 28) |
      util_bitpack_uint(values->IntraPredMode4x48x8LumaErrorControl, 29, 29) |
      util_bitpack_uint(values->InitCurrentMBNumber, 30, 30) |
      util_bitpack_uint(values->ConcealmentMethod, 31, 31);

   dw[1] =
      util_bitpack_uint(values->FirstMBBitOffset, 0, 2) |
      util_bitpack_uint(values->LastSlice, 3, 3) |
      util_bitpack_uint(values->EmulationPreventionBytePresent, 4, 4) |
      util_bitpack_uint(values->FixPrevMBSkipped, 7, 7) |
      util_bitpack_uint(values->FirstMBByteOffsetofSliceDataorSliceHeader, 16, 31);

   dw[2] =
      util_bitpack_uint(values->IntraPredictionErrorControl, 0, 0) |
      util_bitpack_uint(values->Intra8x84x4PredictionErrorConcealmentControl, 1, 1) |
      util_bitpack_uint(values->BSliceTemporalInterConcealmentMode, 4, 6) |
      util_bitpack_uint(values->BSliceSpatialInterConcealmentMode, 8, 10) |
      util_bitpack_uint(values->BSliceInterDirectTypeConcealmentMode, 12, 13) |
      util_bitpack_uint(values->BSliceConcealmentMode, 15, 15) |
      util_bitpack_uint(values->PSliceInterConcealmentMode, 16, 18) |
      util_bitpack_uint(values->PSliceConcealmentMode, 23, 23) |
      util_bitpack_uint(values->ConcealmentReferencePictureFieldBit, 24, 29) |
      util_bitpack_uint(values->ISliceConcealmentMode, 31, 31);
}

#define GFX9_INTERFACE_DESCRIPTOR_DATA_length      8
struct GFX9_INTERFACE_DESCRIPTOR_DATA {
   uint64_t                             KernelStartPointer;
   bool                                 SoftwareExceptionEnable;
   bool                                 MaskStackExceptionEnable;
   bool                                 IllegalOpcodeExceptionEnable;
   uint32_t                             FloatingPointMode;
#define IEEE754                                  0
#define Alternate                                1
   uint32_t                             ThreadPriority;
#define NormalPriority                           0
#define HighPriority                             1
   bool                                 SingleProgramFlow;
   uint32_t                             DenormMode;
#define Ftz                                      0
#define SetByKernel                              1
   uint32_t                             SamplerCount;
#define Nosamplersused                           0
#define Between1and4samplersused                 1
#define Between5and8samplersused                 2
#define Between9and12samplersused                3
#define Between13and16samplersused               4
   uint64_t                             SamplerStatePointer;
   uint32_t                             BindingTableEntryCount;
   uint64_t                             BindingTablePointer;
   uint32_t                             ConstantURBEntryReadOffset;
   uint32_t                             ConstantURBEntryReadLength;
   uint32_t                             NumberofThreadsinGPGPUThreadGroup;
   bool                                 GlobalBarrierEnable;
   uint32_t                             SharedLocalMemorySize;
#define Encodes0K                                0
#define Encodes1K                                1
#define Encodes2K                                2
#define Encodes4K                                3
#define Encodes8K                                4
#define Encodes16K                               5
#define Encodes32K                               6
#define Encodes64K                               7
   bool                                 BarrierEnable;
   uint32_t                             RoundingMode;
#define RTNE                                     0
#define RU                                       1
#define RD                                       2
#define RTZ                                      3
   uint32_t                             CrossThreadConstantDataReadLength;
};

static inline __attribute__((always_inline)) void
GFX9_INTERFACE_DESCRIPTOR_DATA_pack(__attribute__((unused)) __gen_user_data *data,
                                    __attribute__((unused)) void * restrict dst,
                                    __attribute__((unused)) const struct GFX9_INTERFACE_DESCRIPTOR_DATA * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      __gen_offset(values->KernelStartPointer, 6, 47);
   dw[0] = v0;
   dw[1] = v0 >> 32;

   dw[2] =
      util_bitpack_uint(values->SoftwareExceptionEnable, 7, 7) |
      util_bitpack_uint(values->MaskStackExceptionEnable, 11, 11) |
      util_bitpack_uint(values->IllegalOpcodeExceptionEnable, 13, 13) |
      util_bitpack_uint(values->FloatingPointMode, 16, 16) |
      util_bitpack_uint(values->ThreadPriority, 17, 17) |
      util_bitpack_uint(values->SingleProgramFlow, 18, 18) |
      util_bitpack_uint(values->DenormMode, 19, 19);

   dw[3] =
      util_bitpack_uint(values->SamplerCount, 2, 4) |
      __gen_offset(values->SamplerStatePointer, 5, 31);

   dw[4] =
      util_bitpack_uint(values->BindingTableEntryCount, 0, 4) |
      __gen_offset(values->BindingTablePointer, 5, 15);

   dw[5] =
      util_bitpack_uint(values->ConstantURBEntryReadOffset, 0, 15) |
      util_bitpack_uint(values->ConstantURBEntryReadLength, 16, 31);

   dw[6] =
      util_bitpack_uint(values->NumberofThreadsinGPGPUThreadGroup, 0, 9) |
      util_bitpack_uint(values->GlobalBarrierEnable, 15, 15) |
      util_bitpack_uint(values->SharedLocalMemorySize, 16, 20) |
      util_bitpack_uint(values->BarrierEnable, 21, 21) |
      util_bitpack_uint(values->RoundingMode, 22, 23);

   dw[7] =
      util_bitpack_uint(values->CrossThreadConstantDataReadLength, 0, 7);
}

#define GFX9_MFD_MPEG2_BSD_OBJECT_INLINE_DATA_DESCRIPTION_length      2
struct GFX9_MFD_MPEG2_BSD_OBJECT_INLINE_DATA_DESCRIPTION {
   uint32_t                             FirstMBBitOffset;
   bool                                 LastMB;
   bool                                 LastPicSlice;
   uint32_t                             SliceConcealmentType;
   uint32_t                             SliceConcealmentOverride;
   uint32_t                             MBCount;
   uint32_t                             SliceVerticalPosition;
   uint32_t                             SliceHorizontalPosition;
   uint32_t                             NextSliceHorizontalPosition;
   uint32_t                             NextSliceVerticalPosition;
   uint32_t                             QuantizerScaleCode;
};

static inline __attribute__((always_inline)) void
GFX9_MFD_MPEG2_BSD_OBJECT_INLINE_DATA_DESCRIPTION_pack(__attribute__((unused)) __gen_user_data *data,
                                                       __attribute__((unused)) void * restrict dst,
                                                       __attribute__((unused)) const struct GFX9_MFD_MPEG2_BSD_OBJECT_INLINE_DATA_DESCRIPTION * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->FirstMBBitOffset, 0, 2) |
      util_bitpack_uint(values->LastMB, 3, 3) |
      util_bitpack_uint(values->LastPicSlice, 5, 5) |
      util_bitpack_uint(values->SliceConcealmentType, 6, 6) |
      util_bitpack_uint(values->SliceConcealmentOverride, 7, 7) |
      util_bitpack_uint(values->MBCount, 8, 15) |
      util_bitpack_uint(values->SliceVerticalPosition, 16, 23) |
      util_bitpack_uint(values->SliceHorizontalPosition, 24, 31);

   dw[1] =
      util_bitpack_uint(values->NextSliceHorizontalPosition, 0, 7) |
      util_bitpack_uint(values->NextSliceVerticalPosition, 8, 16) |
      util_bitpack_uint(values->QuantizerScaleCode, 24, 28);
}

#define GFX9_MI_MATH_ALU_INSTRUCTION_length      1
struct GFX9_MI_MATH_ALU_INSTRUCTION {
   uint32_t                             Operand2;
#define MI_ALU_REG0                              0
#define MI_ALU_REG1                              1
#define MI_ALU_REG2                              2
#define MI_ALU_REG3                              3
#define MI_ALU_REG4                              4
#define MI_ALU_REG5                              5
#define MI_ALU_REG6                              6
#define MI_ALU_REG7                              7
#define MI_ALU_REG8                              8
#define MI_ALU_REG9                              9
#define MI_ALU_REG10                             10
#define MI_ALU_REG11                             11
#define MI_ALU_REG12                             12
#define MI_ALU_REG13                             13
#define MI_ALU_REG14                             14
#define MI_ALU_REG15                             15
#define MI_ALU_SRCA                              32
#define MI_ALU_SRCB                              33
#define MI_ALU_ACCU                              49
#define MI_ALU_ZF                                50
#define MI_ALU_CF                                51
   uint32_t                             Operand1;
#define MI_ALU_REG0                              0
#define MI_ALU_REG1                              1
#define MI_ALU_REG2                              2
#define MI_ALU_REG3                              3
#define MI_ALU_REG4                              4
#define MI_ALU_REG5                              5
#define MI_ALU_REG6                              6
#define MI_ALU_REG7                              7
#define MI_ALU_REG8                              8
#define MI_ALU_REG9                              9
#define MI_ALU_REG10                             10
#define MI_ALU_REG11                             11
#define MI_ALU_REG12                             12
#define MI_ALU_REG13                             13
#define MI_ALU_REG14                             14
#define MI_ALU_REG15                             15
#define MI_ALU_SRCA                              32
#define MI_ALU_SRCB                              33
#define MI_ALU_ACCU                              49
#define MI_ALU_ZF                                50
#define MI_ALU_CF                                51
   uint32_t                             ALUOpcode;
#define MI_ALU_NOOP                              0
#define MI_ALU_LOAD                              128
#define MI_ALU_LOADINV                           1152
#define MI_ALU_LOAD0                             129
#define MI_ALU_LOAD1                             1153
#define MI_ALU_ADD                               256
#define MI_ALU_SUB                               257
#define MI_ALU_AND                               258
#define MI_ALU_OR                                259
#define MI_ALU_XOR                               260
#define MI_ALU_STORE                             384
#define MI_ALU_STOREINV                          1408
};

static inline __attribute__((always_inline)) void
GFX9_MI_MATH_ALU_INSTRUCTION_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_MI_MATH_ALU_INSTRUCTION * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->Operand2, 0, 9) |
      util_bitpack_uint(values->Operand1, 10, 19) |
      util_bitpack_uint(values->ALUOpcode, 20, 31);
}

#define GFX9_PALETTE_ENTRY_length              1
struct GFX9_PALETTE_ENTRY {
   uint32_t                             Blue;
   uint32_t                             Green;
   uint32_t                             Red;
   uint32_t                             Alpha;
};

static inline __attribute__((always_inline)) void
GFX9_PALETTE_ENTRY_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_PALETTE_ENTRY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->Blue, 0, 7) |
      util_bitpack_uint(values->Green, 8, 15) |
      util_bitpack_uint(values->Red, 16, 23) |
      util_bitpack_uint(values->Alpha, 24, 31);
}

#define GFX9_RENDER_SURFACE_STATE_length      16
struct GFX9_RENDER_SURFACE_STATE {
   bool                                 CubeFaceEnablePositiveZ;
   bool                                 CubeFaceEnableNegativeZ;
   bool                                 CubeFaceEnablePositiveY;
   bool                                 CubeFaceEnableNegativeY;
   bool                                 CubeFaceEnablePositiveX;
   bool                                 CubeFaceEnableNegativeX;
   uint32_t                             MediaBoundaryPixelMode;
#define NORMAL_MODE                              0
#define PROGRESSIVE_FRAME                        2
#define INTERLACED_FRAME                         3
   uint32_t                             RenderCacheReadWriteMode;
#define WriteOnlyCache                           0
#define ReadWriteCache                           1
   bool                                 SamplerL2BypassModeDisable;
   uint32_t                             VerticalLineStrideOffset;
   uint32_t                             VerticalLineStride;
   uint32_t                             TileMode;
#define LINEAR                                   0
#define WMAJOR                                   1
#define XMAJOR                                   2
#define YMAJOR                                   3
   uint32_t                             SurfaceHorizontalAlignment;
#define HALIGN_4                                 1
#define HALIGN_8                                 2
#define HALIGN_16                                3
   uint32_t                             SurfaceVerticalAlignment;
#define VALIGN_4                                 1
#define VALIGN_8                                 2
#define VALIGN_16                                3
   uint32_t                             SurfaceFormat;
   bool                                 SurfaceArray;
   uint32_t                             SurfaceType;
#define SURFTYPE_1D                              0
#define SURFTYPE_2D                              1
#define SURFTYPE_3D                              2
#define SURFTYPE_CUBE                            3
#define SURFTYPE_BUFFER                          4
#define SURFTYPE_STRBUF                          5
#define SURFTYPE_NULL                            7
   uint32_t                             SurfaceQPitch;
   float                                BaseMipLevel;
   uint32_t                             MOCS;
   uint32_t                             Width;
   uint32_t                             Height;
   uint32_t                             SurfacePitch;
   uint32_t                             Depth;
   uint32_t                             MultisamplePositionPaletteIndex;
   uint32_t                             NumberofMultisamples;
#define MULTISAMPLECOUNT_1                       0
#define MULTISAMPLECOUNT_2                       1
#define MULTISAMPLECOUNT_4                       2
#define MULTISAMPLECOUNT_8                       3
#define MULTISAMPLECOUNT_16                      4
   uint32_t                             MultisampledSurfaceStorageFormat;
#define MSFMT_MSS                                0
#define MSFMT_DEPTH_STENCIL                      1
   uint32_t                             RenderTargetViewExtent;
   uint32_t                             MinimumArrayElement;
   uint32_t                             RenderTargetAndSampleUnormRotation;
#define _0DEG                                    0
#define _90DEG                                   1
#define _180DEG                                  2
#define _270DEG                                  3
   uint32_t                             MIPCountLOD;
   uint32_t                             SurfaceMinLOD;
   uint32_t                             MipTailStartLOD;
   uint32_t                             CoherencyType;
#define GPUcoherent                              0
#define IAcoherent                               1
   uint32_t                             TiledResourceMode;
#define NONE                                     0
#define _4KB                                     1
#define _64KB                                    2
#define TILEYF                                   1
#define TILEYS                                   2
   bool                                 EWADisableForCube;
   uint32_t                             YOffset;
   uint32_t                             XOffset;
   uint32_t                             AuxiliarySurfaceMode;
#define AUX_NONE                                 0
#define AUX_CCS_D                                1
#define AUX_APPEND                               2
#define AUX_HIZ                                  3
#define AUX_CCS_E                                5
   uint32_t                             YOffsetforUorUVPlane;
   uint32_t                             AuxiliarySurfacePitch;
   uint32_t                             AuxiliarySurfaceQPitch;
   uint32_t                             XOffsetforUorUVPlane;
   bool                                 SeparateUVPlaneEnable;
   float                                ResourceMinLOD;
   enum GFX9_ShaderChannelSelect        ShaderChannelSelectAlpha;
   enum GFX9_ShaderChannelSelect        ShaderChannelSelectBlue;
   enum GFX9_ShaderChannelSelect        ShaderChannelSelectGreen;
   enum GFX9_ShaderChannelSelect        ShaderChannelSelectRed;
   bool                                 MemoryCompressionEnable;
   uint32_t                             MemoryCompressionMode;
#define Horizontal                               0
#define Vertical                                 1
   __gen_address_type                   SurfaceBaseAddress;
   uint32_t                             QuiltWidth;
   uint32_t                             QuiltHeight;
   __gen_address_type                   AuxiliarySurfaceBaseAddress;
   uint32_t                             AuxiliaryTableIndexforMediaCompressedSurface;
   uint32_t                             YOffsetforVPlane;
   uint32_t                             XOffsetforVPlane;
   float                                HierarchicalDepthClearValue;
   int32_t                              RedClearColor;
   int32_t                              GreenClearColor;
   int32_t                              BlueClearColor;
   int32_t                              AlphaClearColor;
};

static inline __attribute__((always_inline)) void
GFX9_RENDER_SURFACE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_RENDER_SURFACE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->CubeFaceEnablePositiveZ, 0, 0) |
      util_bitpack_uint(values->CubeFaceEnableNegativeZ, 1, 1) |
      util_bitpack_uint(values->CubeFaceEnablePositiveY, 2, 2) |
      util_bitpack_uint(values->CubeFaceEnableNegativeY, 3, 3) |
      util_bitpack_uint(values->CubeFaceEnablePositiveX, 4, 4) |
      util_bitpack_uint(values->CubeFaceEnableNegativeX, 5, 5) |
      util_bitpack_uint(values->MediaBoundaryPixelMode, 6, 7) |
      util_bitpack_uint(values->RenderCacheReadWriteMode, 8, 8) |
      util_bitpack_uint(values->SamplerL2BypassModeDisable, 9, 9) |
      util_bitpack_uint(values->VerticalLineStrideOffset, 10, 10) |
      util_bitpack_uint(values->VerticalLineStride, 11, 11) |
      util_bitpack_uint(values->TileMode, 12, 13) |
      util_bitpack_uint(values->SurfaceHorizontalAlignment, 14, 15) |
      util_bitpack_uint(values->SurfaceVerticalAlignment, 16, 17) |
      util_bitpack_uint(values->SurfaceFormat, 18, 27) |
      util_bitpack_uint(values->SurfaceArray, 28, 28) |
      util_bitpack_uint(values->SurfaceType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->SurfaceQPitch, 0, 14) |
      util_bitpack_ufixed(values->BaseMipLevel, 19, 23, 1) |
      util_bitpack_uint_nonzero(values->MOCS, 24, 30);

   dw[2] =
      util_bitpack_uint(values->Width, 0, 13) |
      util_bitpack_uint(values->Height, 16, 29);

   dw[3] =
      util_bitpack_uint(values->SurfacePitch, 0, 17) |
      util_bitpack_uint(values->Depth, 21, 31);

   dw[4] =
      util_bitpack_uint(values->MultisamplePositionPaletteIndex, 0, 2) |
      util_bitpack_uint(values->NumberofMultisamples, 3, 5) |
      util_bitpack_uint(values->MultisampledSurfaceStorageFormat, 6, 6) |
      util_bitpack_uint(values->RenderTargetViewExtent, 7, 17) |
      util_bitpack_uint(values->MinimumArrayElement, 18, 28) |
      util_bitpack_uint(values->RenderTargetAndSampleUnormRotation, 29, 30);

   dw[5] =
      util_bitpack_uint(values->MIPCountLOD, 0, 3) |
      util_bitpack_uint(values->SurfaceMinLOD, 4, 7) |
      util_bitpack_uint(values->MipTailStartLOD, 8, 11) |
      util_bitpack_uint(values->CoherencyType, 14, 14) |
      util_bitpack_uint(values->TiledResourceMode, 18, 19) |
      util_bitpack_uint(values->EWADisableForCube, 20, 20) |
      util_bitpack_uint(values->YOffset, 21, 23) |
      util_bitpack_uint(values->XOffset, 25, 31);

   dw[6] =
      util_bitpack_uint(values->AuxiliarySurfaceMode, 0, 2) |
      util_bitpack_uint(values->YOffsetforUorUVPlane, 0, 13) |
      util_bitpack_uint(values->AuxiliarySurfacePitch, 3, 11) |
      util_bitpack_uint(values->AuxiliarySurfaceQPitch, 16, 30) |
      util_bitpack_uint(values->XOffsetforUorUVPlane, 16, 29) |
      util_bitpack_uint(values->SeparateUVPlaneEnable, 31, 31);

   dw[7] =
      util_bitpack_ufixed(values->ResourceMinLOD, 0, 11, 8) |
      util_bitpack_uint(values->ShaderChannelSelectAlpha, 16, 18) |
      util_bitpack_uint(values->ShaderChannelSelectBlue, 19, 21) |
      util_bitpack_uint(values->ShaderChannelSelectGreen, 22, 24) |
      util_bitpack_uint(values->ShaderChannelSelectRed, 25, 27) |
      util_bitpack_uint(values->MemoryCompressionEnable, 30, 30) |
      util_bitpack_uint(values->MemoryCompressionMode, 31, 31);

   const uint64_t v8_address =
      __gen_address(data, &dw[8], values->SurfaceBaseAddress, 0, 0, 63);
   dw[8] = v8_address;
   dw[9] = v8_address >> 32;

   const uint64_t v10 =
      util_bitpack_uint(values->QuiltWidth, 0, 4) |
      util_bitpack_uint(values->QuiltHeight, 5, 9) |
      util_bitpack_uint(values->AuxiliaryTableIndexforMediaCompressedSurface, 21, 31) |
      util_bitpack_uint(values->YOffsetforVPlane, 32, 45) |
      util_bitpack_uint(values->XOffsetforVPlane, 48, 61);
   const uint64_t v10_address =
      __gen_address(data, &dw[10], values->AuxiliarySurfaceBaseAddress, v10, 12, 63);
   dw[10] = v10_address;
   dw[11] = (v10_address >> 32) | (v10 >> 32);

   dw[12] =
      util_bitpack_float(values->HierarchicalDepthClearValue) |
      util_bitpack_sint(values->RedClearColor, 0, 31);

   dw[13] =
      util_bitpack_sint(values->GreenClearColor, 0, 31);

   dw[14] =
      util_bitpack_sint(values->BlueClearColor, 0, 31);

   dw[15] =
      util_bitpack_sint(values->AlphaClearColor, 0, 31);
}

#define GFX9_ROUNDINGPRECISIONTABLE_3_BITS_length      1
struct GFX9_ROUNDINGPRECISIONTABLE_3_BITS {
   uint32_t                             RoundingPrecision;
#define _116                                     0
#define _216                                     1
#define _316                                     2
#define _416                                     3
#define _516                                     4
#define _616                                     5
#define _716                                     6
#define _816                                     7
};

static inline __attribute__((always_inline)) void
GFX9_ROUNDINGPRECISIONTABLE_3_BITS_pack(__attribute__((unused)) __gen_user_data *data,
                                        __attribute__((unused)) void * restrict dst,
                                        __attribute__((unused)) const struct GFX9_ROUNDINGPRECISIONTABLE_3_BITS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->RoundingPrecision, 0, 2);
}

#define GFX9_SAMPLER_BORDER_COLOR_STATE_length      4
struct GFX9_SAMPLER_BORDER_COLOR_STATE {
   float                                BorderColorFloatRed;
   uint32_t                             BorderColor32bitRed;
   float                                BorderColorFloatGreen;
   uint32_t                             BorderColor32bitGreen;
   float                                BorderColorFloatBlue;
   uint32_t                             BorderColor32bitBlue;
   float                                BorderColorFloatAlpha;
   uint32_t                             BorderColor32bitAlpha;
};

static inline __attribute__((always_inline)) void
GFX9_SAMPLER_BORDER_COLOR_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                     __attribute__((unused)) void * restrict dst,
                                     __attribute__((unused)) const struct GFX9_SAMPLER_BORDER_COLOR_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_float(values->BorderColorFloatRed) |
      util_bitpack_uint(values->BorderColor32bitRed, 0, 31);

   dw[1] =
      util_bitpack_float(values->BorderColorFloatGreen) |
      util_bitpack_uint(values->BorderColor32bitGreen, 0, 31);

   dw[2] =
      util_bitpack_float(values->BorderColorFloatBlue) |
      util_bitpack_uint(values->BorderColor32bitBlue, 0, 31);

   dw[3] =
      util_bitpack_float(values->BorderColorFloatAlpha) |
      util_bitpack_uint(values->BorderColor32bitAlpha, 0, 31);
}

#define GFX9_SAMPLER_STATE_length              4
struct GFX9_SAMPLER_STATE {
   uint32_t                             AnisotropicAlgorithm;
#define LEGACY                                   0
#define EWAApproximation                         1
   float                                TextureLODBias;
   uint32_t                             MinModeFilter;
#define MAPFILTER_NEAREST                        0
#define MAPFILTER_LINEAR                         1
#define MAPFILTER_ANISOTROPIC                    2
#define MAPFILTER_MONO                           6
   uint32_t                             MagModeFilter;
#define MAPFILTER_NEAREST                        0
#define MAPFILTER_LINEAR                         1
#define MAPFILTER_ANISOTROPIC                    2
#define MAPFILTER_MONO                           6
   uint32_t                             MipModeFilter;
#define MIPFILTER_NONE                           0
#define MIPFILTER_NEAREST                        1
#define MIPFILTER_LINEAR                         3
   uint32_t                             CoarseLODQualityMode;
   uint32_t                             LODPreClampMode;
#define CLAMP_MODE_NONE                          0
#define CLAMP_MODE_OGL                           2
   uint32_t                             TextureBorderColorMode;
#define DX10OGL                                  0
#define DX9                                      1
   bool                                 SamplerDisable;
   uint32_t                             CubeSurfaceControlMode;
#define PROGRAMMED                               0
#define OVERRIDE                                 1
   uint32_t                             ShadowFunction;
#define PREFILTEROP_ALWAYS                       0
#define PREFILTEROP_NEVER                        1
#define PREFILTEROP_LESS                         2
#define PREFILTEROP_EQUAL                        3
#define PREFILTEROP_LEQUAL                       4
#define PREFILTEROP_GREATER                      5
#define PREFILTEROP_NOTEQUAL                     6
#define PREFILTEROP_GEQUAL                       7
   uint32_t                             ChromaKeyMode;
#define KEYFILTER_KILL_ON_ANY_MATCH              0
#define KEYFILTER_REPLACE_BLACK                  1
   uint32_t                             ChromaKeyIndex;
   bool                                 ChromaKeyEnable;
   float                                MaxLOD;
   float                                MinLOD;
   uint32_t                             LODClampMagnificationMode;
#define MIPNONE                                  0
#define MIPFILTER                                1
   uint64_t                             BorderColorPointer;
   enum GFX9_TextureCoordinateMode      TCZAddressControlMode;
   enum GFX9_TextureCoordinateMode      TCYAddressControlMode;
   enum GFX9_TextureCoordinateMode      TCXAddressControlMode;
   bool                                 ReductionTypeEnable;
   bool                                 NonnormalizedCoordinateEnable;
   uint32_t                             TrilinearFilterQuality;
#define FULL                                     0
#define HIGH                                     1
#define MED                                      2
#define LOW                                      3
   bool                                 RAddressMinFilterRoundingEnable;
   bool                                 RAddressMagFilterRoundingEnable;
   bool                                 VAddressMinFilterRoundingEnable;
   bool                                 VAddressMagFilterRoundingEnable;
   bool                                 UAddressMinFilterRoundingEnable;
   bool                                 UAddressMagFilterRoundingEnable;
   uint32_t                             MaximumAnisotropy;
#define RATIO21                                  0
#define RATIO41                                  1
#define RATIO61                                  2
#define RATIO81                                  3
#define RATIO101                                 4
#define RATIO121                                 5
#define RATIO141                                 6
#define RATIO161                                 7
   uint32_t                             ReductionType;
#define STD_FILTER                               0
#define COMPARISON                               1
#define MINIMUM                                  2
#define MAXIMUM                                  3
};

static inline __attribute__((always_inline)) void
GFX9_SAMPLER_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_SAMPLER_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->AnisotropicAlgorithm, 0, 0) |
      util_bitpack_sfixed(values->TextureLODBias, 1, 13, 8) |
      util_bitpack_uint(values->MinModeFilter, 14, 16) |
      util_bitpack_uint(values->MagModeFilter, 17, 19) |
      util_bitpack_uint(values->MipModeFilter, 20, 21) |
      util_bitpack_uint(values->CoarseLODQualityMode, 22, 26) |
      util_bitpack_uint(values->LODPreClampMode, 27, 28) |
      util_bitpack_uint(values->TextureBorderColorMode, 29, 29) |
      util_bitpack_uint(values->SamplerDisable, 31, 31);

   dw[1] =
      util_bitpack_uint(values->CubeSurfaceControlMode, 0, 0) |
      util_bitpack_uint(values->ShadowFunction, 1, 3) |
      util_bitpack_uint(values->ChromaKeyMode, 4, 4) |
      util_bitpack_uint(values->ChromaKeyIndex, 5, 6) |
      util_bitpack_uint(values->ChromaKeyEnable, 7, 7) |
      util_bitpack_ufixed(values->MaxLOD, 8, 19, 8) |
      util_bitpack_ufixed(values->MinLOD, 20, 31, 8);

   dw[2] =
      util_bitpack_uint(values->LODClampMagnificationMode, 0, 0) |
      __gen_offset(values->BorderColorPointer, 6, 23);

   dw[3] =
      util_bitpack_uint(values->TCZAddressControlMode, 0, 2) |
      util_bitpack_uint(values->TCYAddressControlMode, 3, 5) |
      util_bitpack_uint(values->TCXAddressControlMode, 6, 8) |
      util_bitpack_uint(values->ReductionTypeEnable, 9, 9) |
      util_bitpack_uint(values->NonnormalizedCoordinateEnable, 10, 10) |
      util_bitpack_uint(values->TrilinearFilterQuality, 11, 12) |
      util_bitpack_uint(values->RAddressMinFilterRoundingEnable, 13, 13) |
      util_bitpack_uint(values->RAddressMagFilterRoundingEnable, 14, 14) |
      util_bitpack_uint(values->VAddressMinFilterRoundingEnable, 15, 15) |
      util_bitpack_uint(values->VAddressMagFilterRoundingEnable, 16, 16) |
      util_bitpack_uint(values->UAddressMinFilterRoundingEnable, 17, 17) |
      util_bitpack_uint(values->UAddressMagFilterRoundingEnable, 18, 18) |
      util_bitpack_uint(values->MaximumAnisotropy, 19, 21) |
      util_bitpack_uint(values->ReductionType, 22, 23);
}

#define GFX9_SAMPLER_STATE_8X8_AVS_COEFFICIENTS_length      8
struct GFX9_SAMPLER_STATE_8X8_AVS_COEFFICIENTS {
   float                                Table0FilterCoefficient[4];
   float                                Table1FilterCoefficient0[4];
   float                                Table1FilterCoefficient1[4];
};

static inline __attribute__((always_inline)) void
GFX9_SAMPLER_STATE_8X8_AVS_COEFFICIENTS_pack(__attribute__((unused)) __gen_user_data *data,
                                             __attribute__((unused)) void * restrict dst,
                                             __attribute__((unused)) const struct GFX9_SAMPLER_STATE_8X8_AVS_COEFFICIENTS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_sfixed(values->Table0FilterCoefficient[0], 0, 7, 6) |
      util_bitpack_sfixed(values->Table0FilterCoefficient[1], 8, 15, 6) |
      util_bitpack_sfixed(values->Table0FilterCoefficient[2], 16, 23, 6) |
      util_bitpack_sfixed(values->Table0FilterCoefficient[3], 24, 31, 6) |
      util_bitpack_sfixed(values->Table1FilterCoefficient0[0], 0, 7, 6) |
      util_bitpack_sfixed(values->Table1FilterCoefficient1[0], 8, 15, 6);

   dw[1] =
      util_bitpack_sfixed(values->Table1FilterCoefficient0[1], 0, 7, 6) |
      util_bitpack_sfixed(values->Table1FilterCoefficient1[1], 8, 15, 6);

   dw[2] =
      util_bitpack_sfixed(values->Table1FilterCoefficient0[2], 0, 7, 6) |
      util_bitpack_sfixed(values->Table1FilterCoefficient1[2], 8, 15, 6);

   dw[3] =
      util_bitpack_sfixed(values->Table1FilterCoefficient0[3], 0, 7, 6) |
      util_bitpack_sfixed(values->Table1FilterCoefficient1[3], 8, 15, 6);

   dw[4] = 0;

   dw[5] = 0;

   dw[6] = 0;

   dw[7] = 0;
}

#define GFX9_SCISSOR_RECT_length               2
struct GFX9_SCISSOR_RECT {
   uint32_t                             ScissorRectangleXMin;
   uint32_t                             ScissorRectangleYMin;
   uint32_t                             ScissorRectangleXMax;
   uint32_t                             ScissorRectangleYMax;
};

static inline __attribute__((always_inline)) void
GFX9_SCISSOR_RECT_pack(__attribute__((unused)) __gen_user_data *data,
                       __attribute__((unused)) void * restrict dst,
                       __attribute__((unused)) const struct GFX9_SCISSOR_RECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->ScissorRectangleXMin, 0, 15) |
      util_bitpack_uint(values->ScissorRectangleYMin, 16, 31);

   dw[1] =
      util_bitpack_uint(values->ScissorRectangleXMax, 0, 15) |
      util_bitpack_uint(values->ScissorRectangleYMax, 16, 31);
}

#define GFX9_SFC_AVS_CHROMA_COEFF_TABLE_BODY_length     64
struct GFX9_SFC_AVS_CHROMA_COEFF_TABLE_BODY {
   float                                Table1XFilterCoefficientn2;
   float                                Table1YFilterCoefficientn2;
   float                                Table1XFilterCoefficientn3;
   float                                Table1YFilterCoefficientn3;
   float                                Table1XFilterCoefficientn4;
   float                                Table1YFilterCoefficientn4;
   float                                Table1XFilterCoefficientn5;
   float                                Table1YFilterCoefficientn5;
   uint64_t                             FilterCoefficients[31];
};

static inline __attribute__((always_inline)) void
GFX9_SFC_AVS_CHROMA_COEFF_TABLE_BODY_pack(__attribute__((unused)) __gen_user_data *data,
                                          __attribute__((unused)) void * restrict dst,
                                          __attribute__((unused)) const struct GFX9_SFC_AVS_CHROMA_COEFF_TABLE_BODY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_sfixed(values->Table1XFilterCoefficientn2, 0, 7, 6) |
      util_bitpack_sfixed(values->Table1YFilterCoefficientn2, 8, 15, 6) |
      util_bitpack_sfixed(values->Table1XFilterCoefficientn3, 16, 23, 6) |
      util_bitpack_sfixed(values->Table1YFilterCoefficientn3, 24, 31, 6);

   dw[1] =
      util_bitpack_sfixed(values->Table1XFilterCoefficientn4, 0, 7, 6) |
      util_bitpack_sfixed(values->Table1YFilterCoefficientn4, 8, 15, 6) |
      util_bitpack_sfixed(values->Table1XFilterCoefficientn5, 16, 23, 6) |
      util_bitpack_sfixed(values->Table1YFilterCoefficientn5, 24, 31, 6);

   const uint64_t v2 =
      util_bitpack_uint(values->FilterCoefficients[0], 0, 63);
   dw[2] = v2;
   dw[3] = v2 >> 32;

   const uint64_t v4 =
      util_bitpack_uint(values->FilterCoefficients[1], 0, 63);
   dw[4] = v4;
   dw[5] = v4 >> 32;

   const uint64_t v6 =
      util_bitpack_uint(values->FilterCoefficients[2], 0, 63);
   dw[6] = v6;
   dw[7] = v6 >> 32;

   const uint64_t v8 =
      util_bitpack_uint(values->FilterCoefficients[3], 0, 63);
   dw[8] = v8;
   dw[9] = v8 >> 32;

   const uint64_t v10 =
      util_bitpack_uint(values->FilterCoefficients[4], 0, 63);
   dw[10] = v10;
   dw[11] = v10 >> 32;

   const uint64_t v12 =
      util_bitpack_uint(values->FilterCoefficients[5], 0, 63);
   dw[12] = v12;
   dw[13] = v12 >> 32;

   const uint64_t v14 =
      util_bitpack_uint(values->FilterCoefficients[6], 0, 63);
   dw[14] = v14;
   dw[15] = v14 >> 32;

   const uint64_t v16 =
      util_bitpack_uint(values->FilterCoefficients[7], 0, 63);
   dw[16] = v16;
   dw[17] = v16 >> 32;

   const uint64_t v18 =
      util_bitpack_uint(values->FilterCoefficients[8], 0, 63);
   dw[18] = v18;
   dw[19] = v18 >> 32;

   const uint64_t v20 =
      util_bitpack_uint(values->FilterCoefficients[9], 0, 63);
   dw[20] = v20;
   dw[21] = v20 >> 32;

   const uint64_t v22 =
      util_bitpack_uint(values->FilterCoefficients[10], 0, 63);
   dw[22] = v22;
   dw[23] = v22 >> 32;

   const uint64_t v24 =
      util_bitpack_uint(values->FilterCoefficients[11], 0, 63);
   dw[24] = v24;
   dw[25] = v24 >> 32;

   const uint64_t v26 =
      util_bitpack_uint(values->FilterCoefficients[12], 0, 63);
   dw[26] = v26;
   dw[27] = v26 >> 32;

   const uint64_t v28 =
      util_bitpack_uint(values->FilterCoefficients[13], 0, 63);
   dw[28] = v28;
   dw[29] = v28 >> 32;

   const uint64_t v30 =
      util_bitpack_uint(values->FilterCoefficients[14], 0, 63);
   dw[30] = v30;
   dw[31] = v30 >> 32;

   const uint64_t v32 =
      util_bitpack_uint(values->FilterCoefficients[15], 0, 63);
   dw[32] = v32;
   dw[33] = v32 >> 32;

   const uint64_t v34 =
      util_bitpack_uint(values->FilterCoefficients[16], 0, 63);
   dw[34] = v34;
   dw[35] = v34 >> 32;

   const uint64_t v36 =
      util_bitpack_uint(values->FilterCoefficients[17], 0, 63);
   dw[36] = v36;
   dw[37] = v36 >> 32;

   const uint64_t v38 =
      util_bitpack_uint(values->FilterCoefficients[18], 0, 63);
   dw[38] = v38;
   dw[39] = v38 >> 32;

   const uint64_t v40 =
      util_bitpack_uint(values->FilterCoefficients[19], 0, 63);
   dw[40] = v40;
   dw[41] = v40 >> 32;

   const uint64_t v42 =
      util_bitpack_uint(values->FilterCoefficients[20], 0, 63);
   dw[42] = v42;
   dw[43] = v42 >> 32;

   const uint64_t v44 =
      util_bitpack_uint(values->FilterCoefficients[21], 0, 63);
   dw[44] = v44;
   dw[45] = v44 >> 32;

   const uint64_t v46 =
      util_bitpack_uint(values->FilterCoefficients[22], 0, 63);
   dw[46] = v46;
   dw[47] = v46 >> 32;

   const uint64_t v48 =
      util_bitpack_uint(values->FilterCoefficients[23], 0, 63);
   dw[48] = v48;
   dw[49] = v48 >> 32;

   const uint64_t v50 =
      util_bitpack_uint(values->FilterCoefficients[24], 0, 63);
   dw[50] = v50;
   dw[51] = v50 >> 32;

   const uint64_t v52 =
      util_bitpack_uint(values->FilterCoefficients[25], 0, 63);
   dw[52] = v52;
   dw[53] = v52 >> 32;

   const uint64_t v54 =
      util_bitpack_uint(values->FilterCoefficients[26], 0, 63);
   dw[54] = v54;
   dw[55] = v54 >> 32;

   const uint64_t v56 =
      util_bitpack_uint(values->FilterCoefficients[27], 0, 63);
   dw[56] = v56;
   dw[57] = v56 >> 32;

   const uint64_t v58 =
      util_bitpack_uint(values->FilterCoefficients[28], 0, 63);
   dw[58] = v58;
   dw[59] = v58 >> 32;

   const uint64_t v60 =
      util_bitpack_uint(values->FilterCoefficients[29], 0, 63);
   dw[60] = v60;
   dw[61] = v60 >> 32;

   const uint64_t v62 =
      util_bitpack_uint(values->FilterCoefficients[30], 0, 63);
   dw[62] = v62;
   dw[63] = v62 >> 32;
}

#define GFX9_SFC_AVS_LUMA_COEFF_TABLE_BODY_length    128
struct GFX9_SFC_AVS_LUMA_COEFF_TABLE_BODY {
   float                                Table0XFilterCoefficientn0;
   float                                Table0YFilterCoefficientn0;
   float                                Table0XFilterCoefficientn1;
   float                                Table0YFilterCoefficientn1;
   float                                Table0XFilterCoefficientn2;
   float                                Table0YFilterCoefficientn2;
   float                                Table0XFilterCoefficientn3;
   float                                Table0YFilterCoefficientn3;
   float                                Table0XFilterCoefficientn4;
   float                                Table0YFilterCoefficientn4;
   float                                Table0XFilterCoefficientn5;
   float                                Table0YFilterCoefficientn5;
   float                                Table0XFilterCoefficientn6;
   float                                Table0YFilterCoefficientn6;
   float                                Table0XFilterCoefficientn7;
   float                                Table0YFilterCoefficientn7;
   uint64_t                             FilterCoefficients[31];
};

static inline __attribute__((always_inline)) void
GFX9_SFC_AVS_LUMA_COEFF_TABLE_BODY_pack(__attribute__((unused)) __gen_user_data *data,
                                        __attribute__((unused)) void * restrict dst,
                                        __attribute__((unused)) const struct GFX9_SFC_AVS_LUMA_COEFF_TABLE_BODY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_sfixed(values->Table0XFilterCoefficientn0, 0, 7, 6) |
      util_bitpack_sfixed(values->Table0YFilterCoefficientn0, 8, 15, 6) |
      util_bitpack_sfixed(values->Table0XFilterCoefficientn1, 16, 23, 6) |
      util_bitpack_sfixed(values->Table0YFilterCoefficientn1, 24, 31, 6);

   dw[1] =
      util_bitpack_sfixed(values->Table0XFilterCoefficientn2, 0, 7, 6) |
      util_bitpack_sfixed(values->Table0YFilterCoefficientn2, 8, 15, 6) |
      util_bitpack_sfixed(values->Table0XFilterCoefficientn3, 16, 23, 6) |
      util_bitpack_sfixed(values->Table0YFilterCoefficientn3, 24, 31, 6);

   dw[2] =
      util_bitpack_sfixed(values->Table0XFilterCoefficientn4, 0, 7, 6) |
      util_bitpack_sfixed(values->Table0YFilterCoefficientn4, 8, 15, 6) |
      util_bitpack_sfixed(values->Table0XFilterCoefficientn5, 16, 23, 6) |
      util_bitpack_sfixed(values->Table0YFilterCoefficientn5, 24, 31, 6);

   dw[3] =
      util_bitpack_sfixed(values->Table0XFilterCoefficientn6, 0, 7, 6) |
      util_bitpack_sfixed(values->Table0YFilterCoefficientn6, 8, 15, 6) |
      util_bitpack_sfixed(values->Table0XFilterCoefficientn7, 16, 23, 6) |
      util_bitpack_sfixed(values->Table0YFilterCoefficientn7, 24, 31, 6);

   const uint64_t v4 =
      util_bitpack_uint(values->FilterCoefficients[0], 0, 127);
   dw[4] = v4;
   dw[5] = v4 >> 32;

   const uint64_t v8 =
      util_bitpack_uint(values->FilterCoefficients[1], 0, 127);
   dw[8] = v8;
   dw[9] = v8 >> 32;

   const uint64_t v12 =
      util_bitpack_uint(values->FilterCoefficients[2], 0, 127);
   dw[12] = v12;
   dw[13] = v12 >> 32;

   const uint64_t v16 =
      util_bitpack_uint(values->FilterCoefficients[3], 0, 127);
   dw[16] = v16;
   dw[17] = v16 >> 32;

   const uint64_t v20 =
      util_bitpack_uint(values->FilterCoefficients[4], 0, 127);
   dw[20] = v20;
   dw[21] = v20 >> 32;

   const uint64_t v24 =
      util_bitpack_uint(values->FilterCoefficients[5], 0, 127);
   dw[24] = v24;
   dw[25] = v24 >> 32;

   const uint64_t v28 =
      util_bitpack_uint(values->FilterCoefficients[6], 0, 127);
   dw[28] = v28;
   dw[29] = v28 >> 32;

   const uint64_t v32 =
      util_bitpack_uint(values->FilterCoefficients[7], 0, 127);
   dw[32] = v32;
   dw[33] = v32 >> 32;

   const uint64_t v36 =
      util_bitpack_uint(values->FilterCoefficients[8], 0, 127);
   dw[36] = v36;
   dw[37] = v36 >> 32;

   const uint64_t v40 =
      util_bitpack_uint(values->FilterCoefficients[9], 0, 127);
   dw[40] = v40;
   dw[41] = v40 >> 32;

   const uint64_t v44 =
      util_bitpack_uint(values->FilterCoefficients[10], 0, 127);
   dw[44] = v44;
   dw[45] = v44 >> 32;

   const uint64_t v48 =
      util_bitpack_uint(values->FilterCoefficients[11], 0, 127);
   dw[48] = v48;
   dw[49] = v48 >> 32;

   const uint64_t v52 =
      util_bitpack_uint(values->FilterCoefficients[12], 0, 127);
   dw[52] = v52;
   dw[53] = v52 >> 32;

   const uint64_t v56 =
      util_bitpack_uint(values->FilterCoefficients[13], 0, 127);
   dw[56] = v56;
   dw[57] = v56 >> 32;

   const uint64_t v60 =
      util_bitpack_uint(values->FilterCoefficients[14], 0, 127);
   dw[60] = v60;
   dw[61] = v60 >> 32;

   const uint64_t v64 =
      util_bitpack_uint(values->FilterCoefficients[15], 0, 127);
   dw[64] = v64;
   dw[65] = v64 >> 32;

   const uint64_t v68 =
      util_bitpack_uint(values->FilterCoefficients[16], 0, 127);
   dw[68] = v68;
   dw[69] = v68 >> 32;

   const uint64_t v72 =
      util_bitpack_uint(values->FilterCoefficients[17], 0, 127);
   dw[72] = v72;
   dw[73] = v72 >> 32;

   const uint64_t v76 =
      util_bitpack_uint(values->FilterCoefficients[18], 0, 127);
   dw[76] = v76;
   dw[77] = v76 >> 32;

   const uint64_t v80 =
      util_bitpack_uint(values->FilterCoefficients[19], 0, 127);
   dw[80] = v80;
   dw[81] = v80 >> 32;

   const uint64_t v84 =
      util_bitpack_uint(values->FilterCoefficients[20], 0, 127);
   dw[84] = v84;
   dw[85] = v84 >> 32;

   const uint64_t v88 =
      util_bitpack_uint(values->FilterCoefficients[21], 0, 127);
   dw[88] = v88;
   dw[89] = v88 >> 32;

   const uint64_t v92 =
      util_bitpack_uint(values->FilterCoefficients[22], 0, 127);
   dw[92] = v92;
   dw[93] = v92 >> 32;

   const uint64_t v96 =
      util_bitpack_uint(values->FilterCoefficients[23], 0, 127);
   dw[96] = v96;
   dw[97] = v96 >> 32;

   const uint64_t v100 =
      util_bitpack_uint(values->FilterCoefficients[24], 0, 127);
   dw[100] = v100;
   dw[101] = v100 >> 32;

   const uint64_t v104 =
      util_bitpack_uint(values->FilterCoefficients[25], 0, 127);
   dw[104] = v104;
   dw[105] = v104 >> 32;

   const uint64_t v108 =
      util_bitpack_uint(values->FilterCoefficients[26], 0, 127);
   dw[108] = v108;
   dw[109] = v108 >> 32;

   const uint64_t v112 =
      util_bitpack_uint(values->FilterCoefficients[27], 0, 127);
   dw[112] = v112;
   dw[113] = v112 >> 32;

   const uint64_t v116 =
      util_bitpack_uint(values->FilterCoefficients[28], 0, 127);
   dw[116] = v116;
   dw[117] = v116 >> 32;

   const uint64_t v120 =
      util_bitpack_uint(values->FilterCoefficients[29], 0, 127);
   dw[120] = v120;
   dw[121] = v120 >> 32;

   const uint64_t v124 =
      util_bitpack_uint(values->FilterCoefficients[30], 0, 127);
   dw[124] = v124;
   dw[125] = v124 >> 32;
}

#define GFX9_SFC_AVS_STATE_BODY_length         2
struct GFX9_SFC_AVS_STATE_BODY {
   uint32_t                             TransitionAreawith8Pixels;
   uint32_t                             TransitionAreawith4Pixels;
   uint32_t                             SharpnessLevel;
   uint32_t                             MaxDerivative8Pixels;
   uint32_t                             MaxDerivative4Pixels;
};

static inline __attribute__((always_inline)) void
GFX9_SFC_AVS_STATE_BODY_pack(__attribute__((unused)) __gen_user_data *data,
                             __attribute__((unused)) void * restrict dst,
                             __attribute__((unused)) const struct GFX9_SFC_AVS_STATE_BODY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->TransitionAreawith8Pixels, 0, 2) |
      util_bitpack_uint(values->TransitionAreawith4Pixels, 4, 6) |
      util_bitpack_uint(values->SharpnessLevel, 24, 31);

   dw[1] =
      util_bitpack_uint(values->MaxDerivative8Pixels, 0, 7) |
      util_bitpack_uint(values->MaxDerivative4Pixels, 16, 23);
}

#define GFX9_SFC_IEF_STATE_BODY_length        23
struct GFX9_SFC_IEF_STATE_BODY {
   uint32_t                             GainFactor;
   uint32_t                             WeakEdgeThreshold;
   uint32_t                             StrongEdgeThreshold;
   float                                R3xCoefficient;
   float                                R3cCoefficient;
   uint32_t                             GlobalNoiseEstimation;
   uint32_t                             NonEdgeWeight;
   uint32_t                             RegularWeight;
   uint32_t                             StrongEdgeWeight;
   float                                R5xCoefficient;
   float                                R5cxCoefficient;
   float                                R5cCoefficient;
   float                                STDSinalpha;
   float                                STDCosalpha;
   uint32_t                             Sat_Max;
   uint32_t                             Hue_Max;
   float                                S3U;
   uint32_t                             DiamondMargin;
   bool                                 VY_STD_Enable;
   uint32_t                             U_Mid;
   uint32_t                             V_Mid;
   int32_t                              Diamond_dv;
   uint32_t                             Diamond_Th;
   float                                Diamond_alpha;
   uint32_t                             HS_margin;
   int32_t                              Diamond_du;
   uint32_t                             SkinDetailFactor;
#define DetailRevealed                           0
#define NotDetailRevealed                        1
   uint32_t                             Y_point_1;
   uint32_t                             Y_point_2;
   uint32_t                             Y_point_3;
   uint32_t                             Y_point_4;
   float                                INV_Margin_VYL;
   float                                INV_Margin_VYU;
   uint32_t                             P0L;
   uint32_t                             P1L;
   uint32_t                             P2L;
   uint32_t                             P3L;
   uint32_t                             B0L;
   uint32_t                             B1L;
   uint32_t                             B2L;
   uint32_t                             B3L;
   float                                S0L;
   float                                Y_Slope_2;
   float                                S1L;
   float                                S2L;
   float                                S3L;
   uint32_t                             P0U;
   uint32_t                             P1U;
   float                                Y_Slope1;
   uint32_t                             P2U;
   uint32_t                             P3U;
   uint32_t                             B0U;
   uint32_t                             B1U;
   uint32_t                             B2U;
   uint32_t                             B3U;
   float                                S0U;
   float                                S1U;
   float                                S2U;
   bool                                 TransformEnable;
   bool                                 YUVChannelSwap;
   float                                C0;
   float                                C1;
   float                                C2;
   float                                C3;
   float                                C4;
   float                                C5;
   float                                C6;
   float                                C7;
   float                                C8;
   float                                OffsetIn1;
   float                                OffsetOut1;
   float                                OffsetIn2;
   float                                OffsetOut2;
   float                                OffsetIn3;
   float                                OffsetOut3;
};

static inline __attribute__((always_inline)) void
GFX9_SFC_IEF_STATE_BODY_pack(__attribute__((unused)) __gen_user_data *data,
                             __attribute__((unused)) void * restrict dst,
                             __attribute__((unused)) const struct GFX9_SFC_IEF_STATE_BODY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->GainFactor, 0, 5) |
      util_bitpack_uint(values->WeakEdgeThreshold, 6, 11) |
      util_bitpack_uint(values->StrongEdgeThreshold, 12, 17) |
      util_bitpack_ufixed(values->R3xCoefficient, 18, 22, 5) |
      util_bitpack_ufixed(values->R3cCoefficient, 23, 27, 5);

   dw[1] =
      util_bitpack_uint(values->GlobalNoiseEstimation, 0, 7) |
      util_bitpack_uint(values->NonEdgeWeight, 8, 10) |
      util_bitpack_uint(values->RegularWeight, 11, 13) |
      util_bitpack_uint(values->StrongEdgeWeight, 14, 16) |
      util_bitpack_ufixed(values->R5xCoefficient, 17, 21, 5) |
      util_bitpack_ufixed(values->R5cxCoefficient, 22, 26, 5) |
      util_bitpack_ufixed(values->R5cCoefficient, 27, 31, 5);

   dw[2] =
      util_bitpack_sfixed(values->STDSinalpha, 0, 7, 7) |
      util_bitpack_sfixed(values->STDCosalpha, 8, 15, 7) |
      util_bitpack_uint(values->Sat_Max, 16, 21) |
      util_bitpack_uint(values->Hue_Max, 22, 27);

   dw[3] =
      util_bitpack_sfixed(values->S3U, 0, 10, 8) |
      util_bitpack_uint(values->DiamondMargin, 12, 14) |
      util_bitpack_uint(values->VY_STD_Enable, 15, 15) |
      util_bitpack_uint(values->U_Mid, 16, 23) |
      util_bitpack_uint(values->V_Mid, 24, 31);

   dw[4] =
      util_bitpack_sint(values->Diamond_dv, 0, 6) |
      util_bitpack_uint(values->Diamond_Th, 7, 12) |
      util_bitpack_ufixed(values->Diamond_alpha, 13, 20, 6) |
      util_bitpack_uint(values->HS_margin, 21, 23) |
      util_bitpack_sint(values->Diamond_du, 24, 30) |
      util_bitpack_uint(values->SkinDetailFactor, 31, 31);

   dw[5] =
      util_bitpack_uint(values->Y_point_1, 0, 7) |
      util_bitpack_uint(values->Y_point_2, 8, 15) |
      util_bitpack_uint(values->Y_point_3, 16, 23) |
      util_bitpack_uint(values->Y_point_4, 24, 31);

   dw[6] =
      util_bitpack_ufixed(values->INV_Margin_VYL, 0, 15, 16);

   dw[7] =
      util_bitpack_ufixed(values->INV_Margin_VYU, 0, 15, 16) |
      util_bitpack_uint(values->P0L, 16, 23) |
      util_bitpack_uint(values->P1L, 24, 31);

   dw[8] =
      util_bitpack_uint(values->P2L, 0, 7) |
      util_bitpack_uint(values->P3L, 8, 15) |
      util_bitpack_uint(values->B0L, 16, 23) |
      util_bitpack_uint(values->B1L, 24, 31);

   dw[9] =
      util_bitpack_uint(values->B2L, 0, 7) |
      util_bitpack_uint(values->B3L, 8, 15) |
      util_bitpack_sfixed(values->S0L, 16, 26, 8) |
      util_bitpack_ufixed(values->Y_Slope_2, 27, 31, 3);

   dw[10] =
      util_bitpack_sfixed(values->S1L, 0, 10, 8) |
      util_bitpack_sfixed(values->S2L, 11, 21, 8);

   dw[11] =
      util_bitpack_sfixed(values->S3L, 0, 10, 8) |
      util_bitpack_uint(values->P0U, 11, 18) |
      util_bitpack_uint(values->P1U, 19, 26) |
      util_bitpack_ufixed(values->Y_Slope1, 27, 31, 3);

   dw[12] =
      util_bitpack_uint(values->P2U, 0, 7) |
      util_bitpack_uint(values->P3U, 8, 15) |
      util_bitpack_uint(values->B0U, 16, 23) |
      util_bitpack_uint(values->B1U, 24, 31);

   dw[13] =
      util_bitpack_uint(values->B2U, 0, 7) |
      util_bitpack_uint(values->B3U, 8, 15) |
      util_bitpack_sfixed(values->S0U, 16, 26, 8);

   dw[14] =
      util_bitpack_sfixed(values->S1U, 0, 10, 8) |
      util_bitpack_sfixed(values->S2U, 11, 21, 8);

   dw[15] =
      util_bitpack_uint(values->TransformEnable, 0, 0) |
      util_bitpack_uint(values->YUVChannelSwap, 1, 1) |
      util_bitpack_sfixed(values->C0, 3, 15, 10) |
      util_bitpack_sfixed(values->C1, 16, 28, 10);

   dw[16] =
      util_bitpack_sfixed(values->C2, 0, 12, 10) |
      util_bitpack_sfixed(values->C3, 13, 25, 10);

   dw[17] =
      util_bitpack_sfixed(values->C4, 0, 12, 10) |
      util_bitpack_sfixed(values->C5, 13, 25, 10);

   dw[18] =
      util_bitpack_sfixed(values->C6, 0, 12, 10) |
      util_bitpack_sfixed(values->C7, 13, 25, 10);

   dw[19] =
      util_bitpack_sfixed(values->C8, 0, 12, 10);

   dw[20] =
      util_bitpack_sfixed(values->OffsetIn1, 0, 10, 8) |
      util_bitpack_sfixed(values->OffsetOut1, 11, 21, 8);

   dw[21] =
      util_bitpack_sfixed(values->OffsetIn2, 0, 10, 8) |
      util_bitpack_sfixed(values->OffsetOut2, 11, 21, 8);

   dw[22] =
      util_bitpack_sfixed(values->OffsetIn3, 0, 10, 8) |
      util_bitpack_sfixed(values->OffsetOut3, 11, 21, 8);
}

#define GFX9_SFC_LOCK_BODY_length              1
struct GFX9_SFC_LOCK_BODY {
   uint32_t                             VESFCPipeSelect;
   bool                                 PreScaledOutputSurfaceOutputEnable;
};

static inline __attribute__((always_inline)) void
GFX9_SFC_LOCK_BODY_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_SFC_LOCK_BODY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->VESFCPipeSelect, 0, 0) |
      util_bitpack_uint(values->PreScaledOutputSurfaceOutputEnable, 1, 1);
}

#define GFX9_SF_CLIP_VIEWPORT_length          16
struct GFX9_SF_CLIP_VIEWPORT {
   float                                ViewportMatrixElementm00;
   float                                ViewportMatrixElementm11;
   float                                ViewportMatrixElementm22;
   float                                ViewportMatrixElementm30;
   float                                ViewportMatrixElementm31;
   float                                ViewportMatrixElementm32;
   float                                XMinClipGuardband;
   float                                XMaxClipGuardband;
   float                                YMinClipGuardband;
   float                                YMaxClipGuardband;
   float                                XMinViewPort;
   float                                XMaxViewPort;
   float                                YMinViewPort;
   float                                YMaxViewPort;
};

static inline __attribute__((always_inline)) void
GFX9_SF_CLIP_VIEWPORT_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_SF_CLIP_VIEWPORT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_float(values->ViewportMatrixElementm00);

   dw[1] =
      util_bitpack_float(values->ViewportMatrixElementm11);

   dw[2] =
      util_bitpack_float(values->ViewportMatrixElementm22);

   dw[3] =
      util_bitpack_float(values->ViewportMatrixElementm30);

   dw[4] =
      util_bitpack_float(values->ViewportMatrixElementm31);

   dw[5] =
      util_bitpack_float(values->ViewportMatrixElementm32);

   dw[6] = 0;

   dw[7] = 0;

   dw[8] =
      util_bitpack_float(values->XMinClipGuardband);

   dw[9] =
      util_bitpack_float(values->XMaxClipGuardband);

   dw[10] =
      util_bitpack_float(values->YMinClipGuardband);

   dw[11] =
      util_bitpack_float(values->YMaxClipGuardband);

   dw[12] =
      util_bitpack_float(values->XMinViewPort);

   dw[13] =
      util_bitpack_float(values->XMaxViewPort);

   dw[14] =
      util_bitpack_float(values->YMinViewPort);

   dw[15] =
      util_bitpack_float(values->YMaxViewPort);
}

#define GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_length      1
struct GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL {
   uint32_t                             SourceAttribute;
   uint32_t                             SwizzleSelect;
#define INPUTATTR                                0
#define INPUTATTR_FACING                         1
#define INPUTATTR_W                              2
#define INPUTATTR_FACING_W                       3
   uint32_t                             ConstantSource;
#define CONST_0000                               0
#define CONST_0001_FLOAT                         1
#define CONST_1111_FLOAT                         2
#define PRIM_ID                                  3
   uint32_t                             SwizzleControlMode;
   bool                                 ComponentOverrideX;
   bool                                 ComponentOverrideY;
   bool                                 ComponentOverrideZ;
   bool                                 ComponentOverrideW;
};

static inline __attribute__((always_inline)) void
GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(__attribute__((unused)) __gen_user_data *data,
                                     __attribute__((unused)) void * restrict dst,
                                     __attribute__((unused)) const struct GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->SourceAttribute, 0, 4) |
      util_bitpack_uint(values->SwizzleSelect, 6, 7) |
      util_bitpack_uint(values->ConstantSource, 9, 10) |
      util_bitpack_uint(values->SwizzleControlMode, 11, 11) |
      util_bitpack_uint(values->ComponentOverrideX, 12, 12) |
      util_bitpack_uint(values->ComponentOverrideY, 13, 13) |
      util_bitpack_uint(values->ComponentOverrideZ, 14, 14) |
      util_bitpack_uint(values->ComponentOverrideW, 15, 15);
}

#define GFX9_SO_DECL_length                    1
struct GFX9_SO_DECL {
   uint32_t                             ComponentMask;
   uint32_t                             RegisterIndex;
   bool                                 HoleFlag;
   uint32_t                             OutputBufferSlot;
};

static inline __attribute__((always_inline)) void
GFX9_SO_DECL_pack(__attribute__((unused)) __gen_user_data *data,
                  __attribute__((unused)) void * restrict dst,
                  __attribute__((unused)) const struct GFX9_SO_DECL * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->ComponentMask, 0, 3) |
      util_bitpack_uint(values->RegisterIndex, 4, 9) |
      util_bitpack_uint(values->HoleFlag, 11, 11) |
      util_bitpack_uint(values->OutputBufferSlot, 12, 13);
}

#define GFX9_SO_DECL_ENTRY_length              2
struct GFX9_SO_DECL_ENTRY {
   struct GFX9_SO_DECL                  Stream0Decl;
   struct GFX9_SO_DECL                  Stream1Decl;
   struct GFX9_SO_DECL                  Stream2Decl;
   struct GFX9_SO_DECL                  Stream3Decl;
};

static inline __attribute__((always_inline)) void
GFX9_SO_DECL_ENTRY_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_SO_DECL_ENTRY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   uint32_t v0_0;
   GFX9_SO_DECL_pack(data, &v0_0, &values->Stream0Decl);

   uint32_t v0_1;
   GFX9_SO_DECL_pack(data, &v0_1, &values->Stream1Decl);

   dw[0] =
      util_bitpack_uint(v0_0, 0, 15) |
      util_bitpack_uint(v0_1, 16, 31);

   uint32_t v1_0;
   GFX9_SO_DECL_pack(data, &v1_0, &values->Stream2Decl);

   uint32_t v1_1;
   GFX9_SO_DECL_pack(data, &v1_1, &values->Stream3Decl);

   dw[1] =
      util_bitpack_uint(v1_0, 0, 15) |
      util_bitpack_uint(v1_1, 16, 31);
}

#define GFX9_VDENC_SURFACE_CONTROL_BITS_length      1
struct GFX9_VDENC_SURFACE_CONTROL_BITS {
   uint32_t                             MOCS;
   uint32_t                             ArbitrationPriorityControl;
#define Highestpriority                          0
#define Secondhighestpriority                    1
#define Thirdhighestpriority                     2
#define Lowestpriority                           3
   bool                                 MemoryCompressionEnable;
   uint32_t                             MemoryCompressionMode;
   uint32_t                             CacheSelect;
   uint32_t                             TiledResourceMode;
#define TRMODE_NONE                              0
#define TRMODE_TILEYF                            1
#define TRMODE_TILEYS                            2
};

static inline __attribute__((always_inline)) void
GFX9_VDENC_SURFACE_CONTROL_BITS_pack(__attribute__((unused)) __gen_user_data *data,
                                     __attribute__((unused)) void * restrict dst,
                                     __attribute__((unused)) const struct GFX9_VDENC_SURFACE_CONTROL_BITS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint_nonzero(values->MOCS, 1, 6) |
      util_bitpack_uint(values->ArbitrationPriorityControl, 7, 8) |
      util_bitpack_uint(values->MemoryCompressionEnable, 9, 9) |
      util_bitpack_uint(values->MemoryCompressionMode, 10, 10) |
      util_bitpack_uint(values->CacheSelect, 12, 12) |
      util_bitpack_uint(values->TiledResourceMode, 13, 14);
}

#define GFX9_VDENC_PICTURE_length              3
struct GFX9_VDENC_PICTURE {
   __gen_address_type                   Address;
   struct GFX9_VDENC_SURFACE_CONTROL_BITS PictureFields;
};

static inline __attribute__((always_inline)) void
GFX9_VDENC_PICTURE_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_VDENC_PICTURE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0_address =
      __gen_address(data, &dw[0], values->Address, 0, 0, 63);
   dw[0] = v0_address;
   dw[1] = v0_address >> 32;

   GFX9_VDENC_SURFACE_CONTROL_BITS_pack(data, &dw[2], &values->PictureFields);
}

#define GFX9_VDENC_SURFACE_STATE_FIELDS_length      4
struct GFX9_VDENC_SURFACE_STATE_FIELDS {
   float                                CrVCbUPixelOffsetVDirection;
   bool                                 SurfaceFormatByteSwizzle;
   uint32_t                             Colorspaceselection;
   uint32_t                             Width;
   uint32_t                             Height;
   uint32_t                             TileWalk;
#define TW_XMAJOR                                0
#define TW_YMAJOR                                1
   uint32_t                             TiledSurface;
   bool                                 HalfPitchforChroma;
   uint32_t                             SurfacePitch;
   uint32_t                             Format;
   uint32_t                             SurfaceFormat;
#define VDENC_YUV422                             0
#define VDENC_RGBA4444                           1
#define VDENC_YUV444                             2
#define VDENC_Y8_UNORM                           3
#define VDENC_PLANAR_420_8                       4
   uint32_t                             YOffsetforUCb;
   uint32_t                             XOffsetforUCb;
   uint32_t                             YOffsetforVCr;
   uint32_t                             XOffsetforVCr;
};

static inline __attribute__((always_inline)) void
GFX9_VDENC_SURFACE_STATE_FIELDS_pack(__attribute__((unused)) __gen_user_data *data,
                                     __attribute__((unused)) void * restrict dst,
                                     __attribute__((unused)) const struct GFX9_VDENC_SURFACE_STATE_FIELDS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_ufixed(values->CrVCbUPixelOffsetVDirection, 0, 1, 2) |
      util_bitpack_uint(values->SurfaceFormatByteSwizzle, 2, 2) |
      util_bitpack_uint(values->Colorspaceselection, 3, 3) |
      util_bitpack_uint(values->Width, 4, 17) |
      util_bitpack_uint(values->Height, 18, 31);

   dw[1] =
      util_bitpack_uint(values->TileWalk, 0, 0) |
      util_bitpack_uint(values->TiledSurface, 1, 1) |
      util_bitpack_uint(values->HalfPitchforChroma, 2, 2) |
      util_bitpack_uint(values->SurfacePitch, 3, 19) |
      util_bitpack_uint(values->Format, 27, 31) |
      util_bitpack_uint(values->SurfaceFormat, 28, 31);

   dw[2] =
      util_bitpack_uint(values->YOffsetforUCb, 0, 14) |
      util_bitpack_uint(values->XOffsetforUCb, 16, 30);

   dw[3] =
      util_bitpack_uint(values->YOffsetforVCr, 0, 15) |
      util_bitpack_uint(values->XOffsetforVCr, 16, 28);
}

#define GFX9_VERTEX_BUFFER_STATE_length        4
struct GFX9_VERTEX_BUFFER_STATE {
   uint32_t                             BufferPitch;
   bool                                 NullVertexBuffer;
   bool                                 AddressModifyEnable;
   uint32_t                             MOCS;
   uint32_t                             VertexBufferIndex;
   __gen_address_type                   BufferStartingAddress;
   uint32_t                             BufferSize;
};

static inline __attribute__((always_inline)) void
GFX9_VERTEX_BUFFER_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_VERTEX_BUFFER_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->BufferPitch, 0, 11) |
      util_bitpack_uint(values->NullVertexBuffer, 13, 13) |
      util_bitpack_uint(values->AddressModifyEnable, 14, 14) |
      util_bitpack_uint_nonzero(values->MOCS, 16, 22) |
      util_bitpack_uint(values->VertexBufferIndex, 26, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->BufferStartingAddress, 0, 0, 63);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;

   dw[3] =
      util_bitpack_uint(values->BufferSize, 0, 31);
}

#define GFX9_VERTEX_ELEMENT_STATE_length       2
struct GFX9_VERTEX_ELEMENT_STATE {
   uint32_t                             SourceElementOffset;
   bool                                 EdgeFlagEnable;
   uint32_t                             SourceElementFormat;
   bool                                 Valid;
   uint32_t                             VertexBufferIndex;
   enum GFX9_3D_Vertex_Component_Control Component3Control;
   enum GFX9_3D_Vertex_Component_Control Component2Control;
   enum GFX9_3D_Vertex_Component_Control Component1Control;
   enum GFX9_3D_Vertex_Component_Control Component0Control;
};

static inline __attribute__((always_inline)) void
GFX9_VERTEX_ELEMENT_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_VERTEX_ELEMENT_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->SourceElementOffset, 0, 11) |
      util_bitpack_uint(values->EdgeFlagEnable, 15, 15) |
      util_bitpack_uint(values->SourceElementFormat, 16, 24) |
      util_bitpack_uint(values->Valid, 25, 25) |
      util_bitpack_uint(values->VertexBufferIndex, 26, 31);

   dw[1] =
      util_bitpack_uint(values->Component3Control, 16, 18) |
      util_bitpack_uint(values->Component2Control, 20, 22) |
      util_bitpack_uint(values->Component1Control, 24, 26) |
      util_bitpack_uint(values->Component0Control, 28, 30);
}

#define GFX9_3DPRIMITIVE_length                7
#define GFX9_3DPRIMITIVE_length_bias           2
#define GFX9_3DPRIMITIVE_header                 \
   .DWordLength                         =      5,  \
   ._3DCommandSubOpcode                 =      0,  \
   ._3DCommandOpcode                    =      3,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DPRIMITIVE {
   uint32_t                             DWordLength;
   bool                                 PredicateEnable;
   bool                                 UAVCoherencyRequired;
   bool                                 IndirectParameterEnable;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   enum GFX9_3D_Prim_Topo_Type          PrimitiveTopologyType;
   uint32_t                             VertexAccessType;
#define SEQUENTIAL                               0
#define RANDOM                                   1
   bool                                 EndOffsetEnable;
   uint32_t                             VertexCountPerInstance;
   uint32_t                             StartVertexLocation;
   uint32_t                             InstanceCount;
   uint32_t                             StartInstanceLocation;
   int32_t                              BaseVertexLocation;
};

static inline __attribute__((always_inline)) void
GFX9_3DPRIMITIVE_pack(__attribute__((unused)) __gen_user_data *data,
                      __attribute__((unused)) void * restrict dst,
                      __attribute__((unused)) const struct GFX9_3DPRIMITIVE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->PredicateEnable, 8, 8) |
      util_bitpack_uint(values->UAVCoherencyRequired, 9, 9) |
      util_bitpack_uint(values->IndirectParameterEnable, 10, 10) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->PrimitiveTopologyType, 0, 5) |
      util_bitpack_uint(values->VertexAccessType, 8, 8) |
      util_bitpack_uint(values->EndOffsetEnable, 9, 9);

   dw[2] =
      util_bitpack_uint(values->VertexCountPerInstance, 0, 31);

   dw[3] =
      util_bitpack_uint(values->StartVertexLocation, 0, 31);

   dw[4] =
      util_bitpack_uint(values->InstanceCount, 0, 31);

   dw[5] =
      util_bitpack_uint(values->StartInstanceLocation, 0, 31);

   dw[6] =
      util_bitpack_sint(values->BaseVertexLocation, 0, 31);
}

#define GFX9_3DSTATE_AA_LINE_PARAMETERS_length      3
#define GFX9_3DSTATE_AA_LINE_PARAMETERS_length_bias      2
#define GFX9_3DSTATE_AA_LINE_PARAMETERS_header  \
   .DWordLength                         =      1,  \
   ._3DCommandSubOpcode                 =     10,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_AA_LINE_PARAMETERS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   float                                AACoverageSlope;
   float                                AAPointCoverageSlope;
   float                                AACoverageBias;
   float                                AAPointCoverageBias;
   float                                AACoverageEndCapSlope;
   float                                AAPointCoverageEndCapSlope;
   float                                AACoverageEndCapBias;
   float                                AAPointCoverageEndCapBias;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_AA_LINE_PARAMETERS_pack(__attribute__((unused)) __gen_user_data *data,
                                     __attribute__((unused)) void * restrict dst,
                                     __attribute__((unused)) const struct GFX9_3DSTATE_AA_LINE_PARAMETERS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_ufixed(values->AACoverageSlope, 0, 7, 8) |
      util_bitpack_ufixed(values->AAPointCoverageSlope, 8, 15, 8) |
      util_bitpack_ufixed(values->AACoverageBias, 16, 23, 8) |
      util_bitpack_ufixed(values->AAPointCoverageBias, 24, 31, 8);

   dw[2] =
      util_bitpack_ufixed(values->AACoverageEndCapSlope, 0, 7, 8) |
      util_bitpack_ufixed(values->AAPointCoverageEndCapSlope, 8, 15, 8) |
      util_bitpack_ufixed(values->AACoverageEndCapBias, 16, 23, 8) |
      util_bitpack_ufixed(values->AAPointCoverageEndCapBias, 24, 31, 8);
}

#define GFX9_3DSTATE_BINDING_TABLE_EDIT_DS_length_bias      2
#define GFX9_3DSTATE_BINDING_TABLE_EDIT_DS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     70,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_BINDING_TABLE_EDIT_DS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             BindingTableEditTarget;
#define AllCores                                 3
#define Core1                                    2
#define Core0                                    1
   uint32_t                             BindingTableBlockClear;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_BINDING_TABLE_EDIT_DS_pack(__attribute__((unused)) __gen_user_data *data,
                                        __attribute__((unused)) void * restrict dst,
                                        __attribute__((unused)) const struct GFX9_3DSTATE_BINDING_TABLE_EDIT_DS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 8) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->BindingTableEditTarget, 0, 1) |
      util_bitpack_uint(values->BindingTableBlockClear, 16, 31);
}

#define GFX9_3DSTATE_BINDING_TABLE_EDIT_GS_length_bias      2
#define GFX9_3DSTATE_BINDING_TABLE_EDIT_GS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     68,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_BINDING_TABLE_EDIT_GS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             BindingTableEditTarget;
#define AllCores                                 3
#define Core1                                    2
#define Core0                                    1
   uint32_t                             BindingTableBlockClear;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_BINDING_TABLE_EDIT_GS_pack(__attribute__((unused)) __gen_user_data *data,
                                        __attribute__((unused)) void * restrict dst,
                                        __attribute__((unused)) const struct GFX9_3DSTATE_BINDING_TABLE_EDIT_GS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 8) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->BindingTableEditTarget, 0, 1) |
      util_bitpack_uint(values->BindingTableBlockClear, 16, 31);
}

#define GFX9_3DSTATE_BINDING_TABLE_EDIT_HS_length_bias      2
#define GFX9_3DSTATE_BINDING_TABLE_EDIT_HS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     69,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_BINDING_TABLE_EDIT_HS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             BindingTableEditTarget;
#define AllCores                                 3
#define Core1                                    2
#define Core0                                    1
   uint32_t                             BindingTableBlockClear;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_BINDING_TABLE_EDIT_HS_pack(__attribute__((unused)) __gen_user_data *data,
                                        __attribute__((unused)) void * restrict dst,
                                        __attribute__((unused)) const struct GFX9_3DSTATE_BINDING_TABLE_EDIT_HS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 8) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->BindingTableEditTarget, 0, 1) |
      util_bitpack_uint(values->BindingTableBlockClear, 16, 31);
}

#define GFX9_3DSTATE_BINDING_TABLE_EDIT_PS_length_bias      2
#define GFX9_3DSTATE_BINDING_TABLE_EDIT_PS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     71,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_BINDING_TABLE_EDIT_PS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             BindingTableEditTarget;
#define AllCores                                 3
#define Core1                                    2
#define Core0                                    1
   uint32_t                             BindingTableBlockClear;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_BINDING_TABLE_EDIT_PS_pack(__attribute__((unused)) __gen_user_data *data,
                                        __attribute__((unused)) void * restrict dst,
                                        __attribute__((unused)) const struct GFX9_3DSTATE_BINDING_TABLE_EDIT_PS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 8) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->BindingTableEditTarget, 0, 1) |
      util_bitpack_uint(values->BindingTableBlockClear, 16, 31);
}

#define GFX9_3DSTATE_BINDING_TABLE_EDIT_VS_length_bias      2
#define GFX9_3DSTATE_BINDING_TABLE_EDIT_VS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     67,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_BINDING_TABLE_EDIT_VS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             BindingTableEditTarget;
#define AllCores                                 3
#define Core1                                    2
#define Core0                                    1
   uint32_t                             BindingTableBlockClear;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_BINDING_TABLE_EDIT_VS_pack(__attribute__((unused)) __gen_user_data *data,
                                        __attribute__((unused)) void * restrict dst,
                                        __attribute__((unused)) const struct GFX9_3DSTATE_BINDING_TABLE_EDIT_VS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 8) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->BindingTableEditTarget, 0, 1) |
      util_bitpack_uint(values->BindingTableBlockClear, 16, 31);
}

#define GFX9_3DSTATE_BINDING_TABLE_POINTERS_DS_length      2
#define GFX9_3DSTATE_BINDING_TABLE_POINTERS_DS_length_bias      2
#define GFX9_3DSTATE_BINDING_TABLE_POINTERS_DS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     40,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_BINDING_TABLE_POINTERS_DS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             PointertoDSBindingTable;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_BINDING_TABLE_POINTERS_DS_pack(__attribute__((unused)) __gen_user_data *data,
                                            __attribute__((unused)) void * restrict dst,
                                            __attribute__((unused)) const struct GFX9_3DSTATE_BINDING_TABLE_POINTERS_DS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->PointertoDSBindingTable, 5, 15);
}

#define GFX9_3DSTATE_BINDING_TABLE_POINTERS_GS_length      2
#define GFX9_3DSTATE_BINDING_TABLE_POINTERS_GS_length_bias      2
#define GFX9_3DSTATE_BINDING_TABLE_POINTERS_GS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     41,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_BINDING_TABLE_POINTERS_GS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             PointertoGSBindingTable;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_BINDING_TABLE_POINTERS_GS_pack(__attribute__((unused)) __gen_user_data *data,
                                            __attribute__((unused)) void * restrict dst,
                                            __attribute__((unused)) const struct GFX9_3DSTATE_BINDING_TABLE_POINTERS_GS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->PointertoGSBindingTable, 5, 15);
}

#define GFX9_3DSTATE_BINDING_TABLE_POINTERS_HS_length      2
#define GFX9_3DSTATE_BINDING_TABLE_POINTERS_HS_length_bias      2
#define GFX9_3DSTATE_BINDING_TABLE_POINTERS_HS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     39,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_BINDING_TABLE_POINTERS_HS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             PointertoHSBindingTable;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_BINDING_TABLE_POINTERS_HS_pack(__attribute__((unused)) __gen_user_data *data,
                                            __attribute__((unused)) void * restrict dst,
                                            __attribute__((unused)) const struct GFX9_3DSTATE_BINDING_TABLE_POINTERS_HS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->PointertoHSBindingTable, 5, 15);
}

#define GFX9_3DSTATE_BINDING_TABLE_POINTERS_PS_length      2
#define GFX9_3DSTATE_BINDING_TABLE_POINTERS_PS_length_bias      2
#define GFX9_3DSTATE_BINDING_TABLE_POINTERS_PS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     42,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_BINDING_TABLE_POINTERS_PS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             PointertoPSBindingTable;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_BINDING_TABLE_POINTERS_PS_pack(__attribute__((unused)) __gen_user_data *data,
                                            __attribute__((unused)) void * restrict dst,
                                            __attribute__((unused)) const struct GFX9_3DSTATE_BINDING_TABLE_POINTERS_PS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->PointertoPSBindingTable, 5, 15);
}

#define GFX9_3DSTATE_BINDING_TABLE_POINTERS_VS_length      2
#define GFX9_3DSTATE_BINDING_TABLE_POINTERS_VS_length_bias      2
#define GFX9_3DSTATE_BINDING_TABLE_POINTERS_VS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     38,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_BINDING_TABLE_POINTERS_VS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             PointertoVSBindingTable;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_BINDING_TABLE_POINTERS_VS_pack(__attribute__((unused)) __gen_user_data *data,
                                            __attribute__((unused)) void * restrict dst,
                                            __attribute__((unused)) const struct GFX9_3DSTATE_BINDING_TABLE_POINTERS_VS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->PointertoVSBindingTable, 5, 15);
}

#define GFX9_3DSTATE_BINDING_TABLE_POOL_ALLOC_length      4
#define GFX9_3DSTATE_BINDING_TABLE_POOL_ALLOC_length_bias      2
#define GFX9_3DSTATE_BINDING_TABLE_POOL_ALLOC_header\
   .DWordLength                         =      2,  \
   ._3DCommandSubOpcode                 =     25,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_BINDING_TABLE_POOL_ALLOC {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             MOCS;
   bool                                 BindingTablePoolEnable;
   __gen_address_type                   BindingTablePoolBaseAddress;
   uint32_t                             BindingTablePoolBufferSize;
#define NoValidData                              0
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_BINDING_TABLE_POOL_ALLOC_pack(__attribute__((unused)) __gen_user_data *data,
                                           __attribute__((unused)) void * restrict dst,
                                           __attribute__((unused)) const struct GFX9_3DSTATE_BINDING_TABLE_POOL_ALLOC * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1 =
      util_bitpack_uint_nonzero(values->MOCS, 0, 6) |
      util_bitpack_uint(values->BindingTablePoolEnable, 11, 11);
   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->BindingTablePoolBaseAddress, v1, 12, 63);
   dw[1] = v1_address;
   dw[2] = (v1_address >> 32) | (v1 >> 32);

   dw[3] =
      util_bitpack_uint(values->BindingTablePoolBufferSize, 12, 31);
}

#define GFX9_3DSTATE_BLEND_STATE_POINTERS_length      2
#define GFX9_3DSTATE_BLEND_STATE_POINTERS_length_bias      2
#define GFX9_3DSTATE_BLEND_STATE_POINTERS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     36,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_BLEND_STATE_POINTERS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   bool                                 BlendStatePointerValid;
   uint64_t                             BlendStatePointer;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_BLEND_STATE_POINTERS_pack(__attribute__((unused)) __gen_user_data *data,
                                       __attribute__((unused)) void * restrict dst,
                                       __attribute__((unused)) const struct GFX9_3DSTATE_BLEND_STATE_POINTERS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->BlendStatePointerValid, 0, 0) |
      __gen_offset(values->BlendStatePointer, 6, 31);
}

#define GFX9_3DSTATE_CC_STATE_POINTERS_length      2
#define GFX9_3DSTATE_CC_STATE_POINTERS_length_bias      2
#define GFX9_3DSTATE_CC_STATE_POINTERS_header   \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     14,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_CC_STATE_POINTERS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   bool                                 ColorCalcStatePointerValid;
   uint64_t                             ColorCalcStatePointer;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_CC_STATE_POINTERS_pack(__attribute__((unused)) __gen_user_data *data,
                                    __attribute__((unused)) void * restrict dst,
                                    __attribute__((unused)) const struct GFX9_3DSTATE_CC_STATE_POINTERS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ColorCalcStatePointerValid, 0, 0) |
      __gen_offset(values->ColorCalcStatePointer, 6, 31);
}

#define GFX9_3DSTATE_CHROMA_KEY_length         4
#define GFX9_3DSTATE_CHROMA_KEY_length_bias      2
#define GFX9_3DSTATE_CHROMA_KEY_header          \
   .DWordLength                         =      2,  \
   ._3DCommandSubOpcode                 =      4,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_CHROMA_KEY {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             ChromaKeyTableIndex;
   uint32_t                             ChromaKeyLowValue;
   uint32_t                             ChromaKeyHighValue;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_CHROMA_KEY_pack(__attribute__((unused)) __gen_user_data *data,
                             __attribute__((unused)) void * restrict dst,
                             __attribute__((unused)) const struct GFX9_3DSTATE_CHROMA_KEY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ChromaKeyTableIndex, 30, 31);

   dw[2] =
      util_bitpack_uint(values->ChromaKeyLowValue, 0, 31);

   dw[3] =
      util_bitpack_uint(values->ChromaKeyHighValue, 0, 31);
}

#define GFX9_3DSTATE_CLEAR_PARAMS_length       3
#define GFX9_3DSTATE_CLEAR_PARAMS_length_bias      2
#define GFX9_3DSTATE_CLEAR_PARAMS_header        \
   .DWordLength                         =      1,  \
   ._3DCommandSubOpcode                 =      4,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_CLEAR_PARAMS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   float                                DepthClearValue;
   bool                                 DepthClearValueValid;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_CLEAR_PARAMS_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_3DSTATE_CLEAR_PARAMS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_float(values->DepthClearValue);

   dw[2] =
      util_bitpack_uint(values->DepthClearValueValid, 0, 0);
}

#define GFX9_3DSTATE_CLIP_length               4
#define GFX9_3DSTATE_CLIP_length_bias          2
#define GFX9_3DSTATE_CLIP_header                \
   .DWordLength                         =      2,  \
   ._3DCommandSubOpcode                 =     18,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_CLIP {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             UserClipDistanceCullTestEnableBitmask;
   bool                                 StatisticsEnable;
   bool                                 ForceClipMode;
   bool                                 ForceUserClipDistanceClipTestEnableBitmask;
   bool                                 EarlyCullEnable;
   uint32_t                             VertexSubPixelPrecisionSelect;
#define _8Bit                                    0
#define _4Bit                                    1
   bool                                 ForceUserClipDistanceCullTestEnableBitmask;
   uint32_t                             TriangleFanProvokingVertexSelect;
   uint32_t                             LineStripListProvokingVertexSelect;
   uint32_t                             TriangleStripListProvokingVertexSelect;
   bool                                 NonPerspectiveBarycentricEnable;
   bool                                 PerspectiveDivideDisable;
   uint32_t                             ClipMode;
#define CLIPMODE_NORMAL                          0
#define CLIPMODE_REJECT_ALL                      3
#define CLIPMODE_ACCEPT_ALL                      4
   uint32_t                             UserClipDistanceClipTestEnableBitmask;
   bool                                 GuardbandClipTestEnable;
   bool                                 ViewportXYClipTestEnable;
   uint32_t                             APIMode;
#define APIMODE_OGL                              0
#define APIMODE_D3D                              1
   bool                                 ClipEnable;
   uint32_t                             MaximumVPIndex;
   bool                                 ForceZeroRTAIndexEnable;
   float                                MaximumPointWidth;
   float                                MinimumPointWidth;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_CLIP_pack(__attribute__((unused)) __gen_user_data *data,
                       __attribute__((unused)) void * restrict dst,
                       __attribute__((unused)) const struct GFX9_3DSTATE_CLIP * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->UserClipDistanceCullTestEnableBitmask, 0, 7) |
      util_bitpack_uint(values->StatisticsEnable, 10, 10) |
      util_bitpack_uint(values->ForceClipMode, 16, 16) |
      util_bitpack_uint(values->ForceUserClipDistanceClipTestEnableBitmask, 17, 17) |
      util_bitpack_uint(values->EarlyCullEnable, 18, 18) |
      util_bitpack_uint(values->VertexSubPixelPrecisionSelect, 19, 19) |
      util_bitpack_uint(values->ForceUserClipDistanceCullTestEnableBitmask, 20, 20);

   dw[2] =
      util_bitpack_uint(values->TriangleFanProvokingVertexSelect, 0, 1) |
      util_bitpack_uint(values->LineStripListProvokingVertexSelect, 2, 3) |
      util_bitpack_uint(values->TriangleStripListProvokingVertexSelect, 4, 5) |
      util_bitpack_uint(values->NonPerspectiveBarycentricEnable, 8, 8) |
      util_bitpack_uint(values->PerspectiveDivideDisable, 9, 9) |
      util_bitpack_uint(values->ClipMode, 13, 15) |
      util_bitpack_uint(values->UserClipDistanceClipTestEnableBitmask, 16, 23) |
      util_bitpack_uint(values->GuardbandClipTestEnable, 26, 26) |
      util_bitpack_uint(values->ViewportXYClipTestEnable, 28, 28) |
      util_bitpack_uint(values->APIMode, 30, 30) |
      util_bitpack_uint(values->ClipEnable, 31, 31);

   dw[3] =
      util_bitpack_uint(values->MaximumVPIndex, 0, 3) |
      util_bitpack_uint(values->ForceZeroRTAIndexEnable, 5, 5) |
      util_bitpack_ufixed(values->MaximumPointWidth, 6, 16, 3) |
      util_bitpack_ufixed(values->MinimumPointWidth, 17, 27, 3);
}

#define GFX9_3DSTATE_CONSTANT_DS_length       11
#define GFX9_3DSTATE_CONSTANT_DS_length_bias      2
#define GFX9_3DSTATE_CONSTANT_DS_header         \
   .DWordLength                         =      9,  \
   ._3DCommandSubOpcode                 =     26,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_CONSTANT_DS {
   uint32_t                             DWordLength;
   uint32_t                             MOCS;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   struct GFX9_3DSTATE_CONSTANT_BODY    ConstantBody;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_CONSTANT_DS_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_3DSTATE_CONSTANT_DS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint_nonzero(values->MOCS, 8, 14) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   GFX9_3DSTATE_CONSTANT_BODY_pack(data, &dw[1], &values->ConstantBody);
}

#define GFX9_3DSTATE_CONSTANT_GS_length       11
#define GFX9_3DSTATE_CONSTANT_GS_length_bias      2
#define GFX9_3DSTATE_CONSTANT_GS_header         \
   .DWordLength                         =      9,  \
   ._3DCommandSubOpcode                 =     22,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_CONSTANT_GS {
   uint32_t                             DWordLength;
   uint32_t                             MOCS;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   struct GFX9_3DSTATE_CONSTANT_BODY    ConstantBody;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_CONSTANT_GS_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_3DSTATE_CONSTANT_GS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint_nonzero(values->MOCS, 8, 14) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   GFX9_3DSTATE_CONSTANT_BODY_pack(data, &dw[1], &values->ConstantBody);
}

#define GFX9_3DSTATE_CONSTANT_HS_length       11
#define GFX9_3DSTATE_CONSTANT_HS_length_bias      2
#define GFX9_3DSTATE_CONSTANT_HS_header         \
   .DWordLength                         =      9,  \
   ._3DCommandSubOpcode                 =     25,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_CONSTANT_HS {
   uint32_t                             DWordLength;
   uint32_t                             MOCS;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   struct GFX9_3DSTATE_CONSTANT_BODY    ConstantBody;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_CONSTANT_HS_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_3DSTATE_CONSTANT_HS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint_nonzero(values->MOCS, 8, 14) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   GFX9_3DSTATE_CONSTANT_BODY_pack(data, &dw[1], &values->ConstantBody);
}

#define GFX9_3DSTATE_CONSTANT_PS_length       11
#define GFX9_3DSTATE_CONSTANT_PS_length_bias      2
#define GFX9_3DSTATE_CONSTANT_PS_header         \
   .DWordLength                         =      9,  \
   ._3DCommandSubOpcode                 =     23,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_CONSTANT_PS {
   uint32_t                             DWordLength;
   uint32_t                             MOCS;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   struct GFX9_3DSTATE_CONSTANT_BODY    ConstantBody;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_CONSTANT_PS_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_3DSTATE_CONSTANT_PS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint_nonzero(values->MOCS, 8, 14) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   GFX9_3DSTATE_CONSTANT_BODY_pack(data, &dw[1], &values->ConstantBody);
}

#define GFX9_3DSTATE_CONSTANT_VS_length       11
#define GFX9_3DSTATE_CONSTANT_VS_length_bias      2
#define GFX9_3DSTATE_CONSTANT_VS_header         \
   .DWordLength                         =      9,  \
   ._3DCommandSubOpcode                 =     21,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_CONSTANT_VS {
   uint32_t                             DWordLength;
   uint32_t                             MOCS;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   struct GFX9_3DSTATE_CONSTANT_BODY    ConstantBody;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_CONSTANT_VS_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_3DSTATE_CONSTANT_VS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint_nonzero(values->MOCS, 8, 14) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   GFX9_3DSTATE_CONSTANT_BODY_pack(data, &dw[1], &values->ConstantBody);
}

#define GFX9_3DSTATE_DEPTH_BUFFER_length       8
#define GFX9_3DSTATE_DEPTH_BUFFER_length_bias      2
#define GFX9_3DSTATE_DEPTH_BUFFER_header        \
   .DWordLength                         =      6,  \
   ._3DCommandSubOpcode                 =      5,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_DEPTH_BUFFER {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             SurfacePitch;
   uint32_t                             SurfaceFormat;
#define D32_FLOAT                                1
#define D24_UNORM_X8_UINT                        3
#define D16_UNORM                                5
   bool                                 HierarchicalDepthBufferEnable;
   bool                                 StencilWriteEnable;
   bool                                 DepthWriteEnable;
   uint32_t                             SurfaceType;
#define SURFTYPE_2D                              1
#define SURFTYPE_CUBE                            3
#define SURFTYPE_NULL                            7
   __gen_address_type                   SurfaceBaseAddress;
   uint32_t                             LOD;
   uint32_t                             Width;
   uint32_t                             Height;
   uint32_t                             MOCS;
   uint32_t                             MinimumArrayElement;
   uint32_t                             Depth;
   uint32_t                             MipTailStartLOD;
   uint32_t                             TiledResourceMode;
#define NONE                                     0
#define TILEYF                                   1
#define TILEYS                                   2
   uint32_t                             SurfaceQPitch;
   uint32_t                             RenderTargetViewExtent;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_DEPTH_BUFFER_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_3DSTATE_DEPTH_BUFFER * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->SurfacePitch, 0, 17) |
      util_bitpack_uint(values->SurfaceFormat, 18, 20) |
      util_bitpack_uint(values->HierarchicalDepthBufferEnable, 22, 22) |
      util_bitpack_uint(values->StencilWriteEnable, 27, 27) |
      util_bitpack_uint(values->DepthWriteEnable, 28, 28) |
      util_bitpack_uint(values->SurfaceType, 29, 31);

   const uint64_t v2_address =
      __gen_address(data, &dw[2], values->SurfaceBaseAddress, 0, 0, 63);
   dw[2] = v2_address;
   dw[3] = v2_address >> 32;

   dw[4] =
      util_bitpack_uint(values->LOD, 0, 3) |
      util_bitpack_uint(values->Width, 4, 17) |
      util_bitpack_uint(values->Height, 18, 31);

   dw[5] =
      util_bitpack_uint_nonzero(values->MOCS, 0, 6) |
      util_bitpack_uint(values->MinimumArrayElement, 10, 20) |
      util_bitpack_uint(values->Depth, 21, 31);

   dw[6] =
      util_bitpack_uint(values->MipTailStartLOD, 26, 29) |
      util_bitpack_uint(values->TiledResourceMode, 30, 31);

   dw[7] =
      util_bitpack_uint(values->SurfaceQPitch, 0, 14) |
      util_bitpack_uint(values->RenderTargetViewExtent, 21, 31);
}

#define GFX9_3DSTATE_DRAWING_RECTANGLE_length      4
#define GFX9_3DSTATE_DRAWING_RECTANGLE_length_bias      2
#define GFX9_3DSTATE_DRAWING_RECTANGLE_header   \
   .DWordLength                         =      2,  \
   ._3DCommandSubOpcode                 =      0,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_DRAWING_RECTANGLE {
   uint32_t                             DWordLength;
   uint32_t                             CoreModeSelect;
#define Legacy                                   0
#define Core0Enabled                             1
#define Core1Enabled                             2
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             ClippedDrawingRectangleXMin;
   uint32_t                             ClippedDrawingRectangleYMin;
   uint32_t                             ClippedDrawingRectangleXMax;
   uint32_t                             ClippedDrawingRectangleYMax;
   int32_t                              DrawingRectangleOriginX;
   int32_t                              DrawingRectangleOriginY;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_DRAWING_RECTANGLE_pack(__attribute__((unused)) __gen_user_data *data,
                                    __attribute__((unused)) void * restrict dst,
                                    __attribute__((unused)) const struct GFX9_3DSTATE_DRAWING_RECTANGLE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->CoreModeSelect, 14, 15) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ClippedDrawingRectangleXMin, 0, 15) |
      util_bitpack_uint(values->ClippedDrawingRectangleYMin, 16, 31);

   dw[2] =
      util_bitpack_uint(values->ClippedDrawingRectangleXMax, 0, 15) |
      util_bitpack_uint(values->ClippedDrawingRectangleYMax, 16, 31);

   dw[3] =
      util_bitpack_sint(values->DrawingRectangleOriginX, 0, 15) |
      util_bitpack_sint(values->DrawingRectangleOriginY, 16, 31);
}

#define GFX9_3DSTATE_DS_length                11
#define GFX9_3DSTATE_DS_length_bias            2
#define GFX9_3DSTATE_DS_header                  \
   .DWordLength                         =      9,  \
   ._3DCommandSubOpcode                 =     29,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_DS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             KernelStartPointer;
   bool                                 SoftwareExceptionEnable;
   bool                                 IllegalOpcodeExceptionEnable;
   bool                                 AccessesUAV;
   uint32_t                             FloatingPointMode;
#define IEEE754                                  0
#define Alternate                                1
   uint32_t                             ThreadDispatchPriority;
#define High                                     1
   uint32_t                             BindingTableEntryCount;
   uint32_t                             SamplerCount;
#define NoSamplers                               0
#define _14Samplers                              1
#define _58Samplers                              2
#define _912Samplers                             3
#define _1316Samplers                            4
   bool                                 VectorMaskEnable;
   uint32_t                             PerThreadScratchSpace;
   __gen_address_type                   ScratchSpaceBasePointer;
   uint32_t                             PatchURBEntryReadOffset;
   uint32_t                             PatchURBEntryReadLength;
   uint32_t                             DispatchGRFStartRegisterForURBData;
   bool                                 Enable;
   bool                                 CacheDisable;
   bool                                 ComputeWCoordinateEnable;
   uint32_t                             DispatchMode;
#define DISPATCH_MODE_SIMD4X2                    0
#define DISPATCH_MODE_SIMD8_SINGLE_PATCH         1
#define DISPATCH_MODE_SIMD8_SINGLE_OR_DUAL_PATCH 2
   bool                                 StatisticsEnable;
   uint32_t                             MaximumNumberofThreads;
   uint32_t                             UserClipDistanceCullTestEnableBitmask;
   uint32_t                             UserClipDistanceClipTestEnableBitmask;
   uint32_t                             VertexURBEntryOutputLength;
   uint32_t                             VertexURBEntryOutputReadOffset;
   uint64_t                             DUAL_PATCHKernelStartPointer;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_DS_pack(__attribute__((unused)) __gen_user_data *data,
                     __attribute__((unused)) void * restrict dst,
                     __attribute__((unused)) const struct GFX9_3DSTATE_DS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1 =
      __gen_offset(values->KernelStartPointer, 6, 63);
   dw[1] = v1;
   dw[2] = v1 >> 32;

   dw[3] =
      util_bitpack_uint(values->SoftwareExceptionEnable, 7, 7) |
      util_bitpack_uint(values->IllegalOpcodeExceptionEnable, 13, 13) |
      util_bitpack_uint(values->AccessesUAV, 14, 14) |
      util_bitpack_uint(values->FloatingPointMode, 16, 16) |
      util_bitpack_uint(values->ThreadDispatchPriority, 17, 17) |
      util_bitpack_uint(values->BindingTableEntryCount, 18, 25) |
      util_bitpack_uint(values->SamplerCount, 27, 29) |
      util_bitpack_uint(values->VectorMaskEnable, 30, 30);

   const uint64_t v4 =
      util_bitpack_uint(values->PerThreadScratchSpace, 0, 3);
   const uint64_t v4_address =
      __gen_address(data, &dw[4], values->ScratchSpaceBasePointer, v4, 10, 63);
   dw[4] = v4_address;
   dw[5] = (v4_address >> 32) | (v4 >> 32);

   dw[6] =
      util_bitpack_uint(values->PatchURBEntryReadOffset, 4, 9) |
      util_bitpack_uint(values->PatchURBEntryReadLength, 11, 17) |
      util_bitpack_uint(values->DispatchGRFStartRegisterForURBData, 20, 24);

   dw[7] =
      util_bitpack_uint(values->Enable, 0, 0) |
      util_bitpack_uint(values->CacheDisable, 1, 1) |
      util_bitpack_uint(values->ComputeWCoordinateEnable, 2, 2) |
      util_bitpack_uint(values->DispatchMode, 3, 4) |
      util_bitpack_uint(values->StatisticsEnable, 10, 10) |
      util_bitpack_uint(values->MaximumNumberofThreads, 21, 29);

   dw[8] =
      util_bitpack_uint(values->UserClipDistanceCullTestEnableBitmask, 0, 7) |
      util_bitpack_uint(values->UserClipDistanceClipTestEnableBitmask, 8, 15) |
      util_bitpack_uint(values->VertexURBEntryOutputLength, 16, 20) |
      util_bitpack_uint(values->VertexURBEntryOutputReadOffset, 21, 26);

   const uint64_t v9 =
      __gen_offset(values->DUAL_PATCHKernelStartPointer, 6, 63);
   dw[9] = v9;
   dw[10] = v9 >> 32;
}

#define GFX9_3DSTATE_GATHER_CONSTANT_DS_length_bias      2
#define GFX9_3DSTATE_GATHER_CONSTANT_DS_header  \
   .DWordLength                         =      1,  \
   ._3DCommandSubOpcode                 =     55,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_GATHER_CONSTANT_DS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             UpdateGatherTableOnly;
#define CommitGather                             0
#define NonCommitGather                          1
   uint32_t                             ConstantBufferBindingTableBlock;
   uint32_t                             ConstantBufferValid;
   uint32_t                             OnDieTable;
#define Load                                     0
#define Read                                     1
   bool                                 ConstantBufferDx9GenerateStall;
   uint64_t                             GatherBufferOffset;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_GATHER_CONSTANT_DS_pack(__attribute__((unused)) __gen_user_data *data,
                                     __attribute__((unused)) void * restrict dst,
                                     __attribute__((unused)) const struct GFX9_3DSTATE_GATHER_CONSTANT_DS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->UpdateGatherTableOnly, 1, 1) |
      util_bitpack_uint(values->ConstantBufferBindingTableBlock, 12, 15) |
      util_bitpack_uint(values->ConstantBufferValid, 16, 31);

   dw[2] =
      util_bitpack_uint(values->OnDieTable, 3, 3) |
      util_bitpack_uint(values->ConstantBufferDx9GenerateStall, 5, 5) |
      __gen_offset(values->GatherBufferOffset, 6, 22);
}

#define GFX9_3DSTATE_GATHER_CONSTANT_GS_length_bias      2
#define GFX9_3DSTATE_GATHER_CONSTANT_GS_header  \
   .DWordLength                         =      1,  \
   ._3DCommandSubOpcode                 =     53,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_GATHER_CONSTANT_GS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             UpdateGatherTableOnly;
#define CommitGather                             0
#define NonCommitGather                          1
   uint32_t                             ConstantBufferBindingTableBlock;
   uint32_t                             ConstantBufferValid;
   uint32_t                             OnDieTable;
#define Load                                     0
#define Read                                     1
   bool                                 ConstantBufferDx9GenerateStall;
   uint64_t                             GatherBufferOffset;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_GATHER_CONSTANT_GS_pack(__attribute__((unused)) __gen_user_data *data,
                                     __attribute__((unused)) void * restrict dst,
                                     __attribute__((unused)) const struct GFX9_3DSTATE_GATHER_CONSTANT_GS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->UpdateGatherTableOnly, 1, 1) |
      util_bitpack_uint(values->ConstantBufferBindingTableBlock, 12, 15) |
      util_bitpack_uint(values->ConstantBufferValid, 16, 31);

   dw[2] =
      util_bitpack_uint(values->OnDieTable, 3, 3) |
      util_bitpack_uint(values->ConstantBufferDx9GenerateStall, 5, 5) |
      __gen_offset(values->GatherBufferOffset, 6, 22);
}

#define GFX9_3DSTATE_GATHER_CONSTANT_HS_length_bias      2
#define GFX9_3DSTATE_GATHER_CONSTANT_HS_header  \
   .DWordLength                         =      1,  \
   ._3DCommandSubOpcode                 =     54,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_GATHER_CONSTANT_HS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             UpdateGatherTableOnly;
#define CommitGather                             0
#define NonCommitGather                          1
   uint32_t                             ConstantBufferBindingTableBlock;
   uint32_t                             ConstantBufferValid;
   uint32_t                             OnDieTable;
#define Load                                     0
#define Read                                     1
   bool                                 ConstantBufferDx9GenerateStall;
   uint64_t                             GatherBufferOffset;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_GATHER_CONSTANT_HS_pack(__attribute__((unused)) __gen_user_data *data,
                                     __attribute__((unused)) void * restrict dst,
                                     __attribute__((unused)) const struct GFX9_3DSTATE_GATHER_CONSTANT_HS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->UpdateGatherTableOnly, 1, 1) |
      util_bitpack_uint(values->ConstantBufferBindingTableBlock, 12, 15) |
      util_bitpack_uint(values->ConstantBufferValid, 16, 31);

   dw[2] =
      util_bitpack_uint(values->OnDieTable, 3, 3) |
      util_bitpack_uint(values->ConstantBufferDx9GenerateStall, 5, 5) |
      __gen_offset(values->GatherBufferOffset, 6, 22);
}

#define GFX9_3DSTATE_GATHER_CONSTANT_PS_length_bias      2
#define GFX9_3DSTATE_GATHER_CONSTANT_PS_header  \
   .DWordLength                         =      1,  \
   ._3DCommandSubOpcode                 =     56,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_GATHER_CONSTANT_PS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   bool                                 DX9OnDieRegisterReadEnable;
   uint32_t                             UpdateGatherTableOnly;
#define CommitGather                             0
#define NonCommitGather                          1
   uint32_t                             ConstantBufferBindingTableBlock;
   uint32_t                             ConstantBufferValid;
   uint32_t                             OnDieTable;
#define Load                                     0
#define Read                                     1
   bool                                 ConstantBufferDx9Enable;
   bool                                 ConstantBufferDx9GenerateStall;
   uint64_t                             GatherBufferOffset;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_GATHER_CONSTANT_PS_pack(__attribute__((unused)) __gen_user_data *data,
                                     __attribute__((unused)) void * restrict dst,
                                     __attribute__((unused)) const struct GFX9_3DSTATE_GATHER_CONSTANT_PS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->DX9OnDieRegisterReadEnable, 0, 0) |
      util_bitpack_uint(values->UpdateGatherTableOnly, 1, 1) |
      util_bitpack_uint(values->ConstantBufferBindingTableBlock, 12, 15) |
      util_bitpack_uint(values->ConstantBufferValid, 16, 31);

   dw[2] =
      util_bitpack_uint(values->OnDieTable, 3, 3) |
      util_bitpack_uint(values->ConstantBufferDx9Enable, 4, 4) |
      util_bitpack_uint(values->ConstantBufferDx9GenerateStall, 5, 5) |
      __gen_offset(values->GatherBufferOffset, 6, 22);
}

#define GFX9_3DSTATE_GATHER_CONSTANT_VS_length_bias      2
#define GFX9_3DSTATE_GATHER_CONSTANT_VS_header  \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     52,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_GATHER_CONSTANT_VS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   bool                                 DX9OnDieRegisterReadEnable;
   uint32_t                             UpdateGatherTableOnly;
#define CommitGather                             0
#define NonCommitGather                          1
   uint32_t                             ConstantBufferBindingTableBlock;
   uint32_t                             ConstantBufferValid;
   uint32_t                             OnDieTable;
#define Load                                     0
#define Read                                     1
   bool                                 ConstantBufferDx9Enable;
   bool                                 ConstantBufferDx9GenerateStall;
   uint64_t                             GatherBufferOffset;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_GATHER_CONSTANT_VS_pack(__attribute__((unused)) __gen_user_data *data,
                                     __attribute__((unused)) void * restrict dst,
                                     __attribute__((unused)) const struct GFX9_3DSTATE_GATHER_CONSTANT_VS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->DX9OnDieRegisterReadEnable, 0, 0) |
      util_bitpack_uint(values->UpdateGatherTableOnly, 1, 1) |
      util_bitpack_uint(values->ConstantBufferBindingTableBlock, 12, 15) |
      util_bitpack_uint(values->ConstantBufferValid, 16, 31);

   dw[2] =
      util_bitpack_uint(values->OnDieTable, 3, 3) |
      util_bitpack_uint(values->ConstantBufferDx9Enable, 4, 4) |
      util_bitpack_uint(values->ConstantBufferDx9GenerateStall, 5, 5) |
      __gen_offset(values->GatherBufferOffset, 6, 22);
}

#define GFX9_3DSTATE_GATHER_POOL_ALLOC_length      4
#define GFX9_3DSTATE_GATHER_POOL_ALLOC_length_bias      2
#define GFX9_3DSTATE_GATHER_POOL_ALLOC_header   \
   .DWordLength                         =      2,  \
   ._3DCommandSubOpcode                 =     26,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_GATHER_POOL_ALLOC {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             MOCS;
   bool                                 GatherPoolEnable;
   __gen_address_type                   GatherPoolBaseAddress;
   uint32_t                             GatherPoolBufferSize;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_GATHER_POOL_ALLOC_pack(__attribute__((unused)) __gen_user_data *data,
                                    __attribute__((unused)) void * restrict dst,
                                    __attribute__((unused)) const struct GFX9_3DSTATE_GATHER_POOL_ALLOC * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1 =
      util_bitpack_uint_nonzero(values->MOCS, 0, 6) |
      util_bitpack_uint(values->GatherPoolEnable, 11, 11);
   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->GatherPoolBaseAddress, v1, 12, 63);
   dw[1] = v1_address;
   dw[2] = (v1_address >> 32) | (v1 >> 32);

   dw[3] =
      util_bitpack_uint(values->GatherPoolBufferSize, 12, 31);
}

#define GFX9_3DSTATE_GS_length                10
#define GFX9_3DSTATE_GS_length_bias            2
#define GFX9_3DSTATE_GS_header                  \
   .DWordLength                         =      8,  \
   ._3DCommandSubOpcode                 =     17,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_GS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             KernelStartPointer;
   uint32_t                             ExpectedVertexCount;
   bool                                 SoftwareExceptionEnable;
   bool                                 MaskStackExceptionEnable;
   bool                                 AccessesUAV;
   bool                                 IllegalOpcodeExceptionEnable;
   uint32_t                             FloatingPointMode;
#define IEEE754                                  0
#define Alternate                                1
   uint32_t                             ThreadDispatchPriority;
#define High                                     1
   uint32_t                             BindingTableEntryCount;
   uint32_t                             SamplerCount;
#define NoSamplers                               0
#define _14Samplers                              1
#define _58Samplers                              2
#define _912Samplers                             3
#define _1316Samplers                            4
   bool                                 VectorMaskEnable;
   bool                                 SingleProgramFlow;
   uint32_t                             PerThreadScratchSpace;
   __gen_address_type                   ScratchSpaceBasePointer;
   uint32_t                             DispatchGRFStartRegisterForURBData;
   uint32_t                             VertexURBEntryReadOffset;
   bool                                 IncludeVertexHandles;
   uint32_t                             VertexURBEntryReadLength;
   enum GFX9_3D_Prim_Topo_Type          OutputTopology;
   uint32_t                             OutputVertexSize;
   uint32_t                             DispatchGRFStartRegisterForURBData54;
   bool                                 Enable;
   bool                                 DiscardAdjacency;
   uint32_t                             ReorderMode;
#define LEADING                                  0
#define TRAILING                                 1
   uint32_t                             Hint;
   bool                                 IncludePrimitiveID;
   uint32_t                             InvocationsIncrementValue;
   bool                                 StatisticsEnable;
   uint32_t                             DispatchMode;
#define DISPATCH_MODE_DualInstance               1
#define DISPATCH_MODE_DualObject                 2
#define DISPATCH_MODE_SIMD8                      3
   uint32_t                             DefaultStreamId;
   uint32_t                             InstanceControl;
   uint32_t                             ControlDataHeaderSize;
   uint32_t                             MaximumNumberofThreads;
   uint32_t                             StaticOutputVertexCount;
   bool                                 StaticOutput;
   uint32_t                             ControlDataFormat;
#define CUT                                      0
#define SID                                      1
   uint32_t                             UserClipDistanceCullTestEnableBitmask;
   uint32_t                             UserClipDistanceClipTestEnableBitmask;
   uint32_t                             VertexURBEntryOutputLength;
   uint32_t                             VertexURBEntryOutputReadOffset;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_GS_pack(__attribute__((unused)) __gen_user_data *data,
                     __attribute__((unused)) void * restrict dst,
                     __attribute__((unused)) const struct GFX9_3DSTATE_GS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1 =
      __gen_offset(values->KernelStartPointer, 6, 63);
   dw[1] = v1;
   dw[2] = v1 >> 32;

   dw[3] =
      util_bitpack_uint(values->ExpectedVertexCount, 0, 5) |
      util_bitpack_uint(values->SoftwareExceptionEnable, 7, 7) |
      util_bitpack_uint(values->MaskStackExceptionEnable, 11, 11) |
      util_bitpack_uint(values->AccessesUAV, 12, 12) |
      util_bitpack_uint(values->IllegalOpcodeExceptionEnable, 13, 13) |
      util_bitpack_uint(values->FloatingPointMode, 16, 16) |
      util_bitpack_uint(values->ThreadDispatchPriority, 17, 17) |
      util_bitpack_uint(values->BindingTableEntryCount, 18, 25) |
      util_bitpack_uint(values->SamplerCount, 27, 29) |
      util_bitpack_uint(values->VectorMaskEnable, 30, 30) |
      util_bitpack_uint(values->SingleProgramFlow, 31, 31);

   const uint64_t v4 =
      util_bitpack_uint(values->PerThreadScratchSpace, 0, 3);
   const uint64_t v4_address =
      __gen_address(data, &dw[4], values->ScratchSpaceBasePointer, v4, 10, 63);
   dw[4] = v4_address;
   dw[5] = (v4_address >> 32) | (v4 >> 32);

   dw[6] =
      util_bitpack_uint(values->DispatchGRFStartRegisterForURBData, 0, 3) |
      util_bitpack_uint(values->VertexURBEntryReadOffset, 4, 9) |
      util_bitpack_uint(values->IncludeVertexHandles, 10, 10) |
      util_bitpack_uint(values->VertexURBEntryReadLength, 11, 16) |
      util_bitpack_uint(values->OutputTopology, 17, 22) |
      util_bitpack_uint(values->OutputVertexSize, 23, 28) |
      util_bitpack_uint(values->DispatchGRFStartRegisterForURBData54, 29, 30);

   dw[7] =
      util_bitpack_uint(values->Enable, 0, 0) |
      util_bitpack_uint(values->DiscardAdjacency, 1, 1) |
      util_bitpack_uint(values->ReorderMode, 2, 2) |
      util_bitpack_uint(values->Hint, 3, 3) |
      util_bitpack_uint(values->IncludePrimitiveID, 4, 4) |
      util_bitpack_uint(values->InvocationsIncrementValue, 5, 9) |
      util_bitpack_uint(values->StatisticsEnable, 10, 10) |
      util_bitpack_uint(values->DispatchMode, 11, 12) |
      util_bitpack_uint(values->DefaultStreamId, 13, 14) |
      util_bitpack_uint(values->InstanceControl, 15, 19) |
      util_bitpack_uint(values->ControlDataHeaderSize, 20, 23);

   dw[8] =
      util_bitpack_uint(values->MaximumNumberofThreads, 0, 8) |
      util_bitpack_uint(values->StaticOutputVertexCount, 16, 26) |
      util_bitpack_uint(values->StaticOutput, 30, 30) |
      util_bitpack_uint(values->ControlDataFormat, 31, 31);

   dw[9] =
      util_bitpack_uint(values->UserClipDistanceCullTestEnableBitmask, 0, 7) |
      util_bitpack_uint(values->UserClipDistanceClipTestEnableBitmask, 8, 15) |
      util_bitpack_uint(values->VertexURBEntryOutputLength, 16, 20) |
      util_bitpack_uint(values->VertexURBEntryOutputReadOffset, 21, 26);
}

#define GFX9_3DSTATE_HIER_DEPTH_BUFFER_length      5
#define GFX9_3DSTATE_HIER_DEPTH_BUFFER_length_bias      2
#define GFX9_3DSTATE_HIER_DEPTH_BUFFER_header   \
   .DWordLength                         =      3,  \
   ._3DCommandSubOpcode                 =      7,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_HIER_DEPTH_BUFFER {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             SurfacePitch;
   uint32_t                             MOCS;
   __gen_address_type                   SurfaceBaseAddress;
   uint32_t                             SurfaceQPitch;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_HIER_DEPTH_BUFFER_pack(__attribute__((unused)) __gen_user_data *data,
                                    __attribute__((unused)) void * restrict dst,
                                    __attribute__((unused)) const struct GFX9_3DSTATE_HIER_DEPTH_BUFFER * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->SurfacePitch, 0, 16) |
      util_bitpack_uint_nonzero(values->MOCS, 25, 31);

   const uint64_t v2_address =
      __gen_address(data, &dw[2], values->SurfaceBaseAddress, 0, 0, 63);
   dw[2] = v2_address;
   dw[3] = v2_address >> 32;

   dw[4] =
      util_bitpack_uint(values->SurfaceQPitch, 0, 14);
}

#define GFX9_3DSTATE_HS_length                 9
#define GFX9_3DSTATE_HS_length_bias            2
#define GFX9_3DSTATE_HS_header                  \
   .DWordLength                         =      7,  \
   ._3DCommandSubOpcode                 =     27,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_HS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   bool                                 SoftwareExceptionEnable;
   bool                                 IllegalOpcodeExceptionEnable;
   uint32_t                             FloatingPointMode;
#define IEEE754                                  0
#define alternate                                1
   uint32_t                             ThreadDispatchPriority;
#define High                                     1
   uint32_t                             BindingTableEntryCount;
   uint32_t                             SamplerCount;
#define NoSamplers                               0
#define _14Samplers                              1
#define _58Samplers                              2
#define _912Samplers                             3
#define _1316Samplers                            4
   uint32_t                             InstanceCount;
   uint32_t                             MaximumNumberofThreads;
   bool                                 StatisticsEnable;
   bool                                 Enable;
   uint64_t                             KernelStartPointer;
   uint32_t                             PerThreadScratchSpace;
   __gen_address_type                   ScratchSpaceBasePointer;
   bool                                 IncludePrimitiveID;
   uint32_t                             VertexURBEntryReadOffset;
   uint32_t                             VertexURBEntryReadLength;
   uint32_t                             DispatchMode;
#define DISPATCH_MODE_SINGLE_PATCH               0
#define DISPATCH_MODE_DUAL_PATCH                 1
#define DISPATCH_MODE_8_PATCH                    2
   uint32_t                             DispatchGRFStartRegisterForURBData;
   bool                                 IncludeVertexHandles;
   bool                                 AccessesUAV;
   bool                                 VectorMaskEnable;
   bool                                 SingleProgramFlow;
   uint32_t                             DispatchGRFStartRegisterForURBData5;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_HS_pack(__attribute__((unused)) __gen_user_data *data,
                     __attribute__((unused)) void * restrict dst,
                     __attribute__((unused)) const struct GFX9_3DSTATE_HS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->SoftwareExceptionEnable, 12, 12) |
      util_bitpack_uint(values->IllegalOpcodeExceptionEnable, 13, 13) |
      util_bitpack_uint(values->FloatingPointMode, 16, 16) |
      util_bitpack_uint(values->ThreadDispatchPriority, 17, 17) |
      util_bitpack_uint(values->BindingTableEntryCount, 18, 25) |
      util_bitpack_uint(values->SamplerCount, 27, 29);

   dw[2] =
      util_bitpack_uint(values->InstanceCount, 0, 3) |
      util_bitpack_uint(values->MaximumNumberofThreads, 8, 16) |
      util_bitpack_uint(values->StatisticsEnable, 29, 29) |
      util_bitpack_uint(values->Enable, 31, 31);

   const uint64_t v3 =
      __gen_offset(values->KernelStartPointer, 6, 63);
   dw[3] = v3;
   dw[4] = v3 >> 32;

   const uint64_t v5 =
      util_bitpack_uint(values->PerThreadScratchSpace, 0, 3);
   const uint64_t v5_address =
      __gen_address(data, &dw[5], values->ScratchSpaceBasePointer, v5, 10, 63);
   dw[5] = v5_address;
   dw[6] = (v5_address >> 32) | (v5 >> 32);

   dw[7] =
      util_bitpack_uint(values->IncludePrimitiveID, 0, 0) |
      util_bitpack_uint(values->VertexURBEntryReadOffset, 4, 9) |
      util_bitpack_uint(values->VertexURBEntryReadLength, 11, 16) |
      util_bitpack_uint(values->DispatchMode, 17, 18) |
      util_bitpack_uint(values->DispatchGRFStartRegisterForURBData, 19, 23) |
      util_bitpack_uint(values->IncludeVertexHandles, 24, 24) |
      util_bitpack_uint(values->AccessesUAV, 25, 25) |
      util_bitpack_uint(values->VectorMaskEnable, 26, 26) |
      util_bitpack_uint(values->SingleProgramFlow, 27, 27) |
      util_bitpack_uint(values->DispatchGRFStartRegisterForURBData5, 28, 28);

   dw[8] = 0;
}

#define GFX9_3DSTATE_INDEX_BUFFER_length       5
#define GFX9_3DSTATE_INDEX_BUFFER_length_bias      2
#define GFX9_3DSTATE_INDEX_BUFFER_header        \
   .DWordLength                         =      3,  \
   ._3DCommandSubOpcode                 =     10,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_INDEX_BUFFER {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             MOCS;
   uint32_t                             IndexFormat;
#define INDEX_BYTE                               0
#define INDEX_WORD                               1
#define INDEX_DWORD                              2
   __gen_address_type                   BufferStartingAddress;
   uint32_t                             BufferSize;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_INDEX_BUFFER_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_3DSTATE_INDEX_BUFFER * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint_nonzero(values->MOCS, 0, 6) |
      util_bitpack_uint(values->IndexFormat, 8, 9);

   const uint64_t v2_address =
      __gen_address(data, &dw[2], values->BufferStartingAddress, 0, 0, 63);
   dw[2] = v2_address;
   dw[3] = v2_address >> 32;

   dw[4] =
      util_bitpack_uint(values->BufferSize, 0, 31);
}

#define GFX9_3DSTATE_LINE_STIPPLE_length       3
#define GFX9_3DSTATE_LINE_STIPPLE_length_bias      2
#define GFX9_3DSTATE_LINE_STIPPLE_header        \
   .DWordLength                         =      1,  \
   ._3DCommandSubOpcode                 =      8,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_LINE_STIPPLE {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             LineStipplePattern;
   uint32_t                             CurrentStippleIndex;
   uint32_t                             CurrentRepeatCounter;
   bool                                 ModifyEnableCurrentRepeatCounterCurrentStippleIndex;
   uint32_t                             LineStippleRepeatCount;
   float                                LineStippleInverseRepeatCount;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_LINE_STIPPLE_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_3DSTATE_LINE_STIPPLE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->LineStipplePattern, 0, 15) |
      util_bitpack_uint(values->CurrentStippleIndex, 16, 19) |
      util_bitpack_uint(values->CurrentRepeatCounter, 21, 29) |
      util_bitpack_uint(values->ModifyEnableCurrentRepeatCounterCurrentStippleIndex, 31, 31);

   dw[2] =
      util_bitpack_uint(values->LineStippleRepeatCount, 0, 8) |
      util_bitpack_ufixed(values->LineStippleInverseRepeatCount, 15, 31, 16);
}

#define GFX9_3DSTATE_MONOFILTER_SIZE_length      2
#define GFX9_3DSTATE_MONOFILTER_SIZE_length_bias      2
#define GFX9_3DSTATE_MONOFILTER_SIZE_header     \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     17,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_MONOFILTER_SIZE {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             MonochromeFilterHeight;
   uint32_t                             MonochromeFilterWidth;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_MONOFILTER_SIZE_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_3DSTATE_MONOFILTER_SIZE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->MonochromeFilterHeight, 0, 2) |
      util_bitpack_uint(values->MonochromeFilterWidth, 3, 5);
}

#define GFX9_3DSTATE_MULTISAMPLE_length        2
#define GFX9_3DSTATE_MULTISAMPLE_length_bias      2
#define GFX9_3DSTATE_MULTISAMPLE_header         \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     13,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_MULTISAMPLE {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             NumberofMultisamples;
   uint32_t                             PixelLocation;
#define CENTER                                   0
#define UL_CORNER                                1
   bool                                 PixelPositionOffsetEnable;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_MULTISAMPLE_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_3DSTATE_MULTISAMPLE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->NumberofMultisamples, 1, 3) |
      util_bitpack_uint(values->PixelLocation, 4, 4) |
      util_bitpack_uint(values->PixelPositionOffsetEnable, 5, 5);
}

#define GFX9_3DSTATE_POLY_STIPPLE_OFFSET_length      2
#define GFX9_3DSTATE_POLY_STIPPLE_OFFSET_length_bias      2
#define GFX9_3DSTATE_POLY_STIPPLE_OFFSET_header \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =      6,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_POLY_STIPPLE_OFFSET {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             PolygonStippleYOffset;
   uint32_t                             PolygonStippleXOffset;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_POLY_STIPPLE_OFFSET_pack(__attribute__((unused)) __gen_user_data *data,
                                      __attribute__((unused)) void * restrict dst,
                                      __attribute__((unused)) const struct GFX9_3DSTATE_POLY_STIPPLE_OFFSET * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->PolygonStippleYOffset, 0, 4) |
      util_bitpack_uint(values->PolygonStippleXOffset, 8, 12);
}

#define GFX9_3DSTATE_POLY_STIPPLE_PATTERN_length     33
#define GFX9_3DSTATE_POLY_STIPPLE_PATTERN_length_bias      2
#define GFX9_3DSTATE_POLY_STIPPLE_PATTERN_header\
   .DWordLength                         =     31,  \
   ._3DCommandSubOpcode                 =      7,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_POLY_STIPPLE_PATTERN {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             PatternRow[32];
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_POLY_STIPPLE_PATTERN_pack(__attribute__((unused)) __gen_user_data *data,
                                       __attribute__((unused)) void * restrict dst,
                                       __attribute__((unused)) const struct GFX9_3DSTATE_POLY_STIPPLE_PATTERN * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->PatternRow[0], 0, 31);

   dw[2] =
      util_bitpack_uint(values->PatternRow[1], 0, 31);

   dw[3] =
      util_bitpack_uint(values->PatternRow[2], 0, 31);

   dw[4] =
      util_bitpack_uint(values->PatternRow[3], 0, 31);

   dw[5] =
      util_bitpack_uint(values->PatternRow[4], 0, 31);

   dw[6] =
      util_bitpack_uint(values->PatternRow[5], 0, 31);

   dw[7] =
      util_bitpack_uint(values->PatternRow[6], 0, 31);

   dw[8] =
      util_bitpack_uint(values->PatternRow[7], 0, 31);

   dw[9] =
      util_bitpack_uint(values->PatternRow[8], 0, 31);

   dw[10] =
      util_bitpack_uint(values->PatternRow[9], 0, 31);

   dw[11] =
      util_bitpack_uint(values->PatternRow[10], 0, 31);

   dw[12] =
      util_bitpack_uint(values->PatternRow[11], 0, 31);

   dw[13] =
      util_bitpack_uint(values->PatternRow[12], 0, 31);

   dw[14] =
      util_bitpack_uint(values->PatternRow[13], 0, 31);

   dw[15] =
      util_bitpack_uint(values->PatternRow[14], 0, 31);

   dw[16] =
      util_bitpack_uint(values->PatternRow[15], 0, 31);

   dw[17] =
      util_bitpack_uint(values->PatternRow[16], 0, 31);

   dw[18] =
      util_bitpack_uint(values->PatternRow[17], 0, 31);

   dw[19] =
      util_bitpack_uint(values->PatternRow[18], 0, 31);

   dw[20] =
      util_bitpack_uint(values->PatternRow[19], 0, 31);

   dw[21] =
      util_bitpack_uint(values->PatternRow[20], 0, 31);

   dw[22] =
      util_bitpack_uint(values->PatternRow[21], 0, 31);

   dw[23] =
      util_bitpack_uint(values->PatternRow[22], 0, 31);

   dw[24] =
      util_bitpack_uint(values->PatternRow[23], 0, 31);

   dw[25] =
      util_bitpack_uint(values->PatternRow[24], 0, 31);

   dw[26] =
      util_bitpack_uint(values->PatternRow[25], 0, 31);

   dw[27] =
      util_bitpack_uint(values->PatternRow[26], 0, 31);

   dw[28] =
      util_bitpack_uint(values->PatternRow[27], 0, 31);

   dw[29] =
      util_bitpack_uint(values->PatternRow[28], 0, 31);

   dw[30] =
      util_bitpack_uint(values->PatternRow[29], 0, 31);

   dw[31] =
      util_bitpack_uint(values->PatternRow[30], 0, 31);

   dw[32] =
      util_bitpack_uint(values->PatternRow[31], 0, 31);
}

#define GFX9_3DSTATE_PS_length                12
#define GFX9_3DSTATE_PS_length_bias            2
#define GFX9_3DSTATE_PS_header                  \
   .DWordLength                         =     10,  \
   ._3DCommandSubOpcode                 =     32,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_PS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             KernelStartPointer0;
   bool                                 SoftwareExceptionEnable;
   bool                                 MaskStackExceptionEnable;
   bool                                 IllegalOpcodeExceptionEnable;
   uint32_t                             RoundingMode;
#define RTNE                                     0
#define RU                                       1
#define RD                                       2
#define RTZ                                      3
   uint32_t                             FloatingPointMode;
#define IEEE754                                  0
#define Alternate                                1
   uint32_t                             ThreadDispatchPriority;
#define High                                     1
   uint32_t                             BindingTableEntryCount;
   uint32_t                             SinglePrecisionDenormalMode;
#define FlushedtoZero                            0
#define Retained                                 1
   uint32_t                             SamplerCount;
#define NoSamplers                               0
#define _14Samplers                              1
#define _58Samplers                              2
#define _912Samplers                             3
#define _1316Samplers                            4
   bool                                 VectorMaskEnable;
   bool                                 SingleProgramFlow;
   uint32_t                             PerThreadScratchSpace;
   __gen_address_type                   ScratchSpaceBasePointer;
   bool                                 _8PixelDispatchEnable;
   bool                                 _16PixelDispatchEnable;
   bool                                 _32PixelDispatchEnable;
   uint32_t                             PositionXYOffsetSelect;
#define POSOFFSET_NONE                           0
#define POSOFFSET_CENTROID                       2
#define POSOFFSET_SAMPLE                         3
   uint32_t                             RenderTargetResolveType;
#define RESOLVE_DISABLED                         0
#define RESOLVE_PARTIAL                          1
#define RESOLVE_FULL                             3
   bool                                 RenderTargetFastClearEnable;
   bool                                 PushConstantEnable;
   uint32_t                             MaximumNumberofThreadsPerPSD;
   uint32_t                             DispatchGRFStartRegisterForConstantSetupData2;
   uint32_t                             DispatchGRFStartRegisterForConstantSetupData1;
   uint32_t                             DispatchGRFStartRegisterForConstantSetupData0;
   uint64_t                             KernelStartPointer1;
   uint64_t                             KernelStartPointer2;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_PS_pack(__attribute__((unused)) __gen_user_data *data,
                     __attribute__((unused)) void * restrict dst,
                     __attribute__((unused)) const struct GFX9_3DSTATE_PS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1 =
      __gen_offset(values->KernelStartPointer0, 6, 63);
   dw[1] = v1;
   dw[2] = v1 >> 32;

   dw[3] =
      util_bitpack_uint(values->SoftwareExceptionEnable, 7, 7) |
      util_bitpack_uint(values->MaskStackExceptionEnable, 11, 11) |
      util_bitpack_uint(values->IllegalOpcodeExceptionEnable, 13, 13) |
      util_bitpack_uint(values->RoundingMode, 14, 15) |
      util_bitpack_uint(values->FloatingPointMode, 16, 16) |
      util_bitpack_uint(values->ThreadDispatchPriority, 17, 17) |
      util_bitpack_uint(values->BindingTableEntryCount, 18, 25) |
      util_bitpack_uint(values->SinglePrecisionDenormalMode, 26, 26) |
      util_bitpack_uint(values->SamplerCount, 27, 29) |
      util_bitpack_uint(values->VectorMaskEnable, 30, 30) |
      util_bitpack_uint(values->SingleProgramFlow, 31, 31);

   const uint64_t v4 =
      util_bitpack_uint(values->PerThreadScratchSpace, 0, 3);
   const uint64_t v4_address =
      __gen_address(data, &dw[4], values->ScratchSpaceBasePointer, v4, 10, 63);
   dw[4] = v4_address;
   dw[5] = (v4_address >> 32) | (v4 >> 32);

   dw[6] =
      util_bitpack_uint(values->_8PixelDispatchEnable, 0, 0) |
      util_bitpack_uint(values->_16PixelDispatchEnable, 1, 1) |
      util_bitpack_uint(values->_32PixelDispatchEnable, 2, 2) |
      util_bitpack_uint(values->PositionXYOffsetSelect, 3, 4) |
      util_bitpack_uint(values->RenderTargetResolveType, 6, 7) |
      util_bitpack_uint(values->RenderTargetFastClearEnable, 8, 8) |
      util_bitpack_uint(values->PushConstantEnable, 11, 11) |
      util_bitpack_uint(values->MaximumNumberofThreadsPerPSD, 23, 31);

   dw[7] =
      util_bitpack_uint(values->DispatchGRFStartRegisterForConstantSetupData2, 0, 6) |
      util_bitpack_uint(values->DispatchGRFStartRegisterForConstantSetupData1, 8, 14) |
      util_bitpack_uint(values->DispatchGRFStartRegisterForConstantSetupData0, 16, 22);

   const uint64_t v8 =
      __gen_offset(values->KernelStartPointer1, 6, 63);
   dw[8] = v8;
   dw[9] = v8 >> 32;

   const uint64_t v10 =
      __gen_offset(values->KernelStartPointer2, 6, 63);
   dw[10] = v10;
   dw[11] = v10 >> 32;
}

#define GFX9_3DSTATE_PS_BLEND_length           2
#define GFX9_3DSTATE_PS_BLEND_length_bias      2
#define GFX9_3DSTATE_PS_BLEND_header            \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     77,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_PS_BLEND {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   bool                                 IndependentAlphaBlendEnable;
   bool                                 AlphaTestEnable;
   enum GFX9_3D_Color_Buffer_Blend_Factor DestinationBlendFactor;
   enum GFX9_3D_Color_Buffer_Blend_Factor SourceBlendFactor;
   enum GFX9_3D_Color_Buffer_Blend_Factor DestinationAlphaBlendFactor;
   enum GFX9_3D_Color_Buffer_Blend_Factor SourceAlphaBlendFactor;
   bool                                 ColorBufferBlendEnable;
   bool                                 HasWriteableRT;
   bool                                 AlphaToCoverageEnable;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_PS_BLEND_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_3DSTATE_PS_BLEND * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->IndependentAlphaBlendEnable, 7, 7) |
      util_bitpack_uint(values->AlphaTestEnable, 8, 8) |
      util_bitpack_uint(values->DestinationBlendFactor, 9, 13) |
      util_bitpack_uint(values->SourceBlendFactor, 14, 18) |
      util_bitpack_uint(values->DestinationAlphaBlendFactor, 19, 23) |
      util_bitpack_uint(values->SourceAlphaBlendFactor, 24, 28) |
      util_bitpack_uint(values->ColorBufferBlendEnable, 29, 29) |
      util_bitpack_uint(values->HasWriteableRT, 30, 30) |
      util_bitpack_uint(values->AlphaToCoverageEnable, 31, 31);
}

#define GFX9_3DSTATE_PS_EXTRA_length           2
#define GFX9_3DSTATE_PS_EXTRA_length_bias      2
#define GFX9_3DSTATE_PS_EXTRA_header            \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     79,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_PS_EXTRA {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             InputCoverageMaskState;
#define ICMS_NONE                                0
#define ICMS_NORMAL                              1
#define ICMS_INNER_CONSERVATIVE                  2
#define ICMS_DEPTH_COVERAGE                      3
   bool                                 PixelShaderHasUAV;
   bool                                 PixelShaderPullsBary;
   bool                                 PixelShaderComputesStencil;
   bool                                 PixelShaderIsPerSample;
   bool                                 PixelShaderDisablesAlphaToCoverage;
   bool                                 AttributeEnable;
   bool                                 PixelShaderUsesSourceW;
   bool                                 PixelShaderUsesSourceDepth;
   bool                                 ForceComputedDepth;
   uint32_t                             PixelShaderComputedDepthMode;
#define PSCDEPTH_OFF                             0
#define PSCDEPTH_ON                              1
#define PSCDEPTH_ON_GE                           2
#define PSCDEPTH_ON_LE                           3
   bool                                 PixelShaderKillsPixel;
   bool                                 oMaskPresenttoRenderTarget;
   bool                                 PixelShaderValid;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_PS_EXTRA_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_3DSTATE_PS_EXTRA * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->InputCoverageMaskState, 0, 1) |
      util_bitpack_uint(values->PixelShaderHasUAV, 2, 2) |
      util_bitpack_uint(values->PixelShaderPullsBary, 3, 3) |
      util_bitpack_uint(values->PixelShaderComputesStencil, 5, 5) |
      util_bitpack_uint(values->PixelShaderIsPerSample, 6, 6) |
      util_bitpack_uint(values->PixelShaderDisablesAlphaToCoverage, 7, 7) |
      util_bitpack_uint(values->AttributeEnable, 8, 8) |
      util_bitpack_uint(values->PixelShaderUsesSourceW, 23, 23) |
      util_bitpack_uint(values->PixelShaderUsesSourceDepth, 24, 24) |
      util_bitpack_uint(values->ForceComputedDepth, 25, 25) |
      util_bitpack_uint(values->PixelShaderComputedDepthMode, 26, 27) |
      util_bitpack_uint(values->PixelShaderKillsPixel, 28, 28) |
      util_bitpack_uint(values->oMaskPresenttoRenderTarget, 29, 29) |
      util_bitpack_uint(values->PixelShaderValid, 31, 31);
}

#define GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_DS_length      2
#define GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_DS_length_bias      2
#define GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_DS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     20,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_DS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             ConstantBufferSize;
   uint32_t                             ConstantBufferOffset;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_DS_pack(__attribute__((unused)) __gen_user_data *data,
                                         __attribute__((unused)) void * restrict dst,
                                         __attribute__((unused)) const struct GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_DS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ConstantBufferSize, 0, 5) |
      util_bitpack_uint(values->ConstantBufferOffset, 16, 20);
}

#define GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_GS_length      2
#define GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_GS_length_bias      2
#define GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_GS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     21,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_GS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             ConstantBufferSize;
   uint32_t                             ConstantBufferOffset;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_GS_pack(__attribute__((unused)) __gen_user_data *data,
                                         __attribute__((unused)) void * restrict dst,
                                         __attribute__((unused)) const struct GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_GS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ConstantBufferSize, 0, 5) |
      util_bitpack_uint(values->ConstantBufferOffset, 16, 20);
}

#define GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_HS_length      2
#define GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_HS_length_bias      2
#define GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_HS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     19,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_HS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             ConstantBufferSize;
   uint32_t                             ConstantBufferOffset;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_HS_pack(__attribute__((unused)) __gen_user_data *data,
                                         __attribute__((unused)) void * restrict dst,
                                         __attribute__((unused)) const struct GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_HS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ConstantBufferSize, 0, 5) |
      util_bitpack_uint(values->ConstantBufferOffset, 16, 20);
}

#define GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_PS_length      2
#define GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_PS_length_bias      2
#define GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_PS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     22,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_PS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             ConstantBufferSize;
   uint32_t                             ConstantBufferOffset;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_PS_pack(__attribute__((unused)) __gen_user_data *data,
                                         __attribute__((unused)) void * restrict dst,
                                         __attribute__((unused)) const struct GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_PS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ConstantBufferSize, 0, 5) |
      util_bitpack_uint(values->ConstantBufferOffset, 16, 20);
}

#define GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_VS_length      2
#define GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_VS_length_bias      2
#define GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_VS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     18,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_VS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             ConstantBufferSize;
   uint32_t                             ConstantBufferOffset;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_VS_pack(__attribute__((unused)) __gen_user_data *data,
                                         __attribute__((unused)) void * restrict dst,
                                         __attribute__((unused)) const struct GFX9_3DSTATE_PUSH_CONSTANT_ALLOC_VS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ConstantBufferSize, 0, 5) |
      util_bitpack_uint(values->ConstantBufferOffset, 16, 20);
}

#define GFX9_3DSTATE_RASTER_length             5
#define GFX9_3DSTATE_RASTER_length_bias        2
#define GFX9_3DSTATE_RASTER_header              \
   .DWordLength                         =      3,  \
   ._3DCommandSubOpcode                 =     80,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_RASTER {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   bool                                 ViewportZNearClipTestEnable;
   bool                                 ScissorRectangleEnable;
   bool                                 AntialiasingEnable;
   uint32_t                             BackFaceFillMode;
#define FILL_MODE_SOLID                          0
#define FILL_MODE_WIREFRAME                      1
#define FILL_MODE_POINT                          2
   uint32_t                             FrontFaceFillMode;
#define FILL_MODE_SOLID                          0
#define FILL_MODE_WIREFRAME                      1
#define FILL_MODE_POINT                          2
   bool                                 GlobalDepthOffsetEnablePoint;
   bool                                 GlobalDepthOffsetEnableWireframe;
   bool                                 GlobalDepthOffsetEnableSolid;
   uint32_t                             DXMultisampleRasterizationMode;
#define MSRASTMODE_OFF_PIXEL                     0
#define MSRASTMODE_OFF_PATTERN                   1
#define MSRASTMODE_ON_PIXEL                      2
#define MSRASTMODE_ON_PATTERN                    3
   bool                                 DXMultisampleRasterizationEnable;
   bool                                 SmoothPointEnable;
   uint32_t                             ForceMultisampling;
   uint32_t                             CullMode;
#define CULLMODE_BOTH                            0
#define CULLMODE_NONE                            1
#define CULLMODE_FRONT                           2
#define CULLMODE_BACK                            3
   uint32_t                             ForcedSampleCount;
#define FSC_NUMRASTSAMPLES_0                     0
#define FSC_NUMRASTSAMPLES_1                     1
#define FSC_NUMRASTSAMPLES_2                     2
#define FSC_NUMRASTSAMPLES_4                     3
#define FSC_NUMRASTSAMPLES_8                     4
#define FSC_NUMRASTSAMPLES_16                    5
   uint32_t                             FrontWinding;
#define Clockwise                                0
#define CounterClockwise                         1
   uint32_t                             APIMode;
#define DX9OGL                                   0
#define DX100                                    1
#define DX101                                    2
   bool                                 ConservativeRasterizationEnable;
   bool                                 ViewportZFarClipTestEnable;
   float                                GlobalDepthOffsetConstant;
   float                                GlobalDepthOffsetScale;
   float                                GlobalDepthOffsetClamp;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_RASTER_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_3DSTATE_RASTER * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ViewportZNearClipTestEnable, 0, 0) |
      util_bitpack_uint(values->ScissorRectangleEnable, 1, 1) |
      util_bitpack_uint(values->AntialiasingEnable, 2, 2) |
      util_bitpack_uint(values->BackFaceFillMode, 3, 4) |
      util_bitpack_uint(values->FrontFaceFillMode, 5, 6) |
      util_bitpack_uint(values->GlobalDepthOffsetEnablePoint, 7, 7) |
      util_bitpack_uint(values->GlobalDepthOffsetEnableWireframe, 8, 8) |
      util_bitpack_uint(values->GlobalDepthOffsetEnableSolid, 9, 9) |
      util_bitpack_uint(values->DXMultisampleRasterizationMode, 10, 11) |
      util_bitpack_uint(values->DXMultisampleRasterizationEnable, 12, 12) |
      util_bitpack_uint(values->SmoothPointEnable, 13, 13) |
      util_bitpack_uint(values->ForceMultisampling, 14, 14) |
      util_bitpack_uint(values->CullMode, 16, 17) |
      util_bitpack_uint(values->ForcedSampleCount, 18, 20) |
      util_bitpack_uint(values->FrontWinding, 21, 21) |
      util_bitpack_uint(values->APIMode, 22, 23) |
      util_bitpack_uint(values->ConservativeRasterizationEnable, 24, 24) |
      util_bitpack_uint(values->ViewportZFarClipTestEnable, 26, 26);

   dw[2] =
      util_bitpack_float(values->GlobalDepthOffsetConstant);

   dw[3] =
      util_bitpack_float(values->GlobalDepthOffsetScale);

   dw[4] =
      util_bitpack_float(values->GlobalDepthOffsetClamp);
}

#define GFX9_3DSTATE_RS_CONSTANT_POINTER_length      4
#define GFX9_3DSTATE_RS_CONSTANT_POINTER_length_bias      2
#define GFX9_3DSTATE_RS_CONSTANT_POINTER_header \
   .DWordLength                         =      2,  \
   ._3DCommandSubOpcode                 =     84,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_RS_CONSTANT_POINTER {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             OperationLoadorStore;
#define RS_Store                                 0
#define RS_Load                                  1
   uint32_t                             ShaderSelect;
#define VS                                       0
#define PS                                       4
   __gen_address_type                   GlobalConstantBufferAddress;
   __gen_address_type                   GlobalConstantBufferAddressHigh;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_RS_CONSTANT_POINTER_pack(__attribute__((unused)) __gen_user_data *data,
                                      __attribute__((unused)) void * restrict dst,
                                      __attribute__((unused)) const struct GFX9_3DSTATE_RS_CONSTANT_POINTER * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->OperationLoadorStore, 12, 12) |
      util_bitpack_uint(values->ShaderSelect, 28, 30);

   dw[2] = __gen_address(data, &dw[2], values->GlobalConstantBufferAddress, 0, 6, 31);

   dw[3] = __gen_address(data, &dw[3], values->GlobalConstantBufferAddressHigh, 0, 0, 31);
}

#define GFX9_3DSTATE_SAMPLER_PALETTE_LOAD0_length_bias      2
#define GFX9_3DSTATE_SAMPLER_PALETTE_LOAD0_header\
   ._3DCommandSubOpcode                 =      2,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_SAMPLER_PALETTE_LOAD0 {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_SAMPLER_PALETTE_LOAD0_pack(__attribute__((unused)) __gen_user_data *data,
                                        __attribute__((unused)) void * restrict dst,
                                        __attribute__((unused)) const struct GFX9_3DSTATE_SAMPLER_PALETTE_LOAD0 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_3DSTATE_SAMPLER_PALETTE_LOAD1_length_bias      2
#define GFX9_3DSTATE_SAMPLER_PALETTE_LOAD1_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     12,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_SAMPLER_PALETTE_LOAD1 {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_SAMPLER_PALETTE_LOAD1_pack(__attribute__((unused)) __gen_user_data *data,
                                        __attribute__((unused)) void * restrict dst,
                                        __attribute__((unused)) const struct GFX9_3DSTATE_SAMPLER_PALETTE_LOAD1 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_3DSTATE_SAMPLER_STATE_POINTERS_DS_length      2
#define GFX9_3DSTATE_SAMPLER_STATE_POINTERS_DS_length_bias      2
#define GFX9_3DSTATE_SAMPLER_STATE_POINTERS_DS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     45,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_SAMPLER_STATE_POINTERS_DS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             PointertoDSSamplerState;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_SAMPLER_STATE_POINTERS_DS_pack(__attribute__((unused)) __gen_user_data *data,
                                            __attribute__((unused)) void * restrict dst,
                                            __attribute__((unused)) const struct GFX9_3DSTATE_SAMPLER_STATE_POINTERS_DS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->PointertoDSSamplerState, 5, 31);
}

#define GFX9_3DSTATE_SAMPLER_STATE_POINTERS_GS_length      2
#define GFX9_3DSTATE_SAMPLER_STATE_POINTERS_GS_length_bias      2
#define GFX9_3DSTATE_SAMPLER_STATE_POINTERS_GS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     46,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_SAMPLER_STATE_POINTERS_GS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             PointertoGSSamplerState;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_SAMPLER_STATE_POINTERS_GS_pack(__attribute__((unused)) __gen_user_data *data,
                                            __attribute__((unused)) void * restrict dst,
                                            __attribute__((unused)) const struct GFX9_3DSTATE_SAMPLER_STATE_POINTERS_GS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->PointertoGSSamplerState, 5, 31);
}

#define GFX9_3DSTATE_SAMPLER_STATE_POINTERS_HS_length      2
#define GFX9_3DSTATE_SAMPLER_STATE_POINTERS_HS_length_bias      2
#define GFX9_3DSTATE_SAMPLER_STATE_POINTERS_HS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     44,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_SAMPLER_STATE_POINTERS_HS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             PointertoHSSamplerState;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_SAMPLER_STATE_POINTERS_HS_pack(__attribute__((unused)) __gen_user_data *data,
                                            __attribute__((unused)) void * restrict dst,
                                            __attribute__((unused)) const struct GFX9_3DSTATE_SAMPLER_STATE_POINTERS_HS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->PointertoHSSamplerState, 5, 31);
}

#define GFX9_3DSTATE_SAMPLER_STATE_POINTERS_PS_length      2
#define GFX9_3DSTATE_SAMPLER_STATE_POINTERS_PS_length_bias      2
#define GFX9_3DSTATE_SAMPLER_STATE_POINTERS_PS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     47,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_SAMPLER_STATE_POINTERS_PS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             PointertoPSSamplerState;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_SAMPLER_STATE_POINTERS_PS_pack(__attribute__((unused)) __gen_user_data *data,
                                            __attribute__((unused)) void * restrict dst,
                                            __attribute__((unused)) const struct GFX9_3DSTATE_SAMPLER_STATE_POINTERS_PS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->PointertoPSSamplerState, 5, 31);
}

#define GFX9_3DSTATE_SAMPLER_STATE_POINTERS_VS_length      2
#define GFX9_3DSTATE_SAMPLER_STATE_POINTERS_VS_length_bias      2
#define GFX9_3DSTATE_SAMPLER_STATE_POINTERS_VS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     43,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_SAMPLER_STATE_POINTERS_VS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             PointertoVSSamplerState;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_SAMPLER_STATE_POINTERS_VS_pack(__attribute__((unused)) __gen_user_data *data,
                                            __attribute__((unused)) void * restrict dst,
                                            __attribute__((unused)) const struct GFX9_3DSTATE_SAMPLER_STATE_POINTERS_VS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->PointertoVSSamplerState, 5, 31);
}

#define GFX9_3DSTATE_SAMPLE_MASK_length        2
#define GFX9_3DSTATE_SAMPLE_MASK_length_bias      2
#define GFX9_3DSTATE_SAMPLE_MASK_header         \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     24,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_SAMPLE_MASK {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             SampleMask;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_SAMPLE_MASK_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_3DSTATE_SAMPLE_MASK * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->SampleMask, 0, 15);
}

#define GFX9_3DSTATE_SAMPLE_PATTERN_length      9
#define GFX9_3DSTATE_SAMPLE_PATTERN_length_bias      2
#define GFX9_3DSTATE_SAMPLE_PATTERN_header      \
   .DWordLength                         =      7,  \
   ._3DCommandSubOpcode                 =     28,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_SAMPLE_PATTERN {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   float                                _16xSample0YOffset;
   float                                _16xSample0XOffset;
   float                                _16xSample1YOffset;
   float                                _16xSample1XOffset;
   float                                _16xSample2YOffset;
   float                                _16xSample2XOffset;
   float                                _16xSample3YOffset;
   float                                _16xSample3XOffset;
   float                                _16xSample4YOffset;
   float                                _16xSample4XOffset;
   float                                _16xSample5YOffset;
   float                                _16xSample5XOffset;
   float                                _16xSample6YOffset;
   float                                _16xSample6XOffset;
   float                                _16xSample7YOffset;
   float                                _16xSample7XOffset;
   float                                _16xSample8YOffset;
   float                                _16xSample8XOffset;
   float                                _16xSample9YOffset;
   float                                _16xSample9XOffset;
   float                                _16xSample10YOffset;
   float                                _16xSample10XOffset;
   float                                _16xSample11YOffset;
   float                                _16xSample11XOffset;
   float                                _16xSample12YOffset;
   float                                _16xSample12XOffset;
   float                                _16xSample13YOffset;
   float                                _16xSample13XOffset;
   float                                _16xSample14YOffset;
   float                                _16xSample14XOffset;
   float                                _16xSample15YOffset;
   float                                _16xSample15XOffset;
   float                                _8xSample4YOffset;
   float                                _8xSample4XOffset;
   float                                _8xSample5YOffset;
   float                                _8xSample5XOffset;
   float                                _8xSample6YOffset;
   float                                _8xSample6XOffset;
   float                                _8xSample7YOffset;
   float                                _8xSample7XOffset;
   float                                _8xSample0YOffset;
   float                                _8xSample0XOffset;
   float                                _8xSample1YOffset;
   float                                _8xSample1XOffset;
   float                                _8xSample2YOffset;
   float                                _8xSample2XOffset;
   float                                _8xSample3YOffset;
   float                                _8xSample3XOffset;
   float                                _4xSample0YOffset;
   float                                _4xSample0XOffset;
   float                                _4xSample1YOffset;
   float                                _4xSample1XOffset;
   float                                _4xSample2YOffset;
   float                                _4xSample2XOffset;
   float                                _4xSample3YOffset;
   float                                _4xSample3XOffset;
   float                                _2xSample0YOffset;
   float                                _2xSample0XOffset;
   float                                _2xSample1YOffset;
   float                                _2xSample1XOffset;
   float                                _1xSample0YOffset;
   float                                _1xSample0XOffset;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_SAMPLE_PATTERN_pack(__attribute__((unused)) __gen_user_data *data,
                                 __attribute__((unused)) void * restrict dst,
                                 __attribute__((unused)) const struct GFX9_3DSTATE_SAMPLE_PATTERN * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_ufixed(values->_16xSample0YOffset, 0, 3, 4) |
      util_bitpack_ufixed(values->_16xSample0XOffset, 4, 7, 4) |
      util_bitpack_ufixed(values->_16xSample1YOffset, 8, 11, 4) |
      util_bitpack_ufixed(values->_16xSample1XOffset, 12, 15, 4) |
      util_bitpack_ufixed(values->_16xSample2YOffset, 16, 19, 4) |
      util_bitpack_ufixed(values->_16xSample2XOffset, 20, 23, 4) |
      util_bitpack_ufixed(values->_16xSample3YOffset, 24, 27, 4) |
      util_bitpack_ufixed(values->_16xSample3XOffset, 28, 31, 4);

   dw[2] =
      util_bitpack_ufixed(values->_16xSample4YOffset, 0, 3, 4) |
      util_bitpack_ufixed(values->_16xSample4XOffset, 4, 7, 4) |
      util_bitpack_ufixed(values->_16xSample5YOffset, 8, 11, 4) |
      util_bitpack_ufixed(values->_16xSample5XOffset, 12, 15, 4) |
      util_bitpack_ufixed(values->_16xSample6YOffset, 16, 19, 4) |
      util_bitpack_ufixed(values->_16xSample6XOffset, 20, 23, 4) |
      util_bitpack_ufixed(values->_16xSample7YOffset, 24, 27, 4) |
      util_bitpack_ufixed(values->_16xSample7XOffset, 28, 31, 4);

   dw[3] =
      util_bitpack_ufixed(values->_16xSample8YOffset, 0, 3, 4) |
      util_bitpack_ufixed(values->_16xSample8XOffset, 4, 7, 4) |
      util_bitpack_ufixed(values->_16xSample9YOffset, 8, 11, 4) |
      util_bitpack_ufixed(values->_16xSample9XOffset, 12, 15, 4) |
      util_bitpack_ufixed(values->_16xSample10YOffset, 16, 19, 4) |
      util_bitpack_ufixed(values->_16xSample10XOffset, 20, 23, 4) |
      util_bitpack_ufixed(values->_16xSample11YOffset, 24, 27, 4) |
      util_bitpack_ufixed(values->_16xSample11XOffset, 28, 31, 4);

   dw[4] =
      util_bitpack_ufixed(values->_16xSample12YOffset, 0, 3, 4) |
      util_bitpack_ufixed(values->_16xSample12XOffset, 4, 7, 4) |
      util_bitpack_ufixed(values->_16xSample13YOffset, 8, 11, 4) |
      util_bitpack_ufixed(values->_16xSample13XOffset, 12, 15, 4) |
      util_bitpack_ufixed(values->_16xSample14YOffset, 16, 19, 4) |
      util_bitpack_ufixed(values->_16xSample14XOffset, 20, 23, 4) |
      util_bitpack_ufixed(values->_16xSample15YOffset, 24, 27, 4) |
      util_bitpack_ufixed(values->_16xSample15XOffset, 28, 31, 4);

   dw[5] =
      util_bitpack_ufixed(values->_8xSample4YOffset, 0, 3, 4) |
      util_bitpack_ufixed(values->_8xSample4XOffset, 4, 7, 4) |
      util_bitpack_ufixed(values->_8xSample5YOffset, 8, 11, 4) |
      util_bitpack_ufixed(values->_8xSample5XOffset, 12, 15, 4) |
      util_bitpack_ufixed(values->_8xSample6YOffset, 16, 19, 4) |
      util_bitpack_ufixed(values->_8xSample6XOffset, 20, 23, 4) |
      util_bitpack_ufixed(values->_8xSample7YOffset, 24, 27, 4) |
      util_bitpack_ufixed(values->_8xSample7XOffset, 28, 31, 4);

   dw[6] =
      util_bitpack_ufixed(values->_8xSample0YOffset, 0, 3, 4) |
      util_bitpack_ufixed(values->_8xSample0XOffset, 4, 7, 4) |
      util_bitpack_ufixed(values->_8xSample1YOffset, 8, 11, 4) |
      util_bitpack_ufixed(values->_8xSample1XOffset, 12, 15, 4) |
      util_bitpack_ufixed(values->_8xSample2YOffset, 16, 19, 4) |
      util_bitpack_ufixed(values->_8xSample2XOffset, 20, 23, 4) |
      util_bitpack_ufixed(values->_8xSample3YOffset, 24, 27, 4) |
      util_bitpack_ufixed(values->_8xSample3XOffset, 28, 31, 4);

   dw[7] =
      util_bitpack_ufixed(values->_4xSample0YOffset, 0, 3, 4) |
      util_bitpack_ufixed(values->_4xSample0XOffset, 4, 7, 4) |
      util_bitpack_ufixed(values->_4xSample1YOffset, 8, 11, 4) |
      util_bitpack_ufixed(values->_4xSample1XOffset, 12, 15, 4) |
      util_bitpack_ufixed(values->_4xSample2YOffset, 16, 19, 4) |
      util_bitpack_ufixed(values->_4xSample2XOffset, 20, 23, 4) |
      util_bitpack_ufixed(values->_4xSample3YOffset, 24, 27, 4) |
      util_bitpack_ufixed(values->_4xSample3XOffset, 28, 31, 4);

   dw[8] =
      util_bitpack_ufixed(values->_2xSample0YOffset, 0, 3, 4) |
      util_bitpack_ufixed(values->_2xSample0XOffset, 4, 7, 4) |
      util_bitpack_ufixed(values->_2xSample1YOffset, 8, 11, 4) |
      util_bitpack_ufixed(values->_2xSample1XOffset, 12, 15, 4) |
      util_bitpack_ufixed(values->_1xSample0YOffset, 16, 19, 4) |
      util_bitpack_ufixed(values->_1xSample0XOffset, 20, 23, 4);
}

#define GFX9_3DSTATE_SBE_length                6
#define GFX9_3DSTATE_SBE_length_bias           2
#define GFX9_3DSTATE_SBE_header                 \
   .DWordLength                         =      4,  \
   ._3DCommandSubOpcode                 =     31,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_SBE {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             PrimitiveIDOverrideAttributeSelect;
   uint32_t                             VertexURBEntryReadOffset;
   uint32_t                             VertexURBEntryReadLength;
   bool                                 PrimitiveIDOverrideComponentX;
   bool                                 PrimitiveIDOverrideComponentY;
   bool                                 PrimitiveIDOverrideComponentZ;
   bool                                 PrimitiveIDOverrideComponentW;
   uint32_t                             PointSpriteTextureCoordinateOrigin;
#define UPPERLEFT                                0
#define LOWERLEFT                                1
   bool                                 AttributeSwizzleEnable;
   uint32_t                             NumberofSFOutputAttributes;
   bool                                 ForceVertexURBEntryReadOffset;
   bool                                 ForceVertexURBEntryReadLength;
   uint32_t                             PointSpriteTextureCoordinateEnable;
   uint32_t                             ConstantInterpolationEnable;
   uint32_t                             AttributeActiveComponentFormat[32];
#define ACTIVE_COMPONENT_DISABLED                0
#define ACTIVE_COMPONENT_XY                      1
#define ACTIVE_COMPONENT_XYZ                     2
#define ACTIVE_COMPONENT_XYZW                    3
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_SBE_pack(__attribute__((unused)) __gen_user_data *data,
                      __attribute__((unused)) void * restrict dst,
                      __attribute__((unused)) const struct GFX9_3DSTATE_SBE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->PrimitiveIDOverrideAttributeSelect, 0, 4) |
      util_bitpack_uint(values->VertexURBEntryReadOffset, 5, 10) |
      util_bitpack_uint(values->VertexURBEntryReadLength, 11, 15) |
      util_bitpack_uint(values->PrimitiveIDOverrideComponentX, 16, 16) |
      util_bitpack_uint(values->PrimitiveIDOverrideComponentY, 17, 17) |
      util_bitpack_uint(values->PrimitiveIDOverrideComponentZ, 18, 18) |
      util_bitpack_uint(values->PrimitiveIDOverrideComponentW, 19, 19) |
      util_bitpack_uint(values->PointSpriteTextureCoordinateOrigin, 20, 20) |
      util_bitpack_uint(values->AttributeSwizzleEnable, 21, 21) |
      util_bitpack_uint(values->NumberofSFOutputAttributes, 22, 27) |
      util_bitpack_uint(values->ForceVertexURBEntryReadOffset, 28, 28) |
      util_bitpack_uint(values->ForceVertexURBEntryReadLength, 29, 29);

   dw[2] =
      util_bitpack_uint(values->PointSpriteTextureCoordinateEnable, 0, 31);

   dw[3] =
      util_bitpack_uint(values->ConstantInterpolationEnable, 0, 31);

   dw[4] =
      util_bitpack_uint(values->AttributeActiveComponentFormat[0], 0, 1) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[1], 2, 3) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[2], 4, 5) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[3], 6, 7) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[4], 8, 9) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[5], 10, 11) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[6], 12, 13) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[7], 14, 15) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[8], 16, 17) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[9], 18, 19) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[10], 20, 21) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[11], 22, 23) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[12], 24, 25) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[13], 26, 27) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[14], 28, 29) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[15], 30, 31);

   dw[5] =
      util_bitpack_uint(values->AttributeActiveComponentFormat[16], 0, 1) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[17], 2, 3) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[18], 4, 5) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[19], 6, 7) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[20], 8, 9) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[21], 10, 11) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[22], 12, 13) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[23], 14, 15) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[24], 16, 17) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[25], 18, 19) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[26], 20, 21) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[27], 22, 23) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[28], 24, 25) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[29], 26, 27) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[30], 28, 29) |
      util_bitpack_uint(values->AttributeActiveComponentFormat[31], 30, 31);
}

#define GFX9_3DSTATE_SBE_SWIZ_length          11
#define GFX9_3DSTATE_SBE_SWIZ_length_bias      2
#define GFX9_3DSTATE_SBE_SWIZ_header            \
   .DWordLength                         =      9,  \
   ._3DCommandSubOpcode                 =     81,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_SBE_SWIZ {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   struct GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL Attribute[16];
   uint32_t                             AttributeWrapShortestEnables[16];
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_SBE_SWIZ_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_3DSTATE_SBE_SWIZ * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   uint32_t v1_0;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v1_0, &values->Attribute[0]);

   uint32_t v1_1;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v1_1, &values->Attribute[1]);

   dw[1] =
      util_bitpack_uint(v1_0, 0, 15) |
      util_bitpack_uint(v1_1, 16, 31);

   uint32_t v2_0;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v2_0, &values->Attribute[2]);

   uint32_t v2_1;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v2_1, &values->Attribute[3]);

   dw[2] =
      util_bitpack_uint(v2_0, 0, 15) |
      util_bitpack_uint(v2_1, 16, 31);

   uint32_t v3_0;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v3_0, &values->Attribute[4]);

   uint32_t v3_1;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v3_1, &values->Attribute[5]);

   dw[3] =
      util_bitpack_uint(v3_0, 0, 15) |
      util_bitpack_uint(v3_1, 16, 31);

   uint32_t v4_0;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v4_0, &values->Attribute[6]);

   uint32_t v4_1;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v4_1, &values->Attribute[7]);

   dw[4] =
      util_bitpack_uint(v4_0, 0, 15) |
      util_bitpack_uint(v4_1, 16, 31);

   uint32_t v5_0;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v5_0, &values->Attribute[8]);

   uint32_t v5_1;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v5_1, &values->Attribute[9]);

   dw[5] =
      util_bitpack_uint(v5_0, 0, 15) |
      util_bitpack_uint(v5_1, 16, 31);

   uint32_t v6_0;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v6_0, &values->Attribute[10]);

   uint32_t v6_1;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v6_1, &values->Attribute[11]);

   dw[6] =
      util_bitpack_uint(v6_0, 0, 15) |
      util_bitpack_uint(v6_1, 16, 31);

   uint32_t v7_0;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v7_0, &values->Attribute[12]);

   uint32_t v7_1;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v7_1, &values->Attribute[13]);

   dw[7] =
      util_bitpack_uint(v7_0, 0, 15) |
      util_bitpack_uint(v7_1, 16, 31);

   uint32_t v8_0;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v8_0, &values->Attribute[14]);

   uint32_t v8_1;
   GFX9_SF_OUTPUT_ATTRIBUTE_DETAIL_pack(data, &v8_1, &values->Attribute[15]);

   dw[8] =
      util_bitpack_uint(v8_0, 0, 15) |
      util_bitpack_uint(v8_1, 16, 31);

   dw[9] =
      util_bitpack_uint(values->AttributeWrapShortestEnables[0], 0, 3) |
      util_bitpack_uint(values->AttributeWrapShortestEnables[1], 4, 7) |
      util_bitpack_uint(values->AttributeWrapShortestEnables[2], 8, 11) |
      util_bitpack_uint(values->AttributeWrapShortestEnables[3], 12, 15) |
      util_bitpack_uint(values->AttributeWrapShortestEnables[4], 16, 19) |
      util_bitpack_uint(values->AttributeWrapShortestEnables[5], 20, 23) |
      util_bitpack_uint(values->AttributeWrapShortestEnables[6], 24, 27) |
      util_bitpack_uint(values->AttributeWrapShortestEnables[7], 28, 31);

   dw[10] =
      util_bitpack_uint(values->AttributeWrapShortestEnables[8], 0, 3) |
      util_bitpack_uint(values->AttributeWrapShortestEnables[9], 4, 7) |
      util_bitpack_uint(values->AttributeWrapShortestEnables[10], 8, 11) |
      util_bitpack_uint(values->AttributeWrapShortestEnables[11], 12, 15) |
      util_bitpack_uint(values->AttributeWrapShortestEnables[12], 16, 19) |
      util_bitpack_uint(values->AttributeWrapShortestEnables[13], 20, 23) |
      util_bitpack_uint(values->AttributeWrapShortestEnables[14], 24, 27) |
      util_bitpack_uint(values->AttributeWrapShortestEnables[15], 28, 31);
}

#define GFX9_3DSTATE_SCISSOR_STATE_POINTERS_length      2
#define GFX9_3DSTATE_SCISSOR_STATE_POINTERS_length_bias      2
#define GFX9_3DSTATE_SCISSOR_STATE_POINTERS_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     15,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_SCISSOR_STATE_POINTERS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             ScissorRectPointer;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_SCISSOR_STATE_POINTERS_pack(__attribute__((unused)) __gen_user_data *data,
                                         __attribute__((unused)) void * restrict dst,
                                         __attribute__((unused)) const struct GFX9_3DSTATE_SCISSOR_STATE_POINTERS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->ScissorRectPointer, 5, 31);
}

#define GFX9_3DSTATE_SF_length                 4
#define GFX9_3DSTATE_SF_length_bias            2
#define GFX9_3DSTATE_SF_header                  \
   .DWordLength                         =      2,  \
   ._3DCommandSubOpcode                 =     19,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_SF {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   bool                                 ViewportTransformEnable;
   bool                                 StatisticsEnable;
   bool                                 LegacyGlobalDepthBiasEnable;
   float                                LineWidth;
   uint32_t                             LineEndCapAntialiasingRegionWidth;
#define _05pixels                                0
#define _10pixels                                1
#define _20pixels                                2
#define _40pixels                                3
   float                                PointWidth;
   uint32_t                             PointWidthSource;
#define Vertex                                   0
#define State                                    1
   uint32_t                             VertexSubPixelPrecisionSelect;
#define _8Bit                                    0
#define _4Bit                                    1
   bool                                 SmoothPointEnable;
   uint32_t                             AALineDistanceMode;
#define AALINEDISTANCE_TRUE                      1
   uint32_t                             TriangleFanProvokingVertexSelect;
   uint32_t                             LineStripListProvokingVertexSelect;
   uint32_t                             TriangleStripListProvokingVertexSelect;
   bool                                 LastPixelEnable;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_SF_pack(__attribute__((unused)) __gen_user_data *data,
                     __attribute__((unused)) void * restrict dst,
                     __attribute__((unused)) const struct GFX9_3DSTATE_SF * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ViewportTransformEnable, 1, 1) |
      util_bitpack_uint(values->StatisticsEnable, 10, 10) |
      util_bitpack_uint(values->LegacyGlobalDepthBiasEnable, 11, 11) |
      util_bitpack_ufixed(values->LineWidth, 12, 29, 7);

   dw[2] =
      util_bitpack_uint(values->LineEndCapAntialiasingRegionWidth, 16, 17);

   dw[3] =
      util_bitpack_ufixed(values->PointWidth, 0, 10, 3) |
      util_bitpack_uint(values->PointWidthSource, 11, 11) |
      util_bitpack_uint(values->VertexSubPixelPrecisionSelect, 12, 12) |
      util_bitpack_uint(values->SmoothPointEnable, 13, 13) |
      util_bitpack_uint(values->AALineDistanceMode, 14, 14) |
      util_bitpack_uint(values->TriangleFanProvokingVertexSelect, 25, 26) |
      util_bitpack_uint(values->LineStripListProvokingVertexSelect, 27, 28) |
      util_bitpack_uint(values->TriangleStripListProvokingVertexSelect, 29, 30) |
      util_bitpack_uint(values->LastPixelEnable, 31, 31);
}

#define GFX9_3DSTATE_SO_BUFFER_length          8
#define GFX9_3DSTATE_SO_BUFFER_length_bias      2
#define GFX9_3DSTATE_SO_BUFFER_header           \
   .DWordLength                         =      6,  \
   ._3DCommandSubOpcode                 =     24,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_SO_BUFFER {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   bool                                 StreamOutputBufferOffsetAddressEnable;
   bool                                 StreamOffsetWriteEnable;
   uint32_t                             MOCS;
   uint32_t                             SOBufferIndex;
   bool                                 SOBufferEnable;
   __gen_address_type                   SurfaceBaseAddress;
   uint32_t                             SurfaceSize;
   __gen_address_type                   StreamOutputBufferOffsetAddress;
   uint32_t                             StreamOffset;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_SO_BUFFER_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_3DSTATE_SO_BUFFER * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->StreamOutputBufferOffsetAddressEnable, 20, 20) |
      util_bitpack_uint(values->StreamOffsetWriteEnable, 21, 21) |
      util_bitpack_uint_nonzero(values->MOCS, 22, 28) |
      util_bitpack_uint(values->SOBufferIndex, 29, 30) |
      util_bitpack_uint(values->SOBufferEnable, 31, 31);

   const uint64_t v2_address =
      __gen_address(data, &dw[2], values->SurfaceBaseAddress, 0, 2, 47);
   dw[2] = v2_address;
   dw[3] = v2_address >> 32;

   dw[4] =
      util_bitpack_uint(values->SurfaceSize, 0, 29);

   const uint64_t v5_address =
      __gen_address(data, &dw[5], values->StreamOutputBufferOffsetAddress, 0, 2, 47);
   dw[5] = v5_address;
   dw[6] = v5_address >> 32;

   dw[7] =
      util_bitpack_uint(values->StreamOffset, 0, 31);
}

#define GFX9_3DSTATE_SO_DECL_LIST_length_bias      2
#define GFX9_3DSTATE_SO_DECL_LIST_header        \
   ._3DCommandSubOpcode                 =     23,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_SO_DECL_LIST {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             StreamtoBufferSelects0;
   uint32_t                             StreamtoBufferSelects1;
   uint32_t                             StreamtoBufferSelects2;
   uint32_t                             StreamtoBufferSelects3;
   uint32_t                             NumEntries0;
   uint32_t                             NumEntries1;
   uint32_t                             NumEntries2;
   uint32_t                             NumEntries3;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_SO_DECL_LIST_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_3DSTATE_SO_DECL_LIST * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 8) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->StreamtoBufferSelects0, 0, 3) |
      util_bitpack_uint(values->StreamtoBufferSelects1, 4, 7) |
      util_bitpack_uint(values->StreamtoBufferSelects2, 8, 11) |
      util_bitpack_uint(values->StreamtoBufferSelects3, 12, 15);

   dw[2] =
      util_bitpack_uint(values->NumEntries0, 0, 7) |
      util_bitpack_uint(values->NumEntries1, 8, 15) |
      util_bitpack_uint(values->NumEntries2, 16, 23) |
      util_bitpack_uint(values->NumEntries3, 24, 31);
}

#define GFX9_3DSTATE_STENCIL_BUFFER_length      5
#define GFX9_3DSTATE_STENCIL_BUFFER_length_bias      2
#define GFX9_3DSTATE_STENCIL_BUFFER_header      \
   .DWordLength                         =      3,  \
   ._3DCommandSubOpcode                 =      6,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_STENCIL_BUFFER {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             SurfacePitch;
   uint32_t                             MOCS;
   bool                                 StencilBufferEnable;
   __gen_address_type                   SurfaceBaseAddress;
   uint32_t                             SurfaceQPitch;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_STENCIL_BUFFER_pack(__attribute__((unused)) __gen_user_data *data,
                                 __attribute__((unused)) void * restrict dst,
                                 __attribute__((unused)) const struct GFX9_3DSTATE_STENCIL_BUFFER * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->SurfacePitch, 0, 16) |
      util_bitpack_uint_nonzero(values->MOCS, 22, 28) |
      util_bitpack_uint(values->StencilBufferEnable, 31, 31);

   const uint64_t v2_address =
      __gen_address(data, &dw[2], values->SurfaceBaseAddress, 0, 0, 63);
   dw[2] = v2_address;
   dw[3] = v2_address >> 32;

   dw[4] =
      util_bitpack_uint(values->SurfaceQPitch, 0, 14);
}

#define GFX9_3DSTATE_STREAMOUT_length          5
#define GFX9_3DSTATE_STREAMOUT_length_bias      2
#define GFX9_3DSTATE_STREAMOUT_header           \
   .DWordLength                         =      3,  \
   ._3DCommandSubOpcode                 =     30,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_STREAMOUT {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             ForceRendering;
#define Resreved                                 1
#define Force_Off                                2
#define Force_on                                 3
   bool                                 SOStatisticsEnable;
   uint32_t                             ReorderMode;
#define LEADING                                  0
#define TRAILING                                 1
   uint32_t                             RenderStreamSelect;
   bool                                 RenderingDisable;
   bool                                 SOFunctionEnable;
   uint32_t                             Stream0VertexReadLength;
   uint32_t                             Stream0VertexReadOffset;
   uint32_t                             Stream1VertexReadLength;
   uint32_t                             Stream1VertexReadOffset;
   uint32_t                             Stream2VertexReadLength;
   uint32_t                             Stream2VertexReadOffset;
   uint32_t                             Stream3VertexReadLength;
   uint32_t                             Stream3VertexReadOffset;
   uint32_t                             Buffer0SurfacePitch;
   uint32_t                             Buffer1SurfacePitch;
   uint32_t                             Buffer2SurfacePitch;
   uint32_t                             Buffer3SurfacePitch;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_STREAMOUT_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_3DSTATE_STREAMOUT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ForceRendering, 23, 24) |
      util_bitpack_uint(values->SOStatisticsEnable, 25, 25) |
      util_bitpack_uint(values->ReorderMode, 26, 26) |
      util_bitpack_uint(values->RenderStreamSelect, 27, 28) |
      util_bitpack_uint(values->RenderingDisable, 30, 30) |
      util_bitpack_uint(values->SOFunctionEnable, 31, 31);

   dw[2] =
      util_bitpack_uint(values->Stream0VertexReadLength, 0, 4) |
      util_bitpack_uint(values->Stream0VertexReadOffset, 5, 5) |
      util_bitpack_uint(values->Stream1VertexReadLength, 8, 12) |
      util_bitpack_uint(values->Stream1VertexReadOffset, 13, 13) |
      util_bitpack_uint(values->Stream2VertexReadLength, 16, 20) |
      util_bitpack_uint(values->Stream2VertexReadOffset, 21, 21) |
      util_bitpack_uint(values->Stream3VertexReadLength, 24, 28) |
      util_bitpack_uint(values->Stream3VertexReadOffset, 29, 29);

   dw[3] =
      util_bitpack_uint(values->Buffer0SurfacePitch, 0, 11) |
      util_bitpack_uint(values->Buffer1SurfacePitch, 16, 27);

   dw[4] =
      util_bitpack_uint(values->Buffer2SurfacePitch, 0, 11) |
      util_bitpack_uint(values->Buffer3SurfacePitch, 16, 27);
}

#define GFX9_3DSTATE_TE_length                 4
#define GFX9_3DSTATE_TE_length_bias            2
#define GFX9_3DSTATE_TE_header                  \
   .DWordLength                         =      2,  \
   ._3DCommandSubOpcode                 =     28,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_TE {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   bool                                 TEEnable;
   uint32_t                             TEMode;
#define HW_TESS                                  0
   uint32_t                             TEDomain;
#define QUAD                                     0
#define TRI                                      1
#define ISOLINE                                  2
   uint32_t                             OutputTopology;
#define OUTPUT_POINT                             0
#define OUTPUT_LINE                              1
#define OUTPUT_TRI_CW                            2
#define OUTPUT_TRI_CCW                           3
   uint32_t                             Partitioning;
#define INTEGER                                  0
#define ODD_FRACTIONAL                           1
#define EVEN_FRACTIONAL                          2
   float                                MaximumTessellationFactorOdd;
   float                                MaximumTessellationFactorNotOdd;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_TE_pack(__attribute__((unused)) __gen_user_data *data,
                     __attribute__((unused)) void * restrict dst,
                     __attribute__((unused)) const struct GFX9_3DSTATE_TE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->TEEnable, 0, 0) |
      util_bitpack_uint(values->TEMode, 1, 2) |
      util_bitpack_uint(values->TEDomain, 4, 5) |
      util_bitpack_uint(values->OutputTopology, 8, 9) |
      util_bitpack_uint(values->Partitioning, 12, 13);

   dw[2] =
      util_bitpack_float(values->MaximumTessellationFactorOdd);

   dw[3] =
      util_bitpack_float(values->MaximumTessellationFactorNotOdd);
}

#define GFX9_3DSTATE_URB_CLEAR_length          2
#define GFX9_3DSTATE_URB_CLEAR_length_bias      2
#define GFX9_3DSTATE_URB_CLEAR_header           \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     29,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_URB_CLEAR {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             URBAddress;
   uint32_t                             URBClearLength;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_URB_CLEAR_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_3DSTATE_URB_CLEAR * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->URBAddress, 0, 14) |
      util_bitpack_uint(values->URBClearLength, 16, 29);
}

#define GFX9_3DSTATE_URB_DS_length             2
#define GFX9_3DSTATE_URB_DS_length_bias        2
#define GFX9_3DSTATE_URB_DS_header              \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     50,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_URB_DS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             DSNumberofURBEntries;
   uint32_t                             DSURBEntryAllocationSize;
   uint32_t                             DSURBStartingAddress;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_URB_DS_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_3DSTATE_URB_DS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->DSNumberofURBEntries, 0, 15) |
      util_bitpack_uint(values->DSURBEntryAllocationSize, 16, 24) |
      util_bitpack_uint(values->DSURBStartingAddress, 25, 31);
}

#define GFX9_3DSTATE_URB_GS_length             2
#define GFX9_3DSTATE_URB_GS_length_bias        2
#define GFX9_3DSTATE_URB_GS_header              \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     51,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_URB_GS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             GSNumberofURBEntries;
   uint32_t                             GSURBEntryAllocationSize;
   uint32_t                             GSURBStartingAddress;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_URB_GS_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_3DSTATE_URB_GS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->GSNumberofURBEntries, 0, 15) |
      util_bitpack_uint(values->GSURBEntryAllocationSize, 16, 24) |
      util_bitpack_uint(values->GSURBStartingAddress, 25, 31);
}

#define GFX9_3DSTATE_URB_HS_length             2
#define GFX9_3DSTATE_URB_HS_length_bias        2
#define GFX9_3DSTATE_URB_HS_header              \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     49,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_URB_HS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             HSNumberofURBEntries;
   uint32_t                             HSURBEntryAllocationSize;
   uint32_t                             HSURBStartingAddress;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_URB_HS_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_3DSTATE_URB_HS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->HSNumberofURBEntries, 0, 15) |
      util_bitpack_uint(values->HSURBEntryAllocationSize, 16, 24) |
      util_bitpack_uint(values->HSURBStartingAddress, 25, 31);
}

#define GFX9_3DSTATE_URB_VS_length             2
#define GFX9_3DSTATE_URB_VS_length_bias        2
#define GFX9_3DSTATE_URB_VS_header              \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     48,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_URB_VS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             VSNumberofURBEntries;
   uint32_t                             VSURBEntryAllocationSize;
   uint32_t                             VSURBStartingAddress;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_URB_VS_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_3DSTATE_URB_VS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->VSNumberofURBEntries, 0, 15) |
      util_bitpack_uint(values->VSURBEntryAllocationSize, 16, 24) |
      util_bitpack_uint(values->VSURBStartingAddress, 25, 31);
}

#define GFX9_3DSTATE_VERTEX_BUFFERS_length_bias      2
#define GFX9_3DSTATE_VERTEX_BUFFERS_header      \
   .DWordLength                         =      3,  \
   ._3DCommandSubOpcode                 =      8,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_VERTEX_BUFFERS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_VERTEX_BUFFERS_pack(__attribute__((unused)) __gen_user_data *data,
                                 __attribute__((unused)) void * restrict dst,
                                 __attribute__((unused)) const struct GFX9_3DSTATE_VERTEX_BUFFERS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_3DSTATE_VERTEX_ELEMENTS_length_bias      2
#define GFX9_3DSTATE_VERTEX_ELEMENTS_header     \
   .DWordLength                         =      1,  \
   ._3DCommandSubOpcode                 =      9,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_VERTEX_ELEMENTS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_VERTEX_ELEMENTS_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_3DSTATE_VERTEX_ELEMENTS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_3DSTATE_VF_length                 2
#define GFX9_3DSTATE_VF_length_bias            2
#define GFX9_3DSTATE_VF_header                  \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     12,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_VF {
   uint32_t                             DWordLength;
   bool                                 IndexedDrawCutIndexEnable;
   bool                                 ComponentPackingEnable;
   bool                                 SequentialDrawCutIndexEnable;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             CutIndex;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_VF_pack(__attribute__((unused)) __gen_user_data *data,
                     __attribute__((unused)) void * restrict dst,
                     __attribute__((unused)) const struct GFX9_3DSTATE_VF * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->IndexedDrawCutIndexEnable, 8, 8) |
      util_bitpack_uint(values->ComponentPackingEnable, 9, 9) |
      util_bitpack_uint(values->SequentialDrawCutIndexEnable, 10, 10) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->CutIndex, 0, 31);
}

#define GFX9_3DSTATE_VF_COMPONENT_PACKING_length      5
#define GFX9_3DSTATE_VF_COMPONENT_PACKING_length_bias      2
#define GFX9_3DSTATE_VF_COMPONENT_PACKING_header\
   .DWordLength                         =      3,  \
   ._3DCommandSubOpcode                 =     85,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_VF_COMPONENT_PACKING {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             VertexElement00Enables;
   uint32_t                             VertexElement01Enables;
   uint32_t                             VertexElement02Enables;
   uint32_t                             VertexElement03Enables;
   uint32_t                             VertexElement04Enables;
   uint32_t                             VertexElement05Enables;
   uint32_t                             VertexElement06Enables;
   uint32_t                             VertexElement07Enables;
   uint32_t                             VertexElement08Enables;
   uint32_t                             VertexElement09Enables;
   uint32_t                             VertexElement10Enables;
   uint32_t                             VertexElement11Enables;
   uint32_t                             VertexElement12Enables;
   uint32_t                             VertexElement13Enables;
   uint32_t                             VertexElement14Enables;
   uint32_t                             VertexElement15Enables;
   uint32_t                             VertexElement16Enables;
   uint32_t                             VertexElement17Enables;
   uint32_t                             VertexElement18Enables;
   uint32_t                             VertexElement19Enables;
   uint32_t                             VertexElement20Enables;
   uint32_t                             VertexElement21Enables;
   uint32_t                             VertexElement22Enables;
   uint32_t                             VertexElement23Enables;
   uint32_t                             VertexElement24Enables;
   uint32_t                             VertexElement25Enables;
   uint32_t                             VertexElement26Enables;
   uint32_t                             VertexElement27Enables;
   uint32_t                             VertexElement28Enables;
   uint32_t                             VertexElement29Enables;
   uint32_t                             VertexElement30Enables;
   uint32_t                             VertexElement31Enables;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_VF_COMPONENT_PACKING_pack(__attribute__((unused)) __gen_user_data *data,
                                       __attribute__((unused)) void * restrict dst,
                                       __attribute__((unused)) const struct GFX9_3DSTATE_VF_COMPONENT_PACKING * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->VertexElement00Enables, 0, 3) |
      util_bitpack_uint(values->VertexElement01Enables, 4, 7) |
      util_bitpack_uint(values->VertexElement02Enables, 8, 11) |
      util_bitpack_uint(values->VertexElement03Enables, 12, 15) |
      util_bitpack_uint(values->VertexElement04Enables, 16, 19) |
      util_bitpack_uint(values->VertexElement05Enables, 20, 23) |
      util_bitpack_uint(values->VertexElement06Enables, 24, 27) |
      util_bitpack_uint(values->VertexElement07Enables, 28, 31);

   dw[2] =
      util_bitpack_uint(values->VertexElement08Enables, 0, 3) |
      util_bitpack_uint(values->VertexElement09Enables, 4, 7) |
      util_bitpack_uint(values->VertexElement10Enables, 8, 11) |
      util_bitpack_uint(values->VertexElement11Enables, 12, 15) |
      util_bitpack_uint(values->VertexElement12Enables, 16, 19) |
      util_bitpack_uint(values->VertexElement13Enables, 20, 23) |
      util_bitpack_uint(values->VertexElement14Enables, 24, 27) |
      util_bitpack_uint(values->VertexElement15Enables, 28, 31);

   dw[3] =
      util_bitpack_uint(values->VertexElement16Enables, 0, 3) |
      util_bitpack_uint(values->VertexElement17Enables, 4, 7) |
      util_bitpack_uint(values->VertexElement18Enables, 8, 11) |
      util_bitpack_uint(values->VertexElement19Enables, 12, 15) |
      util_bitpack_uint(values->VertexElement20Enables, 16, 19) |
      util_bitpack_uint(values->VertexElement21Enables, 20, 23) |
      util_bitpack_uint(values->VertexElement22Enables, 24, 27) |
      util_bitpack_uint(values->VertexElement23Enables, 28, 31);

   dw[4] =
      util_bitpack_uint(values->VertexElement24Enables, 0, 3) |
      util_bitpack_uint(values->VertexElement25Enables, 4, 7) |
      util_bitpack_uint(values->VertexElement26Enables, 8, 11) |
      util_bitpack_uint(values->VertexElement27Enables, 12, 15) |
      util_bitpack_uint(values->VertexElement28Enables, 16, 19) |
      util_bitpack_uint(values->VertexElement29Enables, 20, 23) |
      util_bitpack_uint(values->VertexElement30Enables, 24, 27) |
      util_bitpack_uint(values->VertexElement31Enables, 28, 31);
}

#define GFX9_3DSTATE_VF_INSTANCING_length      3
#define GFX9_3DSTATE_VF_INSTANCING_length_bias      2
#define GFX9_3DSTATE_VF_INSTANCING_header       \
   .DWordLength                         =      1,  \
   ._3DCommandSubOpcode                 =     73,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_VF_INSTANCING {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             VertexElementIndex;
   bool                                 InstancingEnable;
   uint32_t                             InstanceDataStepRate;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_VF_INSTANCING_pack(__attribute__((unused)) __gen_user_data *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GFX9_3DSTATE_VF_INSTANCING * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->VertexElementIndex, 0, 5) |
      util_bitpack_uint(values->InstancingEnable, 8, 8);

   dw[2] =
      util_bitpack_uint(values->InstanceDataStepRate, 0, 31);
}

#define GFX9_3DSTATE_VF_SGVS_length            2
#define GFX9_3DSTATE_VF_SGVS_length_bias       2
#define GFX9_3DSTATE_VF_SGVS_header             \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     74,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_VF_SGVS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             VertexIDElementOffset;
   uint32_t                             VertexIDComponentNumber;
#define COMP_0                                   0
#define COMP_1                                   1
#define COMP_2                                   2
#define COMP_3                                   3
   bool                                 VertexIDEnable;
   uint32_t                             InstanceIDElementOffset;
   uint32_t                             InstanceIDComponentNumber;
#define COMP_0                                   0
#define COMP_1                                   1
#define COMP_2                                   2
#define COMP_3                                   3
   bool                                 InstanceIDEnable;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_VF_SGVS_pack(__attribute__((unused)) __gen_user_data *data,
                          __attribute__((unused)) void * restrict dst,
                          __attribute__((unused)) const struct GFX9_3DSTATE_VF_SGVS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->VertexIDElementOffset, 0, 5) |
      util_bitpack_uint(values->VertexIDComponentNumber, 13, 14) |
      util_bitpack_uint(values->VertexIDEnable, 15, 15) |
      util_bitpack_uint(values->InstanceIDElementOffset, 16, 21) |
      util_bitpack_uint(values->InstanceIDComponentNumber, 29, 30) |
      util_bitpack_uint(values->InstanceIDEnable, 31, 31);
}

#define GFX9_3DSTATE_VF_STATISTICS_length      1
#define GFX9_3DSTATE_VF_STATISTICS_length_bias      1
#define GFX9_3DSTATE_VF_STATISTICS_header       \
   ._3DCommandSubOpcode                 =     11,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      1,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_VF_STATISTICS {
   bool                                 StatisticsEnable;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_VF_STATISTICS_pack(__attribute__((unused)) __gen_user_data *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GFX9_3DSTATE_VF_STATISTICS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->StatisticsEnable, 0, 0) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_3DSTATE_VF_TOPOLOGY_length        2
#define GFX9_3DSTATE_VF_TOPOLOGY_length_bias      2
#define GFX9_3DSTATE_VF_TOPOLOGY_header         \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     75,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_VF_TOPOLOGY {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   enum GFX9_3D_Prim_Topo_Type          PrimitiveTopologyType;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_VF_TOPOLOGY_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_3DSTATE_VF_TOPOLOGY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->PrimitiveTopologyType, 0, 5);
}

#define GFX9_3DSTATE_VIEWPORT_STATE_POINTERS_CC_length      2
#define GFX9_3DSTATE_VIEWPORT_STATE_POINTERS_CC_length_bias      2
#define GFX9_3DSTATE_VIEWPORT_STATE_POINTERS_CC_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     35,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_VIEWPORT_STATE_POINTERS_CC {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             CCViewportPointer;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_VIEWPORT_STATE_POINTERS_CC_pack(__attribute__((unused)) __gen_user_data *data,
                                             __attribute__((unused)) void * restrict dst,
                                             __attribute__((unused)) const struct GFX9_3DSTATE_VIEWPORT_STATE_POINTERS_CC * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->CCViewportPointer, 5, 31);
}

#define GFX9_3DSTATE_VIEWPORT_STATE_POINTERS_SF_CLIP_length      2
#define GFX9_3DSTATE_VIEWPORT_STATE_POINTERS_SF_CLIP_length_bias      2
#define GFX9_3DSTATE_VIEWPORT_STATE_POINTERS_SF_CLIP_header\
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     33,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_VIEWPORT_STATE_POINTERS_SF_CLIP {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             SFClipViewportPointer;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_VIEWPORT_STATE_POINTERS_SF_CLIP_pack(__attribute__((unused)) __gen_user_data *data,
                                                  __attribute__((unused)) void * restrict dst,
                                                  __attribute__((unused)) const struct GFX9_3DSTATE_VIEWPORT_STATE_POINTERS_SF_CLIP * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->SFClipViewportPointer, 6, 31);
}

#define GFX9_3DSTATE_VS_length                 9
#define GFX9_3DSTATE_VS_length_bias            2
#define GFX9_3DSTATE_VS_header                  \
   .DWordLength                         =      7,  \
   ._3DCommandSubOpcode                 =     16,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_VS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             KernelStartPointer;
   bool                                 SoftwareExceptionEnable;
   bool                                 AccessesUAV;
   bool                                 IllegalOpcodeExceptionEnable;
   uint32_t                             FloatingPointMode;
#define IEEE754                                  0
#define Alternate                                1
   uint32_t                             ThreadDispatchPriority;
#define High                                     1
   uint32_t                             BindingTableEntryCount;
   uint32_t                             SamplerCount;
#define NoSamplers                               0
#define _14Samplers                              1
#define _58Samplers                              2
#define _912Samplers                             3
#define _1316Samplers                            4
   bool                                 VectorMaskEnable;
   bool                                 SingleVertexDispatch;
   uint32_t                             PerThreadScratchSpace;
   __gen_address_type                   ScratchSpaceBasePointer;
   uint32_t                             VertexURBEntryReadOffset;
   uint32_t                             VertexURBEntryReadLength;
   uint32_t                             DispatchGRFStartRegisterForURBData;
   bool                                 Enable;
   bool                                 VertexCacheDisable;
   bool                                 SIMD8DispatchEnable;
   bool                                 StatisticsEnable;
   uint32_t                             MaximumNumberofThreads;
   uint32_t                             UserClipDistanceCullTestEnableBitmask;
   uint32_t                             UserClipDistanceClipTestEnableBitmask;
   uint32_t                             VertexURBEntryOutputLength;
   uint32_t                             VertexURBEntryOutputReadOffset;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_VS_pack(__attribute__((unused)) __gen_user_data *data,
                     __attribute__((unused)) void * restrict dst,
                     __attribute__((unused)) const struct GFX9_3DSTATE_VS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1 =
      __gen_offset(values->KernelStartPointer, 6, 63);
   dw[1] = v1;
   dw[2] = v1 >> 32;

   dw[3] =
      util_bitpack_uint(values->SoftwareExceptionEnable, 7, 7) |
      util_bitpack_uint(values->AccessesUAV, 12, 12) |
      util_bitpack_uint(values->IllegalOpcodeExceptionEnable, 13, 13) |
      util_bitpack_uint(values->FloatingPointMode, 16, 16) |
      util_bitpack_uint(values->ThreadDispatchPriority, 17, 17) |
      util_bitpack_uint(values->BindingTableEntryCount, 18, 25) |
      util_bitpack_uint(values->SamplerCount, 27, 29) |
      util_bitpack_uint(values->VectorMaskEnable, 30, 30) |
      util_bitpack_uint(values->SingleVertexDispatch, 31, 31);

   const uint64_t v4 =
      util_bitpack_uint(values->PerThreadScratchSpace, 0, 3);
   const uint64_t v4_address =
      __gen_address(data, &dw[4], values->ScratchSpaceBasePointer, v4, 10, 63);
   dw[4] = v4_address;
   dw[5] = (v4_address >> 32) | (v4 >> 32);

   dw[6] =
      util_bitpack_uint(values->VertexURBEntryReadOffset, 4, 9) |
      util_bitpack_uint(values->VertexURBEntryReadLength, 11, 16) |
      util_bitpack_uint(values->DispatchGRFStartRegisterForURBData, 20, 24);

   dw[7] =
      util_bitpack_uint(values->Enable, 0, 0) |
      util_bitpack_uint(values->VertexCacheDisable, 1, 1) |
      util_bitpack_uint(values->SIMD8DispatchEnable, 2, 2) |
      util_bitpack_uint(values->StatisticsEnable, 10, 10) |
      util_bitpack_uint(values->MaximumNumberofThreads, 23, 31);

   dw[8] =
      util_bitpack_uint(values->UserClipDistanceCullTestEnableBitmask, 0, 7) |
      util_bitpack_uint(values->UserClipDistanceClipTestEnableBitmask, 8, 15) |
      util_bitpack_uint(values->VertexURBEntryOutputLength, 16, 20) |
      util_bitpack_uint(values->VertexURBEntryOutputReadOffset, 21, 26);
}

#define GFX9_3DSTATE_WM_length                 2
#define GFX9_3DSTATE_WM_length_bias            2
#define GFX9_3DSTATE_WM_header                  \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     20,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_WM {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             ForceKillPixelEnable;
#define ForceOff                                 1
#define ForceON                                  2
   uint32_t                             PointRasterizationRule;
#define RASTRULE_UPPER_LEFT                      0
#define RASTRULE_UPPER_RIGHT                     1
   bool                                 LineStippleEnable;
   bool                                 PolygonStippleEnable;
   uint32_t                             LineAntialiasingRegionWidth;
#define _05pixels                                0
#define _10pixels                                1
#define _20pixels                                2
#define _40pixels                                3
   uint32_t                             LineEndCapAntialiasingRegionWidth;
#define _05pixels                                0
#define _10pixels                                1
#define _20pixels                                2
#define _40pixels                                3
   uint32_t                             BarycentricInterpolationMode;
#define BIM_PERSPECTIVE_PIXEL                    1
#define BIM_PERSPECTIVE_CENTROID                 2
#define BIM_PERSPECTIVE_SAMPLE                   4
#define BIM_LINEAR_PIXEL                         8
#define BIM_LINEAR_CENTROID                      16
#define BIM_LINEAR_SAMPLE                        32
   uint32_t                             PositionZWInterpolationMode;
#define INTERP_PIXEL                             0
#define INTERP_CENTROID                          2
#define INTERP_SAMPLE                            3
   uint32_t                             ForceThreadDispatchEnable;
#define ForceOff                                 1
#define ForceON                                  2
   uint32_t                             EarlyDepthStencilControl;
#define EDSC_NORMAL                              0
#define EDSC_PSEXEC                              1
#define EDSC_PREPS                               2
   bool                                 LegacyDiamondLineRasterization;
   bool                                 LegacyHierarchicalDepthBufferResolveEnable;
   bool                                 LegacyDepthBufferResolveEnable;
   bool                                 LegacyDepthBufferClearEnable;
   bool                                 StatisticsEnable;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_WM_pack(__attribute__((unused)) __gen_user_data *data,
                     __attribute__((unused)) void * restrict dst,
                     __attribute__((unused)) const struct GFX9_3DSTATE_WM * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ForceKillPixelEnable, 0, 1) |
      util_bitpack_uint(values->PointRasterizationRule, 2, 2) |
      util_bitpack_uint(values->LineStippleEnable, 3, 3) |
      util_bitpack_uint(values->PolygonStippleEnable, 4, 4) |
      util_bitpack_uint(values->LineAntialiasingRegionWidth, 6, 7) |
      util_bitpack_uint(values->LineEndCapAntialiasingRegionWidth, 8, 9) |
      util_bitpack_uint(values->BarycentricInterpolationMode, 11, 16) |
      util_bitpack_uint(values->PositionZWInterpolationMode, 17, 18) |
      util_bitpack_uint(values->ForceThreadDispatchEnable, 19, 20) |
      util_bitpack_uint(values->EarlyDepthStencilControl, 21, 22) |
      util_bitpack_uint(values->LegacyDiamondLineRasterization, 26, 26) |
      util_bitpack_uint(values->LegacyHierarchicalDepthBufferResolveEnable, 27, 27) |
      util_bitpack_uint(values->LegacyDepthBufferResolveEnable, 28, 28) |
      util_bitpack_uint(values->LegacyDepthBufferClearEnable, 30, 30) |
      util_bitpack_uint(values->StatisticsEnable, 31, 31);
}

#define GFX9_3DSTATE_WM_CHROMAKEY_length       2
#define GFX9_3DSTATE_WM_CHROMAKEY_length_bias      2
#define GFX9_3DSTATE_WM_CHROMAKEY_header        \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =     76,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_WM_CHROMAKEY {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   bool                                 ChromaKeyKillEnable;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_WM_CHROMAKEY_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_3DSTATE_WM_CHROMAKEY * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ChromaKeyKillEnable, 31, 31);
}

#define GFX9_3DSTATE_WM_DEPTH_STENCIL_length      4
#define GFX9_3DSTATE_WM_DEPTH_STENCIL_length_bias      2
#define GFX9_3DSTATE_WM_DEPTH_STENCIL_header    \
   .DWordLength                         =      2,  \
   ._3DCommandSubOpcode                 =     78,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_WM_DEPTH_STENCIL {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   bool                                 DepthBufferWriteEnable;
   bool                                 DepthTestEnable;
   bool                                 StencilBufferWriteEnable;
   bool                                 StencilTestEnable;
   bool                                 DoubleSidedStencilEnable;
   enum GFX9_3D_Compare_Function        DepthTestFunction;
   enum GFX9_3D_Compare_Function        StencilTestFunction;
   enum GFX9_3D_Stencil_Operation       BackfaceStencilPassDepthPassOp;
   enum GFX9_3D_Stencil_Operation       BackfaceStencilPassDepthFailOp;
   enum GFX9_3D_Stencil_Operation       BackfaceStencilFailOp;
   enum GFX9_3D_Compare_Function        BackfaceStencilTestFunction;
   enum GFX9_3D_Stencil_Operation       StencilPassDepthPassOp;
   enum GFX9_3D_Stencil_Operation       StencilPassDepthFailOp;
   enum GFX9_3D_Stencil_Operation       StencilFailOp;
   uint32_t                             BackfaceStencilWriteMask;
   uint32_t                             BackfaceStencilTestMask;
   uint32_t                             StencilWriteMask;
   uint32_t                             StencilTestMask;
   uint32_t                             BackfaceStencilReferenceValue;
   uint32_t                             StencilReferenceValue;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_WM_DEPTH_STENCIL_pack(__attribute__((unused)) __gen_user_data *data,
                                   __attribute__((unused)) void * restrict dst,
                                   __attribute__((unused)) const struct GFX9_3DSTATE_WM_DEPTH_STENCIL * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->DepthBufferWriteEnable, 0, 0) |
      util_bitpack_uint(values->DepthTestEnable, 1, 1) |
      util_bitpack_uint(values->StencilBufferWriteEnable, 2, 2) |
      util_bitpack_uint(values->StencilTestEnable, 3, 3) |
      util_bitpack_uint(values->DoubleSidedStencilEnable, 4, 4) |
      util_bitpack_uint(values->DepthTestFunction, 5, 7) |
      util_bitpack_uint(values->StencilTestFunction, 8, 10) |
      util_bitpack_uint(values->BackfaceStencilPassDepthPassOp, 11, 13) |
      util_bitpack_uint(values->BackfaceStencilPassDepthFailOp, 14, 16) |
      util_bitpack_uint(values->BackfaceStencilFailOp, 17, 19) |
      util_bitpack_uint(values->BackfaceStencilTestFunction, 20, 22) |
      util_bitpack_uint(values->StencilPassDepthPassOp, 23, 25) |
      util_bitpack_uint(values->StencilPassDepthFailOp, 26, 28) |
      util_bitpack_uint(values->StencilFailOp, 29, 31);

   dw[2] =
      util_bitpack_uint(values->BackfaceStencilWriteMask, 0, 7) |
      util_bitpack_uint(values->BackfaceStencilTestMask, 8, 15) |
      util_bitpack_uint(values->StencilWriteMask, 16, 23) |
      util_bitpack_uint(values->StencilTestMask, 24, 31);

   dw[3] =
      util_bitpack_uint(values->BackfaceStencilReferenceValue, 0, 7) |
      util_bitpack_uint(values->StencilReferenceValue, 8, 15);
}

#define GFX9_3DSTATE_WM_HZ_OP_length           5
#define GFX9_3DSTATE_WM_HZ_OP_length_bias      2
#define GFX9_3DSTATE_WM_HZ_OP_header            \
   .DWordLength                         =      3,  \
   ._3DCommandSubOpcode                 =     82,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_3DSTATE_WM_HZ_OP {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             NumberofMultisamples;
   uint32_t                             StencilClearValue;
   bool                                 FullSurfaceDepthandStencilClear;
   bool                                 PixelPositionOffsetEnable;
   bool                                 HierarchicalDepthBufferResolveEnable;
   bool                                 DepthBufferResolveEnable;
   bool                                 ScissorRectangleEnable;
   bool                                 DepthBufferClearEnable;
   bool                                 StencilBufferClearEnable;
   uint32_t                             ClearRectangleXMin;
   uint32_t                             ClearRectangleYMin;
   uint32_t                             ClearRectangleXMax;
   uint32_t                             ClearRectangleYMax;
   uint32_t                             SampleMask;
};

static inline __attribute__((always_inline)) void
GFX9_3DSTATE_WM_HZ_OP_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_3DSTATE_WM_HZ_OP * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->NumberofMultisamples, 13, 15) |
      util_bitpack_uint(values->StencilClearValue, 16, 23) |
      util_bitpack_uint(values->FullSurfaceDepthandStencilClear, 25, 25) |
      util_bitpack_uint(values->PixelPositionOffsetEnable, 26, 26) |
      util_bitpack_uint(values->HierarchicalDepthBufferResolveEnable, 27, 27) |
      util_bitpack_uint(values->DepthBufferResolveEnable, 28, 28) |
      util_bitpack_uint(values->ScissorRectangleEnable, 29, 29) |
      util_bitpack_uint(values->DepthBufferClearEnable, 30, 30) |
      util_bitpack_uint(values->StencilBufferClearEnable, 31, 31);

   dw[2] =
      util_bitpack_uint(values->ClearRectangleXMin, 0, 15) |
      util_bitpack_uint(values->ClearRectangleYMin, 16, 31);

   dw[3] =
      util_bitpack_uint(values->ClearRectangleXMax, 0, 15) |
      util_bitpack_uint(values->ClearRectangleYMax, 16, 31);

   dw[4] =
      util_bitpack_uint(values->SampleMask, 0, 15);
}

#define GFX9_GPGPU_CSR_BASE_ADDRESS_length      3
#define GFX9_GPGPU_CSR_BASE_ADDRESS_length_bias      2
#define GFX9_GPGPU_CSR_BASE_ADDRESS_header      \
   .DWordLength                         =      1,  \
   ._3DCommandSubOpcode                 =      4,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      0,  \
   .CommandType                         =      3

struct GFX9_GPGPU_CSR_BASE_ADDRESS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   __gen_address_type                   GPGPUCSRBaseAddress;
};

static inline __attribute__((always_inline)) void
GFX9_GPGPU_CSR_BASE_ADDRESS_pack(__attribute__((unused)) __gen_user_data *data,
                                 __attribute__((unused)) void * restrict dst,
                                 __attribute__((unused)) const struct GFX9_GPGPU_CSR_BASE_ADDRESS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->GPGPUCSRBaseAddress, 0, 12, 63);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;
}

#define GFX9_GPGPU_WALKER_length              15
#define GFX9_GPGPU_WALKER_length_bias          2
#define GFX9_GPGPU_WALKER_header                \
   .DWordLength                         =     13,  \
   .SubOpcode                           =      5,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_GPGPU_WALKER {
   uint32_t                             DWordLength;
   bool                                 PredicateEnable;
   bool                                 IndirectParameterEnable;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             InterfaceDescriptorOffset;
   uint32_t                             IndirectDataLength;
   uint64_t                             IndirectDataStartAddress;
   uint32_t                             ThreadWidthCounterMaximum;
   uint32_t                             ThreadHeightCounterMaximum;
   uint32_t                             ThreadDepthCounterMaximum;
   uint32_t                             SIMDSize;
#define SIMD8                                    0
#define SIMD16                                   1
#define SIMD32                                   2
   uint32_t                             ThreadGroupIDStartingX;
   uint32_t                             ThreadGroupIDXDimension;
   uint32_t                             ThreadGroupIDStartingY;
   uint32_t                             ThreadGroupIDYDimension;
   uint32_t                             ThreadGroupIDStartingResumeZ;
   uint32_t                             ThreadGroupIDZDimension;
   uint32_t                             RightExecutionMask;
   uint32_t                             BottomExecutionMask;
};

static inline __attribute__((always_inline)) void
GFX9_GPGPU_WALKER_pack(__attribute__((unused)) __gen_user_data *data,
                       __attribute__((unused)) void * restrict dst,
                       __attribute__((unused)) const struct GFX9_GPGPU_WALKER * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->PredicateEnable, 8, 8) |
      util_bitpack_uint(values->IndirectParameterEnable, 10, 10) |
      util_bitpack_uint(values->SubOpcode, 16, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->InterfaceDescriptorOffset, 0, 5);

   dw[2] =
      util_bitpack_uint(values->IndirectDataLength, 0, 16);

   dw[3] =
      __gen_offset(values->IndirectDataStartAddress, 6, 31);

   dw[4] =
      util_bitpack_uint(values->ThreadWidthCounterMaximum, 0, 5) |
      util_bitpack_uint(values->ThreadHeightCounterMaximum, 8, 13) |
      util_bitpack_uint(values->ThreadDepthCounterMaximum, 16, 21) |
      util_bitpack_uint(values->SIMDSize, 30, 31);

   dw[5] =
      util_bitpack_uint(values->ThreadGroupIDStartingX, 0, 31);

   dw[6] = 0;

   dw[7] =
      util_bitpack_uint(values->ThreadGroupIDXDimension, 0, 31);

   dw[8] =
      util_bitpack_uint(values->ThreadGroupIDStartingY, 0, 31);

   dw[9] = 0;

   dw[10] =
      util_bitpack_uint(values->ThreadGroupIDYDimension, 0, 31);

   dw[11] =
      util_bitpack_uint(values->ThreadGroupIDStartingResumeZ, 0, 31);

   dw[12] =
      util_bitpack_uint(values->ThreadGroupIDZDimension, 0, 31);

   dw[13] =
      util_bitpack_uint(values->RightExecutionMask, 0, 31);

   dw[14] =
      util_bitpack_uint(values->BottomExecutionMask, 0, 31);
}

#define GFX9_HCP_BSD_OBJECT_length             3
#define GFX9_HCP_BSD_OBJECT_length_bias        2
#define GFX9_HCP_BSD_OBJECT_header              \
   .SubOpcode                           =     32,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_BSD_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             IndirectBSDDataLength;
   uint64_t                             IndirectBSDDataStartAddress;
};

static inline __attribute__((always_inline)) void
GFX9_HCP_BSD_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_HCP_BSD_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->IndirectBSDDataLength, 0, 31);

   dw[2] =
      __gen_offset(values->IndirectBSDDataStartAddress, 0, 28);
}

#define GFX9_HCP_FQM_STATE_length             34
#define GFX9_HCP_FQM_STATE_length_bias         2
#define GFX9_HCP_FQM_STATE_header               \
   .SubOpcode                           =      5,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_FQM_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             IntraInter;
#define Intra                                    0
#define Inter                                    1
   uint32_t                             SizeID;
#define SZ_4x4                                   0
#define SZ_8x8                                   1
#define SZ_16x16                                 2
#define SZ_32x32                                 3
   uint32_t                             ColorComponent;
#define Luma                                     0
#define ChromaCb                                 1
#define ChromaCr                                 2
   uint32_t                             FQMDCValue;
   uint32_t                             QuantizerMatrix8x8[64];
};

static inline __attribute__((always_inline)) void
GFX9_HCP_FQM_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_HCP_FQM_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->IntraInter, 0, 0) |
      util_bitpack_uint(values->SizeID, 1, 2) |
      util_bitpack_uint(values->ColorComponent, 3, 4) |
      util_bitpack_uint(values->FQMDCValue, 16, 31);

   dw[2] =
      util_bitpack_uint(values->QuantizerMatrix8x8[0], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[1], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[2], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[3], 24, 31);

   dw[3] =
      util_bitpack_uint(values->QuantizerMatrix8x8[4], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[5], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[6], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[7], 24, 31);

   dw[4] =
      util_bitpack_uint(values->QuantizerMatrix8x8[8], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[9], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[10], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[11], 24, 31);

   dw[5] =
      util_bitpack_uint(values->QuantizerMatrix8x8[12], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[13], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[14], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[15], 24, 31);

   dw[6] =
      util_bitpack_uint(values->QuantizerMatrix8x8[16], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[17], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[18], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[19], 24, 31);

   dw[7] =
      util_bitpack_uint(values->QuantizerMatrix8x8[20], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[21], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[22], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[23], 24, 31);

   dw[8] =
      util_bitpack_uint(values->QuantizerMatrix8x8[24], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[25], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[26], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[27], 24, 31);

   dw[9] =
      util_bitpack_uint(values->QuantizerMatrix8x8[28], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[29], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[30], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[31], 24, 31);

   dw[10] =
      util_bitpack_uint(values->QuantizerMatrix8x8[32], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[33], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[34], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[35], 24, 31);

   dw[11] =
      util_bitpack_uint(values->QuantizerMatrix8x8[36], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[37], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[38], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[39], 24, 31);

   dw[12] =
      util_bitpack_uint(values->QuantizerMatrix8x8[40], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[41], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[42], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[43], 24, 31);

   dw[13] =
      util_bitpack_uint(values->QuantizerMatrix8x8[44], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[45], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[46], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[47], 24, 31);

   dw[14] =
      util_bitpack_uint(values->QuantizerMatrix8x8[48], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[49], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[50], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[51], 24, 31);

   dw[15] =
      util_bitpack_uint(values->QuantizerMatrix8x8[52], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[53], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[54], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[55], 24, 31);

   dw[16] =
      util_bitpack_uint(values->QuantizerMatrix8x8[56], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[57], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[58], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[59], 24, 31);

   dw[17] =
      util_bitpack_uint(values->QuantizerMatrix8x8[60], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[61], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[62], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[63], 24, 31);

   dw[18] = 0;

   dw[19] = 0;

   dw[20] = 0;

   dw[21] = 0;

   dw[22] = 0;

   dw[23] = 0;

   dw[24] = 0;

   dw[25] = 0;

   dw[26] = 0;

   dw[27] = 0;

   dw[28] = 0;

   dw[29] = 0;

   dw[30] = 0;

   dw[31] = 0;

   dw[32] = 0;

   dw[33] = 0;
}

#define GFX9_HCP_IND_OBJ_BASE_ADDR_STATE_length     14
#define GFX9_HCP_IND_OBJ_BASE_ADDR_STATE_length_bias      2
#define GFX9_HCP_IND_OBJ_BASE_ADDR_STATE_header \
   .SubOpcode                           =      3,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_IND_OBJ_BASE_ADDR_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   __gen_address_type                   HCPIndirectBitstreamObjectBaseAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  HCPIndirectBitstreamObjectMemoryAddressAttributes;
   __gen_address_type                   HCPIndirectBitstreamObjectAccessUpperBound;
   __gen_address_type                   HCPIndirectCUObjectBaseAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  HCPIndirectCUObjectMemoryAddressAttributes;
   __gen_address_type                   HCPPAKBSEObjectBaseAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  HCPPAKBSEObjectMemoryAddressAttributes;
   __gen_address_type                   HCPPAKBSEObjectAccessUpperBound;
};

static inline __attribute__((always_inline)) void
GFX9_HCP_IND_OBJ_BASE_ADDR_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                      __attribute__((unused)) void * restrict dst,
                                      __attribute__((unused)) const struct GFX9_HCP_IND_OBJ_BASE_ADDR_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->HCPIndirectBitstreamObjectBaseAddress, 0, 0, 63);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[3], &values->HCPIndirectBitstreamObjectMemoryAddressAttributes);

   const uint64_t v4_address =
      __gen_address(data, &dw[4], values->HCPIndirectBitstreamObjectAccessUpperBound, 0, 0, 63);
   dw[4] = v4_address;
   dw[5] = v4_address >> 32;

   const uint64_t v6_address =
      __gen_address(data, &dw[6], values->HCPIndirectCUObjectBaseAddress, 0, 0, 63);
   dw[6] = v6_address;
   dw[7] = v6_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[8], &values->HCPIndirectCUObjectMemoryAddressAttributes);

   const uint64_t v9_address =
      __gen_address(data, &dw[9], values->HCPPAKBSEObjectBaseAddress, 0, 0, 63);
   dw[9] = v9_address;
   dw[10] = v9_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[11], &values->HCPPAKBSEObjectMemoryAddressAttributes);

   const uint64_t v12_address =
      __gen_address(data, &dw[12], values->HCPPAKBSEObjectAccessUpperBound, 0, 0, 63);
   dw[12] = v12_address;
   dw[13] = v12_address >> 32;
}

#define GFX9_HCP_PAK_INSERT_OBJECT_length_bias      2
#define GFX9_HCP_PAK_INSERT_OBJECT_header       \
   .DWordLength                         =      0,  \
   .SubOpcode                           =     34,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_PAK_INSERT_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   bool                                 EndofSlice;
   bool                                 LastHeader;
   bool                                 EmulationByteBitsInsertEnable;
   uint32_t                             SkipEmulationByteCount;
   uint32_t                             DataBitsInLastDW;
   uint32_t                             HeaderLengthExcludedFromSize;
#define ACCUMULATE                               0
#define NO_ACCUMULATION                          1
   uint32_t                             DataByteOffset;
   bool                                 IndirectPayloadEnable;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_HCP_PAK_INSERT_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GFX9_HCP_PAK_INSERT_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->EndofSlice, 1, 1) |
      util_bitpack_uint(values->LastHeader, 2, 2) |
      util_bitpack_uint(values->EmulationByteBitsInsertEnable, 3, 3) |
      util_bitpack_uint(values->SkipEmulationByteCount, 4, 7) |
      util_bitpack_uint(values->DataBitsInLastDW, 8, 13) |
      util_bitpack_uint(values->HeaderLengthExcludedFromSize, 15, 15) |
      util_bitpack_uint(values->DataByteOffset, 16, 17) |
      util_bitpack_uint(values->IndirectPayloadEnable, 31, 31);
}

#define GFX9_HCP_PAK_OBJECT_length             2
#define GFX9_HCP_PAK_OBJECT_length_bias        2
#define GFX9_HCP_PAK_OBJECT_header              \
   .SubOpcode                           =     33,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_PAK_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             SplitLevel2Part0;
   uint32_t                             SplitLevel2Part1;
   uint32_t                             SplitLevel2Part2;
   uint32_t                             SplitLevel2Part3;
   uint32_t                             SplitLevel1;
   uint32_t                             SplitLevel0;
   uint32_t                             CUCount;
   bool                                 LastLCUofTile;
   bool                                 LastLCUofSlice;
   uint32_t                             CurrentLCUXAddress;
   uint32_t                             CurrentLCUYAddress;
};

static inline __attribute__((always_inline)) void
GFX9_HCP_PAK_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_HCP_PAK_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->SplitLevel2Part0, 0, 3) |
      util_bitpack_uint(values->SplitLevel2Part1, 4, 7) |
      util_bitpack_uint(values->SplitLevel2Part2, 8, 11) |
      util_bitpack_uint(values->SplitLevel2Part3, 12, 15) |
      util_bitpack_uint(values->SplitLevel1, 16, 19) |
      util_bitpack_uint(values->SplitLevel0, 20, 20) |
      util_bitpack_uint(values->CUCount, 24, 29) |
      util_bitpack_uint(values->LastLCUofTile, 30, 30) |
      util_bitpack_uint(values->LastLCUofSlice, 31, 31);
}

#define GFX9_HCP_PIC_STATE_length              2
#define GFX9_HCP_PIC_STATE_length_bias         2
#define GFX9_HCP_PIC_STATE_header               \
   .SubOpcode                           =     16,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_PIC_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             FrameWidthInMinimumCodingBlockSize;
   bool                                 PAKTransformSkipEnable;
   uint32_t                             FrameHeightInMinimumCodingBlockSize;
   uint32_t                             MinCUSize;
#define LCU_64x64                                3
#define LCU_32x32                                2
#define LCU_16x16                                1
#define LCU_8x8                                  0
   uint32_t                             LCUSize;
#define LCU_64x64                                3
#define LCU_32x32                                2
#define LCU_16x16                                1
#define LCU_Illegalreserved                      0
   uint32_t                             MinTUSize;
#define TU_32x32                                 3
#define TU_16x16                                 2
#define TU_8x8                                   1
#define TU_4x4                                   0
   uint32_t                             MaxTUSize;
#define TU_32x32                                 3
#define TU_16x16                                 2
#define TU_8x8                                   1
#define TU_4x4                                   0
   uint32_t                             MinPCMSize;
#define PCM_32x32                                2
#define PCM_16x16                                1
#define PCM_8x8                                  0
   uint32_t                             MaxPCMSize;
#define PCM_32x32                                2
#define PCM_16x16                                1
#define PCM_8x8                                  0
   bool                                 CollocatedPictureIsISlice;
   bool                                 CurrentPictureIsISlice;
   bool                                 CABACZeroWordInsertionTestEnable;
   bool                                 SampleAdaptiveOffsetEnable;
   bool                                 PCMEnable;
   bool                                 CUQPDeltaEnable;
   uint32_t                             MaxDQPDepth;
   bool                                 PCMLoopFilterDisable;
   bool                                 ConstrainedIntraPrediction;
   uint32_t                             Log2ParallelMergeLevel;
   bool                                 SignDataHiding;
   bool                                 LoopFilterEnable;
   bool                                 EntropyCodingSyncEnable;
   bool                                 TilingEnable;
   bool                                 WeightedBiPredicationEnable;
   bool                                 WeightedPredicationEnable;
   bool                                 FieldPic;
   bool                                 TopField;
   bool                                 TransformSkipEnable;
   bool                                 AMPEnable;
   bool                                 TransquantBypassEnable;
   bool                                 StrongIntraSmoothingEnable;
   uint32_t                             CUPacketStructure;
#define VME                                      0
#define ExtEnc                                   1
   int32_t                              PictureCbQPOffset;
   int32_t                              PictureCrQPOffset;
   uint32_t                             IntraMaxTransformHierarchyDepth;
   uint32_t                             InterMaxTransformHierarchyDepth;
   uint32_t                             ChromaPCMSampleBitDepth;
   uint32_t                             LumaPCMSampleBitDepth;
   uint32_t                             ChromaBitDepth;
#define _8bit                                    0
#define _9bit                                    1
#define _10bit                                   2
#define _11bit                                   3
#define _12bit                                   4
   uint32_t                             LumaBitDepth;
#define _8bit                                    0
#define _9bit                                    1
#define _10bit                                   2
#define _11bit                                   3
#define _12bit                                   4
   uint32_t                             LCUMaxBitSizeAllowed;
   bool                                 NonFirstPass;
   bool                                 LCUMaxSizeReport;
   bool                                 FrameBitrateMaxReport;
   bool                                 FrameBitrateMinReport;
   bool                                 LoadBitstreamPointerPerSlice;
   uint32_t                             FrameBitrateMax;
   uint32_t                             FrameBitrateMaxUnit;
   uint32_t                             FrameBitrateMin;
   uint32_t                             FrameBitrateMinUnit;
   uint32_t                             FrameBitrateMinDelta;
   uint32_t                             FrameBitrateMaxDelta;
   struct GFX9_FRAMEDELTAQP             FrameDeltaQPMax;
   struct GFX9_FRAMEDELTAQP             FrameDeltaQPMin;
   struct GFX9_FRAMEDELTAQPRANGE        FrameDeltaQPMaxRange;
   struct GFX9_FRAMEDELTAQPRANGE        FrameDeltaQPMinRange;
   uint32_t                             MinimumFrameSize;
   uint32_t                             MinimumFrameSizeUnits;
#define HCP_MFSU_4Kb                             0
#define HCP_MFSU_16Kb                            1
};

static inline __attribute__((always_inline)) void
GFX9_HCP_PIC_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_HCP_PIC_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->FrameWidthInMinimumCodingBlockSize, 0, 9) |
      util_bitpack_uint(values->PAKTransformSkipEnable, 15, 15) |
      util_bitpack_uint(values->FrameHeightInMinimumCodingBlockSize, 16, 25);
}

#define GFX9_HCP_PIPE_BUF_ADDR_STATE_length     95
#define GFX9_HCP_PIPE_BUF_ADDR_STATE_length_bias      2
#define GFX9_HCP_PIPE_BUF_ADDR_STATE_header     \
   .SubOpcode                           =      2,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_PIPE_BUF_ADDR_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   __gen_address_type                   DecodedPictureAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  DecodedPictureMemoryAddressAttributes;
   __gen_address_type                   DeblockingFilterLineBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  DeblockingFilterLineBufferMemoryAddressAttributes;
   __gen_address_type                   DeblockingFilterTileLineBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  DeblockingFilterTileLineBufferMemoryAddressAttributes;
   __gen_address_type                   DeblockingFilterTileColumnBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  DeblockingFilterTileColumnBufferMemoryAddressAttributes;
   __gen_address_type                   MetadataLineBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  MetadataLineBufferMemoryAddressAttributes;
   __gen_address_type                   MetadataTileLineBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  MetadataTileLineBufferMemoryAddressAttributes;
   __gen_address_type                   MetadataTileColumnBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  MetadataTileColumnBufferMemoryAddressAttributes;
   __gen_address_type                   SAOLineBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  SAOLineBufferMemoryAddressAttributes;
   __gen_address_type                   SAOTileLineBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  SAOTileLineBufferMemoryAddressAttributes;
   __gen_address_type                   SAOTileColumnBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  SAOTileColumnBufferMemoryAddressAttributes;
   __gen_address_type                   CurrentMVTemporalBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  CurrentMVTemporalBufferMemoryAddressAttributes;
   __gen_address_type                   ReferencePictureAddress[8];
   struct GFX9_MEMORYADDRESSATTRIBUTES  ReferencePictureMemoryAddressAttributes;
   __gen_address_type                   OriginalUncompressedPictureSourceAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  OriginalUncompressedPictureSourceMemoryAddressAttributes;
   __gen_address_type                   StreamOutDataDestinationAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  StreamOutDataDestinationMemoryAddressAttributes;
   __gen_address_type                   DecodedPictureStatusBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  DecodedPictureStatusBufferMemoryAddressAttributes;
   __gen_address_type                   LCUILDBStreamOutBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  LCUILDBStreamOutBufferMemoryAddressAttributes;
   __gen_address_type                   CollocatedMVTemporalBufferAddress[8];
   struct GFX9_MEMORYADDRESSATTRIBUTES  CollocatedMVTemporalBufferMemoryAddressAttributes;
   __gen_address_type                   VP9ProbabilityBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  VP9ProbabilityBufferMemoryAddressAttributes;
   uint64_t                             VP9SegmentIDBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  VP9SegmentIDBufferMemoryAddressAttributes;
   __gen_address_type                   VP9HVDLineRowstoreBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  VP9HVDLineRowstoreBufferMemoryAddressAttributes;
   __gen_address_type                   VP9HVDTileRowstoreBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  VP9HVDTileRowstoreBufferMemoryAddressAttributes;
};

static inline __attribute__((always_inline)) void
GFX9_HCP_PIPE_BUF_ADDR_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_HCP_PIPE_BUF_ADDR_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->DecodedPictureAddress, 0, 0, 63);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[3], &values->DecodedPictureMemoryAddressAttributes);

   const uint64_t v4_address =
      __gen_address(data, &dw[4], values->DeblockingFilterLineBufferAddress, 0, 0, 63);
   dw[4] = v4_address;
   dw[5] = v4_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[6], &values->DeblockingFilterLineBufferMemoryAddressAttributes);

   const uint64_t v7_address =
      __gen_address(data, &dw[7], values->DeblockingFilterTileLineBufferAddress, 0, 0, 63);
   dw[7] = v7_address;
   dw[8] = v7_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[9], &values->DeblockingFilterTileLineBufferMemoryAddressAttributes);

   const uint64_t v10_address =
      __gen_address(data, &dw[10], values->DeblockingFilterTileColumnBufferAddress, 0, 0, 63);
   dw[10] = v10_address;
   dw[11] = v10_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[12], &values->DeblockingFilterTileColumnBufferMemoryAddressAttributes);

   const uint64_t v13_address =
      __gen_address(data, &dw[13], values->MetadataLineBufferAddress, 0, 0, 63);
   dw[13] = v13_address;
   dw[14] = v13_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[15], &values->MetadataLineBufferMemoryAddressAttributes);

   const uint64_t v16_address =
      __gen_address(data, &dw[16], values->MetadataTileLineBufferAddress, 0, 0, 63);
   dw[16] = v16_address;
   dw[17] = v16_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[18], &values->MetadataTileLineBufferMemoryAddressAttributes);

   const uint64_t v19_address =
      __gen_address(data, &dw[19], values->MetadataTileColumnBufferAddress, 0, 0, 63);
   dw[19] = v19_address;
   dw[20] = v19_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[21], &values->MetadataTileColumnBufferMemoryAddressAttributes);

   const uint64_t v22_address =
      __gen_address(data, &dw[22], values->SAOLineBufferAddress, 0, 0, 63);
   dw[22] = v22_address;
   dw[23] = v22_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[24], &values->SAOLineBufferMemoryAddressAttributes);

   const uint64_t v25_address =
      __gen_address(data, &dw[25], values->SAOTileLineBufferAddress, 0, 0, 63);
   dw[25] = v25_address;
   dw[26] = v25_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[27], &values->SAOTileLineBufferMemoryAddressAttributes);

   const uint64_t v28_address =
      __gen_address(data, &dw[28], values->SAOTileColumnBufferAddress, 0, 0, 63);
   dw[28] = v28_address;
   dw[29] = v28_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[30], &values->SAOTileColumnBufferMemoryAddressAttributes);

   const uint64_t v31_address =
      __gen_address(data, &dw[31], values->CurrentMVTemporalBufferAddress, 0, 0, 63);
   dw[31] = v31_address;
   dw[32] = v31_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[33], &values->CurrentMVTemporalBufferMemoryAddressAttributes);

   dw[34] = 0;

   dw[35] = 0;

   dw[36] = 0;

   const uint64_t v37_address =
      __gen_address(data, &dw[37], values->ReferencePictureAddress[0], 0, 0, 63);
   dw[37] = v37_address;
   dw[38] = v37_address >> 32;

   const uint64_t v39_address =
      __gen_address(data, &dw[39], values->ReferencePictureAddress[1], 0, 0, 63);
   dw[39] = v39_address;
   dw[40] = v39_address >> 32;

   const uint64_t v41_address =
      __gen_address(data, &dw[41], values->ReferencePictureAddress[2], 0, 0, 63);
   dw[41] = v41_address;
   dw[42] = v41_address >> 32;

   const uint64_t v43_address =
      __gen_address(data, &dw[43], values->ReferencePictureAddress[3], 0, 0, 63);
   dw[43] = v43_address;
   dw[44] = v43_address >> 32;

   const uint64_t v45_address =
      __gen_address(data, &dw[45], values->ReferencePictureAddress[4], 0, 0, 63);
   dw[45] = v45_address;
   dw[46] = v45_address >> 32;

   const uint64_t v47_address =
      __gen_address(data, &dw[47], values->ReferencePictureAddress[5], 0, 0, 63);
   dw[47] = v47_address;
   dw[48] = v47_address >> 32;

   const uint64_t v49_address =
      __gen_address(data, &dw[49], values->ReferencePictureAddress[6], 0, 0, 63);
   dw[49] = v49_address;
   dw[50] = v49_address >> 32;

   const uint64_t v51_address =
      __gen_address(data, &dw[51], values->ReferencePictureAddress[7], 0, 0, 63);
   dw[51] = v51_address;
   dw[52] = v51_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[53], &values->ReferencePictureMemoryAddressAttributes);

   const uint64_t v54_address =
      __gen_address(data, &dw[54], values->OriginalUncompressedPictureSourceAddress, 0, 0, 63);
   dw[54] = v54_address;
   dw[55] = v54_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[56], &values->OriginalUncompressedPictureSourceMemoryAddressAttributes);

   const uint64_t v57_address =
      __gen_address(data, &dw[57], values->StreamOutDataDestinationAddress, 0, 0, 63);
   dw[57] = v57_address;
   dw[58] = v57_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[59], &values->StreamOutDataDestinationMemoryAddressAttributes);

   const uint64_t v60_address =
      __gen_address(data, &dw[60], values->DecodedPictureStatusBufferAddress, 0, 0, 63);
   dw[60] = v60_address;
   dw[61] = v60_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[62], &values->DecodedPictureStatusBufferMemoryAddressAttributes);

   const uint64_t v63_address =
      __gen_address(data, &dw[63], values->LCUILDBStreamOutBufferAddress, 0, 0, 63);
   dw[63] = v63_address;
   dw[64] = v63_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[65], &values->LCUILDBStreamOutBufferMemoryAddressAttributes);

   const uint64_t v66_address =
      __gen_address(data, &dw[66], values->CollocatedMVTemporalBufferAddress[0], 0, 0, 63);
   dw[66] = v66_address;
   dw[67] = v66_address >> 32;

   const uint64_t v68_address =
      __gen_address(data, &dw[68], values->CollocatedMVTemporalBufferAddress[1], 0, 0, 63);
   dw[68] = v68_address;
   dw[69] = v68_address >> 32;

   const uint64_t v70_address =
      __gen_address(data, &dw[70], values->CollocatedMVTemporalBufferAddress[2], 0, 0, 63);
   dw[70] = v70_address;
   dw[71] = v70_address >> 32;

   const uint64_t v72_address =
      __gen_address(data, &dw[72], values->CollocatedMVTemporalBufferAddress[3], 0, 0, 63);
   dw[72] = v72_address;
   dw[73] = v72_address >> 32;

   const uint64_t v74_address =
      __gen_address(data, &dw[74], values->CollocatedMVTemporalBufferAddress[4], 0, 0, 63);
   dw[74] = v74_address;
   dw[75] = v74_address >> 32;

   const uint64_t v76_address =
      __gen_address(data, &dw[76], values->CollocatedMVTemporalBufferAddress[5], 0, 0, 63);
   dw[76] = v76_address;
   dw[77] = v76_address >> 32;

   const uint64_t v78_address =
      __gen_address(data, &dw[78], values->CollocatedMVTemporalBufferAddress[6], 0, 0, 63);
   dw[78] = v78_address;
   dw[79] = v78_address >> 32;

   const uint64_t v80_address =
      __gen_address(data, &dw[80], values->CollocatedMVTemporalBufferAddress[7], 0, 0, 63);
   dw[80] = v80_address;
   dw[81] = v80_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[82], &values->CollocatedMVTemporalBufferMemoryAddressAttributes);

   const uint64_t v83_address =
      __gen_address(data, &dw[83], values->VP9ProbabilityBufferAddress, 0, 0, 63);
   dw[83] = v83_address;
   dw[84] = v83_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[85], &values->VP9ProbabilityBufferMemoryAddressAttributes);

   const uint64_t v86 =
      util_bitpack_uint(values->VP9SegmentIDBufferAddress, 0, 63);
   dw[86] = v86;
   dw[87] = v86 >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[88], &values->VP9SegmentIDBufferMemoryAddressAttributes);

   const uint64_t v89_address =
      __gen_address(data, &dw[89], values->VP9HVDLineRowstoreBufferAddress, 0, 0, 63);
   dw[89] = v89_address;
   dw[90] = v89_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[91], &values->VP9HVDLineRowstoreBufferMemoryAddressAttributes);

   const uint64_t v92_address =
      __gen_address(data, &dw[92], values->VP9HVDTileRowstoreBufferAddress, 0, 0, 63);
   dw[92] = v92_address;
   dw[93] = v92_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[94], &values->VP9HVDTileRowstoreBufferMemoryAddressAttributes);
}

#define GFX9_HCP_PIPE_MODE_SELECT_length       4
#define GFX9_HCP_PIPE_MODE_SELECT_length_bias      2
#define GFX9_HCP_PIPE_MODE_SELECT_header        \
   .SubOpcode                           =      0,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_PIPE_MODE_SELECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             CodecSelect;
#define Decode                                   0
#define Encode                                   1
   bool                                 DeblockerStreamOutEnable;
   bool                                 PAKPipelineStreamOutEnable;
   bool                                 PicStatusErrorReportEnable;
   uint32_t                             CodecStandardSelect;
#define HEVC                                     0
#define VP9                                      1
   bool                                 AdvancedRateControlEnable;
   bool                                 PAKFrameLevelStreamOutEnable;
   uint32_t                             MediaSoftResetCounter;
   uint32_t                             PicStatusErrorReportID;
};

static inline __attribute__((always_inline)) void
GFX9_HCP_PIPE_MODE_SELECT_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_HCP_PIPE_MODE_SELECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->CodecSelect, 0, 0) |
      util_bitpack_uint(values->DeblockerStreamOutEnable, 1, 1) |
      util_bitpack_uint(values->PAKPipelineStreamOutEnable, 2, 2) |
      util_bitpack_uint(values->PicStatusErrorReportEnable, 3, 3) |
      util_bitpack_uint(values->CodecStandardSelect, 5, 7) |
      util_bitpack_uint(values->AdvancedRateControlEnable, 9, 9) |
      util_bitpack_uint(values->PAKFrameLevelStreamOutEnable, 12, 12);

   dw[2] =
      util_bitpack_uint(values->MediaSoftResetCounter, 0, 31);

   dw[3] =
      util_bitpack_uint(values->PicStatusErrorReportID, 0, 31);
}

#define GFX9_HCP_QM_STATE_length              34
#define GFX9_HCP_QM_STATE_length_bias          2
#define GFX9_HCP_QM_STATE_header                \
   .SubOpcode                           =      4,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_QM_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             PredictionType;
#define Intra                                    0
#define Inter                                    1
   uint32_t                             SizeID;
#define SZ_4x4                                   0
#define SZ_8x8                                   1
#define SZ_16x16                                 2
#define SZ_32x32                                 3
   uint32_t                             ColorComponent;
#define Luma                                     0
#define ChromaCb                                 1
#define ChromaCr                                 2
   uint32_t                             DCCoefficient;
   uint32_t                             QuantizerMatrix8x8[64];
};

static inline __attribute__((always_inline)) void
GFX9_HCP_QM_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                       __attribute__((unused)) void * restrict dst,
                       __attribute__((unused)) const struct GFX9_HCP_QM_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->PredictionType, 0, 0) |
      util_bitpack_uint(values->SizeID, 1, 2) |
      util_bitpack_uint(values->ColorComponent, 3, 4) |
      util_bitpack_uint(values->DCCoefficient, 5, 12);

   dw[2] =
      util_bitpack_uint(values->QuantizerMatrix8x8[0], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[1], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[2], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[3], 24, 31);

   dw[3] =
      util_bitpack_uint(values->QuantizerMatrix8x8[4], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[5], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[6], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[7], 24, 31);

   dw[4] =
      util_bitpack_uint(values->QuantizerMatrix8x8[8], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[9], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[10], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[11], 24, 31);

   dw[5] =
      util_bitpack_uint(values->QuantizerMatrix8x8[12], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[13], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[14], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[15], 24, 31);

   dw[6] =
      util_bitpack_uint(values->QuantizerMatrix8x8[16], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[17], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[18], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[19], 24, 31);

   dw[7] =
      util_bitpack_uint(values->QuantizerMatrix8x8[20], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[21], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[22], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[23], 24, 31);

   dw[8] =
      util_bitpack_uint(values->QuantizerMatrix8x8[24], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[25], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[26], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[27], 24, 31);

   dw[9] =
      util_bitpack_uint(values->QuantizerMatrix8x8[28], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[29], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[30], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[31], 24, 31);

   dw[10] =
      util_bitpack_uint(values->QuantizerMatrix8x8[32], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[33], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[34], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[35], 24, 31);

   dw[11] =
      util_bitpack_uint(values->QuantizerMatrix8x8[36], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[37], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[38], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[39], 24, 31);

   dw[12] =
      util_bitpack_uint(values->QuantizerMatrix8x8[40], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[41], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[42], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[43], 24, 31);

   dw[13] =
      util_bitpack_uint(values->QuantizerMatrix8x8[44], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[45], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[46], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[47], 24, 31);

   dw[14] =
      util_bitpack_uint(values->QuantizerMatrix8x8[48], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[49], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[50], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[51], 24, 31);

   dw[15] =
      util_bitpack_uint(values->QuantizerMatrix8x8[52], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[53], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[54], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[55], 24, 31);

   dw[16] =
      util_bitpack_uint(values->QuantizerMatrix8x8[56], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[57], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[58], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[59], 24, 31);

   dw[17] =
      util_bitpack_uint(values->QuantizerMatrix8x8[60], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[61], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[62], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[63], 24, 31);

   dw[18] = 0;

   dw[19] = 0;

   dw[20] = 0;

   dw[21] = 0;

   dw[22] = 0;

   dw[23] = 0;

   dw[24] = 0;

   dw[25] = 0;

   dw[26] = 0;

   dw[27] = 0;

   dw[28] = 0;

   dw[29] = 0;

   dw[30] = 0;

   dw[31] = 0;

   dw[32] = 0;

   dw[33] = 0;
}

#define GFX9_HCP_REF_IDX_STATE_length         18
#define GFX9_HCP_REF_IDX_STATE_length_bias      2
#define GFX9_HCP_REF_IDX_STATE_header           \
   .SubOpcode                           =     18,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_REF_IDX_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             ReferencePictureListSelect;
   uint32_t                             NumberofReferenceIndexesActive;
   struct GFX9_HCP_REF_LIST_ENTRY       ReferenceListEntry[16];
};

static inline __attribute__((always_inline)) void
GFX9_HCP_REF_IDX_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_HCP_REF_IDX_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ReferencePictureListSelect, 0, 0) |
      util_bitpack_uint(values->NumberofReferenceIndexesActive, 1, 4);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[2], &values->ReferenceListEntry[0]);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[3], &values->ReferenceListEntry[1]);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[4], &values->ReferenceListEntry[2]);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[5], &values->ReferenceListEntry[3]);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[6], &values->ReferenceListEntry[4]);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[7], &values->ReferenceListEntry[5]);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[8], &values->ReferenceListEntry[6]);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[9], &values->ReferenceListEntry[7]);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[10], &values->ReferenceListEntry[8]);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[11], &values->ReferenceListEntry[9]);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[12], &values->ReferenceListEntry[10]);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[13], &values->ReferenceListEntry[11]);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[14], &values->ReferenceListEntry[12]);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[15], &values->ReferenceListEntry[13]);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[16], &values->ReferenceListEntry[14]);

   GFX9_HCP_REF_LIST_ENTRY_pack(data, &dw[17], &values->ReferenceListEntry[15]);
}

#define GFX9_HCP_SLICE_STATE_length            2
#define GFX9_HCP_SLICE_STATE_length_bias       2
#define GFX9_HCP_SLICE_STATE_header             \
   .SubOpcode                           =     20,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_SLICE_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             SliceHorizontalPosition;
   uint32_t                             SliceVerticalPosition;
   uint32_t                             NextSliceHorizontalPosition;
   uint32_t                             NextSliceVerticalPosition;
   uint32_t                             SliceType;
#define HCP_ST_BSlice                            0
#define HCP_ST_PSlice                            1
#define HCP_ST_ISlice                            2
   bool                                 LastSlice;
   uint32_t                             SliceQPSign;
   bool                                 DependentSlice;
   bool                                 SliceTemporalMVPEnable;
   uint32_t                             SliceQP;
   int32_t                              SliceCbQPOffset;
#define _12                                      20
#define _11                                      21
#define _10                                      22
#define _9                                       23
#define _8                                       24
#define _7                                       25
#define _6                                       26
#define _5                                       27
#define _4                                       28
#define _3                                       29
#define _2                                       30
#define _1                                       31
   int32_t                              SliceCrQPOffset;
#define _12                                      20
#define _11                                      21
#define _10                                      22
#define _9                                       23
#define _8                                       24
#define _7                                       25
#define _6                                       26
#define _5                                       27
#define _4                                       28
#define _3                                       29
#define _2                                       30
#define _1                                       31
   bool                                 LastSliceofTile;
   bool                                 SliceHeaderDisableDeblockingFilter;
   int32_t                              SliceTCOffsetDiv2;
   int32_t                              SliceBetaOffsetDiv2;
   bool                                 SliceLoopFilterEnable;
   bool                                 SliceSAOChroma;
   bool                                 SliceSAOLuma;
   bool                                 MVDL1Zero;
   bool                                 LowDelay;
   bool                                 CollocatedFromL0;
   uint32_t                             Log2WeightDenominatorChroma;
   uint32_t                             Log2WeightDenominatorLuma;
   bool                                 CABACInit;
   uint32_t                             MaxMergeIndex;
   uint32_t                             CollocatedMVTemporalBufferIndex;
   uint32_t                             SliceHeaderLength;
   uint32_t                             RoundIntra;
#define _132                                     0
#define _232                                     1
#define _332                                     2
#define _432                                     3
#define _532                                     4
#define _632                                     5
#define _732                                     6
#define _832                                     7
#define _932                                     8
#define _1032                                    9
#define _1132                                    10
#define _1232                                    11
#define _1332                                    12
#define _1432                                    13
#define _1532                                    14
#define _1632                                    15
   uint32_t                             RoundInter;
#define _132                                     0
#define _232                                     1
#define _332                                     2
#define _432                                     3
#define _532                                     4
#define _632                                     5
#define _732                                     6
#define _832                                     7
#define _932                                     8
#define _1032                                    9
#define _1132                                    10
#define _1232                                    11
#define _1332                                    12
#define _1432                                    13
#define _1532                                    14
#define _1632                                    15
   bool                                 CABACZeroWordInsertionEnable;
   bool                                 EmulationByteSliceInsertEnable;
   bool                                 TailInsertionPresent;
   bool                                 SliceDataInsertionPresent;
   bool                                 HeaderInsertionPresent;
   uint64_t                             IndirectPAKBSEDataStartOffset;
   uint32_t                             TransformSkipLambda;
   uint32_t                             TransformSkipNumberofZeroCoeffsFactor0;
   uint32_t                             TransformSkipNumberofNonZeroCoeffsFactor0;
   uint32_t                             TransformSkipNumberofZeroCoeffsFactor1;
   uint32_t                             TransformSkipNumberofNonZeroCoeffsFactor1;
};

static inline __attribute__((always_inline)) void
GFX9_HCP_SLICE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                          __attribute__((unused)) void * restrict dst,
                          __attribute__((unused)) const struct GFX9_HCP_SLICE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->SliceHorizontalPosition, 0, 8) |
      util_bitpack_uint(values->SliceVerticalPosition, 16, 24);
}

#define GFX9_HCP_SURFACE_STATE_length          3
#define GFX9_HCP_SURFACE_STATE_length_bias      2
#define GFX9_HCP_SURFACE_STATE_header           \
   .SubOpcode                           =      1,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_SURFACE_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             SurfacePitch;
   uint32_t                             SurfaceID;
#define HCP_CurrentDecodedPicture                0
#define HCP_SourceInputPicture                   1
#define HCP_PrevReferencePicture                 2
#define HCP_GoldenReferencePicture               3
#define HCP_AltRefReferencePicture               4
   uint32_t                             YOffsetforUCb;
   uint32_t                             SurfaceFormat;
#define PLANAR_420_8                             4
#define P010                                     13
};

static inline __attribute__((always_inline)) void
GFX9_HCP_SURFACE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_HCP_SURFACE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->SurfacePitch, 0, 16) |
      util_bitpack_uint(values->SurfaceID, 28, 31);

   dw[2] =
      util_bitpack_uint(values->YOffsetforUCb, 0, 14) |
      util_bitpack_uint(values->SurfaceFormat, 28, 31);
}

#define GFX9_HCP_TILE_CODING_length            1
#define GFX9_HCP_TILE_CODING_length_bias       1
#define GFX9_HCP_TILE_CODING_header             \
   .SubOpcode                           =     21,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_TILE_CODING {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             SAOParameterOffset;
};

static inline __attribute__((always_inline)) void
GFX9_HCP_TILE_CODING_pack(__attribute__((unused)) __gen_user_data *data,
                          __attribute__((unused)) void * restrict dst,
                          __attribute__((unused)) const struct GFX9_HCP_TILE_CODING * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_HCP_TILE_STATE_length            13
#define GFX9_HCP_TILE_STATE_length_bias        2
#define GFX9_HCP_TILE_STATE_header              \
   .MediaInstructionCommand             =     17,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_TILE_STATE {
   uint32_t                             DWordLength;
   uint32_t                             MediaInstructionCommand;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             NumberofTileRows;
   uint32_t                             NumberofTileColumns;
   struct GFX9_HCP_TILE_POSITION_IN_CTB ColumnPosition[5];
   struct GFX9_HCP_TILE_POSITION_IN_CTB Rowposition[6];
};

static inline __attribute__((always_inline)) void
GFX9_HCP_TILE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_HCP_TILE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->MediaInstructionCommand, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->NumberofTileRows, 0, 4) |
      util_bitpack_uint(values->NumberofTileColumns, 5, 9);

   GFX9_HCP_TILE_POSITION_IN_CTB_pack(data, &dw[2], &values->ColumnPosition[0]);

   GFX9_HCP_TILE_POSITION_IN_CTB_pack(data, &dw[3], &values->ColumnPosition[1]);

   GFX9_HCP_TILE_POSITION_IN_CTB_pack(data, &dw[4], &values->ColumnPosition[2]);

   GFX9_HCP_TILE_POSITION_IN_CTB_pack(data, &dw[5], &values->ColumnPosition[3]);

   GFX9_HCP_TILE_POSITION_IN_CTB_pack(data, &dw[6], &values->ColumnPosition[4]);

   GFX9_HCP_TILE_POSITION_IN_CTB_pack(data, &dw[7], &values->Rowposition[0]);

   GFX9_HCP_TILE_POSITION_IN_CTB_pack(data, &dw[8], &values->Rowposition[1]);

   GFX9_HCP_TILE_POSITION_IN_CTB_pack(data, &dw[9], &values->Rowposition[2]);

   GFX9_HCP_TILE_POSITION_IN_CTB_pack(data, &dw[10], &values->Rowposition[3]);

   GFX9_HCP_TILE_POSITION_IN_CTB_pack(data, &dw[11], &values->Rowposition[4]);

   GFX9_HCP_TILE_POSITION_IN_CTB_pack(data, &dw[12], &values->Rowposition[5]);
}

#define GFX9_HCP_VP9_PIC_STATE_length          2
#define GFX9_HCP_VP9_PIC_STATE_length_bias      2
#define GFX9_HCP_VP9_PIC_STATE_header           \
   .SubOpcode                           =     48,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_VP9_PIC_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             FrameWidth;
   uint32_t                             FrameHeight;
   uint32_t                             FrameType;
#define VP9_KeyFrame                             0
#define VP9_InterFrame                           1
   bool                                 AdaptProbabilities;
   bool                                 IntraOnly;
   bool                                 AllowHiPrecisionMV;
   uint32_t                             MotionCompensationFilterType;
#define Eighttap                                 0
#define EighttapSmooth                           1
#define EighttapSharp                            2
#define Bilinear                                 3
#define Switchable                               4
   uint32_t                             ReferenceFrameSignBias;
   bool                                 UsePrevinFindMVReferences;
   uint32_t                             HybridPredictionMode;
   uint32_t                             SelectableTXMode;
   uint32_t                             LastFrameType;
#define VP9_KeyFrame                             0
#define VP9_NonKeyFrame                          1
   bool                                 RefreshFrameContextEnable;
   bool                                 ErrorResilientModeEnable;
   bool                                 FrameParallelDecodingModeEnable;
   uint32_t                             FilterLevel;
   uint32_t                             SharpnessLevel;
   bool                                 SegmentationEnable;
   bool                                 SegmentationUpdateMap;
   bool                                 SegmentationTemporalUpdate;
   bool                                 LosslessMode;
   bool                                 SegmentIDStreamOutEnable;
   bool                                 SegmentIDStreamInEnable;
   uint32_t                             Log2TileColumn;
#define _1TileColumn                             0
#define _2TileColumn                             1
#define _4TileColumn                             2
#define _8TileColumn                             3
#define _16TileColumn                            4
#define _32TileColumn                            5
#define _64TileColumn                            6
   uint32_t                             Log2TileRow;
#define _1TileRow                                0
#define _2TileRow                                1
#define _4TileRow                                2
   uint32_t                             ChromaSamplingFormat;
#define Format_420                               0
   uint32_t                             BitDepth;
#define _8bit                                    0
#define _10bit                                   2
#define _12bit                                   4
   uint32_t                             ProfileLevel;
#define Profile_0                                0
#define Profile_2                                2
   float                                VerticalScaleFactorforLAST;
   float                                HorizontalScaleFactorforLAST;
   float                                VerticalScaleFactorforGOLDEN;
   float                                HorizontalScaleFactorforGOLDEN;
   float                                VerticalScaleFactorforALTREF;
   float                                HorizontalScaleFactorforALTREF;
   uint32_t                             LastFrameWidth;
   uint32_t                             LastFrameHeight;
   uint32_t                             GoldenFrameWidth;
   uint32_t                             GoldenFrameHeight;
   uint32_t                             AltrefFrameWidth;
   uint32_t                             AltrefFrameHeight;
   uint32_t                             UncompressedHeaderLength;
   uint32_t                             FirstPartitionSize;
   bool                                 MotionCompScalingEnable;
   uint32_t                             CompressedHeaderBINcount;
   uint32_t                             LumaACQIndexDelta;
   int32_t                              ChromaACQIndexDelta;
   int32_t                              ChromaDCQIndexDelta;
   int32_t                              LumaDCQIndexDelta;
   int32_t                              LFRefDelta0;
   int32_t                              LFRefDelta1;
   int32_t                              LFRefDelta2;
   int32_t                              LFRefDelta3;
   int32_t                              LFModeDelta0;
   int32_t                              LFModeDelta1;
   uint32_t                             BitOffsetforLFRefDelta;
   uint32_t                             BitOffsetforLFModeDelta;
   uint32_t                             BitOffsetforQindex;
   uint32_t                             BitOffsetforLFLevel;
};

static inline __attribute__((always_inline)) void
GFX9_HCP_VP9_PIC_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_HCP_VP9_PIC_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->FrameWidth, 0, 13) |
      util_bitpack_uint(values->FrameHeight, 16, 29);
}

#define GFX9_HCP_VP9_SEGMENT_STATE_length      8
#define GFX9_HCP_VP9_SEGMENT_STATE_length_bias      2
#define GFX9_HCP_VP9_SEGMENT_STATE_header       \
   .SubOpcode                           =     50,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_VP9_SEGMENT_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             SegmentID;
   bool                                 SegmentSkipped;
   uint32_t                             SegmentReference;
   bool                                 SegmentReferenceEnable;
   uint32_t                             FilterLevelRef0Mode0;
   uint32_t                             FilterLevelRef0Mode1;
   uint32_t                             FilterLevelRef1Mode0;
   uint32_t                             FilterLevelRef1Mode1;
   uint32_t                             FilterLevelRef2Mode0;
   uint32_t                             FilterLevelRef2Mode1;
   uint32_t                             FilterLevelRef3Mode0;
   uint32_t                             FilterLevelRef3Mode1;
   uint32_t                             LumaDCQuantScale;
   uint32_t                             LumaACQuantScale;
   uint32_t                             ChromaDCQuantScale;
   uint32_t                             ChromaACQuantScale;
};

static inline __attribute__((always_inline)) void
GFX9_HCP_VP9_SEGMENT_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GFX9_HCP_VP9_SEGMENT_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->SegmentID, 0, 2);

   dw[2] =
      util_bitpack_uint(values->SegmentSkipped, 0, 0) |
      util_bitpack_uint(values->SegmentReference, 1, 2) |
      util_bitpack_uint(values->SegmentReferenceEnable, 3, 3);

   dw[3] =
      util_bitpack_uint(values->FilterLevelRef0Mode0, 0, 5) |
      util_bitpack_uint(values->FilterLevelRef0Mode1, 8, 13) |
      util_bitpack_uint(values->FilterLevelRef1Mode0, 16, 21) |
      util_bitpack_uint(values->FilterLevelRef1Mode1, 24, 29);

   dw[4] =
      util_bitpack_uint(values->FilterLevelRef2Mode0, 0, 5) |
      util_bitpack_uint(values->FilterLevelRef2Mode1, 8, 13) |
      util_bitpack_uint(values->FilterLevelRef3Mode0, 16, 21) |
      util_bitpack_uint(values->FilterLevelRef3Mode1, 24, 29);

   dw[5] =
      util_bitpack_uint(values->LumaDCQuantScale, 0, 14) |
      util_bitpack_uint(values->LumaACQuantScale, 16, 30);

   dw[6] =
      util_bitpack_uint(values->ChromaDCQuantScale, 0, 14) |
      util_bitpack_uint(values->ChromaACQuantScale, 16, 30);

   dw[7] = 0;
}

#define GFX9_HCP_WEIGHTOFFSET_STATE_length     34
#define GFX9_HCP_WEIGHTOFFSET_STATE_length_bias      2
#define GFX9_HCP_WEIGHTOFFSET_STATE_header      \
   .SubOpcode                           =     19,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HCP_WEIGHTOFFSET_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             ReferencePictureListSelect;
   struct GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY LumaOffsets[16];
   struct GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY ChromaOffsets[16];
};

static inline __attribute__((always_inline)) void
GFX9_HCP_WEIGHTOFFSET_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                 __attribute__((unused)) void * restrict dst,
                                 __attribute__((unused)) const struct GFX9_HCP_WEIGHTOFFSET_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ReferencePictureListSelect, 0, 0);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[2], &values->LumaOffsets[0]);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[3], &values->LumaOffsets[1]);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[4], &values->LumaOffsets[2]);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[5], &values->LumaOffsets[3]);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[6], &values->LumaOffsets[4]);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[7], &values->LumaOffsets[5]);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[8], &values->LumaOffsets[6]);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[9], &values->LumaOffsets[7]);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[10], &values->LumaOffsets[8]);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[11], &values->LumaOffsets[9]);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[12], &values->LumaOffsets[10]);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[13], &values->LumaOffsets[11]);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[14], &values->LumaOffsets[12]);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[15], &values->LumaOffsets[13]);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[16], &values->LumaOffsets[14]);

   GFX9_HCP_WEIGHTOFFSET_LUMA_ENTRY_pack(data, &dw[17], &values->LumaOffsets[15]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[18], &values->ChromaOffsets[0]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[19], &values->ChromaOffsets[1]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[20], &values->ChromaOffsets[2]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[21], &values->ChromaOffsets[3]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[22], &values->ChromaOffsets[4]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[23], &values->ChromaOffsets[5]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[24], &values->ChromaOffsets[6]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[25], &values->ChromaOffsets[7]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[26], &values->ChromaOffsets[8]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[27], &values->ChromaOffsets[9]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[28], &values->ChromaOffsets[10]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[29], &values->ChromaOffsets[11]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[30], &values->ChromaOffsets[12]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[31], &values->ChromaOffsets[13]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[32], &values->ChromaOffsets[14]);

   GFX9_HCP_WEIGHTOFFSET_CHROMA_ENTRY_pack(data, &dw[33], &values->ChromaOffsets[15]);
}

#define GFX9_HEVC_VP9_RDOQ_STATE_length       62
#define GFX9_HEVC_VP9_RDOQ_STATE_length_bias      2
#define GFX9_HEVC_VP9_RDOQ_STATE_header         \
   .DWordLength                         =     60,  \
   .SubOpcodeB                          =      8,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HEVC_VP9_RDOQ_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   bool                                 HTQPerformanceFix1Disable;
   bool                                 HTQPerformanceFix0Disable;
   struct GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS IntraLumaLambda[32];
   struct GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS IntraChromaLambda[32];
   struct GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS InterLumaLambda[32];
   struct GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS InterChromaLambda[32];
};

static inline __attribute__((always_inline)) void
GFX9_HEVC_VP9_RDOQ_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_HEVC_VP9_RDOQ_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->HTQPerformanceFix1Disable, 30, 30) |
      util_bitpack_uint(values->HTQPerformanceFix0Disable, 31, 31);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[2], &values->IntraLumaLambda[0]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[3], &values->IntraLumaLambda[1]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[4], &values->IntraLumaLambda[2]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[5], &values->IntraLumaLambda[3]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[6], &values->IntraLumaLambda[4]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[7], &values->IntraLumaLambda[5]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[8], &values->IntraLumaLambda[6]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[9], &values->IntraLumaLambda[7]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[10], &values->IntraLumaLambda[8]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[11], &values->IntraLumaLambda[9]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[12], &values->IntraLumaLambda[10]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[13], &values->IntraLumaLambda[11]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[14], &values->IntraLumaLambda[12]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[15], &values->IntraLumaLambda[13]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[16], &values->IntraLumaLambda[14]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[17], &values->IntraLumaLambda[15]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[18], &values->IntraLumaLambda[16]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[19], &values->IntraLumaLambda[17]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[20], &values->IntraLumaLambda[18]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[21], &values->IntraLumaLambda[19]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[22], &values->IntraLumaLambda[20]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[23], &values->IntraLumaLambda[21]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[24], &values->IntraLumaLambda[22]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[25], &values->IntraLumaLambda[23]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[26], &values->IntraLumaLambda[24]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[27], &values->IntraLumaLambda[25]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[28], &values->IntraLumaLambda[26]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[29], &values->IntraLumaLambda[27]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[30], &values->IntraLumaLambda[28]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[31], &values->IntraLumaLambda[29]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[32], &values->IntraLumaLambda[30]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[33], &values->IntraLumaLambda[31]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[34], &values->IntraChromaLambda[0]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[35], &values->IntraChromaLambda[1]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[36], &values->IntraChromaLambda[2]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[37], &values->IntraChromaLambda[3]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[38], &values->IntraChromaLambda[4]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[39], &values->IntraChromaLambda[5]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[40], &values->IntraChromaLambda[6]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[41], &values->IntraChromaLambda[7]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[42], &values->IntraChromaLambda[8]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[43], &values->IntraChromaLambda[9]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[44], &values->IntraChromaLambda[10]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[45], &values->IntraChromaLambda[11]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[46], &values->IntraChromaLambda[12]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[47], &values->IntraChromaLambda[13]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[48], &values->IntraChromaLambda[14]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[49], &values->IntraChromaLambda[15]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[50], &values->IntraChromaLambda[16]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[51], &values->IntraChromaLambda[17]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[52], &values->IntraChromaLambda[18]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[53], &values->IntraChromaLambda[19]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[54], &values->IntraChromaLambda[20]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[55], &values->IntraChromaLambda[21]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[56], &values->IntraChromaLambda[22]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[57], &values->IntraChromaLambda[23]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[58], &values->IntraChromaLambda[24]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[59], &values->IntraChromaLambda[25]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[60], &values->IntraChromaLambda[26]);

   GFX9_HEVC_VP9_RDOQ_LAMBDA_FIELDS_pack(data, &dw[61], &values->IntraChromaLambda[27]);
}

#define GFX9_HUC_CFG_STATE_length              2
#define GFX9_HUC_CFG_STATE_length_bias         2
#define GFX9_HUC_CFG_STATE_header               \
   .SubOpcode                           =      3,  \
   .MediaCommandOpcode                  =     11,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HUC_CFG_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             P24C;
#define Normaloperation                          0
#define Forcereset                               1
};

static inline __attribute__((always_inline)) void
GFX9_HUC_CFG_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_HUC_CFG_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->P24C, 0, 0);
}

#define GFX9_HUC_DMEM_STATE_length             6
#define GFX9_HUC_DMEM_STATE_length_bias        2
#define GFX9_HUC_DMEM_STATE_header              \
   .SubOpcode                           =      2,  \
   .MediaCommandOpcode                  =     11,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HUC_DMEM_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   __gen_address_type                   HUCDataSourceAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  HUCDataSourceMemoryAddressAttributes;
   __gen_address_type                   HUCDataDestinationAddress;
   uint32_t                             HUCDataLength;
};

static inline __attribute__((always_inline)) void
GFX9_HUC_DMEM_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_HUC_DMEM_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->HUCDataSourceAddress, 0, 0, 63);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[3], &values->HUCDataSourceMemoryAddressAttributes);

   dw[4] = __gen_address(data, &dw[4], values->HUCDataDestinationAddress, 0, 6, 16);

   dw[5] =
      util_bitpack_uint(values->HUCDataLength, 6, 16);
}

#define GFX9_HUC_IMEM_STATE_length             5
#define GFX9_HUC_IMEM_STATE_length_bias        2
#define GFX9_HUC_IMEM_STATE_header              \
   .SubOpcode                           =      1,  \
   .MediaCommandOpcode                  =     11,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HUC_IMEM_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             HUCFirmwareDescriptor;
};

static inline __attribute__((always_inline)) void
GFX9_HUC_IMEM_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_HUC_IMEM_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] = 0;

   dw[2] = 0;

   dw[3] = 0;

   dw[4] =
      util_bitpack_uint(values->HUCFirmwareDescriptor, 0, 7);
}

#define GFX9_HUC_IND_OBJ_BASE_ADDR_STATE_length     11
#define GFX9_HUC_IND_OBJ_BASE_ADDR_STATE_length_bias      2
#define GFX9_HUC_IND_OBJ_BASE_ADDR_STATE_header \
   .SubOpcode                           =      5,  \
   .MediaCommandOpcode                  =     11,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HUC_IND_OBJ_BASE_ADDR_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   __gen_address_type                   HUCIndirectStreamInObjectAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  HUCIndirectStreamInObjectMemoryAddressAttributes;
   __gen_address_type                   HUCIndirectStreamInObjectAccessUpperBound;
   __gen_address_type                   HUCIndirectStreamOutObjectAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  HUCIndirectStreamOutObjectMemoryAddressAttributes;
   __gen_address_type                   HUCIndirectStreamOutObjectAccessUpperBound;
};

static inline __attribute__((always_inline)) void
GFX9_HUC_IND_OBJ_BASE_ADDR_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                      __attribute__((unused)) void * restrict dst,
                                      __attribute__((unused)) const struct GFX9_HUC_IND_OBJ_BASE_ADDR_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->HUCIndirectStreamInObjectAddress, 0, 0, 63);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[3], &values->HUCIndirectStreamInObjectMemoryAddressAttributes);

   const uint64_t v4_address =
      __gen_address(data, &dw[4], values->HUCIndirectStreamInObjectAccessUpperBound, 0, 0, 63);
   dw[4] = v4_address;
   dw[5] = v4_address >> 32;

   const uint64_t v6_address =
      __gen_address(data, &dw[6], values->HUCIndirectStreamOutObjectAddress, 0, 0, 63);
   dw[6] = v6_address;
   dw[7] = v6_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[8], &values->HUCIndirectStreamOutObjectMemoryAddressAttributes);

   const uint64_t v9_address =
      __gen_address(data, &dw[9], values->HUCIndirectStreamOutObjectAccessUpperBound, 0, 0, 63);
   dw[9] = v9_address;
   dw[10] = v9_address >> 32;
}

#define GFX9_HUC_PIPE_MODE_SELECT_length       3
#define GFX9_HUC_PIPE_MODE_SELECT_length_bias      2
#define GFX9_HUC_PIPE_MODE_SELECT_header        \
   .SubOpcode                           =      0,  \
   .MediaCommandOpcode                  =     11,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HUC_PIPE_MODE_SELECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   bool                                 IndirectStreamOutEnable;
   uint32_t                             MediaSoftResetCounter;
};

static inline __attribute__((always_inline)) void
GFX9_HUC_PIPE_MODE_SELECT_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_HUC_PIPE_MODE_SELECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->IndirectStreamOutEnable, 4, 4);

   dw[2] =
      util_bitpack_uint(values->MediaSoftResetCounter, 0, 31);
}

#define GFX9_HUC_START_length                  2
#define GFX9_HUC_START_length_bias             2
#define GFX9_HUC_START_header                   \
   .SubOpcode                           =     33,  \
   .MediaCommandOpcode                  =     11,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HUC_START {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   bool                                 LastStreamObject;
};

static inline __attribute__((always_inline)) void
GFX9_HUC_START_pack(__attribute__((unused)) __gen_user_data *data,
                    __attribute__((unused)) void * restrict dst,
                    __attribute__((unused)) const struct GFX9_HUC_START * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->LastStreamObject, 0, 0);
}

#define GFX9_HUC_STREAM_OBJECT_length          5
#define GFX9_HUC_STREAM_OBJECT_length_bias      2
#define GFX9_HUC_STREAM_OBJECT_header           \
   .SubOpcode                           =     32,  \
   .MediaCommandOpcode                  =     11,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HUC_STREAM_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             IndirectStreamInDataLength;
   __gen_address_type                   IndirectStreamInAddress;
   bool                                 HUCProcessing;
   __gen_address_type                   IndirectStreamOutAddress;
   uint32_t                             StartCodeByte0;
   uint32_t                             StartCodeByte1;
   uint32_t                             StartCodeByte2;
   bool                                 StartCodeSearchEngine;
   bool                                 EmulationPreventionByteRemoval;
   bool                                 StreamOut;
   uint32_t                             DRMLengthMode;
#define StartCodeMode                            0
#define LengthMode                               1
   bool                                 HUCBitstreamEnable;
};

static inline __attribute__((always_inline)) void
GFX9_HUC_STREAM_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_HUC_STREAM_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->IndirectStreamInDataLength, 0, 31);

   const uint32_t v2 =
      util_bitpack_uint(values->HUCProcessing, 31, 31);
   dw[2] = __gen_address(data, &dw[2], values->IndirectStreamInAddress, v2, 0, 28);

   dw[3] = __gen_address(data, &dw[3], values->IndirectStreamOutAddress, 0, 0, 28);

   dw[4] =
      util_bitpack_uint(values->StartCodeByte0, 0, 7) |
      util_bitpack_uint(values->StartCodeByte1, 8, 15) |
      util_bitpack_uint(values->StartCodeByte2, 16, 23) |
      util_bitpack_uint(values->StartCodeSearchEngine, 24, 24) |
      util_bitpack_uint(values->EmulationPreventionByteRemoval, 25, 25) |
      util_bitpack_uint(values->StreamOut, 26, 26) |
      util_bitpack_uint(values->DRMLengthMode, 27, 28) |
      util_bitpack_uint(values->HUCBitstreamEnable, 29, 29);
}

#define GFX9_HUC_VIRTUAL_ADDR_STATE_length     49
#define GFX9_HUC_VIRTUAL_ADDR_STATE_length_bias      2
#define GFX9_HUC_VIRTUAL_ADDR_STATE_header      \
   .SubOpcode                           =      4,  \
   .MediaCommandOpcode                  =     11,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_HUC_VIRTUAL_ADDR_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   struct GFX9_HUC_VIRTUAL_ADDR_REGION  HUCVirtualAddressRegion[16];
};

static inline __attribute__((always_inline)) void
GFX9_HUC_VIRTUAL_ADDR_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                 __attribute__((unused)) void * restrict dst,
                                 __attribute__((unused)) const struct GFX9_HUC_VIRTUAL_ADDR_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcode, 16, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[1], &values->HUCVirtualAddressRegion[0]);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[4], &values->HUCVirtualAddressRegion[1]);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[7], &values->HUCVirtualAddressRegion[2]);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[10], &values->HUCVirtualAddressRegion[3]);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[13], &values->HUCVirtualAddressRegion[4]);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[16], &values->HUCVirtualAddressRegion[5]);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[19], &values->HUCVirtualAddressRegion[6]);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[22], &values->HUCVirtualAddressRegion[7]);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[25], &values->HUCVirtualAddressRegion[8]);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[28], &values->HUCVirtualAddressRegion[9]);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[31], &values->HUCVirtualAddressRegion[10]);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[34], &values->HUCVirtualAddressRegion[11]);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[37], &values->HUCVirtualAddressRegion[12]);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[40], &values->HUCVirtualAddressRegion[13]);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[43], &values->HUCVirtualAddressRegion[14]);

   GFX9_HUC_VIRTUAL_ADDR_REGION_pack(data, &dw[46], &values->HUCVirtualAddressRegion[15]);
}

#define GFX9_MEDIA_CURBE_LOAD_length           4
#define GFX9_MEDIA_CURBE_LOAD_length_bias      2
#define GFX9_MEDIA_CURBE_LOAD_header            \
   .DWordLength                         =      2,  \
   .SubOpcode                           =      1,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MEDIA_CURBE_LOAD {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             CURBETotalDataLength;
   uint32_t                             CURBEDataStartAddress;
};

static inline __attribute__((always_inline)) void
GFX9_MEDIA_CURBE_LOAD_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_MEDIA_CURBE_LOAD * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 15) |
      util_bitpack_uint(values->SubOpcode, 16, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] = 0;

   dw[2] =
      util_bitpack_uint(values->CURBETotalDataLength, 0, 16);

   dw[3] =
      util_bitpack_uint(values->CURBEDataStartAddress, 0, 31);
}

#define GFX9_MEDIA_INTERFACE_DESCRIPTOR_LOAD_length      4
#define GFX9_MEDIA_INTERFACE_DESCRIPTOR_LOAD_length_bias      2
#define GFX9_MEDIA_INTERFACE_DESCRIPTOR_LOAD_header\
   .DWordLength                         =      2,  \
   .SubOpcode                           =      2,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MEDIA_INTERFACE_DESCRIPTOR_LOAD {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             InterfaceDescriptorTotalLength;
   uint64_t                             InterfaceDescriptorDataStartAddress;
};

static inline __attribute__((always_inline)) void
GFX9_MEDIA_INTERFACE_DESCRIPTOR_LOAD_pack(__attribute__((unused)) __gen_user_data *data,
                                          __attribute__((unused)) void * restrict dst,
                                          __attribute__((unused)) const struct GFX9_MEDIA_INTERFACE_DESCRIPTOR_LOAD * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 15) |
      util_bitpack_uint(values->SubOpcode, 16, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] = 0;

   dw[2] =
      util_bitpack_uint(values->InterfaceDescriptorTotalLength, 0, 16);

   dw[3] =
      __gen_offset(values->InterfaceDescriptorDataStartAddress, 0, 31);
}

#define GFX9_MEDIA_OBJECT_length_bias          2
#define GFX9_MEDIA_OBJECT_header                \
   .DWordLength                         =      4,  \
   .MediaCommandSubOpcode               =      0,  \
   .MediaCommandOpcode                  =      1,  \
   .MediaCommandPipeline                =      2,  \
   .CommandType                         =      3

struct GFX9_MEDIA_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             MediaCommandSubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             MediaCommandPipeline;
   uint32_t                             CommandType;
   uint32_t                             InterfaceDescriptorOffset;
   uint32_t                             IndirectDataLength;
   uint32_t                             SubSliceDestinationSelect;
#define Subslice3                                3
#define SubSlice2                                2
#define SubSlice1                                1
#define SubSlice0                                0
   uint32_t                             SliceDestinationSelect;
#define Slice0                                   0
#define Slice1                                   1
#define Slice2                                   2
   uint32_t                             UseScoreboard;
#define Notusingscoreboard                       0
#define Usingscoreboard                          1
   uint32_t                             ForceDestination;
   uint32_t                             ThreadSynchronization;
#define Nothreadsynchronization                  0
#define Threaddispatchissynchronizedbythespawnrootthreadmessage 1
   uint32_t                             SliceDestinationSelectMSBs;
   bool                                 ChildrenPresent;
   __gen_address_type                   IndirectDataStartAddress;
   uint32_t                             ScoreboardX;
   uint32_t                             ScoredboardY;
   uint32_t                             ScoreboardMask;
   uint32_t                             ScoreboardColor;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_MEDIA_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                       __attribute__((unused)) void * restrict dst,
                       __attribute__((unused)) const struct GFX9_MEDIA_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 15) |
      util_bitpack_uint(values->MediaCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->MediaCommandPipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->InterfaceDescriptorOffset, 0, 5);

   dw[2] =
      util_bitpack_uint(values->IndirectDataLength, 0, 16) |
      util_bitpack_uint(values->SubSliceDestinationSelect, 17, 18) |
      util_bitpack_uint(values->SliceDestinationSelect, 19, 20) |
      util_bitpack_uint(values->UseScoreboard, 21, 21) |
      util_bitpack_uint(values->ForceDestination, 22, 22) |
      util_bitpack_uint(values->ThreadSynchronization, 24, 24) |
      util_bitpack_uint(values->SliceDestinationSelectMSBs, 25, 26) |
      util_bitpack_uint(values->ChildrenPresent, 31, 31);

   dw[3] = __gen_address(data, &dw[3], values->IndirectDataStartAddress, 0, 0, 31);

   dw[4] =
      util_bitpack_uint(values->ScoreboardX, 0, 8) |
      util_bitpack_uint(values->ScoredboardY, 16, 24);

   dw[5] =
      util_bitpack_uint(values->ScoreboardMask, 0, 7) |
      util_bitpack_uint(values->ScoreboardColor, 16, 19);
}

#define GFX9_MEDIA_OBJECT_GRPID_length_bias      2
#define GFX9_MEDIA_OBJECT_GRPID_header          \
   .DWordLength                         =      5,  \
   .MediaCommandSubOpcode               =      6,  \
   .MediaCommandOpcode                  =      1,  \
   .MediaCommandPipeline                =      2,  \
   .CommandType                         =      3

struct GFX9_MEDIA_OBJECT_GRPID {
   uint32_t                             DWordLength;
   uint32_t                             MediaCommandSubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             MediaCommandPipeline;
   uint32_t                             CommandType;
   uint32_t                             InterfaceDescriptorOffset;
   uint32_t                             IndirectDataLength;
   uint32_t                             SubSliceDestinationSelect;
#define Subslice3                                3
#define SubSlice2                                2
#define SubSlice1                                1
#define SubSlice0                                0
   uint32_t                             SliceDestinationSelect;
#define Slice0                                   0
#define Slice1                                   1
#define Slice2                                   2
   uint32_t                             UseScoreboard;
#define Notusingscoreboard                       0
#define Usingscoreboard                          1
   uint32_t                             ForceDestination;
   uint32_t                             EndofThreadGroup;
   uint32_t                             SliceDestinationSelectMSB;
   __gen_address_type                   IndirectDataStartAddress;
   uint32_t                             ScoreboardX;
   uint32_t                             ScoreboardY;
   uint32_t                             ScoreboardMask;
   uint32_t                             ScoreboardColor;
   uint32_t                             GroupID;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_MEDIA_OBJECT_GRPID_pack(__attribute__((unused)) __gen_user_data *data,
                             __attribute__((unused)) void * restrict dst,
                             __attribute__((unused)) const struct GFX9_MEDIA_OBJECT_GRPID * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 15) |
      util_bitpack_uint(values->MediaCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->MediaCommandPipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->InterfaceDescriptorOffset, 0, 5);

   dw[2] =
      util_bitpack_uint(values->IndirectDataLength, 0, 16) |
      util_bitpack_uint(values->SubSliceDestinationSelect, 17, 18) |
      util_bitpack_uint(values->SliceDestinationSelect, 19, 20) |
      util_bitpack_uint(values->UseScoreboard, 21, 21) |
      util_bitpack_uint(values->ForceDestination, 22, 22) |
      util_bitpack_uint(values->EndofThreadGroup, 23, 23) |
      util_bitpack_uint(values->SliceDestinationSelectMSB, 24, 24);

   dw[3] = __gen_address(data, &dw[3], values->IndirectDataStartAddress, 0, 0, 31);

   dw[4] =
      util_bitpack_uint(values->ScoreboardX, 0, 8) |
      util_bitpack_uint(values->ScoreboardY, 16, 24);

   dw[5] =
      util_bitpack_uint(values->ScoreboardMask, 0, 7) |
      util_bitpack_uint(values->ScoreboardColor, 16, 19);

   dw[6] =
      util_bitpack_uint(values->GroupID, 0, 31);
}

#define GFX9_MEDIA_OBJECT_PRT_length          16
#define GFX9_MEDIA_OBJECT_PRT_length_bias      2
#define GFX9_MEDIA_OBJECT_PRT_header            \
   .DWordLength                         =     14,  \
   .SubOpcode                           =      2,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MEDIA_OBJECT_PRT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             InterfaceDescriptorOffset;
   uint32_t                             PRT_FenceType;
#define Rootthreadqueue                          0
#define VFEstateflush                            1
   bool                                 PRT_FenceNeeded;
   bool                                 ChildrenPresent;
   uint32_t                             InlineData[12];
};

static inline __attribute__((always_inline)) void
GFX9_MEDIA_OBJECT_PRT_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_MEDIA_OBJECT_PRT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 15) |
      util_bitpack_uint(values->SubOpcode, 16, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->InterfaceDescriptorOffset, 0, 5);

   dw[2] =
      util_bitpack_uint(values->PRT_FenceType, 22, 22) |
      util_bitpack_uint(values->PRT_FenceNeeded, 23, 23) |
      util_bitpack_uint(values->ChildrenPresent, 31, 31);

   dw[3] = 0;

   dw[4] =
      util_bitpack_uint(values->InlineData[0], 0, 31);

   dw[5] =
      util_bitpack_uint(values->InlineData[1], 0, 31);

   dw[6] =
      util_bitpack_uint(values->InlineData[2], 0, 31);

   dw[7] =
      util_bitpack_uint(values->InlineData[3], 0, 31);

   dw[8] =
      util_bitpack_uint(values->InlineData[4], 0, 31);

   dw[9] =
      util_bitpack_uint(values->InlineData[5], 0, 31);

   dw[10] =
      util_bitpack_uint(values->InlineData[6], 0, 31);

   dw[11] =
      util_bitpack_uint(values->InlineData[7], 0, 31);

   dw[12] =
      util_bitpack_uint(values->InlineData[8], 0, 31);

   dw[13] =
      util_bitpack_uint(values->InlineData[9], 0, 31);

   dw[14] =
      util_bitpack_uint(values->InlineData[10], 0, 31);

   dw[15] =
      util_bitpack_uint(values->InlineData[11], 0, 31);
}

#define GFX9_MEDIA_OBJECT_WALKER_length_bias      2
#define GFX9_MEDIA_OBJECT_WALKER_header         \
   .DWordLength                         =     15,  \
   .SubOpcode                           =      3,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MEDIA_OBJECT_WALKER {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             InterfaceDescriptorOffset;
   uint32_t                             IndirectDataLength;
   uint32_t                             UseScoreboard;
#define Notusingscoreboard                       0
#define Usingscoreboard                          1
   uint32_t                             MaskedDispatch;
   uint32_t                             ThreadSynchronization;
#define Nothreadsynchronization                  0
#define Threaddispatchissynchronizedbythespawnrootthreadmessage 1
   uint32_t                             IndirectDataStartAddress;
   uint32_t                             ScoreboardMask;
   uint32_t                             GroupIDLoopSelect;
#define No_Groups                                0
#define Color_Groups                             1
#define InnerLocal_Groups                        2
#define MidLocal_Groups                          3
#define OuterLocal_Groups                        4
#define InnerGlobal_Groups                       5
   int32_t                              MidLoopUnitX;
   int32_t                              LocalMidLoopUnitY;
   uint32_t                             MiddleLoopExtraSteps;
   uint32_t                             ColorCountMinusOne;
   uint32_t                             LocalLoopExecCount;
   uint32_t                             GlobalLoopExecCount;
   uint32_t                             BlockResolutionX;
   uint32_t                             BlockResolutionY;
   uint32_t                             LocalStartX;
   uint32_t                             LocalStartY;
   int32_t                              LocalOuterLoopStrideX;
   int32_t                              LocalOuterLoopStrideY;
   int32_t                              LocalInnerLoopUnitX;
   int32_t                              LocalInnerLoopUnitY;
   uint32_t                             GlobalResolutionX;
   uint32_t                             GlobalResolutionY;
   int32_t                              GlobalStartX;
   int32_t                              GlobalStartY;
   int32_t                              GlobalOuterLoopStrideX;
   int32_t                              GlobalOuterLoopStrideY;
   int32_t                              GlobalInnerLoopUnitX;
   int32_t                              GlobalInnerLoopUnitY;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_MEDIA_OBJECT_WALKER_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_MEDIA_OBJECT_WALKER * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 15) |
      util_bitpack_uint(values->SubOpcode, 16, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->InterfaceDescriptorOffset, 0, 5);

   dw[2] =
      util_bitpack_uint(values->IndirectDataLength, 0, 16) |
      util_bitpack_uint(values->UseScoreboard, 21, 21) |
      util_bitpack_uint(values->MaskedDispatch, 22, 23) |
      util_bitpack_uint(values->ThreadSynchronization, 24, 24);

   dw[3] =
      util_bitpack_uint(values->IndirectDataStartAddress, 0, 31);

   dw[4] = 0;

   dw[5] =
      util_bitpack_uint(values->ScoreboardMask, 0, 7) |
      util_bitpack_uint(values->GroupIDLoopSelect, 8, 31);

   dw[6] =
      util_bitpack_sint(values->MidLoopUnitX, 8, 9) |
      util_bitpack_sint(values->LocalMidLoopUnitY, 12, 13) |
      util_bitpack_uint(values->MiddleLoopExtraSteps, 16, 20) |
      util_bitpack_uint(values->ColorCountMinusOne, 24, 27);

   dw[7] =
      util_bitpack_uint(values->LocalLoopExecCount, 0, 11) |
      util_bitpack_uint(values->GlobalLoopExecCount, 16, 27);

   dw[8] =
      util_bitpack_uint(values->BlockResolutionX, 0, 10) |
      util_bitpack_uint(values->BlockResolutionY, 16, 26);

   dw[9] =
      util_bitpack_uint(values->LocalStartX, 0, 10) |
      util_bitpack_uint(values->LocalStartY, 16, 26);

   dw[10] = 0;

   dw[11] =
      util_bitpack_sint(values->LocalOuterLoopStrideX, 0, 11) |
      util_bitpack_sint(values->LocalOuterLoopStrideY, 16, 27);

   dw[12] =
      util_bitpack_sint(values->LocalInnerLoopUnitX, 0, 11) |
      util_bitpack_sint(values->LocalInnerLoopUnitY, 16, 27);

   dw[13] =
      util_bitpack_uint(values->GlobalResolutionX, 0, 10) |
      util_bitpack_uint(values->GlobalResolutionY, 16, 26);

   dw[14] =
      util_bitpack_sint(values->GlobalStartX, 0, 11) |
      util_bitpack_sint(values->GlobalStartY, 16, 27);

   dw[15] =
      util_bitpack_sint(values->GlobalOuterLoopStrideX, 0, 11) |
      util_bitpack_sint(values->GlobalOuterLoopStrideY, 16, 27);

   dw[16] =
      util_bitpack_sint(values->GlobalInnerLoopUnitX, 0, 11) |
      util_bitpack_sint(values->GlobalInnerLoopUnitY, 16, 27);
}

#define GFX9_MEDIA_STATE_FLUSH_length          2
#define GFX9_MEDIA_STATE_FLUSH_length_bias      2
#define GFX9_MEDIA_STATE_FLUSH_header           \
   .DWordLength                         =      0,  \
   .SubOpcode                           =      4,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MEDIA_STATE_FLUSH {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             InterfaceDescriptorOffset;
   uint32_t                             WatermarkRequired;
   bool                                 FlushtoGO;
};

static inline __attribute__((always_inline)) void
GFX9_MEDIA_STATE_FLUSH_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_MEDIA_STATE_FLUSH * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 15) |
      util_bitpack_uint(values->SubOpcode, 16, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->InterfaceDescriptorOffset, 0, 5) |
      util_bitpack_uint(values->WatermarkRequired, 6, 6) |
      util_bitpack_uint(values->FlushtoGO, 7, 7);
}

#define GFX9_MEDIA_VFE_STATE_length            9
#define GFX9_MEDIA_VFE_STATE_length_bias       2
#define GFX9_MEDIA_VFE_STATE_header             \
   .DWordLength                         =      7,  \
   .SubOpcode                           =      0,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MEDIA_VFE_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcode;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             PerThreadScratchSpace;
   uint32_t                             StackSize;
   __gen_address_type                   ScratchSpaceBasePointer;
   uint32_t                             ResetGatewayTimer;
#define Maintainingtheexistingtimestampstate     0
#define Resettingrelativetimerandlatchingtheglobaltimestamp 1
   uint32_t                             NumberofURBEntries;
   uint32_t                             MaximumNumberofThreads;
   uint32_t                             SliceDisable;
#define AllSubslicesEnabled                      0
#define OnlySlice0Enabled                        1
#define OnlySlice0Subslice0Enabled               3
   uint32_t                             CURBEAllocationSize;
   uint32_t                             URBEntryAllocationSize;
   uint32_t                             ScoreboardMask;
   uint32_t                             ScoreboardType;
#define StallingScoreboard                       0
#define NonStallingScoreboard                    1
   bool                                 ScoreboardEnable;
   int32_t                              Scoreboard0DeltaX;
   int32_t                              Scoreboard0DeltaY;
   int32_t                              Scoreboard1DeltaX;
   int32_t                              Scoreboard1DeltaY;
   int32_t                              Scoreboard2DeltaX;
   int32_t                              Scoreboard2DeltaY;
   int32_t                              Scoreboard3DeltaX;
   int32_t                              Scoreboard3DeltaY;
   int32_t                              Scoreboard4DeltaX;
   int32_t                              Scoreboard4DeltaY;
   int32_t                              Scoreboard5DeltaX;
   int32_t                              Scoreboard5DeltaY;
   int32_t                              Scoreboard6DeltaX;
   int32_t                              Scoreboard6DeltaY;
   int32_t                              Scoreboard7DeltaX;
   int32_t                              Scoreboard7DeltaY;
};

static inline __attribute__((always_inline)) void
GFX9_MEDIA_VFE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                          __attribute__((unused)) void * restrict dst,
                          __attribute__((unused)) const struct GFX9_MEDIA_VFE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 15) |
      util_bitpack_uint(values->SubOpcode, 16, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1 =
      util_bitpack_uint(values->PerThreadScratchSpace, 0, 3) |
      util_bitpack_uint(values->StackSize, 4, 7);
   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->ScratchSpaceBasePointer, v1, 10, 47);
   dw[1] = v1_address;
   dw[2] = (v1_address >> 32) | (v1 >> 32);

   dw[3] =
      util_bitpack_uint(values->ResetGatewayTimer, 7, 7) |
      util_bitpack_uint(values->NumberofURBEntries, 8, 15) |
      util_bitpack_uint(values->MaximumNumberofThreads, 16, 31);

   dw[4] =
      util_bitpack_uint(values->SliceDisable, 0, 1);

   dw[5] =
      util_bitpack_uint(values->CURBEAllocationSize, 0, 15) |
      util_bitpack_uint(values->URBEntryAllocationSize, 16, 31);

   dw[6] =
      util_bitpack_uint(values->ScoreboardMask, 0, 7) |
      util_bitpack_uint(values->ScoreboardType, 30, 30) |
      util_bitpack_uint(values->ScoreboardEnable, 31, 31);

   dw[7] =
      util_bitpack_sint(values->Scoreboard0DeltaX, 0, 3) |
      util_bitpack_sint(values->Scoreboard0DeltaY, 4, 7) |
      util_bitpack_sint(values->Scoreboard1DeltaX, 8, 11) |
      util_bitpack_sint(values->Scoreboard1DeltaY, 12, 15) |
      util_bitpack_sint(values->Scoreboard2DeltaX, 16, 19) |
      util_bitpack_sint(values->Scoreboard2DeltaY, 20, 23) |
      util_bitpack_sint(values->Scoreboard3DeltaX, 24, 27) |
      util_bitpack_sint(values->Scoreboard3DeltaY, 28, 31);

   dw[8] =
      util_bitpack_sint(values->Scoreboard4DeltaX, 0, 3) |
      util_bitpack_sint(values->Scoreboard4DeltaY, 4, 7) |
      util_bitpack_sint(values->Scoreboard5DeltaX, 8, 11) |
      util_bitpack_sint(values->Scoreboard5DeltaY, 12, 15) |
      util_bitpack_sint(values->Scoreboard6DeltaX, 16, 19) |
      util_bitpack_sint(values->Scoreboard6DeltaY, 20, 23) |
      util_bitpack_sint(values->Scoreboard7DeltaX, 24, 27) |
      util_bitpack_sint(values->Scoreboard7DeltaY, 28, 31);
}

#define GFX9_MFC_AVC_PAK_OBJECT_length        12
#define GFX9_MFC_AVC_PAK_OBJECT_length_bias      2
#define GFX9_MFC_AVC_PAK_OBJECT_header          \
   .DWordLength                         =     10,  \
   .SubOpcodeB                          =      9,  \
   .SubOpcodeA                          =      2,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFC_AVC_PAK_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             IndirectPAKMVDataLength;
   uint64_t                             IndirectPAKMVDataStartAddressOffset;
   uint32_t                             InlineData[8];
   uint32_t                             VDEncModeInlineData[12];
};

static inline __attribute__((always_inline)) void
GFX9_MFC_AVC_PAK_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                             __attribute__((unused)) void * restrict dst,
                             __attribute__((unused)) const struct GFX9_MFC_AVC_PAK_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->IndirectPAKMVDataLength, 0, 9);

   dw[2] =
      __gen_offset(values->IndirectPAKMVDataStartAddressOffset, 0, 28);

   dw[3] =
      util_bitpack_uint(values->InlineData[0], 0, 31);

   dw[4] =
      util_bitpack_uint(values->InlineData[1], 0, 31);

   dw[5] =
      util_bitpack_uint(values->InlineData[2], 0, 31);

   dw[6] =
      util_bitpack_uint(values->InlineData[3], 0, 31);

   dw[7] =
      util_bitpack_uint(values->InlineData[4], 0, 31);

   dw[8] =
      util_bitpack_uint(values->InlineData[5], 0, 31);

   dw[9] =
      util_bitpack_uint(values->InlineData[6], 0, 31);

   dw[10] =
      util_bitpack_uint(values->InlineData[7], 0, 31);

   dw[11] = 0;
}

#define GFX9_MFC_JPEG_HUFF_TABLE_STATE_length    176
#define GFX9_MFC_JPEG_HUFF_TABLE_STATE_length_bias      2
#define GFX9_MFC_JPEG_HUFF_TABLE_STATE_header   \
   .DWordLength                         =    174,  \
   .SubOpcodeB                          =      3,  \
   .SubOpcodeA                          =      2,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFC_JPEG_HUFF_TABLE_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             HuffTableID;
   uint64_t                             DC_TABLE;
   uint64_t                             AC_TABLE;
};

static inline __attribute__((always_inline)) void
GFX9_MFC_JPEG_HUFF_TABLE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                    __attribute__((unused)) void * restrict dst,
                                    __attribute__((unused)) const struct GFX9_MFC_JPEG_HUFF_TABLE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->HuffTableID, 0, 0);

   const uint64_t v2 =
      util_bitpack_uint(values->DC_TABLE, 0, 383);
   dw[2] = v2;
   dw[3] = v2 >> 32;

   const uint64_t v14 =
      util_bitpack_uint(values->AC_TABLE, 0, 5183);
   dw[14] = v14;
   dw[15] = v14 >> 32;
}

#define GFX9_MFC_JPEG_SCAN_OBJECT_length       3
#define GFX9_MFC_JPEG_SCAN_OBJECT_length_bias      2
#define GFX9_MFC_JPEG_SCAN_OBJECT_header        \
   .DWordLength                         =      1,  \
   .SubOpcodeB                          =      9,  \
   .SubOpcodeA                          =      2,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFC_JPEG_SCAN_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             MCUCount;
   uint32_t                             RestartInterval;
   bool                                 LastScan;
   bool                                 HeadPresent;
   uint32_t                             HuffmanDCTable;
   uint32_t                             HuffmanACTable;
};

static inline __attribute__((always_inline)) void
GFX9_MFC_JPEG_SCAN_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_MFC_JPEG_SCAN_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->MCUCount, 0, 25);

   dw[2] =
      util_bitpack_uint(values->RestartInterval, 0, 15) |
      util_bitpack_uint(values->LastScan, 16, 16) |
      util_bitpack_uint(values->HeadPresent, 17, 17) |
      util_bitpack_uint(values->HuffmanDCTable, 18, 20) |
      util_bitpack_uint(values->HuffmanACTable, 22, 24);
}

#define GFX9_MFC_MPEG2_PAK_OBJECT_length       9
#define GFX9_MFC_MPEG2_PAK_OBJECT_length_bias      2
#define GFX9_MFC_MPEG2_PAK_OBJECT_header        \
   .DWordLength                         =      7,  \
   .SubOpcodeB                          =      9,  \
   .SubOpcodeA                          =      2,  \
   .MediaCommandOpcode                  =      3,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFC_MPEG2_PAK_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             InlineData[8];
};

static inline __attribute__((always_inline)) void
GFX9_MFC_MPEG2_PAK_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_MFC_MPEG2_PAK_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->InlineData[0], 0, 31);

   dw[2] =
      util_bitpack_uint(values->InlineData[1], 0, 31);

   dw[3] =
      util_bitpack_uint(values->InlineData[2], 0, 31);

   dw[4] =
      util_bitpack_uint(values->InlineData[3], 0, 31);

   dw[5] =
      util_bitpack_uint(values->InlineData[4], 0, 31);

   dw[6] =
      util_bitpack_uint(values->InlineData[5], 0, 31);

   dw[7] =
      util_bitpack_uint(values->InlineData[6], 0, 31);

   dw[8] =
      util_bitpack_uint(values->InlineData[7], 0, 31);
}

#define GFX9_MFC_MPEG2_SLICEGROUP_STATE_length      8
#define GFX9_MFC_MPEG2_SLICEGROUP_STATE_length_bias      2
#define GFX9_MFC_MPEG2_SLICEGROUP_STATE_header  \
   .DWordLength                         =      6,  \
   .SubOpcodeB                          =      3,  \
   .SubOpcodeA                          =      2,  \
   .MediaCommandOpcode                  =      3,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFC_MPEG2_SLICEGROUP_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             StreamID;
   uint32_t                             SliceID;
   bool                                 IntraSliceFlag;
   bool                                 IntraSlice;
   bool                                 FirstSliceHeaderDisable;
   bool                                 TailInsertionPresent;
   bool                                 SliceDataInsertionPresent;
   bool                                 HeaderInsertionPresent;
   bool                                 CompressedBitStreamOutputDisable;
   bool                                 LastSlice;
   bool                                 MBTypeSkipConversionDisable;
   uint32_t                             RateControlPanicType;
#define QPPanic                                  0
#define CBPPanic                                 1
   bool                                 RateControlPanicEnable;
   uint32_t                             RateControlStableTolerance;
   uint32_t                             RateControlTriggleMode;
#define AlwaysRateControl                        0
#define GentleRateControl                        1
#define LooseRateControl                         2
   bool                                 ResetRateControlCounter;
   bool                                 RateControlCounterEnable;
   uint32_t                             FirstMBXCount;
   uint32_t                             FirstMBYCount;
   uint32_t                             NextSliceGroupMBXCount;
   uint32_t                             NextSliceGroupMBYCount;
   uint32_t                             SliceGroupQP;
   bool                                 SliceGroupSkip;
   uint64_t                             IndirectPAKBSEDataStartAddress;
   uint32_t                             GrowInit;
   uint32_t                             GrowResistance;
   uint32_t                             ShrinkInit;
   uint32_t                             ShrinkResistance;
   uint32_t                             QPMaxPositiveModifierMagnitude;
   uint32_t                             QPMaxNegativeModifierMagnitude;
   uint32_t                             Correct1;
   uint32_t                             Correct2;
   uint32_t                             Correct3;
   uint32_t                             Correct4;
   uint32_t                             Correct5;
   uint32_t                             Correct6;
   uint32_t                             CV0;
   uint32_t                             CV1;
   uint32_t                             CV2;
   uint32_t                             CV3;
   uint32_t                             CV4;
   uint32_t                             CV5;
   uint32_t                             CV6;
   uint32_t                             CV7;
};

static inline __attribute__((always_inline)) void
GFX9_MFC_MPEG2_SLICEGROUP_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                     __attribute__((unused)) void * restrict dst,
                                     __attribute__((unused)) const struct GFX9_MFC_MPEG2_SLICEGROUP_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->StreamID, 0, 1) |
      util_bitpack_uint(values->SliceID, 4, 7) |
      util_bitpack_uint(values->IntraSliceFlag, 12, 12) |
      util_bitpack_uint(values->IntraSlice, 13, 13) |
      util_bitpack_uint(values->FirstSliceHeaderDisable, 14, 14) |
      util_bitpack_uint(values->TailInsertionPresent, 15, 15) |
      util_bitpack_uint(values->SliceDataInsertionPresent, 16, 16) |
      util_bitpack_uint(values->HeaderInsertionPresent, 17, 17) |
      util_bitpack_uint(values->CompressedBitStreamOutputDisable, 18, 18) |
      util_bitpack_uint(values->LastSlice, 19, 19) |
      util_bitpack_uint(values->MBTypeSkipConversionDisable, 20, 20) |
      util_bitpack_uint(values->RateControlPanicType, 22, 22) |
      util_bitpack_uint(values->RateControlPanicEnable, 23, 23) |
      util_bitpack_uint(values->RateControlStableTolerance, 24, 27) |
      util_bitpack_uint(values->RateControlTriggleMode, 28, 29) |
      util_bitpack_uint(values->ResetRateControlCounter, 30, 30) |
      util_bitpack_uint(values->RateControlCounterEnable, 31, 31);

   dw[2] =
      util_bitpack_uint(values->FirstMBXCount, 0, 7) |
      util_bitpack_uint(values->FirstMBYCount, 8, 15) |
      util_bitpack_uint(values->NextSliceGroupMBXCount, 16, 23) |
      util_bitpack_uint(values->NextSliceGroupMBYCount, 24, 31);

   dw[3] =
      util_bitpack_uint(values->SliceGroupQP, 0, 5) |
      util_bitpack_uint(values->SliceGroupSkip, 8, 8);

   dw[4] =
      __gen_offset(values->IndirectPAKBSEDataStartAddress, 0, 28);

   dw[5] =
      util_bitpack_uint(values->GrowInit, 0, 3) |
      util_bitpack_uint(values->GrowResistance, 4, 7) |
      util_bitpack_uint(values->ShrinkInit, 8, 11) |
      util_bitpack_uint(values->ShrinkResistance, 12, 15) |
      util_bitpack_uint(values->QPMaxPositiveModifierMagnitude, 16, 23) |
      util_bitpack_uint(values->QPMaxNegativeModifierMagnitude, 24, 31);

   dw[6] =
      util_bitpack_uint(values->Correct1, 0, 3) |
      util_bitpack_uint(values->Correct2, 4, 7) |
      util_bitpack_uint(values->Correct3, 8, 11) |
      util_bitpack_uint(values->Correct4, 12, 15) |
      util_bitpack_uint(values->Correct5, 16, 19) |
      util_bitpack_uint(values->Correct6, 20, 23);

   dw[7] =
      util_bitpack_uint(values->CV0, 0, 3) |
      util_bitpack_uint(values->CV1, 4, 7) |
      util_bitpack_uint(values->CV2, 8, 11) |
      util_bitpack_uint(values->CV3, 12, 15) |
      util_bitpack_uint(values->CV4, 16, 19) |
      util_bitpack_uint(values->CV5, 20, 23) |
      util_bitpack_uint(values->CV6, 24, 27) |
      util_bitpack_uint(values->CV7, 28, 31);
}

#define GFX9_MFD_AVC_BSD_OBJECT_length         6
#define GFX9_MFD_AVC_BSD_OBJECT_length_bias      2
#define GFX9_MFD_AVC_BSD_OBJECT_header          \
   .DWordLength                         =      4,  \
   .SubOpcodeB                          =      8,  \
   .SubOpcodeA                          =      1,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFD_AVC_BSD_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             IndirectBSDDataLength;
   uint64_t                             IndirectBSDDataStartAddress;
   struct GFX9_INLINE_DATA_DESCRIPTION_FOR_MFD_AVC_BSD_OBJECT InlineData;
};

static inline __attribute__((always_inline)) void
GFX9_MFD_AVC_BSD_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                             __attribute__((unused)) void * restrict dst,
                             __attribute__((unused)) const struct GFX9_MFD_AVC_BSD_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->IndirectBSDDataLength, 0, 31);

   dw[2] =
      __gen_offset(values->IndirectBSDDataStartAddress, 0, 28);

   GFX9_INLINE_DATA_DESCRIPTION_FOR_MFD_AVC_BSD_OBJECT_pack(data, &dw[3], &values->InlineData);
}

#define GFX9_MFD_AVC_DPB_STATE_length         27
#define GFX9_MFD_AVC_DPB_STATE_length_bias      2
#define GFX9_MFD_AVC_DPB_STATE_header           \
   .DWordLength                         =     25,  \
   .SubOpcodeB                          =      6,  \
   .SubOpcodeA                          =      1,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFD_AVC_DPB_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             NonExistingFrame[16];
#define INVALID                                  1
#define VALID                                    0
   uint32_t                             LongTermFrame[16];
   uint32_t                             UsedforReference[16];
#define NOT_REFERENCE                            0
#define TOP_FIELD                                1
#define BOTTOM_FIELD                             2
#define FRAME                                    3
   uint32_t                             LTSTFrameNumberList[16];
   uint32_t                             ViewID[16];
   uint32_t                             L0ViewOrder[16];
   uint32_t                             L1ViewOrder[16];
};

static inline __attribute__((always_inline)) void
GFX9_MFD_AVC_DPB_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_MFD_AVC_DPB_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->NonExistingFrame[0], 0, 0) |
      util_bitpack_uint(values->NonExistingFrame[1], 1, 1) |
      util_bitpack_uint(values->NonExistingFrame[2], 2, 2) |
      util_bitpack_uint(values->NonExistingFrame[3], 3, 3) |
      util_bitpack_uint(values->NonExistingFrame[4], 4, 4) |
      util_bitpack_uint(values->NonExistingFrame[5], 5, 5) |
      util_bitpack_uint(values->NonExistingFrame[6], 6, 6) |
      util_bitpack_uint(values->NonExistingFrame[7], 7, 7) |
      util_bitpack_uint(values->NonExistingFrame[8], 8, 8) |
      util_bitpack_uint(values->NonExistingFrame[9], 9, 9) |
      util_bitpack_uint(values->NonExistingFrame[10], 10, 10) |
      util_bitpack_uint(values->NonExistingFrame[11], 11, 11) |
      util_bitpack_uint(values->NonExistingFrame[12], 12, 12) |
      util_bitpack_uint(values->NonExistingFrame[13], 13, 13) |
      util_bitpack_uint(values->NonExistingFrame[14], 14, 14) |
      util_bitpack_uint(values->NonExistingFrame[15], 15, 15) |
      util_bitpack_uint(values->LongTermFrame[0], 16, 16) |
      util_bitpack_uint(values->LongTermFrame[1], 17, 17) |
      util_bitpack_uint(values->LongTermFrame[2], 18, 18) |
      util_bitpack_uint(values->LongTermFrame[3], 19, 19) |
      util_bitpack_uint(values->LongTermFrame[4], 20, 20) |
      util_bitpack_uint(values->LongTermFrame[5], 21, 21) |
      util_bitpack_uint(values->LongTermFrame[6], 22, 22) |
      util_bitpack_uint(values->LongTermFrame[7], 23, 23) |
      util_bitpack_uint(values->LongTermFrame[8], 24, 24) |
      util_bitpack_uint(values->LongTermFrame[9], 25, 25) |
      util_bitpack_uint(values->LongTermFrame[10], 26, 26) |
      util_bitpack_uint(values->LongTermFrame[11], 27, 27) |
      util_bitpack_uint(values->LongTermFrame[12], 28, 28) |
      util_bitpack_uint(values->LongTermFrame[13], 29, 29) |
      util_bitpack_uint(values->LongTermFrame[14], 30, 30) |
      util_bitpack_uint(values->LongTermFrame[15], 31, 31);

   dw[2] =
      util_bitpack_uint(values->UsedforReference[0], 0, 1) |
      util_bitpack_uint(values->UsedforReference[1], 2, 3) |
      util_bitpack_uint(values->UsedforReference[2], 4, 5) |
      util_bitpack_uint(values->UsedforReference[3], 6, 7) |
      util_bitpack_uint(values->UsedforReference[4], 8, 9) |
      util_bitpack_uint(values->UsedforReference[5], 10, 11) |
      util_bitpack_uint(values->UsedforReference[6], 12, 13) |
      util_bitpack_uint(values->UsedforReference[7], 14, 15) |
      util_bitpack_uint(values->UsedforReference[8], 16, 17) |
      util_bitpack_uint(values->UsedforReference[9], 18, 19) |
      util_bitpack_uint(values->UsedforReference[10], 20, 21) |
      util_bitpack_uint(values->UsedforReference[11], 22, 23) |
      util_bitpack_uint(values->UsedforReference[12], 24, 25) |
      util_bitpack_uint(values->UsedforReference[13], 26, 27) |
      util_bitpack_uint(values->UsedforReference[14], 28, 29) |
      util_bitpack_uint(values->UsedforReference[15], 30, 31);

   dw[3] =
      util_bitpack_uint(values->LTSTFrameNumberList[0], 0, 15) |
      util_bitpack_uint(values->LTSTFrameNumberList[1], 16, 31);

   dw[4] =
      util_bitpack_uint(values->LTSTFrameNumberList[2], 0, 15) |
      util_bitpack_uint(values->LTSTFrameNumberList[3], 16, 31);

   dw[5] =
      util_bitpack_uint(values->LTSTFrameNumberList[4], 0, 15) |
      util_bitpack_uint(values->LTSTFrameNumberList[5], 16, 31);

   dw[6] =
      util_bitpack_uint(values->LTSTFrameNumberList[6], 0, 15) |
      util_bitpack_uint(values->LTSTFrameNumberList[7], 16, 31);

   dw[7] =
      util_bitpack_uint(values->LTSTFrameNumberList[8], 0, 15) |
      util_bitpack_uint(values->LTSTFrameNumberList[9], 16, 31);

   dw[8] =
      util_bitpack_uint(values->LTSTFrameNumberList[10], 0, 15) |
      util_bitpack_uint(values->LTSTFrameNumberList[11], 16, 31);

   dw[9] =
      util_bitpack_uint(values->LTSTFrameNumberList[12], 0, 15) |
      util_bitpack_uint(values->LTSTFrameNumberList[13], 16, 31);

   dw[10] =
      util_bitpack_uint(values->LTSTFrameNumberList[14], 0, 15) |
      util_bitpack_uint(values->LTSTFrameNumberList[15], 16, 31);

   dw[11] =
      util_bitpack_uint(values->ViewID[0], 0, 15) |
      util_bitpack_uint(values->ViewID[1], 16, 31);

   dw[12] =
      util_bitpack_uint(values->ViewID[2], 0, 15) |
      util_bitpack_uint(values->ViewID[3], 16, 31);

   dw[13] =
      util_bitpack_uint(values->ViewID[4], 0, 15) |
      util_bitpack_uint(values->ViewID[5], 16, 31);

   dw[14] =
      util_bitpack_uint(values->ViewID[6], 0, 15) |
      util_bitpack_uint(values->ViewID[7], 16, 31);

   dw[15] =
      util_bitpack_uint(values->ViewID[8], 0, 15) |
      util_bitpack_uint(values->ViewID[9], 16, 31);

   dw[16] =
      util_bitpack_uint(values->ViewID[10], 0, 15) |
      util_bitpack_uint(values->ViewID[11], 16, 31);

   dw[17] =
      util_bitpack_uint(values->ViewID[12], 0, 15) |
      util_bitpack_uint(values->ViewID[13], 16, 31);

   dw[18] =
      util_bitpack_uint(values->ViewID[14], 0, 15) |
      util_bitpack_uint(values->ViewID[15], 16, 31);

   dw[19] =
      util_bitpack_uint(values->L0ViewOrder[0], 0, 7) |
      util_bitpack_uint(values->L0ViewOrder[1], 8, 15) |
      util_bitpack_uint(values->L0ViewOrder[2], 16, 23) |
      util_bitpack_uint(values->L0ViewOrder[3], 24, 31);

   dw[20] =
      util_bitpack_uint(values->L0ViewOrder[4], 0, 7) |
      util_bitpack_uint(values->L0ViewOrder[5], 8, 15) |
      util_bitpack_uint(values->L0ViewOrder[6], 16, 23) |
      util_bitpack_uint(values->L0ViewOrder[7], 24, 31);

   dw[21] =
      util_bitpack_uint(values->L0ViewOrder[8], 0, 7) |
      util_bitpack_uint(values->L0ViewOrder[9], 8, 15) |
      util_bitpack_uint(values->L0ViewOrder[10], 16, 23) |
      util_bitpack_uint(values->L0ViewOrder[11], 24, 31);

   dw[22] =
      util_bitpack_uint(values->L0ViewOrder[12], 0, 7) |
      util_bitpack_uint(values->L0ViewOrder[13], 8, 15) |
      util_bitpack_uint(values->L0ViewOrder[14], 16, 23) |
      util_bitpack_uint(values->L0ViewOrder[15], 24, 31);

   dw[23] =
      util_bitpack_uint(values->L1ViewOrder[0], 0, 7) |
      util_bitpack_uint(values->L1ViewOrder[1], 8, 15) |
      util_bitpack_uint(values->L1ViewOrder[2], 16, 23) |
      util_bitpack_uint(values->L1ViewOrder[3], 24, 31);

   dw[24] =
      util_bitpack_uint(values->L1ViewOrder[4], 0, 7) |
      util_bitpack_uint(values->L1ViewOrder[5], 8, 15) |
      util_bitpack_uint(values->L1ViewOrder[6], 16, 23) |
      util_bitpack_uint(values->L1ViewOrder[7], 24, 31);

   dw[25] =
      util_bitpack_uint(values->L1ViewOrder[8], 0, 7) |
      util_bitpack_uint(values->L1ViewOrder[9], 8, 15) |
      util_bitpack_uint(values->L1ViewOrder[10], 16, 23) |
      util_bitpack_uint(values->L1ViewOrder[11], 24, 31);

   dw[26] =
      util_bitpack_uint(values->L1ViewOrder[12], 0, 7) |
      util_bitpack_uint(values->L1ViewOrder[13], 8, 15) |
      util_bitpack_uint(values->L1ViewOrder[14], 16, 23) |
      util_bitpack_uint(values->L1ViewOrder[15], 24, 31);
}

#define GFX9_MFD_AVC_PICID_STATE_length       10
#define GFX9_MFD_AVC_PICID_STATE_length_bias      2
#define GFX9_MFD_AVC_PICID_STATE_header         \
   .DWordLength                         =      8,  \
   .SubOpcodeB                          =      5,  \
   .SubOpcodeA                          =      1,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFD_AVC_PICID_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             PictureIDRemappingDisable;
#define Use16bitsPictureID                       0
#define Use4bitsFrameStoreID                     1
   uint32_t                             PictureID[16];
};

static inline __attribute__((always_inline)) void
GFX9_MFD_AVC_PICID_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_MFD_AVC_PICID_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->PictureIDRemappingDisable, 0, 0);

   dw[2] =
      util_bitpack_uint(values->PictureID[0], 0, 15) |
      util_bitpack_uint(values->PictureID[1], 16, 31);

   dw[3] =
      util_bitpack_uint(values->PictureID[2], 0, 15) |
      util_bitpack_uint(values->PictureID[3], 16, 31);

   dw[4] =
      util_bitpack_uint(values->PictureID[4], 0, 15) |
      util_bitpack_uint(values->PictureID[5], 16, 31);

   dw[5] =
      util_bitpack_uint(values->PictureID[6], 0, 15) |
      util_bitpack_uint(values->PictureID[7], 16, 31);

   dw[6] =
      util_bitpack_uint(values->PictureID[8], 0, 15) |
      util_bitpack_uint(values->PictureID[9], 16, 31);

   dw[7] =
      util_bitpack_uint(values->PictureID[10], 0, 15) |
      util_bitpack_uint(values->PictureID[11], 16, 31);

   dw[8] =
      util_bitpack_uint(values->PictureID[12], 0, 15) |
      util_bitpack_uint(values->PictureID[13], 16, 31);

   dw[9] =
      util_bitpack_uint(values->PictureID[14], 0, 15) |
      util_bitpack_uint(values->PictureID[15], 16, 31);
}

#define GFX9_MFD_AVC_SLICEADDR_length          3
#define GFX9_MFD_AVC_SLICEADDR_length_bias      2
#define GFX9_MFD_AVC_SLICEADDR_header           \
   .DWordLength                         =      1,  \
   .SubOpcodeB                          =      7,  \
   .SubOpcodeA                          =      1,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFD_AVC_SLICEADDR {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             IndirectBSDDataLength;
   uint64_t                             IndirectBSDDataStartAddress;
};

static inline __attribute__((always_inline)) void
GFX9_MFD_AVC_SLICEADDR_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_MFD_AVC_SLICEADDR * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->IndirectBSDDataLength, 0, 31);

   dw[2] =
      __gen_offset(values->IndirectBSDDataStartAddress, 0, 28);
}

#define GFX9_MFD_IT_OBJECT_length_bias         2
#define GFX9_MFD_IT_OBJECT_header               \
   .DWordLength                         =      6,  \
   .SubOpcodeB                          =      9,  \
   .SubOpcodeA                          =      1,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFD_IT_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             IndirectITMVDataLength;
   uint64_t                             IndirectITMVDataStartAddressOffset;
   uint32_t                             IndirectITCOEFFDataLength;
   uint64_t                             IndirectITCOEFFDataStartAddressOffset;
   uint32_t                             IndirectITDBLKControlDataLength;
   uint64_t                             IndirectITDBLKControlDataStartAddressOffset;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_MFD_IT_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_MFD_IT_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->IndirectITMVDataLength, 0, 9);

   dw[2] =
      __gen_offset(values->IndirectITMVDataStartAddressOffset, 0, 28);

   dw[3] =
      util_bitpack_uint(values->IndirectITCOEFFDataLength, 0, 11);

   dw[4] =
      __gen_offset(values->IndirectITCOEFFDataStartAddressOffset, 0, 28);

   dw[5] =
      util_bitpack_uint(values->IndirectITDBLKControlDataLength, 0, 5);

   dw[6] =
      __gen_offset(values->IndirectITDBLKControlDataStartAddressOffset, 0, 28);
}

#define GFX9_MFD_JPEG_BSD_OBJECT_length        6
#define GFX9_MFD_JPEG_BSD_OBJECT_length_bias      2
#define GFX9_MFD_JPEG_BSD_OBJECT_header         \
   .DWordLength                         =      4,  \
   .SubOpcodeB                          =      8,  \
   .SubOpcodeA                          =      1,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFD_JPEG_BSD_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             IndirectDataLength;
   uint64_t                             IndirectDataStartAddress;
   uint32_t                             ScanVerticalPosition;
   uint32_t                             ScanHorizontalPosition;
   uint32_t                             MCUCount;
   uint32_t                             ScanComponents;
   bool                                 Interleaved;
   uint32_t                             RestartInterval;
};

static inline __attribute__((always_inline)) void
GFX9_MFD_JPEG_BSD_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_MFD_JPEG_BSD_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->IndirectDataLength, 0, 31);

   dw[2] =
      __gen_offset(values->IndirectDataStartAddress, 0, 28);

   dw[3] =
      util_bitpack_uint(values->ScanVerticalPosition, 0, 12) |
      util_bitpack_uint(values->ScanHorizontalPosition, 16, 28);

   dw[4] =
      util_bitpack_uint(values->MCUCount, 0, 25) |
      util_bitpack_uint(values->ScanComponents, 27, 29) |
      util_bitpack_uint(values->Interleaved, 30, 30);

   dw[5] =
      util_bitpack_uint(values->RestartInterval, 0, 15);
}

#define GFX9_MFD_MPEG2_BSD_OBJECT_length       5
#define GFX9_MFD_MPEG2_BSD_OBJECT_length_bias      2
#define GFX9_MFD_MPEG2_BSD_OBJECT_header        \
   .DWordLength                         =      3,  \
   .SubOpcodeB                          =      8,  \
   .SubOpcodeA                          =      1,  \
   .MediaCommandOpcode                  =      3,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFD_MPEG2_BSD_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             IndirectBSDDataLength;
   uint64_t                             IndirectBSDDataStartAddress;
   struct GFX9_MFD_MPEG2_BSD_OBJECT_INLINE_DATA_DESCRIPTION InlineData;
};

static inline __attribute__((always_inline)) void
GFX9_MFD_MPEG2_BSD_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_MFD_MPEG2_BSD_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->IndirectBSDDataLength, 0, 31);

   dw[2] =
      __gen_offset(values->IndirectBSDDataStartAddress, 0, 28);

   GFX9_MFD_MPEG2_BSD_OBJECT_INLINE_DATA_DESCRIPTION_pack(data, &dw[3], &values->InlineData);
}

#define GFX9_MFD_VC1_BSD_OBJECT_length         5
#define GFX9_MFD_VC1_BSD_OBJECT_length_bias      2
#define GFX9_MFD_VC1_BSD_OBJECT_header          \
   .DWordLength                         =      3,  \
   .SubOpcodeB                          =      8,  \
   .SubOpcodeA                          =      1,  \
   .MediaCommandOpcode                  =      2,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFD_VC1_BSD_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             IndirectBSDDataLength;
   uint64_t                             IndirectBSDDataStartAddress;
   uint32_t                             NextSliceVerticalPosition;
   uint32_t                             SliceStartVerticalPosition;
   uint32_t                             FirstMBBitOffset;
   uint32_t                             EmulationPreventionBytePresent;
   uint32_t                             FirstMBByteOffsetofSliceDataorSliceHeader;
};

static inline __attribute__((always_inline)) void
GFX9_MFD_VC1_BSD_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                             __attribute__((unused)) void * restrict dst,
                             __attribute__((unused)) const struct GFX9_MFD_VC1_BSD_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->IndirectBSDDataLength, 0, 23);

   dw[2] =
      __gen_offset(values->IndirectBSDDataStartAddress, 0, 28);

   dw[3] =
      util_bitpack_uint(values->NextSliceVerticalPosition, 0, 8) |
      util_bitpack_uint(values->SliceStartVerticalPosition, 16, 23);

   dw[4] =
      util_bitpack_uint(values->FirstMBBitOffset, 0, 2) |
      util_bitpack_uint(values->EmulationPreventionBytePresent, 4, 4) |
      util_bitpack_uint(values->FirstMBByteOffsetofSliceDataorSliceHeader, 16, 31);
}

#define GFX9_MFD_VC1_LONG_PIC_STATE_length      6
#define GFX9_MFD_VC1_LONG_PIC_STATE_length_bias      2
#define GFX9_MFD_VC1_LONG_PIC_STATE_header      \
   .DWordLength                         =      4,  \
   .SubOpcodeB                          =      1,  \
   .SubOpcodeA                          =      1,  \
   .MediaCommandOpcode                  =      2,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFD_VC1_LONG_PIC_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             PictureWidthInMBs;
   uint32_t                             PictureHeightInMBs;
   uint32_t                             VC1Profile;
#define SimpleMainProfile                        0
#define AdvancedProfile                          1
   bool                                 SecondField;
   bool                                 OverlapSmoothingEnable;
   bool                                 LoopFilterEnable;
   bool                                 RangeReductionEnable;
   uint32_t                             RangeReductionScale;
   uint32_t                             MVMode;
   bool                                 SyncMarker;
   bool                                 InterpolationRounderControl;
   bool                                 ImplicitQuantizer;
   bool                                 DMVSurfaceValid;
   uint32_t                             BitplaneBufferPitch;
   uint32_t                             BScaleFactor;
   uint32_t                             PQValue;
   uint32_t                             AlternativePQValue;
   uint32_t                             FrameCodingMode;
#define ProgressiveFramePicture                  0
#define InterlacedFramePicture                   1
#define FieldPicturewithTopFieldFirst            2
#define FieldPicturewithBottomFieldFirst         3
   uint32_t                             PictureType;
   uint32_t                             CONDOVER;
   bool                                 PQUniform;
   bool                                 HalfQP;
   uint32_t                             AlternativePQConfiguration;
   uint32_t                             AlternativePQEdgeMask;
   uint32_t                             ExtendedMVRange;
   uint32_t                             ExtendedDMVRange;
   uint32_t                             ForwardReferenceDistance;
   uint32_t                             BackwardReferenceDistance;
   uint32_t                             NumberofReferences;
#define Onefieldreferenced                       0
#define Twofieldsreferenced                      1
   uint32_t                             ReferenceFieldPicturePolarity;
#define TopevenField                             0
#define BottomoddField                           1
   uint32_t                             FastUVMotionCompensation;
#define NoRounding                               0
#define QuarterPeloffsetstoHalfFullpelpositions  1
   uint32_t                             FourMVSwitch;
#define Only1MV                                  0
#define _12or4MVs                                1
   uint32_t                             UnifiedMVMode;
#define _1MVhalfpelbilinear                      3
#define _1MV                                     1
#define _1MVhalfpel                              2
#define MixedMV                                  0
   uint32_t                             CodedBlockPatternTable;
   uint32_t                             IntraTransformDCTable;
   uint32_t                             PicturelevelTransformChromaACCodingSetIndex;
   uint32_t                             PicturelevelTransformLumaACCodingSetIndex;
   uint32_t                             MBModeTable;
   bool                                 MBTransformType;
   uint32_t                             PicturelevelTransformType;
#define _8x8Transform                            0
#define _8x4Transform                            1
#define _4x8Transform                            2
#define _4x4Transform                            3
   uint32_t                             _2MVBlockPatternTable;
   uint32_t                             _4MVBlockPatternTable;
   uint32_t                             MVTable;
   bool                                 FIELDTXRaw;
   bool                                 ACPREDRaw;
   bool                                 OVERFLAGSRaw;
   bool                                 DIRECTMBRaw;
   bool                                 SKIPMBRaw;
   bool                                 MVTYPEMBRaw;
   bool                                 FORWARDMBRaw;
   bool                                 BitplaneBufferPresent;
};

static inline __attribute__((always_inline)) void
GFX9_MFD_VC1_LONG_PIC_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                 __attribute__((unused)) void * restrict dst,
                                 __attribute__((unused)) const struct GFX9_MFD_VC1_LONG_PIC_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->PictureWidthInMBs, 0, 7) |
      util_bitpack_uint(values->PictureHeightInMBs, 16, 23);

   dw[2] =
      util_bitpack_uint(values->VC1Profile, 0, 0) |
      util_bitpack_uint(values->SecondField, 3, 3) |
      util_bitpack_uint(values->OverlapSmoothingEnable, 4, 4) |
      util_bitpack_uint(values->LoopFilterEnable, 5, 5) |
      util_bitpack_uint(values->RangeReductionEnable, 6, 6) |
      util_bitpack_uint(values->RangeReductionScale, 7, 7) |
      util_bitpack_uint(values->MVMode, 8, 11) |
      util_bitpack_uint(values->SyncMarker, 12, 12) |
      util_bitpack_uint(values->InterpolationRounderControl, 13, 13) |
      util_bitpack_uint(values->ImplicitQuantizer, 14, 14) |
      util_bitpack_uint(values->DMVSurfaceValid, 15, 15) |
      util_bitpack_uint(values->BitplaneBufferPitch, 24, 31);

   dw[3] =
      util_bitpack_uint(values->BScaleFactor, 0, 7) |
      util_bitpack_uint(values->PQValue, 8, 12) |
      util_bitpack_uint(values->AlternativePQValue, 16, 20) |
      util_bitpack_uint(values->FrameCodingMode, 24, 25) |
      util_bitpack_uint(values->PictureType, 26, 28) |
      util_bitpack_uint(values->CONDOVER, 29, 30);

   dw[4] =
      util_bitpack_uint(values->PQUniform, 0, 0) |
      util_bitpack_uint(values->HalfQP, 1, 1) |
      util_bitpack_uint(values->AlternativePQConfiguration, 2, 3) |
      util_bitpack_uint(values->AlternativePQEdgeMask, 4, 7) |
      util_bitpack_uint(values->ExtendedMVRange, 8, 9) |
      util_bitpack_uint(values->ExtendedDMVRange, 10, 11) |
      util_bitpack_uint(values->ForwardReferenceDistance, 16, 19) |
      util_bitpack_uint(values->BackwardReferenceDistance, 20, 23) |
      util_bitpack_uint(values->NumberofReferences, 24, 24) |
      util_bitpack_uint(values->ReferenceFieldPicturePolarity, 25, 25) |
      util_bitpack_uint(values->FastUVMotionCompensation, 26, 26) |
      util_bitpack_uint(values->FourMVSwitch, 27, 27) |
      util_bitpack_uint(values->UnifiedMVMode, 28, 29);

   dw[5] =
      util_bitpack_uint(values->CodedBlockPatternTable, 0, 2) |
      util_bitpack_uint(values->IntraTransformDCTable, 3, 3) |
      util_bitpack_uint(values->PicturelevelTransformChromaACCodingSetIndex, 4, 5) |
      util_bitpack_uint(values->PicturelevelTransformLumaACCodingSetIndex, 6, 7) |
      util_bitpack_uint(values->MBModeTable, 8, 10) |
      util_bitpack_uint(values->MBTransformType, 11, 11) |
      util_bitpack_uint(values->PicturelevelTransformType, 12, 13) |
      util_bitpack_uint(values->_2MVBlockPatternTable, 16, 17) |
      util_bitpack_uint(values->_4MVBlockPatternTable, 18, 19) |
      util_bitpack_uint(values->MVTable, 20, 22) |
      util_bitpack_uint(values->FIELDTXRaw, 24, 24) |
      util_bitpack_uint(values->ACPREDRaw, 25, 25) |
      util_bitpack_uint(values->OVERFLAGSRaw, 26, 26) |
      util_bitpack_uint(values->DIRECTMBRaw, 27, 27) |
      util_bitpack_uint(values->SKIPMBRaw, 28, 28) |
      util_bitpack_uint(values->MVTYPEMBRaw, 29, 29) |
      util_bitpack_uint(values->FORWARDMBRaw, 30, 30) |
      util_bitpack_uint(values->BitplaneBufferPresent, 31, 31);
}

#define GFX9_MFD_VC1_SHORT_PIC_STATE_length      5
#define GFX9_MFD_VC1_SHORT_PIC_STATE_length_bias      2
#define GFX9_MFD_VC1_SHORT_PIC_STATE_header     \
   .DWordLength                         =      3,  \
   .SubOpcodeB                          =      0,  \
   .SubOpcodeA                          =      1,  \
   .MediaCommandOpcode                  =      2,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFD_VC1_SHORT_PIC_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             PictureWidth;
   uint32_t                             PictureHeight;
   uint32_t                             PictureStructure;
   bool                                 SecondField;
   bool                                 IntraPicture;
   bool                                 BackwardPredictionPresent;
   uint32_t                             VC1Profile;
#define SimpleMainProfile                        0
#define AdvancedProfile                          1
   bool                                 DMVSurfaceValid;
   uint32_t                             MVMode;
   bool                                 InterpolationRounderControl;
   uint32_t                             BitplaneBufferPitch;
   bool                                 variablesizedtransformcoding;
   uint32_t                             DQUANT;
   bool                                 EXTENDED_MVPresent;
   uint32_t                             FastUVMotionCompensation;
#define NoRounding                               0
#define QuarterPeloffsetstoHalfFullpelpositions  1
   bool                                 LoopFilterEnable;
   bool                                 REFDIST_FLAG;
   bool                                 PANSCANPresent;
   uint32_t                             MAXBFRAMES;
   bool                                 RANGEREDPresent;
   bool                                 SYNCMARKERPresent;
   bool                                 MULTIRESPresent;
   uint32_t                             QUANTIZER;
   uint32_t                             PPicRefDistance;
   uint32_t                             ProgressivePicType;
   uint32_t                             RangeReductionEnable;
   uint32_t                             RangeReductionScale;
   bool                                 OverlapSmoothingEnable;
   bool                                 EXTENDED_DMVPresent;
   bool                                 PSF;
   bool                                 REFPIC;
   bool                                 FINTERFLAG;
   bool                                 TFCNTRFLAG;
   bool                                 INTERLACE;
   bool                                 PULLDOWN;
   bool                                 POSTPROC;
   bool                                 _4MVAllowed;
   uint32_t                             BFractionEnumeration;
};

static inline __attribute__((always_inline)) void
GFX9_MFD_VC1_SHORT_PIC_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_MFD_VC1_SHORT_PIC_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->PictureWidth, 0, 7) |
      util_bitpack_uint(values->PictureHeight, 16, 23);

   dw[2] =
      util_bitpack_uint(values->PictureStructure, 0, 1) |
      util_bitpack_uint(values->SecondField, 3, 3) |
      util_bitpack_uint(values->IntraPicture, 4, 4) |
      util_bitpack_uint(values->BackwardPredictionPresent, 5, 5) |
      util_bitpack_uint(values->VC1Profile, 11, 11) |
      util_bitpack_uint(values->DMVSurfaceValid, 15, 15) |
      util_bitpack_uint(values->MVMode, 16, 19) |
      util_bitpack_uint(values->InterpolationRounderControl, 23, 23) |
      util_bitpack_uint(values->BitplaneBufferPitch, 24, 31);

   dw[3] =
      util_bitpack_uint(values->variablesizedtransformcoding, 0, 0) |
      util_bitpack_uint(values->DQUANT, 1, 2) |
      util_bitpack_uint(values->EXTENDED_MVPresent, 3, 3) |
      util_bitpack_uint(values->FastUVMotionCompensation, 4, 4) |
      util_bitpack_uint(values->LoopFilterEnable, 5, 5) |
      util_bitpack_uint(values->REFDIST_FLAG, 6, 6) |
      util_bitpack_uint(values->PANSCANPresent, 7, 7) |
      util_bitpack_uint(values->MAXBFRAMES, 8, 10) |
      util_bitpack_uint(values->RANGEREDPresent, 11, 11) |
      util_bitpack_uint(values->SYNCMARKERPresent, 12, 12) |
      util_bitpack_uint(values->MULTIRESPresent, 13, 13) |
      util_bitpack_uint(values->QUANTIZER, 14, 15) |
      util_bitpack_uint(values->PPicRefDistance, 16, 20) |
      util_bitpack_uint(values->ProgressivePicType, 22, 23) |
      util_bitpack_uint(values->RangeReductionEnable, 28, 28) |
      util_bitpack_uint(values->RangeReductionScale, 29, 29) |
      util_bitpack_uint(values->OverlapSmoothingEnable, 30, 30);

   dw[4] =
      util_bitpack_uint(values->EXTENDED_DMVPresent, 0, 0) |
      util_bitpack_uint(values->PSF, 1, 1) |
      util_bitpack_uint(values->REFPIC, 2, 2) |
      util_bitpack_uint(values->FINTERFLAG, 3, 3) |
      util_bitpack_uint(values->TFCNTRFLAG, 4, 4) |
      util_bitpack_uint(values->INTERLACE, 5, 5) |
      util_bitpack_uint(values->PULLDOWN, 6, 6) |
      util_bitpack_uint(values->POSTPROC, 7, 7) |
      util_bitpack_uint(values->_4MVAllowed, 8, 8) |
      util_bitpack_uint(values->BFractionEnumeration, 24, 28);
}

#define GFX9_MFD_VP8_BSD_OBJECT_length        22
#define GFX9_MFD_VP8_BSD_OBJECT_length_bias      2
#define GFX9_MFD_VP8_BSD_OBJECT_header          \
   .DWordLength                         =     20,  \
   .SubOpcodeB                          =      8,  \
   .SubOpcodeA                          =      1,  \
   .MediaCommandOpCode                  =      4,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFD_VP8_BSD_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpCode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             Partition0FirstMBBitOffsetfromFrameHeader;
   uint32_t                             CodedNumofCoeffTokenPartitions;
   uint32_t                             Partition0CPBACEntropyRange;
   uint32_t                             Partition0CPBACEntropyCount;
   uint32_t                             Partition0CPBACEntropyValue;
   uint32_t                             IndirectPartition0DataLength;
   uint32_t                             IndirectPartition0DataStartOffset;
   uint32_t                             IndirectPartition1DataLength;
   uint32_t                             IndirectPartition1DataStartOffset;
   uint32_t                             IndirectPartition2DataLength;
   uint32_t                             IndirectPartition2DataStartOffset;
   uint32_t                             IndirectPartition3DataLength;
   uint32_t                             IndirectPartition3DataStartOffset;
   uint32_t                             IndirectPartition4DataLength;
   uint32_t                             IndirectPartition4DataStartOffset;
   uint32_t                             IndirectPartition5DataLength;
   uint32_t                             IndirectPartition5DataStartOffset;
   uint32_t                             IndirectPartition6DataLength;
   uint32_t                             IndirectPartition6DataStartOffset;
   uint32_t                             IndirectPartition7DataLength;
   uint32_t                             IndirectPartition7DataStartOffset;
   uint32_t                             IndirectPartition8DataLength;
   uint32_t                             IndirectPartition8DataStartOffset;
   uint32_t                             MBHeaderErrorHandling;
   uint32_t                             EntropyErrorHandling;
   uint32_t                             MPRErrorMVoutofrangeHandling;
   uint32_t                             BSDPrematureCompleteErrorHandling;
   uint32_t                             ConcealmentPictureID;
   uint32_t                             ConcealmentMethod;
#define Intra16x16Prediction                     0
#define InterPCopy                               1
};

static inline __attribute__((always_inline)) void
GFX9_MFD_VP8_BSD_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                             __attribute__((unused)) void * restrict dst,
                             __attribute__((unused)) const struct GFX9_MFD_VP8_BSD_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpCode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->Partition0FirstMBBitOffsetfromFrameHeader, 0, 2) |
      util_bitpack_uint(values->CodedNumofCoeffTokenPartitions, 4, 5) |
      util_bitpack_uint(values->Partition0CPBACEntropyRange, 8, 15) |
      util_bitpack_uint(values->Partition0CPBACEntropyCount, 16, 20);

   dw[2] =
      util_bitpack_uint(values->Partition0CPBACEntropyValue, 24, 31);

   dw[3] =
      util_bitpack_uint(values->IndirectPartition0DataLength, 0, 23);

   dw[4] =
      util_bitpack_uint(values->IndirectPartition0DataStartOffset, 0, 31);

   dw[5] =
      util_bitpack_uint(values->IndirectPartition1DataLength, 0, 23);

   dw[6] =
      util_bitpack_uint(values->IndirectPartition1DataStartOffset, 0, 31);

   dw[7] =
      util_bitpack_uint(values->IndirectPartition2DataLength, 0, 23);

   dw[8] =
      util_bitpack_uint(values->IndirectPartition2DataStartOffset, 0, 31);

   dw[9] =
      util_bitpack_uint(values->IndirectPartition3DataLength, 0, 23);

   dw[10] =
      util_bitpack_uint(values->IndirectPartition3DataStartOffset, 0, 31);

   dw[11] =
      util_bitpack_uint(values->IndirectPartition4DataLength, 0, 23);

   dw[12] =
      util_bitpack_uint(values->IndirectPartition4DataStartOffset, 0, 31);

   dw[13] =
      util_bitpack_uint(values->IndirectPartition5DataLength, 0, 23);

   dw[14] =
      util_bitpack_uint(values->IndirectPartition5DataStartOffset, 0, 31);

   dw[15] =
      util_bitpack_uint(values->IndirectPartition6DataLength, 0, 23);

   dw[16] =
      util_bitpack_uint(values->IndirectPartition6DataStartOffset, 0, 31);

   dw[17] =
      util_bitpack_uint(values->IndirectPartition7DataLength, 0, 23);

   dw[18] =
      util_bitpack_uint(values->IndirectPartition7DataStartOffset, 0, 31);

   dw[19] =
      util_bitpack_uint(values->IndirectPartition8DataLength, 0, 23);

   dw[20] =
      util_bitpack_uint(values->IndirectPartition8DataStartOffset, 0, 31);

   dw[21] =
      util_bitpack_uint(values->MBHeaderErrorHandling, 8, 8) |
      util_bitpack_uint(values->EntropyErrorHandling, 10, 10) |
      util_bitpack_uint(values->MPRErrorMVoutofrangeHandling, 12, 12) |
      util_bitpack_uint(values->BSDPrematureCompleteErrorHandling, 14, 14) |
      util_bitpack_uint(values->ConcealmentPictureID, 16, 17) |
      util_bitpack_uint(values->ConcealmentMethod, 31, 31);
}

#define GFX9_MFX_AVC_DIRECTMODE_STATE_length     71
#define GFX9_MFX_AVC_DIRECTMODE_STATE_length_bias      2
#define GFX9_MFX_AVC_DIRECTMODE_STATE_header    \
   .DWordLength                         =     69,  \
   .SubOpcodeB                          =      2,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_AVC_DIRECTMODE_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   __gen_address_type                   DirectMVBufferAddress[16];
   struct GFX9_MEMORYADDRESSATTRIBUTES  DirectMVBufferAttributes;
   __gen_address_type                   DirectMVBufferWriteAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  DirectMVBufferWriteAttributes;
   uint32_t                             POCList[34];
};

static inline __attribute__((always_inline)) void
GFX9_MFX_AVC_DIRECTMODE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                   __attribute__((unused)) void * restrict dst,
                                   __attribute__((unused)) const struct GFX9_MFX_AVC_DIRECTMODE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->DirectMVBufferAddress[0], 0, 0, 63);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;

   const uint64_t v3_address =
      __gen_address(data, &dw[3], values->DirectMVBufferAddress[1], 0, 0, 63);
   dw[3] = v3_address;
   dw[4] = v3_address >> 32;

   const uint64_t v5_address =
      __gen_address(data, &dw[5], values->DirectMVBufferAddress[2], 0, 0, 63);
   dw[5] = v5_address;
   dw[6] = v5_address >> 32;

   const uint64_t v7_address =
      __gen_address(data, &dw[7], values->DirectMVBufferAddress[3], 0, 0, 63);
   dw[7] = v7_address;
   dw[8] = v7_address >> 32;

   const uint64_t v9_address =
      __gen_address(data, &dw[9], values->DirectMVBufferAddress[4], 0, 0, 63);
   dw[9] = v9_address;
   dw[10] = v9_address >> 32;

   const uint64_t v11_address =
      __gen_address(data, &dw[11], values->DirectMVBufferAddress[5], 0, 0, 63);
   dw[11] = v11_address;
   dw[12] = v11_address >> 32;

   const uint64_t v13_address =
      __gen_address(data, &dw[13], values->DirectMVBufferAddress[6], 0, 0, 63);
   dw[13] = v13_address;
   dw[14] = v13_address >> 32;

   const uint64_t v15_address =
      __gen_address(data, &dw[15], values->DirectMVBufferAddress[7], 0, 0, 63);
   dw[15] = v15_address;
   dw[16] = v15_address >> 32;

   const uint64_t v17_address =
      __gen_address(data, &dw[17], values->DirectMVBufferAddress[8], 0, 0, 63);
   dw[17] = v17_address;
   dw[18] = v17_address >> 32;

   const uint64_t v19_address =
      __gen_address(data, &dw[19], values->DirectMVBufferAddress[9], 0, 0, 63);
   dw[19] = v19_address;
   dw[20] = v19_address >> 32;

   const uint64_t v21_address =
      __gen_address(data, &dw[21], values->DirectMVBufferAddress[10], 0, 0, 63);
   dw[21] = v21_address;
   dw[22] = v21_address >> 32;

   const uint64_t v23_address =
      __gen_address(data, &dw[23], values->DirectMVBufferAddress[11], 0, 0, 63);
   dw[23] = v23_address;
   dw[24] = v23_address >> 32;

   const uint64_t v25_address =
      __gen_address(data, &dw[25], values->DirectMVBufferAddress[12], 0, 0, 63);
   dw[25] = v25_address;
   dw[26] = v25_address >> 32;

   const uint64_t v27_address =
      __gen_address(data, &dw[27], values->DirectMVBufferAddress[13], 0, 0, 63);
   dw[27] = v27_address;
   dw[28] = v27_address >> 32;

   const uint64_t v29_address =
      __gen_address(data, &dw[29], values->DirectMVBufferAddress[14], 0, 0, 63);
   dw[29] = v29_address;
   dw[30] = v29_address >> 32;

   const uint64_t v31_address =
      __gen_address(data, &dw[31], values->DirectMVBufferAddress[15], 0, 0, 63);
   dw[31] = v31_address;
   dw[32] = v31_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[33], &values->DirectMVBufferAttributes);

   const uint64_t v34_address =
      __gen_address(data, &dw[34], values->DirectMVBufferWriteAddress, 0, 0, 63);
   dw[34] = v34_address;
   dw[35] = v34_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[36], &values->DirectMVBufferWriteAttributes);

   dw[37] =
      util_bitpack_uint(values->POCList[0], 0, 31);

   dw[38] =
      util_bitpack_uint(values->POCList[1], 0, 31);

   dw[39] =
      util_bitpack_uint(values->POCList[2], 0, 31);

   dw[40] =
      util_bitpack_uint(values->POCList[3], 0, 31);

   dw[41] =
      util_bitpack_uint(values->POCList[4], 0, 31);

   dw[42] =
      util_bitpack_uint(values->POCList[5], 0, 31);

   dw[43] =
      util_bitpack_uint(values->POCList[6], 0, 31);

   dw[44] =
      util_bitpack_uint(values->POCList[7], 0, 31);

   dw[45] =
      util_bitpack_uint(values->POCList[8], 0, 31);

   dw[46] =
      util_bitpack_uint(values->POCList[9], 0, 31);

   dw[47] =
      util_bitpack_uint(values->POCList[10], 0, 31);

   dw[48] =
      util_bitpack_uint(values->POCList[11], 0, 31);

   dw[49] =
      util_bitpack_uint(values->POCList[12], 0, 31);

   dw[50] =
      util_bitpack_uint(values->POCList[13], 0, 31);

   dw[51] =
      util_bitpack_uint(values->POCList[14], 0, 31);

   dw[52] =
      util_bitpack_uint(values->POCList[15], 0, 31);

   dw[53] =
      util_bitpack_uint(values->POCList[16], 0, 31);

   dw[54] =
      util_bitpack_uint(values->POCList[17], 0, 31);

   dw[55] =
      util_bitpack_uint(values->POCList[18], 0, 31);

   dw[56] =
      util_bitpack_uint(values->POCList[19], 0, 31);

   dw[57] =
      util_bitpack_uint(values->POCList[20], 0, 31);

   dw[58] =
      util_bitpack_uint(values->POCList[21], 0, 31);

   dw[59] =
      util_bitpack_uint(values->POCList[22], 0, 31);

   dw[60] =
      util_bitpack_uint(values->POCList[23], 0, 31);

   dw[61] =
      util_bitpack_uint(values->POCList[24], 0, 31);

   dw[62] =
      util_bitpack_uint(values->POCList[25], 0, 31);

   dw[63] =
      util_bitpack_uint(values->POCList[26], 0, 31);

   dw[64] =
      util_bitpack_uint(values->POCList[27], 0, 31);

   dw[65] =
      util_bitpack_uint(values->POCList[28], 0, 31);

   dw[66] =
      util_bitpack_uint(values->POCList[29], 0, 31);

   dw[67] =
      util_bitpack_uint(values->POCList[30], 0, 31);

   dw[68] =
      util_bitpack_uint(values->POCList[31], 0, 31);

   dw[69] =
      util_bitpack_uint(values->POCList[32], 0, 31);

   dw[70] =
      util_bitpack_uint(values->POCList[33], 0, 31);
}

#define GFX9_MFX_AVC_IMG_STATE_length         21
#define GFX9_MFX_AVC_IMG_STATE_length_bias      2
#define GFX9_MFX_AVC_IMG_STATE_header           \
   .DWordLength                         =     19,  \
   .SubOpcodeB                          =      0,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_AVC_IMG_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             FrameSize;
   uint32_t                             FrameWidth;
   uint32_t                             FrameHeight;
   uint32_t                             ImageStructure;
#define FramePicture                             0
#define TopFieldPicture                          1
#define BottomFieldPicture                       3
#define Invalidnotallowed                        2
   uint32_t                             WeightedBiPredictionIDC;
#define DEFAULT                                  0
#define EXPLICIT                                 1
#define IMPLICIT                                 2
   bool                                 WeightedPredictionEnable;
   bool                                 RhoDomainRateControlEnable;
   int32_t                              FirstChromaQPOffset;
   int32_t                              SecondChromaQPOffset;
   bool                                 FieldPicture;
   bool                                 MBAFFMode;
   bool                                 FrameMBOnly;
   bool                                 _8x8IDCTTransformMode;
   bool                                 Direct8x8Inference;
   bool                                 ConstrainedIntraPrediction;
   bool                                 NonReferencePicture;
   bool                                 EntropyCodingSyncEnable;
   uint32_t                             MBMVFormat;
#define IGNORE                                   0
#define FOLLOW                                   1
   uint32_t                             ChromaFormatIDC;
#define Monochromepicture                        0
#define _420picture                              1
#define _422picturenotsupported                  2
#define _444picturenotsupported                  3
   bool                                 MVUnpackedEnable;
   bool                                 LoadBitstreamPointerPerSlice;
   bool                                 MBStatusRead;
   uint32_t                             MinimumFrameSize;
   bool                                 IntraMBMaxBitControl;
   bool                                 InterMBMaxBitControl;
   bool                                 FrameBitrateMaxReport;
   bool                                 FrameBitrateMinReport;
   bool                                 ForceIPCMControl;
   bool                                 MBLevelRateControl;
   uint32_t                             MinimumFrameSizeUnits;
#define AVC_MFSU_Compatibilitymode               0
#define AVC_MFSU_16bytes                         1
#define AVC_MFSU_4Kb                             2
#define AVC_MFSU_16Kb                            3
   uint32_t                             NonFirstPass;
   bool                                 TrellisQuantizationChromaDisable;
   uint32_t                             TrellisQuantizationRounding;
   bool                                 TrellisQuantizationEnable;
   uint32_t                             IntraMBConformanceMaxSize;
   uint32_t                             InterMBConformanceMaxSize;
   int32_t                              SliceDeltaQPMax0;
   int32_t                              SliceDeltaQPMax1;
   uint32_t                             SliceDeltaQPMax2;
   int32_t                              SliceDeltaQPMax3;
   int32_t                              SliceDeltaQPMin0;
   int32_t                              SliceDeltaQPMin1;
   int32_t                              SliceDeltaQPMin2;
   int32_t                              SliceDeltaQPMin3;
   uint32_t                             FrameBitrateMin;
   uint32_t                             FrameBitrateMinUnitMode;
#define Compatibilitymode                        0
#define Newmode                                  1
   uint32_t                             FrameBitrateMinUnit;
   uint32_t                             FrameBitrateMax;
   uint32_t                             FrameBitrateMaxUnitMode;
#define Compatibilitymode                        0
#define Newmode                                  1
   uint32_t                             FrameBitrateMaxUnit;
   uint32_t                             FrameBitrateMinDelta;
   uint32_t                             FrameBitrateMaxDelta;
   bool                                 SliceStatsStreamOutEnable;
   int32_t                              InitialQPValue;
   uint32_t                             NumberofActiveReferencePicturesfromL0;
   uint32_t                             NumberofActiveReferencePicturesfromL1;
   uint32_t                             NumberofReferenceFrames;
   bool                                 CurrentPictureHasPerformedMMCO5;
   bool                                 PicOrderPresent;
   bool                                 DeltaPicOrderAlwaysZero;
   uint32_t                             PicOrderCountType;
   uint32_t                             SliceGroupMapType;
   bool                                 RedundantPicCountPresent;
   uint32_t                             NumberofSliceGroups;
   bool                                 DeblockingFilterControlPresent;
   uint32_t                             Log2MaxFrameNumber;
   uint32_t                             Log2MaxPicOrderCountLSB;
   uint32_t                             SliceGroupChangeRate;
   uint32_t                             CurrentPictureFrameNumber;
   uint32_t                             CurrentFrameViewID;
   uint32_t                             MaxViewIDXL0;
   uint32_t                             MaxViewIDXL1;
   bool                                 InterViewOrderDisable;
   uint32_t                             RhoDomainAverageMBQP;
   uint32_t                             ThresholdSize;
   uint32_t                             TargetSliceSize;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_AVC_IMG_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_MFX_AVC_IMG_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->FrameSize, 0, 15);

   dw[2] =
      util_bitpack_uint(values->FrameWidth, 0, 7) |
      util_bitpack_uint(values->FrameHeight, 16, 23);

   dw[3] =
      util_bitpack_uint(values->ImageStructure, 8, 9) |
      util_bitpack_uint(values->WeightedBiPredictionIDC, 10, 11) |
      util_bitpack_uint(values->WeightedPredictionEnable, 12, 12) |
      util_bitpack_uint(values->RhoDomainRateControlEnable, 13, 13) |
      util_bitpack_sint(values->FirstChromaQPOffset, 16, 20) |
      util_bitpack_sint(values->SecondChromaQPOffset, 24, 28);

   dw[4] =
      util_bitpack_uint(values->FieldPicture, 0, 0) |
      util_bitpack_uint(values->MBAFFMode, 1, 1) |
      util_bitpack_uint(values->FrameMBOnly, 2, 2) |
      util_bitpack_uint(values->_8x8IDCTTransformMode, 3, 3) |
      util_bitpack_uint(values->Direct8x8Inference, 4, 4) |
      util_bitpack_uint(values->ConstrainedIntraPrediction, 5, 5) |
      util_bitpack_uint(values->NonReferencePicture, 6, 6) |
      util_bitpack_uint(values->EntropyCodingSyncEnable, 7, 7) |
      util_bitpack_uint(values->MBMVFormat, 8, 8) |
      util_bitpack_uint(values->ChromaFormatIDC, 10, 11) |
      util_bitpack_uint(values->MVUnpackedEnable, 12, 12) |
      util_bitpack_uint(values->LoadBitstreamPointerPerSlice, 14, 14) |
      util_bitpack_uint(values->MBStatusRead, 15, 15) |
      util_bitpack_uint(values->MinimumFrameSize, 16, 31);

   dw[5] =
      util_bitpack_uint(values->IntraMBMaxBitControl, 0, 0) |
      util_bitpack_uint(values->InterMBMaxBitControl, 1, 1) |
      util_bitpack_uint(values->FrameBitrateMaxReport, 2, 2) |
      util_bitpack_uint(values->FrameBitrateMinReport, 3, 3) |
      util_bitpack_uint(values->ForceIPCMControl, 7, 7) |
      util_bitpack_uint(values->MBLevelRateControl, 9, 9) |
      util_bitpack_uint(values->MinimumFrameSizeUnits, 10, 11) |
      util_bitpack_uint(values->NonFirstPass, 16, 16) |
      util_bitpack_uint(values->TrellisQuantizationChromaDisable, 27, 27) |
      util_bitpack_uint(values->TrellisQuantizationRounding, 28, 30) |
      util_bitpack_uint(values->TrellisQuantizationEnable, 31, 31);

   dw[6] =
      util_bitpack_uint(values->IntraMBConformanceMaxSize, 0, 11) |
      util_bitpack_uint(values->InterMBConformanceMaxSize, 16, 27);

   dw[7] = 0;

   dw[8] =
      util_bitpack_sint(values->SliceDeltaQPMax0, 0, 7) |
      util_bitpack_sint(values->SliceDeltaQPMax1, 8, 15) |
      util_bitpack_uint(values->SliceDeltaQPMax2, 16, 23) |
      util_bitpack_sint(values->SliceDeltaQPMax3, 24, 31);

   dw[9] =
      util_bitpack_sint(values->SliceDeltaQPMin0, 0, 7) |
      util_bitpack_sint(values->SliceDeltaQPMin1, 8, 15) |
      util_bitpack_sint(values->SliceDeltaQPMin2, 16, 23) |
      util_bitpack_sint(values->SliceDeltaQPMin3, 24, 31);

   dw[10] =
      util_bitpack_uint(values->FrameBitrateMin, 0, 13) |
      util_bitpack_uint(values->FrameBitrateMinUnitMode, 14, 14) |
      util_bitpack_uint(values->FrameBitrateMinUnit, 15, 15) |
      util_bitpack_uint(values->FrameBitrateMax, 16, 29) |
      util_bitpack_uint(values->FrameBitrateMaxUnitMode, 30, 30) |
      util_bitpack_uint(values->FrameBitrateMaxUnit, 31, 31);

   dw[11] =
      util_bitpack_uint(values->FrameBitrateMinDelta, 0, 14) |
      util_bitpack_uint(values->FrameBitrateMaxDelta, 16, 30) |
      util_bitpack_uint(values->SliceStatsStreamOutEnable, 31, 31);

   dw[12] = 0;

   dw[13] =
      util_bitpack_sint(values->InitialQPValue, 0, 7) |
      util_bitpack_uint(values->NumberofActiveReferencePicturesfromL0, 8, 13) |
      util_bitpack_uint(values->NumberofActiveReferencePicturesfromL1, 16, 21) |
      util_bitpack_uint(values->NumberofReferenceFrames, 24, 28) |
      util_bitpack_uint(values->CurrentPictureHasPerformedMMCO5, 29, 29);

   dw[14] =
      util_bitpack_uint(values->PicOrderPresent, 0, 0) |
      util_bitpack_uint(values->DeltaPicOrderAlwaysZero, 1, 1) |
      util_bitpack_uint(values->PicOrderCountType, 2, 3) |
      util_bitpack_uint(values->SliceGroupMapType, 8, 10) |
      util_bitpack_uint(values->RedundantPicCountPresent, 11, 11) |
      util_bitpack_uint(values->NumberofSliceGroups, 12, 14) |
      util_bitpack_uint(values->DeblockingFilterControlPresent, 15, 15) |
      util_bitpack_uint(values->Log2MaxFrameNumber, 16, 23) |
      util_bitpack_uint(values->Log2MaxPicOrderCountLSB, 24, 31);

   dw[15] =
      util_bitpack_uint(values->SliceGroupChangeRate, 0, 15) |
      util_bitpack_uint(values->CurrentPictureFrameNumber, 16, 31);

   dw[16] =
      util_bitpack_uint(values->CurrentFrameViewID, 0, 9) |
      util_bitpack_uint(values->MaxViewIDXL0, 12, 15) |
      util_bitpack_uint(values->MaxViewIDXL1, 18, 21) |
      util_bitpack_uint(values->InterViewOrderDisable, 31, 31);

   dw[17] =
      util_bitpack_uint(values->RhoDomainAverageMBQP, 16, 21);

   dw[18] = 0;

   dw[19] =
      util_bitpack_uint(values->ThresholdSize, 0, 31);

   dw[20] =
      util_bitpack_uint(values->TargetSliceSize, 0, 31);
}

#define GFX9_MFX_AVC_REF_IDX_STATE_length     10
#define GFX9_MFX_AVC_REF_IDX_STATE_length_bias      2
#define GFX9_MFX_AVC_REF_IDX_STATE_header       \
   .DWordLength                         =      8,  \
   .SubOpcodeB                          =      4,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_AVC_REF_IDX_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             ReferencePictureListSelect;
   uint32_t                             ReferenceListEntry[32];
};

static inline __attribute__((always_inline)) void
GFX9_MFX_AVC_REF_IDX_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GFX9_MFX_AVC_REF_IDX_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ReferencePictureListSelect, 0, 0);

   dw[2] =
      util_bitpack_uint(values->ReferenceListEntry[0], 0, 7) |
      util_bitpack_uint(values->ReferenceListEntry[1], 8, 15) |
      util_bitpack_uint(values->ReferenceListEntry[2], 16, 23) |
      util_bitpack_uint(values->ReferenceListEntry[3], 24, 31);

   dw[3] =
      util_bitpack_uint(values->ReferenceListEntry[4], 0, 7) |
      util_bitpack_uint(values->ReferenceListEntry[5], 8, 15) |
      util_bitpack_uint(values->ReferenceListEntry[6], 16, 23) |
      util_bitpack_uint(values->ReferenceListEntry[7], 24, 31);

   dw[4] =
      util_bitpack_uint(values->ReferenceListEntry[8], 0, 7) |
      util_bitpack_uint(values->ReferenceListEntry[9], 8, 15) |
      util_bitpack_uint(values->ReferenceListEntry[10], 16, 23) |
      util_bitpack_uint(values->ReferenceListEntry[11], 24, 31);

   dw[5] =
      util_bitpack_uint(values->ReferenceListEntry[12], 0, 7) |
      util_bitpack_uint(values->ReferenceListEntry[13], 8, 15) |
      util_bitpack_uint(values->ReferenceListEntry[14], 16, 23) |
      util_bitpack_uint(values->ReferenceListEntry[15], 24, 31);

   dw[6] =
      util_bitpack_uint(values->ReferenceListEntry[16], 0, 7) |
      util_bitpack_uint(values->ReferenceListEntry[17], 8, 15) |
      util_bitpack_uint(values->ReferenceListEntry[18], 16, 23) |
      util_bitpack_uint(values->ReferenceListEntry[19], 24, 31);

   dw[7] =
      util_bitpack_uint(values->ReferenceListEntry[20], 0, 7) |
      util_bitpack_uint(values->ReferenceListEntry[21], 8, 15) |
      util_bitpack_uint(values->ReferenceListEntry[22], 16, 23) |
      util_bitpack_uint(values->ReferenceListEntry[23], 24, 31);

   dw[8] =
      util_bitpack_uint(values->ReferenceListEntry[24], 0, 7) |
      util_bitpack_uint(values->ReferenceListEntry[25], 8, 15) |
      util_bitpack_uint(values->ReferenceListEntry[26], 16, 23) |
      util_bitpack_uint(values->ReferenceListEntry[27], 24, 31);

   dw[9] =
      util_bitpack_uint(values->ReferenceListEntry[28], 0, 7) |
      util_bitpack_uint(values->ReferenceListEntry[29], 8, 15) |
      util_bitpack_uint(values->ReferenceListEntry[30], 16, 23) |
      util_bitpack_uint(values->ReferenceListEntry[31], 24, 31);
}

#define GFX9_MFX_AVC_SLICE_STATE_length       10
#define GFX9_MFX_AVC_SLICE_STATE_length_bias      2
#define GFX9_MFX_AVC_SLICE_STATE_header         \
   .DWordLength                         =      8,  \
   .SubOpcodeB                          =      3,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_AVC_SLICE_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             SliceType;
#define AVC_ST_PSlice                            0
#define AVC_ST_BSlice                            1
#define AVC_ST_ISlice                            2
   uint32_t                             Log2WeightDenominatorLuma;
   uint32_t                             Log2WeightDenominatorChroma;
   uint32_t                             NumberofReferencePicturesinInterpredictionList0;
   uint32_t                             NumberofReferencePicturesinInterpredictionList1;
   int32_t                              SliceAlphaC0OffsetDiv2;
   int32_t                              SliceBetaOffsetDiv2;
   uint32_t                             SliceQuantizationParameter;
   uint32_t                             CABACInitIDC;
   uint32_t                             DisableDeblockingFilterIndicator;
   uint32_t                             DirectPredictionType;
#define Temporal                                 0
#define Spatial                                  1
   uint32_t                             WeightedPredictionIndicator;
   uint32_t                             SliceStartMBNumber;
   uint32_t                             SliceHorizontalPosition;
   uint32_t                             SliceVerticalPosition;
   uint32_t                             NextSliceHorizontalPosition;
   uint32_t                             NextSliceVerticalPosition;
   uint32_t                             StreamID;
   uint32_t                             SliceID;
   bool                                 CABACZeroWordInsertionEnable;
   bool                                 EmulationByteSliceInsertEnable;
   bool                                 TailInsertionPresent;
   bool                                 SliceDataInsertionPresent;
   bool                                 HeaderInsertionPresent;
   bool                                 LastSliceGroup;
   bool                                 MBTypeSkipConversionDisable;
   bool                                 MBTypeDirectConversionDisable;
   uint32_t                             RateControlPanicType;
#define QPPanic                                  0
#define CBPPanic                                 1
   bool                                 RateControlPanicEnable;
   uint32_t                             RateControlStableTolerance;
   uint32_t                             RateControlTriggleMode;
#define AlwaysRateControl                        0
#define GentleRateControl                        1
#define LooseRateControl                         2
   bool                                 ResetRateControlCounter;
   uint32_t                             RateControlCounterEnable;
   uint64_t                             IndirectPAKBSEDataStartAddress;
   uint32_t                             GrowInit;
   uint32_t                             GrowResistance;
   uint32_t                             ShrinkInit;
   uint32_t                             ShrinkResistance;
   uint32_t                             QPMaxPositiveModifierMagnitude;
   uint32_t                             QPMaxNegativeModifierMagnitude;
   uint32_t                             Correct1;
   uint32_t                             Correct2;
   uint32_t                             Correct3;
   uint32_t                             Correct4;
   uint32_t                             Correct5;
   uint32_t                             Correct6;
   uint32_t                             RoundIntra;
#define _116                                     0
#define _216                                     1
#define _316                                     2
#define _416                                     3
#define _516                                     4
#define _616                                     5
#define _716                                     6
#define _816                                     7
   bool                                 RoundIntraEnable;
   uint32_t                             RoundInter;
#define _116                                     0
#define _216                                     1
#define _316                                     2
#define _416                                     3
#define _516                                     4
#define _616                                     5
#define _716                                     6
#define _816                                     7
   bool                                 RoundInterEnable;
   uint32_t                             CV0;
   uint32_t                             CV1;
   uint32_t                             CV2;
   uint32_t                             CV3;
   uint32_t                             CV4;
   uint32_t                             CV5;
   uint32_t                             CV6;
   uint32_t                             CV7;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_AVC_SLICE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_MFX_AVC_SLICE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->SliceType, 0, 3);

   dw[2] =
      util_bitpack_uint(values->Log2WeightDenominatorLuma, 0, 2) |
      util_bitpack_uint(values->Log2WeightDenominatorChroma, 8, 10) |
      util_bitpack_uint(values->NumberofReferencePicturesinInterpredictionList0, 16, 21) |
      util_bitpack_uint(values->NumberofReferencePicturesinInterpredictionList1, 24, 29);

   dw[3] =
      util_bitpack_sint(values->SliceAlphaC0OffsetDiv2, 0, 3) |
      util_bitpack_sint(values->SliceBetaOffsetDiv2, 8, 11) |
      util_bitpack_uint(values->SliceQuantizationParameter, 16, 21) |
      util_bitpack_uint(values->CABACInitIDC, 24, 25) |
      util_bitpack_uint(values->DisableDeblockingFilterIndicator, 27, 28) |
      util_bitpack_uint(values->DirectPredictionType, 29, 29) |
      util_bitpack_uint(values->WeightedPredictionIndicator, 30, 31);

   dw[4] =
      util_bitpack_uint(values->SliceStartMBNumber, 0, 14) |
      util_bitpack_uint(values->SliceHorizontalPosition, 16, 23) |
      util_bitpack_uint(values->SliceVerticalPosition, 24, 31);

   dw[5] =
      util_bitpack_uint(values->NextSliceHorizontalPosition, 0, 7) |
      util_bitpack_uint(values->NextSliceVerticalPosition, 16, 23);

   dw[6] =
      util_bitpack_uint(values->StreamID, 0, 1) |
      util_bitpack_uint(values->SliceID, 4, 7) |
      util_bitpack_uint(values->CABACZeroWordInsertionEnable, 12, 12) |
      util_bitpack_uint(values->EmulationByteSliceInsertEnable, 13, 13) |
      util_bitpack_uint(values->TailInsertionPresent, 15, 15) |
      util_bitpack_uint(values->SliceDataInsertionPresent, 16, 16) |
      util_bitpack_uint(values->HeaderInsertionPresent, 17, 17) |
      util_bitpack_uint(values->LastSliceGroup, 19, 19) |
      util_bitpack_uint(values->MBTypeSkipConversionDisable, 20, 20) |
      util_bitpack_uint(values->MBTypeDirectConversionDisable, 21, 21) |
      util_bitpack_uint(values->RateControlPanicType, 22, 22) |
      util_bitpack_uint(values->RateControlPanicEnable, 23, 23) |
      util_bitpack_uint(values->RateControlStableTolerance, 24, 27) |
      util_bitpack_uint(values->RateControlTriggleMode, 28, 29) |
      util_bitpack_uint(values->ResetRateControlCounter, 30, 30) |
      util_bitpack_uint(values->RateControlCounterEnable, 31, 31);

   dw[7] =
      __gen_offset(values->IndirectPAKBSEDataStartAddress, 0, 28);

   dw[8] =
      util_bitpack_uint(values->GrowInit, 0, 3) |
      util_bitpack_uint(values->GrowResistance, 4, 7) |
      util_bitpack_uint(values->ShrinkInit, 8, 11) |
      util_bitpack_uint(values->ShrinkResistance, 12, 15) |
      util_bitpack_uint(values->QPMaxPositiveModifierMagnitude, 16, 23) |
      util_bitpack_uint(values->QPMaxNegativeModifierMagnitude, 24, 31);

   dw[9] =
      util_bitpack_uint(values->Correct1, 0, 3) |
      util_bitpack_uint(values->Correct2, 4, 7) |
      util_bitpack_uint(values->Correct3, 8, 11) |
      util_bitpack_uint(values->Correct4, 12, 15) |
      util_bitpack_uint(values->Correct5, 16, 19) |
      util_bitpack_uint(values->Correct6, 20, 23) |
      util_bitpack_uint(values->RoundIntra, 24, 26) |
      util_bitpack_uint(values->RoundIntraEnable, 27, 27) |
      util_bitpack_uint(values->RoundInter, 28, 30) |
      util_bitpack_uint(values->RoundInterEnable, 31, 31);
}

#define GFX9_MFX_AVC_WEIGHTOFFSET_STATE_length     98
#define GFX9_MFX_AVC_WEIGHTOFFSET_STATE_length_bias      2
#define GFX9_MFX_AVC_WEIGHTOFFSET_STATE_header  \
   .DWordLength                         =     96,  \
   .SubOpcodeB                          =      5,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_AVC_WEIGHTOFFSET_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             WeightandOffsetSelect;
#define L0table                                  0
#define L1table                                  1
   uint32_t                             WeightOffset[96];
};

static inline __attribute__((always_inline)) void
GFX9_MFX_AVC_WEIGHTOFFSET_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                     __attribute__((unused)) void * restrict dst,
                                     __attribute__((unused)) const struct GFX9_MFX_AVC_WEIGHTOFFSET_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->WeightandOffsetSelect, 0, 0);

   dw[2] =
      util_bitpack_uint(values->WeightOffset[0], 0, 31);

   dw[3] =
      util_bitpack_uint(values->WeightOffset[1], 0, 31);

   dw[4] =
      util_bitpack_uint(values->WeightOffset[2], 0, 31);

   dw[5] =
      util_bitpack_uint(values->WeightOffset[3], 0, 31);

   dw[6] =
      util_bitpack_uint(values->WeightOffset[4], 0, 31);

   dw[7] =
      util_bitpack_uint(values->WeightOffset[5], 0, 31);

   dw[8] =
      util_bitpack_uint(values->WeightOffset[6], 0, 31);

   dw[9] =
      util_bitpack_uint(values->WeightOffset[7], 0, 31);

   dw[10] =
      util_bitpack_uint(values->WeightOffset[8], 0, 31);

   dw[11] =
      util_bitpack_uint(values->WeightOffset[9], 0, 31);

   dw[12] =
      util_bitpack_uint(values->WeightOffset[10], 0, 31);

   dw[13] =
      util_bitpack_uint(values->WeightOffset[11], 0, 31);

   dw[14] =
      util_bitpack_uint(values->WeightOffset[12], 0, 31);

   dw[15] =
      util_bitpack_uint(values->WeightOffset[13], 0, 31);

   dw[16] =
      util_bitpack_uint(values->WeightOffset[14], 0, 31);

   dw[17] =
      util_bitpack_uint(values->WeightOffset[15], 0, 31);

   dw[18] =
      util_bitpack_uint(values->WeightOffset[16], 0, 31);

   dw[19] =
      util_bitpack_uint(values->WeightOffset[17], 0, 31);

   dw[20] =
      util_bitpack_uint(values->WeightOffset[18], 0, 31);

   dw[21] =
      util_bitpack_uint(values->WeightOffset[19], 0, 31);

   dw[22] =
      util_bitpack_uint(values->WeightOffset[20], 0, 31);

   dw[23] =
      util_bitpack_uint(values->WeightOffset[21], 0, 31);

   dw[24] =
      util_bitpack_uint(values->WeightOffset[22], 0, 31);

   dw[25] =
      util_bitpack_uint(values->WeightOffset[23], 0, 31);

   dw[26] =
      util_bitpack_uint(values->WeightOffset[24], 0, 31);

   dw[27] =
      util_bitpack_uint(values->WeightOffset[25], 0, 31);

   dw[28] =
      util_bitpack_uint(values->WeightOffset[26], 0, 31);

   dw[29] =
      util_bitpack_uint(values->WeightOffset[27], 0, 31);

   dw[30] =
      util_bitpack_uint(values->WeightOffset[28], 0, 31);

   dw[31] =
      util_bitpack_uint(values->WeightOffset[29], 0, 31);

   dw[32] =
      util_bitpack_uint(values->WeightOffset[30], 0, 31);

   dw[33] =
      util_bitpack_uint(values->WeightOffset[31], 0, 31);

   dw[34] =
      util_bitpack_uint(values->WeightOffset[32], 0, 31);

   dw[35] =
      util_bitpack_uint(values->WeightOffset[33], 0, 31);

   dw[36] =
      util_bitpack_uint(values->WeightOffset[34], 0, 31);

   dw[37] =
      util_bitpack_uint(values->WeightOffset[35], 0, 31);

   dw[38] =
      util_bitpack_uint(values->WeightOffset[36], 0, 31);

   dw[39] =
      util_bitpack_uint(values->WeightOffset[37], 0, 31);

   dw[40] =
      util_bitpack_uint(values->WeightOffset[38], 0, 31);

   dw[41] =
      util_bitpack_uint(values->WeightOffset[39], 0, 31);

   dw[42] =
      util_bitpack_uint(values->WeightOffset[40], 0, 31);

   dw[43] =
      util_bitpack_uint(values->WeightOffset[41], 0, 31);

   dw[44] =
      util_bitpack_uint(values->WeightOffset[42], 0, 31);

   dw[45] =
      util_bitpack_uint(values->WeightOffset[43], 0, 31);

   dw[46] =
      util_bitpack_uint(values->WeightOffset[44], 0, 31);

   dw[47] =
      util_bitpack_uint(values->WeightOffset[45], 0, 31);

   dw[48] =
      util_bitpack_uint(values->WeightOffset[46], 0, 31);

   dw[49] =
      util_bitpack_uint(values->WeightOffset[47], 0, 31);

   dw[50] =
      util_bitpack_uint(values->WeightOffset[48], 0, 31);

   dw[51] =
      util_bitpack_uint(values->WeightOffset[49], 0, 31);

   dw[52] =
      util_bitpack_uint(values->WeightOffset[50], 0, 31);

   dw[53] =
      util_bitpack_uint(values->WeightOffset[51], 0, 31);

   dw[54] =
      util_bitpack_uint(values->WeightOffset[52], 0, 31);

   dw[55] =
      util_bitpack_uint(values->WeightOffset[53], 0, 31);

   dw[56] =
      util_bitpack_uint(values->WeightOffset[54], 0, 31);

   dw[57] =
      util_bitpack_uint(values->WeightOffset[55], 0, 31);

   dw[58] =
      util_bitpack_uint(values->WeightOffset[56], 0, 31);

   dw[59] =
      util_bitpack_uint(values->WeightOffset[57], 0, 31);

   dw[60] =
      util_bitpack_uint(values->WeightOffset[58], 0, 31);

   dw[61] =
      util_bitpack_uint(values->WeightOffset[59], 0, 31);

   dw[62] =
      util_bitpack_uint(values->WeightOffset[60], 0, 31);

   dw[63] =
      util_bitpack_uint(values->WeightOffset[61], 0, 31);

   dw[64] =
      util_bitpack_uint(values->WeightOffset[62], 0, 31);

   dw[65] =
      util_bitpack_uint(values->WeightOffset[63], 0, 31);

   dw[66] =
      util_bitpack_uint(values->WeightOffset[64], 0, 31);

   dw[67] =
      util_bitpack_uint(values->WeightOffset[65], 0, 31);

   dw[68] =
      util_bitpack_uint(values->WeightOffset[66], 0, 31);

   dw[69] =
      util_bitpack_uint(values->WeightOffset[67], 0, 31);

   dw[70] =
      util_bitpack_uint(values->WeightOffset[68], 0, 31);

   dw[71] =
      util_bitpack_uint(values->WeightOffset[69], 0, 31);

   dw[72] =
      util_bitpack_uint(values->WeightOffset[70], 0, 31);

   dw[73] =
      util_bitpack_uint(values->WeightOffset[71], 0, 31);

   dw[74] =
      util_bitpack_uint(values->WeightOffset[72], 0, 31);

   dw[75] =
      util_bitpack_uint(values->WeightOffset[73], 0, 31);

   dw[76] =
      util_bitpack_uint(values->WeightOffset[74], 0, 31);

   dw[77] =
      util_bitpack_uint(values->WeightOffset[75], 0, 31);

   dw[78] =
      util_bitpack_uint(values->WeightOffset[76], 0, 31);

   dw[79] =
      util_bitpack_uint(values->WeightOffset[77], 0, 31);

   dw[80] =
      util_bitpack_uint(values->WeightOffset[78], 0, 31);

   dw[81] =
      util_bitpack_uint(values->WeightOffset[79], 0, 31);

   dw[82] =
      util_bitpack_uint(values->WeightOffset[80], 0, 31);

   dw[83] =
      util_bitpack_uint(values->WeightOffset[81], 0, 31);

   dw[84] =
      util_bitpack_uint(values->WeightOffset[82], 0, 31);

   dw[85] =
      util_bitpack_uint(values->WeightOffset[83], 0, 31);

   dw[86] =
      util_bitpack_uint(values->WeightOffset[84], 0, 31);

   dw[87] =
      util_bitpack_uint(values->WeightOffset[85], 0, 31);

   dw[88] =
      util_bitpack_uint(values->WeightOffset[86], 0, 31);

   dw[89] =
      util_bitpack_uint(values->WeightOffset[87], 0, 31);

   dw[90] =
      util_bitpack_uint(values->WeightOffset[88], 0, 31);

   dw[91] =
      util_bitpack_uint(values->WeightOffset[89], 0, 31);

   dw[92] =
      util_bitpack_uint(values->WeightOffset[90], 0, 31);

   dw[93] =
      util_bitpack_uint(values->WeightOffset[91], 0, 31);

   dw[94] =
      util_bitpack_uint(values->WeightOffset[92], 0, 31);

   dw[95] =
      util_bitpack_uint(values->WeightOffset[93], 0, 31);

   dw[96] =
      util_bitpack_uint(values->WeightOffset[94], 0, 31);

   dw[97] =
      util_bitpack_uint(values->WeightOffset[95], 0, 31);
}

#define GFX9_MFX_BSP_BUF_BASE_ADDR_STATE_length     10
#define GFX9_MFX_BSP_BUF_BASE_ADDR_STATE_length_bias      2
#define GFX9_MFX_BSP_BUF_BASE_ADDR_STATE_header \
   .DWordLength                         =      8,  \
   .SubOpcodeB                          =      4,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_BSP_BUF_BASE_ADDR_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   __gen_address_type                   BSDMPCRowStoreScratchBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  BSDMPCRowStoreScratchBufferAttributes;
   __gen_address_type                   MPRRowStoreScratchBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  MPRRowStoreScratchBufferAttributes;
   __gen_address_type                   BitplaneReadBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  BitplaneReadBufferAttributes;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_BSP_BUF_BASE_ADDR_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                      __attribute__((unused)) void * restrict dst,
                                      __attribute__((unused)) const struct GFX9_MFX_BSP_BUF_BASE_ADDR_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->BSDMPCRowStoreScratchBufferAddress, 0, 6, 47);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[3], &values->BSDMPCRowStoreScratchBufferAttributes);

   const uint64_t v4_address =
      __gen_address(data, &dw[4], values->MPRRowStoreScratchBufferAddress, 0, 6, 47);
   dw[4] = v4_address;
   dw[5] = v4_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[6], &values->MPRRowStoreScratchBufferAttributes);

   const uint64_t v7_address =
      __gen_address(data, &dw[7], values->BitplaneReadBufferAddress, 0, 6, 47);
   dw[7] = v7_address;
   dw[8] = v7_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[9], &values->BitplaneReadBufferAttributes);
}

#define GFX9_MFX_DBK_OBJECT_length            13
#define GFX9_MFX_DBK_OBJECT_length_bias        2
#define GFX9_MFX_DBK_OBJECT_header              \
   .DWordLength                         =     11,  \
   .SubOpcodeB                          =      9,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_DBK_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   __gen_address_type                   PreDeblockingSourceAddress;
   uint32_t                             PreDeblockingSourceMOCS;
   uint32_t                             PreDeblockingSourceArbitrationPriorityControl;
#define Highestpriority                          0
#define Secondhighestpriority                    1
#define Thirdhighestpriority                     2
#define Lowestpriority                           3
   bool                                 PreDeblockingSourceMemoryCompressionEnable;
   uint32_t                             PreDeblockingSourceMemoryCompressionMode;
   uint32_t                             PreDeblockingSourceTiledResourceMode;
#define TRMODE_NONE                              0
#define TRMODE_TILEYF                            1
#define TRMODE_TILEYS                            2
   __gen_address_type                   DeblockingControlAddress;
   uint32_t                             DeblockingControlMOCS;
   uint32_t                             DeblockingControlArbitrationPriorityControl;
#define Highestpriority                          0
#define Secondhighestpriority                    1
#define Thirdhighestpriority                     2
#define Lowestpriority                           3
   bool                                 DeblockingControlMemoryCompressionEnable;
   uint32_t                             DeblockingControlMemoryCompressionMode;
   uint32_t                             DeblockingControlTiledResourceMode;
#define TRMODE_NONE                              0
#define TRMODE_TILEYF                            1
#define TRMODE_TILEYS                            2
   __gen_address_type                   DeblockingDestinationAddressHigh;
   uint32_t                             DeblockingDestinationMOCS;
   uint32_t                             DeblockingDestinationArbitrationPriorityControl;
#define Highestpriority                          0
#define Secondhighestpriority                    1
#define Thirdhighestpriority                     2
#define Lowestpriority                           3
   bool                                 DeblockingDestinationMemoryCompressionEnable;
   uint32_t                             DeblockingDestinationMemoryCompressionMode;
   uint32_t                             DeblockingDestinationTiledResourceMode;
#define TRMODE_NONE                              0
#define TRMODE_TILEYF                            1
#define TRMODE_TILEYS                            2
   __gen_address_type                   DeblockRowStoreAddress;
   uint32_t                             CoeffProbabilityStreamInMOCS;
   uint32_t                             DeblockRowStoreArbitrationPriorityControl;
#define Highestpriority                          0
#define Secondhighestpriority                    1
#define Thirdhighestpriority                     2
#define Lowestpriority                           3
   bool                                 DeblockRowStoreMemoryCompressionEnable;
   uint32_t                             DeblockRowStoreMemoryCompressionMode;
   uint32_t                             DeblockRowStoreTiledResourceMode;
#define TRMODE_NONE                              0
#define TRMODE_TILEYF                            1
#define TRMODE_TILEYS                            2
};

static inline __attribute__((always_inline)) void
GFX9_MFX_DBK_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_MFX_DBK_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->PreDeblockingSourceAddress, 0, 6, 47);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;

   dw[3] =
      util_bitpack_uint_nonzero(values->PreDeblockingSourceMOCS, 1, 6) |
      util_bitpack_uint(values->PreDeblockingSourceArbitrationPriorityControl, 7, 8) |
      util_bitpack_uint(values->PreDeblockingSourceMemoryCompressionEnable, 9, 9) |
      util_bitpack_uint(values->PreDeblockingSourceMemoryCompressionMode, 10, 10) |
      util_bitpack_uint(values->PreDeblockingSourceTiledResourceMode, 13, 14);

   const uint64_t v4_address =
      __gen_address(data, &dw[4], values->DeblockingControlAddress, 0, 6, 47);
   dw[4] = v4_address;
   dw[5] = v4_address >> 32;

   dw[6] =
      util_bitpack_uint_nonzero(values->DeblockingControlMOCS, 1, 6) |
      util_bitpack_uint(values->DeblockingControlArbitrationPriorityControl, 7, 8) |
      util_bitpack_uint(values->DeblockingControlMemoryCompressionEnable, 9, 9) |
      util_bitpack_uint(values->DeblockingControlMemoryCompressionMode, 10, 10) |
      util_bitpack_uint(values->DeblockingControlTiledResourceMode, 13, 14);

   const uint64_t v7_address =
      __gen_address(data, &dw[7], values->DeblockingDestinationAddressHigh, 0, 6, 47);
   dw[7] = v7_address;
   dw[8] = v7_address >> 32;

   dw[9] =
      util_bitpack_uint_nonzero(values->DeblockingDestinationMOCS, 1, 6) |
      util_bitpack_uint(values->DeblockingDestinationArbitrationPriorityControl, 7, 8) |
      util_bitpack_uint(values->DeblockingDestinationMemoryCompressionEnable, 9, 9) |
      util_bitpack_uint(values->DeblockingDestinationMemoryCompressionMode, 10, 10) |
      util_bitpack_uint(values->DeblockingDestinationTiledResourceMode, 13, 14);

   const uint64_t v10_address =
      __gen_address(data, &dw[10], values->DeblockRowStoreAddress, 0, 6, 47);
   dw[10] = v10_address;
   dw[11] = v10_address >> 32;

   dw[12] =
      util_bitpack_uint_nonzero(values->CoeffProbabilityStreamInMOCS, 1, 6) |
      util_bitpack_uint(values->DeblockRowStoreArbitrationPriorityControl, 7, 8) |
      util_bitpack_uint(values->DeblockRowStoreMemoryCompressionEnable, 9, 9) |
      util_bitpack_uint(values->DeblockRowStoreMemoryCompressionMode, 10, 10) |
      util_bitpack_uint(values->DeblockRowStoreTiledResourceMode, 13, 14);
}

#define GFX9_MFX_FQM_STATE_length             34
#define GFX9_MFX_FQM_STATE_length_bias         2
#define GFX9_MFX_FQM_STATE_header               \
   .DWordLength                         =     32,  \
   .SubOpcodeB                          =      8,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_FQM_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             AVC;
#define AVC_4x4_Intra_MATRIX                     0
#define AVC_4x4_Inter_MATRIX                     1
#define AVC_8x8_Intra_MATRIX                     2
#define AVC_8x8_Inter_MATRIX                     3
   uint32_t                             MPEG2;
#define MPEG_INTRA_QUANTIZER_MATRIX              0
#define MPEG_NON_INTRA_QUANTIZER_MATRIX          1
   uint32_t                             JPEG;
#define JPEG_Luma_Y_QUANTIZER_MATRIXorR          0
#define JPEG_Chroma_Cb_QUANTIZER_MATRIXorG       1
#define JPEG_Chroma_Cr_QUANTIZER_MATRIXorB       2
   uint32_t                             QuantizerMatrix8x8[64];
};

static inline __attribute__((always_inline)) void
GFX9_MFX_FQM_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_MFX_FQM_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->AVC, 0, 1) |
      util_bitpack_uint(values->MPEG2, 0, 1) |
      util_bitpack_uint(values->JPEG, 0, 1);

   dw[2] =
      util_bitpack_uint(values->QuantizerMatrix8x8[0], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[1], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[2], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[3], 24, 31);

   dw[3] =
      util_bitpack_uint(values->QuantizerMatrix8x8[4], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[5], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[6], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[7], 24, 31);

   dw[4] =
      util_bitpack_uint(values->QuantizerMatrix8x8[8], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[9], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[10], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[11], 24, 31);

   dw[5] =
      util_bitpack_uint(values->QuantizerMatrix8x8[12], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[13], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[14], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[15], 24, 31);

   dw[6] =
      util_bitpack_uint(values->QuantizerMatrix8x8[16], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[17], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[18], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[19], 24, 31);

   dw[7] =
      util_bitpack_uint(values->QuantizerMatrix8x8[20], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[21], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[22], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[23], 24, 31);

   dw[8] =
      util_bitpack_uint(values->QuantizerMatrix8x8[24], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[25], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[26], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[27], 24, 31);

   dw[9] =
      util_bitpack_uint(values->QuantizerMatrix8x8[28], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[29], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[30], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[31], 24, 31);

   dw[10] =
      util_bitpack_uint(values->QuantizerMatrix8x8[32], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[33], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[34], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[35], 24, 31);

   dw[11] =
      util_bitpack_uint(values->QuantizerMatrix8x8[36], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[37], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[38], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[39], 24, 31);

   dw[12] =
      util_bitpack_uint(values->QuantizerMatrix8x8[40], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[41], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[42], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[43], 24, 31);

   dw[13] =
      util_bitpack_uint(values->QuantizerMatrix8x8[44], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[45], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[46], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[47], 24, 31);

   dw[14] =
      util_bitpack_uint(values->QuantizerMatrix8x8[48], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[49], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[50], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[51], 24, 31);

   dw[15] =
      util_bitpack_uint(values->QuantizerMatrix8x8[52], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[53], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[54], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[55], 24, 31);

   dw[16] =
      util_bitpack_uint(values->QuantizerMatrix8x8[56], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[57], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[58], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[59], 24, 31);

   dw[17] =
      util_bitpack_uint(values->QuantizerMatrix8x8[60], 0, 7) |
      util_bitpack_uint(values->QuantizerMatrix8x8[61], 8, 15) |
      util_bitpack_uint(values->QuantizerMatrix8x8[62], 16, 23) |
      util_bitpack_uint(values->QuantizerMatrix8x8[63], 24, 31);

   dw[18] = 0;

   dw[19] = 0;

   dw[20] = 0;

   dw[21] = 0;

   dw[22] = 0;

   dw[23] = 0;

   dw[24] = 0;

   dw[25] = 0;

   dw[26] = 0;

   dw[27] = 0;

   dw[28] = 0;

   dw[29] = 0;

   dw[30] = 0;

   dw[31] = 0;

   dw[32] = 0;

   dw[33] = 0;
}

#define GFX9_MFX_IND_OBJ_BASE_ADDR_STATE_length     26
#define GFX9_MFX_IND_OBJ_BASE_ADDR_STATE_length_bias      2
#define GFX9_MFX_IND_OBJ_BASE_ADDR_STATE_header \
   .DWordLength                         =     24,  \
   .SubOpcodeB                          =      3,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_IND_OBJ_BASE_ADDR_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   __gen_address_type                   MFXIndirectBitstreamObjectAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  MFXIndirectBitstreamObjectAttributes;
   __gen_address_type                   MFXIndirectBitstreamObjectUpperBound;
   __gen_address_type                   MFXIndirectMVObjectAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  MFXIndirectMVObjectAttributes;
   __gen_address_type                   MFXIndirectMVObjectUpperBound;
   __gen_address_type                   MFDIndirectITCOEFFObjectAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  MFDIndirectITCOEFFObjectAttributes;
   __gen_address_type                   MFDIndirectITCOEFFObjectUpperBound;
   __gen_address_type                   MFDIndirectITDBLKObjectAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  MFDIndirectITDBLKObjectAttributes;
   __gen_address_type                   MFDIndirectITDBLKObjectUpperBound;
   __gen_address_type                   MFCIndirectPAKBSEObjectAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  MFCIndirectPAKBSEObjectAttributes;
   __gen_address_type                   MFCIndirectPAKBSEObjectUpperBound;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_IND_OBJ_BASE_ADDR_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                      __attribute__((unused)) void * restrict dst,
                                      __attribute__((unused)) const struct GFX9_MFX_IND_OBJ_BASE_ADDR_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->MFXIndirectBitstreamObjectAddress, 0, 0, 63);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[3], &values->MFXIndirectBitstreamObjectAttributes);

   const uint64_t v4_address =
      __gen_address(data, &dw[4], values->MFXIndirectBitstreamObjectUpperBound, 0, 0, 63);
   dw[4] = v4_address;
   dw[5] = v4_address >> 32;

   const uint64_t v6_address =
      __gen_address(data, &dw[6], values->MFXIndirectMVObjectAddress, 0, 0, 63);
   dw[6] = v6_address;
   dw[7] = v6_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[8], &values->MFXIndirectMVObjectAttributes);

   const uint64_t v9_address =
      __gen_address(data, &dw[9], values->MFXIndirectMVObjectUpperBound, 0, 0, 63);
   dw[9] = v9_address;
   dw[10] = v9_address >> 32;

   const uint64_t v11_address =
      __gen_address(data, &dw[11], values->MFDIndirectITCOEFFObjectAddress, 0, 0, 63);
   dw[11] = v11_address;
   dw[12] = v11_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[13], &values->MFDIndirectITCOEFFObjectAttributes);

   const uint64_t v14_address =
      __gen_address(data, &dw[14], values->MFDIndirectITCOEFFObjectUpperBound, 0, 0, 63);
   dw[14] = v14_address;
   dw[15] = v14_address >> 32;

   const uint64_t v16_address =
      __gen_address(data, &dw[16], values->MFDIndirectITDBLKObjectAddress, 0, 0, 63);
   dw[16] = v16_address;
   dw[17] = v16_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[18], &values->MFDIndirectITDBLKObjectAttributes);

   const uint64_t v19_address =
      __gen_address(data, &dw[19], values->MFDIndirectITDBLKObjectUpperBound, 0, 0, 63);
   dw[19] = v19_address;
   dw[20] = v19_address >> 32;

   const uint64_t v21_address =
      __gen_address(data, &dw[21], values->MFCIndirectPAKBSEObjectAddress, 0, 0, 63);
   dw[21] = v21_address;
   dw[22] = v21_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[23], &values->MFCIndirectPAKBSEObjectAttributes);

   const uint64_t v24_address =
      __gen_address(data, &dw[24], values->MFCIndirectPAKBSEObjectUpperBound, 0, 0, 63);
   dw[24] = v24_address;
   dw[25] = v24_address >> 32;
}

#define GFX9_MFX_JPEG_HUFF_TABLE_STATE_length    831
#define GFX9_MFX_JPEG_HUFF_TABLE_STATE_length_bias      2
#define GFX9_MFX_JPEG_HUFF_TABLE_STATE_header   \
   .DWordLength                         =    829,  \
   .SubOpcodeB                          =      2,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_JPEG_HUFF_TABLE_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             HuffmanTableID;
   uint32_t                             DC_BITS[12];
   uint32_t                             DC_HUFFVAL[12];
   uint32_t                             AC_BITS[16];
   uint32_t                             AC_HUFFVAL[160];
   uint32_t                             AC_HUFFVAL2[2];
};

static inline __attribute__((always_inline)) void
GFX9_MFX_JPEG_HUFF_TABLE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                    __attribute__((unused)) void * restrict dst,
                                    __attribute__((unused)) const struct GFX9_MFX_JPEG_HUFF_TABLE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->HuffmanTableID, 0, 0);

   dw[2] =
      util_bitpack_uint(values->DC_BITS[0], 0, 7) |
      util_bitpack_uint(values->DC_BITS[1], 8, 15) |
      util_bitpack_uint(values->DC_BITS[2], 16, 23) |
      util_bitpack_uint(values->DC_BITS[3], 24, 31);

   dw[3] =
      util_bitpack_uint(values->DC_BITS[4], 0, 7) |
      util_bitpack_uint(values->DC_BITS[5], 8, 15) |
      util_bitpack_uint(values->DC_BITS[6], 16, 23) |
      util_bitpack_uint(values->DC_BITS[7], 24, 31);

   dw[4] =
      util_bitpack_uint(values->DC_BITS[8], 0, 7) |
      util_bitpack_uint(values->DC_BITS[9], 8, 15) |
      util_bitpack_uint(values->DC_BITS[10], 16, 23) |
      util_bitpack_uint(values->DC_BITS[11], 24, 31);

   dw[5] =
      util_bitpack_uint(values->DC_HUFFVAL[0], 0, 7) |
      util_bitpack_uint(values->DC_HUFFVAL[1], 8, 15) |
      util_bitpack_uint(values->DC_HUFFVAL[2], 16, 23) |
      util_bitpack_uint(values->DC_HUFFVAL[3], 24, 31);

   dw[6] =
      util_bitpack_uint(values->DC_HUFFVAL[4], 0, 7) |
      util_bitpack_uint(values->DC_HUFFVAL[5], 8, 15) |
      util_bitpack_uint(values->DC_HUFFVAL[6], 16, 23) |
      util_bitpack_uint(values->DC_HUFFVAL[7], 24, 31);

   dw[7] =
      util_bitpack_uint(values->DC_HUFFVAL[8], 0, 7) |
      util_bitpack_uint(values->DC_HUFFVAL[9], 8, 15) |
      util_bitpack_uint(values->DC_HUFFVAL[10], 16, 23) |
      util_bitpack_uint(values->DC_HUFFVAL[11], 24, 31);

   const uint64_t v8 =
      util_bitpack_uint(values->AC_BITS[0], 0, 15) |
      util_bitpack_uint(values->AC_BITS[1], 8, 23) |
      util_bitpack_uint(values->AC_BITS[2], 16, 31) |
      util_bitpack_uint(values->AC_BITS[3], 24, 39) |
      util_bitpack_uint(values->AC_BITS[4], 32, 47) |
      util_bitpack_uint(values->AC_BITS[5], 40, 55) |
      util_bitpack_uint(values->AC_BITS[6], 48, 63) |
      util_bitpack_uint(values->AC_BITS[7], 56, 71) |
      util_bitpack_uint(values->AC_BITS[8], 64, 79) |
      util_bitpack_uint(values->AC_BITS[9], 72, 87) |
      util_bitpack_uint(values->AC_BITS[10], 80, 95) |
      util_bitpack_uint(values->AC_BITS[11], 88, 103) |
      util_bitpack_uint(values->AC_BITS[12], 96, 111) |
      util_bitpack_uint(values->AC_BITS[13], 104, 119) |
      util_bitpack_uint(values->AC_BITS[14], 112, 127) |
      util_bitpack_uint(values->AC_BITS[15], 120, 135) |
      util_bitpack_uint(values->AC_HUFFVAL[0], 128, 135) |
      util_bitpack_uint(values->AC_HUFFVAL[1], 136, 143) |
      util_bitpack_uint(values->AC_HUFFVAL[2], 144, 151) |
      util_bitpack_uint(values->AC_HUFFVAL[3], 152, 159);
   dw[8] = v8;
   dw[9] = v8 >> 32;

   dw[13] =
      util_bitpack_uint(values->AC_HUFFVAL[4], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[5], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[6], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[7], 24, 31);

   dw[14] =
      util_bitpack_uint(values->AC_HUFFVAL[8], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[9], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[10], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[11], 24, 31);

   dw[15] =
      util_bitpack_uint(values->AC_HUFFVAL[12], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[13], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[14], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[15], 24, 31);

   dw[16] =
      util_bitpack_uint(values->AC_HUFFVAL[16], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[17], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[18], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[19], 24, 31);

   dw[17] =
      util_bitpack_uint(values->AC_HUFFVAL[20], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[21], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[22], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[23], 24, 31);

   dw[18] =
      util_bitpack_uint(values->AC_HUFFVAL[24], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[25], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[26], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[27], 24, 31);

   dw[19] =
      util_bitpack_uint(values->AC_HUFFVAL[28], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[29], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[30], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[31], 24, 31);

   dw[20] =
      util_bitpack_uint(values->AC_HUFFVAL[32], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[33], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[34], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[35], 24, 31);

   dw[21] =
      util_bitpack_uint(values->AC_HUFFVAL[36], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[37], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[38], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[39], 24, 31);

   dw[22] =
      util_bitpack_uint(values->AC_HUFFVAL[40], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[41], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[42], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[43], 24, 31);

   dw[23] =
      util_bitpack_uint(values->AC_HUFFVAL[44], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[45], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[46], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[47], 24, 31);

   dw[24] =
      util_bitpack_uint(values->AC_HUFFVAL[48], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[49], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[50], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[51], 24, 31);

   dw[25] =
      util_bitpack_uint(values->AC_HUFFVAL[52], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[53], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[54], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[55], 24, 31);

   dw[26] =
      util_bitpack_uint(values->AC_HUFFVAL[56], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[57], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[58], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[59], 24, 31);

   dw[27] =
      util_bitpack_uint(values->AC_HUFFVAL[60], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[61], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[62], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[63], 24, 31);

   dw[28] =
      util_bitpack_uint(values->AC_HUFFVAL[64], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[65], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[66], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[67], 24, 31);

   dw[29] =
      util_bitpack_uint(values->AC_HUFFVAL[68], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[69], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[70], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[71], 24, 31);

   dw[30] =
      util_bitpack_uint(values->AC_HUFFVAL[72], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[73], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[74], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[75], 24, 31);

   dw[31] =
      util_bitpack_uint(values->AC_HUFFVAL[76], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[77], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[78], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[79], 24, 31);

   dw[32] =
      util_bitpack_uint(values->AC_HUFFVAL[80], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[81], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[82], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[83], 24, 31);

   dw[33] =
      util_bitpack_uint(values->AC_HUFFVAL[84], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[85], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[86], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[87], 24, 31);

   dw[34] =
      util_bitpack_uint(values->AC_HUFFVAL[88], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[89], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[90], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[91], 24, 31);

   dw[35] =
      util_bitpack_uint(values->AC_HUFFVAL[92], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[93], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[94], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[95], 24, 31);

   dw[36] =
      util_bitpack_uint(values->AC_HUFFVAL[96], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[97], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[98], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[99], 24, 31);

   dw[37] =
      util_bitpack_uint(values->AC_HUFFVAL[100], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[101], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[102], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[103], 24, 31);

   dw[38] =
      util_bitpack_uint(values->AC_HUFFVAL[104], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[105], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[106], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[107], 24, 31);

   dw[39] =
      util_bitpack_uint(values->AC_HUFFVAL[108], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[109], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[110], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[111], 24, 31);

   dw[40] =
      util_bitpack_uint(values->AC_HUFFVAL[112], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[113], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[114], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[115], 24, 31);

   dw[41] =
      util_bitpack_uint(values->AC_HUFFVAL[116], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[117], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[118], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[119], 24, 31);

   dw[42] =
      util_bitpack_uint(values->AC_HUFFVAL[120], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[121], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[122], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[123], 24, 31);

   dw[43] =
      util_bitpack_uint(values->AC_HUFFVAL[124], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[125], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[126], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[127], 24, 31);

   dw[44] =
      util_bitpack_uint(values->AC_HUFFVAL[128], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[129], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[130], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[131], 24, 31);

   dw[45] =
      util_bitpack_uint(values->AC_HUFFVAL[132], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[133], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[134], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[135], 24, 31);

   dw[46] =
      util_bitpack_uint(values->AC_HUFFVAL[136], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[137], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[138], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[139], 24, 31);

   dw[47] =
      util_bitpack_uint(values->AC_HUFFVAL[140], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[141], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[142], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[143], 24, 31);

   dw[48] =
      util_bitpack_uint(values->AC_HUFFVAL[144], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[145], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[146], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[147], 24, 31);

   dw[49] =
      util_bitpack_uint(values->AC_HUFFVAL[148], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[149], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[150], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[151], 24, 31);

   dw[50] =
      util_bitpack_uint(values->AC_HUFFVAL[152], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[153], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[154], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[155], 24, 31);

   dw[51] =
      util_bitpack_uint(values->AC_HUFFVAL[156], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL[157], 8, 15) |
      util_bitpack_uint(values->AC_HUFFVAL[158], 16, 23) |
      util_bitpack_uint(values->AC_HUFFVAL[159], 24, 31);

   dw[52] =
      util_bitpack_uint(values->AC_HUFFVAL2[0], 0, 7) |
      util_bitpack_uint(values->AC_HUFFVAL2[1], 8, 15);

   dw[53] = 0;

   dw[54] = 0;

   dw[55] = 0;

   dw[56] = 0;

   dw[57] = 0;

   dw[58] = 0;

   dw[59] = 0;

   dw[60] = 0;

   dw[61] = 0;

   dw[62] = 0;

   dw[63] = 0;

   dw[64] = 0;

   dw[65] = 0;

   dw[66] = 0;

   dw[67] = 0;

   dw[68] = 0;

   dw[69] = 0;

   dw[70] = 0;

   dw[71] = 0;

   dw[72] = 0;

   dw[73] = 0;

   dw[74] = 0;

   dw[75] = 0;

   dw[76] = 0;

   dw[77] = 0;

   dw[78] = 0;

   dw[79] = 0;

   dw[80] = 0;

   dw[81] = 0;

   dw[82] = 0;

   dw[83] = 0;

   dw[84] = 0;

   dw[85] = 0;

   dw[86] = 0;

   dw[87] = 0;

   dw[88] = 0;

   dw[89] = 0;

   dw[90] = 0;

   dw[91] = 0;

   dw[92] = 0;

   dw[93] = 0;

   dw[94] = 0;

   dw[95] = 0;

   dw[96] = 0;

   dw[97] = 0;

   dw[98] = 0;

   dw[99] = 0;

   dw[100] = 0;

   dw[101] = 0;

   dw[102] = 0;

   dw[103] = 0;

   dw[104] = 0;

   dw[105] = 0;

   dw[106] = 0;

   dw[107] = 0;

   dw[108] = 0;

   dw[109] = 0;

   dw[110] = 0;

   dw[111] = 0;

   dw[112] = 0;

   dw[113] = 0;

   dw[114] = 0;

   dw[115] = 0;

   dw[116] = 0;

   dw[117] = 0;

   dw[118] = 0;

   dw[119] = 0;

   dw[120] = 0;

   dw[121] = 0;

   dw[122] = 0;

   dw[123] = 0;

   dw[124] = 0;

   dw[125] = 0;

   dw[126] = 0;

   dw[127] = 0;

   dw[128] = 0;

   dw[129] = 0;

   dw[130] = 0;

   dw[131] = 0;

   dw[132] = 0;

   dw[133] = 0;

   dw[134] = 0;

   dw[135] = 0;

   dw[136] = 0;

   dw[137] = 0;

   dw[138] = 0;

   dw[139] = 0;

   dw[140] = 0;

   dw[141] = 0;

   dw[142] = 0;

   dw[143] = 0;

   dw[144] = 0;

   dw[145] = 0;

   dw[146] = 0;

   dw[147] = 0;

   dw[148] = 0;

   dw[149] = 0;

   dw[150] = 0;

   dw[151] = 0;

   dw[152] = 0;

   dw[153] = 0;

   dw[154] = 0;

   dw[155] = 0;

   dw[156] = 0;

   dw[157] = 0;

   dw[158] = 0;

   dw[159] = 0;

   dw[160] = 0;

   dw[161] = 0;

   dw[162] = 0;

   dw[163] = 0;

   dw[164] = 0;

   dw[165] = 0;

   dw[166] = 0;

   dw[167] = 0;

   dw[168] = 0;

   dw[169] = 0;

   dw[170] = 0;

   dw[171] = 0;

   dw[172] = 0;

   dw[173] = 0;

   dw[174] = 0;

   dw[175] = 0;

   dw[176] = 0;

   dw[177] = 0;

   dw[178] = 0;

   dw[179] = 0;

   dw[180] = 0;

   dw[181] = 0;

   dw[182] = 0;

   dw[183] = 0;

   dw[184] = 0;

   dw[185] = 0;

   dw[186] = 0;

   dw[187] = 0;

   dw[188] = 0;

   dw[189] = 0;

   dw[190] = 0;

   dw[191] = 0;

   dw[192] = 0;

   dw[193] = 0;

   dw[194] = 0;

   dw[195] = 0;

   dw[196] = 0;

   dw[197] = 0;

   dw[198] = 0;

   dw[199] = 0;

   dw[200] = 0;

   dw[201] = 0;

   dw[202] = 0;

   dw[203] = 0;

   dw[204] = 0;

   dw[205] = 0;

   dw[206] = 0;

   dw[207] = 0;

   dw[208] = 0;

   dw[209] = 0;

   dw[210] = 0;

   dw[211] = 0;

   dw[212] = 0;

   dw[213] = 0;

   dw[214] = 0;

   dw[215] = 0;

   dw[216] = 0;

   dw[217] = 0;

   dw[218] = 0;

   dw[219] = 0;

   dw[220] = 0;

   dw[221] = 0;

   dw[222] = 0;

   dw[223] = 0;

   dw[224] = 0;

   dw[225] = 0;

   dw[226] = 0;

   dw[227] = 0;

   dw[228] = 0;

   dw[229] = 0;

   dw[230] = 0;

   dw[231] = 0;

   dw[232] = 0;

   dw[233] = 0;

   dw[234] = 0;

   dw[235] = 0;

   dw[236] = 0;

   dw[237] = 0;

   dw[238] = 0;

   dw[239] = 0;

   dw[240] = 0;

   dw[241] = 0;

   dw[242] = 0;

   dw[243] = 0;

   dw[244] = 0;

   dw[245] = 0;

   dw[246] = 0;

   dw[247] = 0;

   dw[248] = 0;

   dw[249] = 0;

   dw[250] = 0;

   dw[251] = 0;

   dw[252] = 0;

   dw[253] = 0;

   dw[254] = 0;

   dw[255] = 0;

   dw[256] = 0;

   dw[257] = 0;

   dw[258] = 0;

   dw[259] = 0;

   dw[260] = 0;

   dw[261] = 0;

   dw[262] = 0;

   dw[263] = 0;

   dw[264] = 0;

   dw[265] = 0;

   dw[266] = 0;

   dw[267] = 0;

   dw[268] = 0;

   dw[269] = 0;

   dw[270] = 0;

   dw[271] = 0;

   dw[272] = 0;

   dw[273] = 0;

   dw[274] = 0;

   dw[275] = 0;

   dw[276] = 0;

   dw[277] = 0;

   dw[278] = 0;

   dw[279] = 0;

   dw[280] = 0;

   dw[281] = 0;

   dw[282] = 0;

   dw[283] = 0;

   dw[284] = 0;

   dw[285] = 0;

   dw[286] = 0;

   dw[287] = 0;

   dw[288] = 0;

   dw[289] = 0;

   dw[290] = 0;

   dw[291] = 0;

   dw[292] = 0;

   dw[293] = 0;

   dw[294] = 0;

   dw[295] = 0;

   dw[296] = 0;

   dw[297] = 0;

   dw[298] = 0;

   dw[299] = 0;

   dw[300] = 0;

   dw[301] = 0;

   dw[302] = 0;

   dw[303] = 0;

   dw[304] = 0;

   dw[305] = 0;

   dw[306] = 0;

   dw[307] = 0;

   dw[308] = 0;

   dw[309] = 0;

   dw[310] = 0;

   dw[311] = 0;

   dw[312] = 0;

   dw[313] = 0;

   dw[314] = 0;

   dw[315] = 0;

   dw[316] = 0;

   dw[317] = 0;

   dw[318] = 0;

   dw[319] = 0;

   dw[320] = 0;

   dw[321] = 0;

   dw[322] = 0;

   dw[323] = 0;

   dw[324] = 0;

   dw[325] = 0;

   dw[326] = 0;

   dw[327] = 0;

   dw[328] = 0;

   dw[329] = 0;

   dw[330] = 0;

   dw[331] = 0;

   dw[332] = 0;

   dw[333] = 0;

   dw[334] = 0;

   dw[335] = 0;

   dw[336] = 0;

   dw[337] = 0;

   dw[338] = 0;

   dw[339] = 0;

   dw[340] = 0;

   dw[341] = 0;

   dw[342] = 0;

   dw[343] = 0;

   dw[344] = 0;

   dw[345] = 0;

   dw[346] = 0;

   dw[347] = 0;

   dw[348] = 0;

   dw[349] = 0;

   dw[350] = 0;

   dw[351] = 0;

   dw[352] = 0;

   dw[353] = 0;

   dw[354] = 0;

   dw[355] = 0;

   dw[356] = 0;

   dw[357] = 0;

   dw[358] = 0;

   dw[359] = 0;

   dw[360] = 0;

   dw[361] = 0;

   dw[362] = 0;

   dw[363] = 0;

   dw[364] = 0;

   dw[365] = 0;

   dw[366] = 0;

   dw[367] = 0;

   dw[368] = 0;

   dw[369] = 0;

   dw[370] = 0;

   dw[371] = 0;

   dw[372] = 0;

   dw[373] = 0;

   dw[374] = 0;

   dw[375] = 0;

   dw[376] = 0;

   dw[377] = 0;

   dw[378] = 0;

   dw[379] = 0;

   dw[380] = 0;

   dw[381] = 0;

   dw[382] = 0;

   dw[383] = 0;

   dw[384] = 0;

   dw[385] = 0;

   dw[386] = 0;

   dw[387] = 0;

   dw[388] = 0;

   dw[389] = 0;

   dw[390] = 0;

   dw[391] = 0;

   dw[392] = 0;

   dw[393] = 0;

   dw[394] = 0;

   dw[395] = 0;

   dw[396] = 0;

   dw[397] = 0;

   dw[398] = 0;

   dw[399] = 0;

   dw[400] = 0;

   dw[401] = 0;

   dw[402] = 0;

   dw[403] = 0;

   dw[404] = 0;

   dw[405] = 0;

   dw[406] = 0;

   dw[407] = 0;

   dw[408] = 0;

   dw[409] = 0;

   dw[410] = 0;

   dw[411] = 0;

   dw[412] = 0;

   dw[413] = 0;

   dw[414] = 0;

   dw[415] = 0;

   dw[416] = 0;

   dw[417] = 0;

   dw[418] = 0;

   dw[419] = 0;

   dw[420] = 0;

   dw[421] = 0;

   dw[422] = 0;

   dw[423] = 0;

   dw[424] = 0;

   dw[425] = 0;

   dw[426] = 0;

   dw[427] = 0;

   dw[428] = 0;

   dw[429] = 0;

   dw[430] = 0;

   dw[431] = 0;

   dw[432] = 0;

   dw[433] = 0;

   dw[434] = 0;

   dw[435] = 0;

   dw[436] = 0;

   dw[437] = 0;

   dw[438] = 0;

   dw[439] = 0;

   dw[440] = 0;

   dw[441] = 0;

   dw[442] = 0;

   dw[443] = 0;

   dw[444] = 0;

   dw[445] = 0;

   dw[446] = 0;

   dw[447] = 0;

   dw[448] = 0;

   dw[449] = 0;

   dw[450] = 0;

   dw[451] = 0;

   dw[452] = 0;

   dw[453] = 0;

   dw[454] = 0;

   dw[455] = 0;

   dw[456] = 0;

   dw[457] = 0;

   dw[458] = 0;

   dw[459] = 0;

   dw[460] = 0;

   dw[461] = 0;

   dw[462] = 0;

   dw[463] = 0;

   dw[464] = 0;

   dw[465] = 0;

   dw[466] = 0;

   dw[467] = 0;

   dw[468] = 0;

   dw[469] = 0;

   dw[470] = 0;

   dw[471] = 0;

   dw[472] = 0;

   dw[473] = 0;

   dw[474] = 0;

   dw[475] = 0;

   dw[476] = 0;

   dw[477] = 0;

   dw[478] = 0;

   dw[479] = 0;

   dw[480] = 0;

   dw[481] = 0;

   dw[482] = 0;

   dw[483] = 0;

   dw[484] = 0;

   dw[485] = 0;

   dw[486] = 0;

   dw[487] = 0;

   dw[488] = 0;

   dw[489] = 0;

   dw[490] = 0;

   dw[491] = 0;

   dw[492] = 0;

   dw[493] = 0;

   dw[494] = 0;

   dw[495] = 0;

   dw[496] = 0;

   dw[497] = 0;

   dw[498] = 0;

   dw[499] = 0;

   dw[500] = 0;

   dw[501] = 0;

   dw[502] = 0;

   dw[503] = 0;

   dw[504] = 0;

   dw[505] = 0;

   dw[506] = 0;

   dw[507] = 0;

   dw[508] = 0;

   dw[509] = 0;

   dw[510] = 0;

   dw[511] = 0;

   dw[512] = 0;

   dw[513] = 0;

   dw[514] = 0;

   dw[515] = 0;

   dw[516] = 0;

   dw[517] = 0;

   dw[518] = 0;

   dw[519] = 0;

   dw[520] = 0;

   dw[521] = 0;

   dw[522] = 0;

   dw[523] = 0;

   dw[524] = 0;

   dw[525] = 0;

   dw[526] = 0;

   dw[527] = 0;

   dw[528] = 0;

   dw[529] = 0;

   dw[530] = 0;

   dw[531] = 0;

   dw[532] = 0;

   dw[533] = 0;

   dw[534] = 0;

   dw[535] = 0;

   dw[536] = 0;

   dw[537] = 0;

   dw[538] = 0;

   dw[539] = 0;

   dw[540] = 0;

   dw[541] = 0;

   dw[542] = 0;

   dw[543] = 0;

   dw[544] = 0;

   dw[545] = 0;

   dw[546] = 0;

   dw[547] = 0;

   dw[548] = 0;

   dw[549] = 0;

   dw[550] = 0;

   dw[551] = 0;

   dw[552] = 0;

   dw[553] = 0;

   dw[554] = 0;

   dw[555] = 0;

   dw[556] = 0;

   dw[557] = 0;

   dw[558] = 0;

   dw[559] = 0;

   dw[560] = 0;

   dw[561] = 0;

   dw[562] = 0;

   dw[563] = 0;

   dw[564] = 0;

   dw[565] = 0;

   dw[566] = 0;

   dw[567] = 0;

   dw[568] = 0;

   dw[569] = 0;

   dw[570] = 0;

   dw[571] = 0;

   dw[572] = 0;

   dw[573] = 0;

   dw[574] = 0;

   dw[575] = 0;

   dw[576] = 0;

   dw[577] = 0;

   dw[578] = 0;

   dw[579] = 0;

   dw[580] = 0;

   dw[581] = 0;

   dw[582] = 0;

   dw[583] = 0;

   dw[584] = 0;

   dw[585] = 0;

   dw[586] = 0;

   dw[587] = 0;

   dw[588] = 0;

   dw[589] = 0;

   dw[590] = 0;

   dw[591] = 0;

   dw[592] = 0;

   dw[593] = 0;

   dw[594] = 0;

   dw[595] = 0;

   dw[596] = 0;

   dw[597] = 0;

   dw[598] = 0;

   dw[599] = 0;

   dw[600] = 0;

   dw[601] = 0;

   dw[602] = 0;

   dw[603] = 0;

   dw[604] = 0;

   dw[605] = 0;

   dw[606] = 0;

   dw[607] = 0;

   dw[608] = 0;

   dw[609] = 0;

   dw[610] = 0;

   dw[611] = 0;

   dw[612] = 0;

   dw[613] = 0;

   dw[614] = 0;

   dw[615] = 0;

   dw[616] = 0;

   dw[617] = 0;

   dw[618] = 0;

   dw[619] = 0;

   dw[620] = 0;

   dw[621] = 0;

   dw[622] = 0;

   dw[623] = 0;

   dw[624] = 0;

   dw[625] = 0;

   dw[626] = 0;

   dw[627] = 0;

   dw[628] = 0;

   dw[629] = 0;

   dw[630] = 0;

   dw[631] = 0;

   dw[632] = 0;

   dw[633] = 0;

   dw[634] = 0;

   dw[635] = 0;

   dw[636] = 0;

   dw[637] = 0;

   dw[638] = 0;

   dw[639] = 0;

   dw[640] = 0;

   dw[641] = 0;

   dw[642] = 0;

   dw[643] = 0;

   dw[644] = 0;

   dw[645] = 0;

   dw[646] = 0;

   dw[647] = 0;

   dw[648] = 0;

   dw[649] = 0;

   dw[650] = 0;

   dw[651] = 0;

   dw[652] = 0;

   dw[653] = 0;

   dw[654] = 0;

   dw[655] = 0;

   dw[656] = 0;

   dw[657] = 0;

   dw[658] = 0;

   dw[659] = 0;

   dw[660] = 0;

   dw[661] = 0;

   dw[662] = 0;

   dw[663] = 0;

   dw[664] = 0;

   dw[665] = 0;

   dw[666] = 0;

   dw[667] = 0;

   dw[668] = 0;

   dw[669] = 0;

   dw[670] = 0;

   dw[671] = 0;

   dw[672] = 0;

   dw[673] = 0;

   dw[674] = 0;

   dw[675] = 0;

   dw[676] = 0;

   dw[677] = 0;

   dw[678] = 0;

   dw[679] = 0;

   dw[680] = 0;

   dw[681] = 0;

   dw[682] = 0;

   dw[683] = 0;

   dw[684] = 0;

   dw[685] = 0;

   dw[686] = 0;

   dw[687] = 0;

   dw[688] = 0;

   dw[689] = 0;

   dw[690] = 0;

   dw[691] = 0;

   dw[692] = 0;

   dw[693] = 0;

   dw[694] = 0;

   dw[695] = 0;

   dw[696] = 0;

   dw[697] = 0;

   dw[698] = 0;

   dw[699] = 0;

   dw[700] = 0;

   dw[701] = 0;

   dw[702] = 0;

   dw[703] = 0;

   dw[704] = 0;

   dw[705] = 0;

   dw[706] = 0;

   dw[707] = 0;

   dw[708] = 0;

   dw[709] = 0;

   dw[710] = 0;

   dw[711] = 0;

   dw[712] = 0;

   dw[713] = 0;

   dw[714] = 0;

   dw[715] = 0;

   dw[716] = 0;

   dw[717] = 0;

   dw[718] = 0;

   dw[719] = 0;

   dw[720] = 0;

   dw[721] = 0;

   dw[722] = 0;

   dw[723] = 0;

   dw[724] = 0;

   dw[725] = 0;

   dw[726] = 0;

   dw[727] = 0;

   dw[728] = 0;

   dw[729] = 0;

   dw[730] = 0;

   dw[731] = 0;

   dw[732] = 0;

   dw[733] = 0;

   dw[734] = 0;

   dw[735] = 0;

   dw[736] = 0;

   dw[737] = 0;

   dw[738] = 0;

   dw[739] = 0;

   dw[740] = 0;

   dw[741] = 0;

   dw[742] = 0;

   dw[743] = 0;

   dw[744] = 0;

   dw[745] = 0;

   dw[746] = 0;

   dw[747] = 0;

   dw[748] = 0;

   dw[749] = 0;

   dw[750] = 0;

   dw[751] = 0;

   dw[752] = 0;

   dw[753] = 0;

   dw[754] = 0;

   dw[755] = 0;

   dw[756] = 0;

   dw[757] = 0;

   dw[758] = 0;

   dw[759] = 0;

   dw[760] = 0;

   dw[761] = 0;

   dw[762] = 0;

   dw[763] = 0;

   dw[764] = 0;

   dw[765] = 0;

   dw[766] = 0;

   dw[767] = 0;

   dw[768] = 0;

   dw[769] = 0;

   dw[770] = 0;

   dw[771] = 0;

   dw[772] = 0;

   dw[773] = 0;

   dw[774] = 0;

   dw[775] = 0;

   dw[776] = 0;

   dw[777] = 0;

   dw[778] = 0;

   dw[779] = 0;

   dw[780] = 0;

   dw[781] = 0;

   dw[782] = 0;

   dw[783] = 0;

   dw[784] = 0;

   dw[785] = 0;

   dw[786] = 0;

   dw[787] = 0;

   dw[788] = 0;

   dw[789] = 0;

   dw[790] = 0;

   dw[791] = 0;

   dw[792] = 0;

   dw[793] = 0;

   dw[794] = 0;

   dw[795] = 0;

   dw[796] = 0;

   dw[797] = 0;

   dw[798] = 0;

   dw[799] = 0;

   dw[800] = 0;

   dw[801] = 0;

   dw[802] = 0;

   dw[803] = 0;

   dw[804] = 0;

   dw[805] = 0;

   dw[806] = 0;

   dw[807] = 0;

   dw[808] = 0;

   dw[809] = 0;

   dw[810] = 0;

   dw[811] = 0;

   dw[812] = 0;

   dw[813] = 0;

   dw[814] = 0;

   dw[815] = 0;

   dw[816] = 0;

   dw[817] = 0;

   dw[818] = 0;

   dw[819] = 0;

   dw[820] = 0;

   dw[821] = 0;

   dw[822] = 0;

   dw[823] = 0;

   dw[824] = 0;

   dw[825] = 0;

   dw[826] = 0;

   dw[827] = 0;

   dw[828] = 0;

   dw[829] = 0;

   dw[830] = 0;
}

#define GFX9_MFX_JPEG_PIC_STATE_length         3
#define GFX9_MFX_JPEG_PIC_STATE_length_bias      2
#define GFX9_MFX_JPEG_PIC_STATE_header          \
   .DWordLength                         =      1,  \
   .SubOpcodeB                          =      0,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      7,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_JPEG_PIC_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             InputFormatYUV;
   uint32_t                             OutputMCUStructure;
#define MCU_YUV400                               0
#define MCU_YUV420                               1
#define MCU_YUV422H_2Y                           2
#define MCU_RGB                                  3
   uint32_t                             Rotation;
   uint32_t                             OutputFormatYUV;
   uint32_t                             InputSurfaceFormatYUV;
#define IS_NV12                                  1
#define IS_UYVY                                  2
#define IS_YUY2                                  3
#define IS_Y8                                    4
#define IS_RGB                                   5
   uint32_t                             AverageDownSampling;
   bool                                 VerticalDownSamplingEnable;
   bool                                 HorizontalDownSamplingEnable;
   bool                                 VerticalUpSamplingEnable;
   uint32_t                             PixelsInVerticalLastMCU;
   uint32_t                             PixelsInHorizontalLastMCU;
   uint32_t                             FrameWidthInBlocks;
   uint32_t                             RoundingQuant;
   uint32_t                             FrameHeightInBlocks;
   uint32_t                             OutputPixelNormalize;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_JPEG_PIC_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                             __attribute__((unused)) void * restrict dst,
                             __attribute__((unused)) const struct GFX9_MFX_JPEG_PIC_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->InputFormatYUV, 0, 2) |
      util_bitpack_uint(values->OutputMCUStructure, 0, 2) |
      util_bitpack_uint(values->Rotation, 4, 5) |
      util_bitpack_uint(values->OutputFormatYUV, 8, 11) |
      util_bitpack_uint(values->InputSurfaceFormatYUV, 8, 11) |
      util_bitpack_uint(values->AverageDownSampling, 16, 16) |
      util_bitpack_uint(values->VerticalDownSamplingEnable, 17, 17) |
      util_bitpack_uint(values->HorizontalDownSamplingEnable, 18, 18) |
      util_bitpack_uint(values->VerticalUpSamplingEnable, 20, 20) |
      util_bitpack_uint(values->PixelsInVerticalLastMCU, 21, 25) |
      util_bitpack_uint(values->PixelsInHorizontalLastMCU, 26, 30);

   dw[2] =
      util_bitpack_uint(values->FrameWidthInBlocks, 0, 12) |
      util_bitpack_uint(values->RoundingQuant, 13, 15) |
      util_bitpack_uint(values->FrameHeightInBlocks, 16, 28) |
      util_bitpack_uint(values->OutputPixelNormalize, 29, 29);
}

#define GFX9_MFX_MPEG2_PIC_STATE_length        2
#define GFX9_MFX_MPEG2_PIC_STATE_length_bias      2
#define GFX9_MFX_MPEG2_PIC_STATE_header         \
   .DWordLength                         =      0,  \
   .SubOpcodeB                          =      0,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      3,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_MPEG2_PIC_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             ScanOrder;
#define MPEG_ZIGZAG_SCAN                         0
#define MPEG_ALTERNATE_VERTICAL_SCAN             1
   uint32_t                             IntraVLCFormat;
   uint32_t                             QuantizerScaleType;
#define MPEG_QSCALE_LINEAR                       0
#define MPEG_QSCALE_NONLINEAR                    1
   bool                                 ConcealmentMV;
   uint32_t                             FramePredictionFrameDCT;
   bool                                 TopFieldFirst;
   uint32_t                             PictureStructure;
#define MPEG_TOP_FIELD                           1
#define MPEG_BOTTOM_FIELD                        2
#define MPEG_FRAME                               3
   uint32_t                             IntraDCPrecision;
   uint32_t                             F_code00;
   uint32_t                             F_code01;
   uint32_t                             F_code10;
   uint32_t                             F_code11;
   bool                                 DisableMismatch;
   bool                                 MismatchControlDisable;
   uint32_t                             PictureCodingType;
#define MPEG_I_PICTURE                           1
#define MPEG_P_PICTURE                           2
#define MPEG_B_PICTURE                           3
   bool                                 LoadBitstreamPointerPerSlice;
   uint32_t                             PBSlicePredictedMVOverride;
#define Predicted                                0
#define ZERO                                     1
   uint32_t                             PBSlicePredictedBidirectionMVTypeOverride;
#define MPEG2_MVTO_BID                           0
#define MPEG2_MVTO_RESERVED                      1
#define MPEG2_MVTO_FWD                           2
#define MPEG2_MVTO_BWD                           3
   uint32_t                             PBSliceConcealmentMode;
#define MPEG2_CM_INTER                           0
#define MPEG2_CM_LEFT                            1
#define MPEG2_CM_ZERO                            2
#define MPEG2_CM_INTRA                           3
   uint32_t                             ISliceConcealmentMode;
#define MPEG2_CM_IntraConcealment                0
#define MPEG2_CM_InterConcealment                1
   uint32_t                             FrameWidthInMBs;
   uint32_t                             FrameHeightInMBs;
   bool                                 SliceConcealmentDisable;
   uint32_t                             RoundIntraDC;
   uint32_t                             RoundInterDC;
   uint32_t                             RoundIntraAC;
   uint32_t                             RoundInterAC;
   uint32_t                             MinimumFrameSize;
   uint32_t                             IntraMBMaxBitControl;
   uint32_t                             InterMBMaxBitControl;
   uint32_t                             FrameBitrateMaxReport;
   uint32_t                             FrameBitrateMinReport;
   uint32_t                             MBRateControlMask;
   uint32_t                             MinimumFrameSizeUnits;
#define MPEG2_MFSU_Compatibilitymode             0
#define MPEG2_MFSU_16bytes                       1
#define MPEG2_MFSU_4Kb                           2
#define MPEG2_MFSU_16Kb                          3
   uint32_t                             InterMBForceCBPtoZeroControl;
   uint32_t                             FrameSizeControl;
   uint32_t                             IntraMBConformanceMaxSize;
   uint32_t                             InterMBConformanceMaxSize;
   int32_t                              SliceDeltaQPMax0;
   int32_t                              SliceDeltaQPMax1;
   int32_t                              SliceDeltaQPMax2;
   int32_t                              SliceDeltaQPMax3;
   int32_t                              SliceDeltaQPMin0;
   int32_t                              SliceDeltaQPMin1;
   int32_t                              SliceDeltaQPMin2;
   int32_t                              SliceDeltaQPMin3;
   uint32_t                             FrameBitrateMin;
   uint32_t                             FrameBitrateMinUnitMode;
#define Compatibilitymode                        0
#define NewMode                                  1
   uint32_t                             FrameBitrateMinUnit;
   uint32_t                             FrameBitrateMax;
   uint32_t                             FrameBitrateMaxUnitMode;
#define Compatibilitymode                        0
#define Newmode                                  1
   uint32_t                             FrameBitrateMaxUnit;
   uint32_t                             FrameBitrateMinDelta;
   uint32_t                             FrameBitrateMaxDelta;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_MPEG2_PIC_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_MFX_MPEG2_PIC_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ScanOrder, 6, 6) |
      util_bitpack_uint(values->IntraVLCFormat, 7, 7) |
      util_bitpack_uint(values->QuantizerScaleType, 8, 8) |
      util_bitpack_uint(values->ConcealmentMV, 9, 9) |
      util_bitpack_uint(values->FramePredictionFrameDCT, 10, 10) |
      util_bitpack_uint(values->TopFieldFirst, 11, 11) |
      util_bitpack_uint(values->PictureStructure, 12, 13) |
      util_bitpack_uint(values->IntraDCPrecision, 14, 15) |
      util_bitpack_uint(values->F_code00, 16, 19) |
      util_bitpack_uint(values->F_code01, 20, 23) |
      util_bitpack_uint(values->F_code10, 24, 27) |
      util_bitpack_uint(values->F_code11, 28, 31);
}

#define GFX9_MFX_MPEG_TS_CONTROLcommand_length      5
#define GFX9_MFX_MPEG_TS_CONTROLcommand_length_bias      2
#define GFX9_MFX_MPEG_TS_CONTROLcommand_header  \
   .DWordLength                         =      3,  \
   .SubOpcodeB                          =     11,  \
   .SubOpcodeA                          =      2,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_MPEG_TS_CONTROLcommand {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             VideoPacketIDHeaderParameter;
   uint32_t                             StreamIDLowerNibble;
   uint32_t                             OutputTSPacketGroupingSelect;
   uint32_t                             CopyRightFlagInPESHeader;
   uint32_t                             OriginalOrFlagInPESHeader;
   uint32_t                             DSMTrickModeFlagInPESHeader;
   bool                                 AdditionalCopyInfoFlagInPESHeader;
   uint32_t                             PayloadUnitStartIndicatorControl;
   uint32_t                             PCR90KHzComponentLeastSignificantBits;
   uint32_t                             _90KHzcounterMSB;
   uint32_t                             _27MHzCounter;
   uint32_t                             PTSDelta;
   uint32_t                             MPEGTSPacketCount;
   uint32_t                             ContinuityCounter;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_MPEG_TS_CONTROLcommand_pack(__attribute__((unused)) __gen_user_data *data,
                                     __attribute__((unused)) void * restrict dst,
                                     __attribute__((unused)) const struct GFX9_MFX_MPEG_TS_CONTROLcommand * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->VideoPacketIDHeaderParameter, 0, 12) |
      util_bitpack_uint(values->StreamIDLowerNibble, 20, 23) |
      util_bitpack_uint(values->OutputTSPacketGroupingSelect, 24, 24) |
      util_bitpack_uint(values->CopyRightFlagInPESHeader, 25, 25) |
      util_bitpack_uint(values->OriginalOrFlagInPESHeader, 26, 26) |
      util_bitpack_uint(values->DSMTrickModeFlagInPESHeader, 27, 27) |
      util_bitpack_uint(values->AdditionalCopyInfoFlagInPESHeader, 28, 28) |
      util_bitpack_uint(values->PayloadUnitStartIndicatorControl, 29, 29);

   dw[2] =
      util_bitpack_uint(values->PCR90KHzComponentLeastSignificantBits, 0, 31);

   dw[3] =
      util_bitpack_uint(values->_90KHzcounterMSB, 0, 0) |
      util_bitpack_uint(values->_27MHzCounter, 23, 31);

   dw[4] =
      util_bitpack_uint(values->PTSDelta, 0, 31);
}

#define GFX9_MFX_PAK_INSERT_OBJECT_length_bias      2
#define GFX9_MFX_PAK_INSERT_OBJECT_header       \
   .DWordLength                         =      0,  \
   .SubOpcodeB                          =      8,  \
   .SubOpcodeA                          =      2,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_PAK_INSERT_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   bool                                 BitstreamStartReset;
   bool                                 EndofSlice;
   bool                                 LastHeader;
   bool                                 EmulationByteBitsInsertEnable;
   uint32_t                             SkipEmulationByteCount;
   uint32_t                             DataBitsInLastDW;
   uint32_t                             SliceHeaderIndicator;
#define SLICE_HEADER                             1
#define LEGACY                                   0
   uint32_t                             HeaderLengthExcludedFromSize;
#define NO_ACCUMULATION                          1
#define ACCUMULATE                               0
   uint32_t                             DataByteOffset;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_MFX_PAK_INSERT_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GFX9_MFX_PAK_INSERT_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->BitstreamStartReset, 0, 0) |
      util_bitpack_uint(values->EndofSlice, 1, 1) |
      util_bitpack_uint(values->LastHeader, 2, 2) |
      util_bitpack_uint(values->EmulationByteBitsInsertEnable, 3, 3) |
      util_bitpack_uint(values->SkipEmulationByteCount, 4, 7) |
      util_bitpack_uint(values->DataBitsInLastDW, 8, 13) |
      util_bitpack_uint(values->SliceHeaderIndicator, 14, 14) |
      util_bitpack_uint(values->HeaderLengthExcludedFromSize, 15, 15) |
      util_bitpack_uint(values->DataByteOffset, 16, 17);
}

#define GFX9_MFX_PIPE_BUF_ADDR_STATE_length     65
#define GFX9_MFX_PIPE_BUF_ADDR_STATE_length_bias      2
#define GFX9_MFX_PIPE_BUF_ADDR_STATE_header     \
   .DWordLength                         =     63,  \
   .SubOpcodeB                          =      2,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_PIPE_BUF_ADDR_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   __gen_address_type                   PreDeblockingDestinationAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  PreDeblockingDestinationAttributes;
   __gen_address_type                   PostDeblockingDestinationAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  PostDeblockingDestinationAttributes;
   __gen_address_type                   OriginalUncompressedPictureSourceAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  OriginalUncompressedPictureSourceAttributes;
   __gen_address_type                   StreamOutDataDestinationAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  StreamOutDataDestinationAttributes;
   __gen_address_type                   IntraRowStoreScratchBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  IntraRowStoreScratchBufferAttributes;
   __gen_address_type                   DeblockingFilterRowStoreScratchAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  DeblockingFilterRowStoreScratchAttributes;
   __gen_address_type                   ReferencePictureAddress[16];
   struct GFX9_MEMORYADDRESSATTRIBUTES  ReferencePictureAttributes;
   __gen_address_type                   MBStatusBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  MBStatusBufferAttributes;
   __gen_address_type                   MBILDBStreamOutBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  MBILDBStreamOutBufferAttributes;
   __gen_address_type                   SecondMBILDBStreamOutBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  SecondMBILDBStreamOutBufferAttributes;
   uint32_t                             ReferencePictureMemoryCompressionMode[16];
   bool                                 ReferencePictureMemoryCompressionEnable[16];
   __gen_address_type                   ScaledReferenceSurfaceAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  ScaledReferenceSurfaceAttributes;
   __gen_address_type                   SliceSizeStreamOutDataDestinationAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  SliceSizeStreamOutDataDestinationAttributes;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_PIPE_BUF_ADDR_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_MFX_PIPE_BUF_ADDR_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->PreDeblockingDestinationAddress, 0, 6, 47);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[3], &values->PreDeblockingDestinationAttributes);

   const uint64_t v4_address =
      __gen_address(data, &dw[4], values->PostDeblockingDestinationAddress, 0, 6, 47);
   dw[4] = v4_address;
   dw[5] = v4_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[6], &values->PostDeblockingDestinationAttributes);

   const uint64_t v7_address =
      __gen_address(data, &dw[7], values->OriginalUncompressedPictureSourceAddress, 0, 6, 47);
   dw[7] = v7_address;
   dw[8] = v7_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[9], &values->OriginalUncompressedPictureSourceAttributes);

   const uint64_t v10_address =
      __gen_address(data, &dw[10], values->StreamOutDataDestinationAddress, 0, 6, 47);
   dw[10] = v10_address;
   dw[11] = v10_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[12], &values->StreamOutDataDestinationAttributes);

   const uint64_t v13_address =
      __gen_address(data, &dw[13], values->IntraRowStoreScratchBufferAddress, 0, 6, 47);
   dw[13] = v13_address;
   dw[14] = v13_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[15], &values->IntraRowStoreScratchBufferAttributes);

   const uint64_t v16_address =
      __gen_address(data, &dw[16], values->DeblockingFilterRowStoreScratchAddress, 0, 6, 47);
   dw[16] = v16_address;
   dw[17] = v16_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[18], &values->DeblockingFilterRowStoreScratchAttributes);

   const uint64_t v19_address =
      __gen_address(data, &dw[19], values->ReferencePictureAddress[0], 0, 0, 63);
   dw[19] = v19_address;
   dw[20] = v19_address >> 32;

   const uint64_t v21_address =
      __gen_address(data, &dw[21], values->ReferencePictureAddress[1], 0, 0, 63);
   dw[21] = v21_address;
   dw[22] = v21_address >> 32;

   const uint64_t v23_address =
      __gen_address(data, &dw[23], values->ReferencePictureAddress[2], 0, 0, 63);
   dw[23] = v23_address;
   dw[24] = v23_address >> 32;

   const uint64_t v25_address =
      __gen_address(data, &dw[25], values->ReferencePictureAddress[3], 0, 0, 63);
   dw[25] = v25_address;
   dw[26] = v25_address >> 32;

   const uint64_t v27_address =
      __gen_address(data, &dw[27], values->ReferencePictureAddress[4], 0, 0, 63);
   dw[27] = v27_address;
   dw[28] = v27_address >> 32;

   const uint64_t v29_address =
      __gen_address(data, &dw[29], values->ReferencePictureAddress[5], 0, 0, 63);
   dw[29] = v29_address;
   dw[30] = v29_address >> 32;

   const uint64_t v31_address =
      __gen_address(data, &dw[31], values->ReferencePictureAddress[6], 0, 0, 63);
   dw[31] = v31_address;
   dw[32] = v31_address >> 32;

   const uint64_t v33_address =
      __gen_address(data, &dw[33], values->ReferencePictureAddress[7], 0, 0, 63);
   dw[33] = v33_address;
   dw[34] = v33_address >> 32;

   const uint64_t v35_address =
      __gen_address(data, &dw[35], values->ReferencePictureAddress[8], 0, 0, 63);
   dw[35] = v35_address;
   dw[36] = v35_address >> 32;

   const uint64_t v37_address =
      __gen_address(data, &dw[37], values->ReferencePictureAddress[9], 0, 0, 63);
   dw[37] = v37_address;
   dw[38] = v37_address >> 32;

   const uint64_t v39_address =
      __gen_address(data, &dw[39], values->ReferencePictureAddress[10], 0, 0, 63);
   dw[39] = v39_address;
   dw[40] = v39_address >> 32;

   const uint64_t v41_address =
      __gen_address(data, &dw[41], values->ReferencePictureAddress[11], 0, 0, 63);
   dw[41] = v41_address;
   dw[42] = v41_address >> 32;

   const uint64_t v43_address =
      __gen_address(data, &dw[43], values->ReferencePictureAddress[12], 0, 0, 63);
   dw[43] = v43_address;
   dw[44] = v43_address >> 32;

   const uint64_t v45_address =
      __gen_address(data, &dw[45], values->ReferencePictureAddress[13], 0, 0, 63);
   dw[45] = v45_address;
   dw[46] = v45_address >> 32;

   const uint64_t v47_address =
      __gen_address(data, &dw[47], values->ReferencePictureAddress[14], 0, 0, 63);
   dw[47] = v47_address;
   dw[48] = v47_address >> 32;

   const uint64_t v49_address =
      __gen_address(data, &dw[49], values->ReferencePictureAddress[15], 0, 0, 63);
   dw[49] = v49_address;
   dw[50] = v49_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[51], &values->ReferencePictureAttributes);

   const uint64_t v52_address =
      __gen_address(data, &dw[52], values->MBStatusBufferAddress, 0, 6, 47);
   dw[52] = v52_address;
   dw[53] = v52_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[54], &values->MBStatusBufferAttributes);

   const uint64_t v55_address =
      __gen_address(data, &dw[55], values->MBILDBStreamOutBufferAddress, 0, 6, 47);
   dw[55] = v55_address;
   dw[56] = v55_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[57], &values->MBILDBStreamOutBufferAttributes);

   const uint64_t v58_address =
      __gen_address(data, &dw[58], values->SecondMBILDBStreamOutBufferAddress, 0, 6, 47);
   dw[58] = v58_address;
   dw[59] = v58_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[60], &values->SecondMBILDBStreamOutBufferAttributes);

   dw[61] =
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[0], 1, 1) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[0], 0, 0) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[1], 3, 3) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[1], 2, 2) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[2], 5, 5) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[2], 4, 4) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[3], 7, 7) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[3], 6, 6) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[4], 9, 9) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[4], 8, 8) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[5], 11, 11) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[5], 10, 10) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[6], 13, 13) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[6], 12, 12) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[7], 15, 15) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[7], 14, 14) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[8], 17, 17) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[8], 16, 16) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[9], 19, 19) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[9], 18, 18) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[10], 21, 21) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[10], 20, 20) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[11], 23, 23) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[11], 22, 22) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[12], 25, 25) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[12], 24, 24) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[13], 27, 27) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[13], 26, 26) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[14], 29, 29) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[14], 28, 28) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionMode[15], 31, 31) |
      util_bitpack_uint(values->ReferencePictureMemoryCompressionEnable[15], 30, 30);

   const uint64_t v62_address =
      __gen_address(data, &dw[62], values->ScaledReferenceSurfaceAddress, 0, 6, 47);
   dw[62] = v62_address;
   dw[63] = v62_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[64], &values->ScaledReferenceSurfaceAttributes);
}

#define GFX9_MFX_PIPE_MODE_SELECT_length       5
#define GFX9_MFX_PIPE_MODE_SELECT_length_bias      2
#define GFX9_MFX_PIPE_MODE_SELECT_header        \
   .DWordLength                         =      3,  \
   .SubOpcodeB                          =      0,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_PIPE_MODE_SELECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             StandardSelect;
#define SS_MPEG2                                 0
#define SS_VC1                                   1
#define SS_AVC                                   2
#define SS_JPEG                                  3
#define SS_VP8                                   5
#define SS_UVLD                                  15
   uint32_t                             CodecSelect;
#define Decode                                   0
#define Encode                                   1
   bool                                 StitchMode;
   bool                                 FrameStatisticsStreamOutEnable;
   bool                                 ScaledSurfaceEnable;
   bool                                 PreDeblockingOutputEnable;
   bool                                 PostDeblockingOutputEnable;
   bool                                 StreamOutEnable;
   bool                                 PicErrorStatusReportEnable;
   bool                                 DeblockerStreamOutEnable;
   uint32_t                             VDEncMode;
#define VM_MBEncMode                             0
#define VM_VDEncMode                             1
   bool                                 StandaloneVDEncModeEnable;
   uint32_t                             DecoderModeSelect;
#define VLDMode                                  0
#define ITMode                                   1
#define DeblockerMode                            2
#define InterlayerMode                           3
   uint32_t                             DecoderShortFormatMode;
#define ShortFormatDriverInterface               0
#define LongFormatDriverInterface                1
   bool                                 ExtendedStreamOutEnable;
   uint32_t                             PicStatusErrorReportID;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_PIPE_MODE_SELECT_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_MFX_PIPE_MODE_SELECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->StandardSelect, 0, 3) |
      util_bitpack_uint(values->CodecSelect, 4, 4) |
      util_bitpack_uint(values->StitchMode, 5, 5) |
      util_bitpack_uint(values->FrameStatisticsStreamOutEnable, 6, 6) |
      util_bitpack_uint(values->ScaledSurfaceEnable, 7, 7) |
      util_bitpack_uint(values->PreDeblockingOutputEnable, 8, 8) |
      util_bitpack_uint(values->PostDeblockingOutputEnable, 9, 9) |
      util_bitpack_uint(values->StreamOutEnable, 10, 10) |
      util_bitpack_uint(values->PicErrorStatusReportEnable, 11, 11) |
      util_bitpack_uint(values->DeblockerStreamOutEnable, 12, 12) |
      util_bitpack_uint(values->VDEncMode, 13, 13) |
      util_bitpack_uint(values->StandaloneVDEncModeEnable, 14, 14) |
      util_bitpack_uint(values->DecoderModeSelect, 15, 16) |
      util_bitpack_uint(values->DecoderShortFormatMode, 17, 17) |
      util_bitpack_uint(values->ExtendedStreamOutEnable, 18, 18);

   dw[2] = 0;

   dw[3] =
      util_bitpack_uint(values->PicStatusErrorReportID, 0, 31);

   dw[4] = 0;
}

#define GFX9_MFX_QM_STATE_length              34
#define GFX9_MFX_QM_STATE_length_bias          2
#define GFX9_MFX_QM_STATE_header                \
   .DWordLength                         =     32,  \
   .SubOpcodeB                          =      7,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_QM_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             AVC;
#define AVC_4x4_Intra_MATRIX                     0
#define AVC_4x4_Inter_MATRIX                     1
#define AVC_8x8_Intra_MATRIX                     2
#define AVC_8x8_Inter_MATRIX                     3
   uint32_t                             MPEG2;
#define MPEG_INTRA_QUANTIZER_MATRIX              0
#define MPEG_NON_INTRA_QUANTIZER_MATRIX          1
   uint32_t                             JPEG;
#define JPEG_Luma_Y_QUANTIZER_MATRIXorR          0
#define JPEG_Chroma_Cb_QUANTIZER_MATRIXorG       1
#define JPEG_Chroma_Cr_QUANTIZER_MATRIXorB       2
   uint32_t                             ForwardQuantizerMatrix[64];
};

static inline __attribute__((always_inline)) void
GFX9_MFX_QM_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                       __attribute__((unused)) void * restrict dst,
                       __attribute__((unused)) const struct GFX9_MFX_QM_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->AVC, 0, 1) |
      util_bitpack_uint(values->MPEG2, 0, 1) |
      util_bitpack_uint(values->JPEG, 0, 1);

   dw[2] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[0], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[1], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[2], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[3], 24, 31);

   dw[3] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[4], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[5], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[6], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[7], 24, 31);

   dw[4] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[8], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[9], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[10], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[11], 24, 31);

   dw[5] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[12], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[13], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[14], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[15], 24, 31);

   dw[6] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[16], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[17], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[18], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[19], 24, 31);

   dw[7] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[20], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[21], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[22], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[23], 24, 31);

   dw[8] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[24], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[25], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[26], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[27], 24, 31);

   dw[9] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[28], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[29], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[30], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[31], 24, 31);

   dw[10] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[32], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[33], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[34], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[35], 24, 31);

   dw[11] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[36], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[37], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[38], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[39], 24, 31);

   dw[12] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[40], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[41], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[42], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[43], 24, 31);

   dw[13] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[44], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[45], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[46], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[47], 24, 31);

   dw[14] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[48], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[49], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[50], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[51], 24, 31);

   dw[15] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[52], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[53], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[54], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[55], 24, 31);

   dw[16] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[56], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[57], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[58], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[59], 24, 31);

   dw[17] =
      util_bitpack_uint(values->ForwardQuantizerMatrix[60], 0, 7) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[61], 8, 15) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[62], 16, 23) |
      util_bitpack_uint(values->ForwardQuantizerMatrix[63], 24, 31);

   dw[18] = 0;

   dw[19] = 0;

   dw[20] = 0;

   dw[21] = 0;

   dw[22] = 0;

   dw[23] = 0;

   dw[24] = 0;

   dw[25] = 0;

   dw[26] = 0;

   dw[27] = 0;

   dw[28] = 0;

   dw[29] = 0;

   dw[30] = 0;

   dw[31] = 0;

   dw[32] = 0;

   dw[33] = 0;
}

#define GFX9_MFX_STATE_POINTER_length          2
#define GFX9_MFX_STATE_POINTER_length_bias      2
#define GFX9_MFX_STATE_POINTER_header           \
   .DWordLength                         =      0,  \
   .SubOpcodeB                          =      6,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_STATE_POINTER {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             StatePointerIndex;
   uint32_t                             StatePointer;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_STATE_POINTER_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_MFX_STATE_POINTER * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->StatePointerIndex, 0, 1) |
      util_bitpack_uint(values->StatePointer, 5, 31);
}

#define GFX9_MFX_STITCH_OBJECT_length_bias      2
#define GFX9_MFX_STITCH_OBJECT_header           \
   .DWordLength                         =      0,  \
   .SubOpcodeB                          =     10,  \
   .SubOpcodeA                          =      2,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_STITCH_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   bool                                 EndofSlice;
   bool                                 LastHeader;
   uint32_t                             SourceDataEndingBitInclusion;
   uint32_t                             SourceDataStartingByteOffset;
   uint32_t                             IndirectDataLength;
   uint64_t                             IndirectDataStartAddress;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_MFX_STITCH_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_MFX_STITCH_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->EndofSlice, 1, 1) |
      util_bitpack_uint(values->LastHeader, 2, 2) |
      util_bitpack_uint(values->SourceDataEndingBitInclusion, 8, 13) |
      util_bitpack_uint(values->SourceDataStartingByteOffset, 16, 17);

   dw[2] =
      util_bitpack_uint(values->IndirectDataLength, 0, 18);

   dw[3] =
      __gen_offset(values->IndirectDataStartAddress, 0, 31);
}

#define GFX9_MFX_SURFACE_STATE_length          6
#define GFX9_MFX_SURFACE_STATE_length_bias      2
#define GFX9_MFX_SURFACE_STATE_header           \
   .DWordLength                         =      4,  \
   .SubOpcodeB                          =      1,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      0,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_SURFACE_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             SurfaceID;
#define MFX_SourceInputPicture                   4
#define MFX_ReconstructedScaledReferencePicture  5
   float                                CrVCbUPixelOffsetVDirection;
   uint32_t                             Width;
   uint32_t                             Height;
   uint32_t                             TileWalk;
#define TW_XMAJOR                                0
#define TW_YMAJOR                                1
   bool                                 TiledSurface;
   bool                                 HalfPitchforChroma;
   uint32_t                             SurfacePitch;
   bool                                 InterleaveChroma;
   uint32_t                             SurfaceFormat;
#define MFX_YCRCB_NORMAL                         0
#define MFX_YCRCB_SWAPUVY                        1
#define MFX_YCRCB_SWAPUV                         2
#define MFX_YCRCB_SWAPY                          3
#define MFX_PLANAR_420_8                         4
#define MFX_PLANAR_411_8                         5
#define MFX_PLANAR_422_8                         6
#define MFX_STMM_DN_STATISTICS                   7
#define MFX_R10G10B10A2_UNORM                    8
#define MFX_R8G8B8A8_UNORM                       9
#define MFX_R8B8_UNORMCrCb                       10
#define MFX_R8_UNORMCrCb                         11
#define MFX_Y8_UNORM                             12
   uint32_t                             YOffsetforUCb;
   uint32_t                             XOffsetforUCb;
   uint32_t                             YOffsetforVCr;
   uint32_t                             XOffsetforVCr;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_SURFACE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_MFX_SURFACE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->SurfaceID, 0, 3);

   dw[2] =
      util_bitpack_ufixed(values->CrVCbUPixelOffsetVDirection, 0, 1, 2) |
      util_bitpack_uint(values->Width, 4, 17) |
      util_bitpack_uint(values->Height, 18, 31);

   dw[3] =
      util_bitpack_uint(values->TileWalk, 0, 0) |
      util_bitpack_uint(values->TiledSurface, 1, 1) |
      util_bitpack_uint(values->HalfPitchforChroma, 2, 2) |
      util_bitpack_uint(values->SurfacePitch, 3, 19) |
      util_bitpack_uint(values->InterleaveChroma, 27, 27) |
      util_bitpack_uint(values->SurfaceFormat, 28, 31);

   dw[4] =
      util_bitpack_uint(values->YOffsetforUCb, 0, 14) |
      util_bitpack_uint(values->XOffsetforUCb, 16, 30);

   dw[5] =
      util_bitpack_uint(values->YOffsetforVCr, 0, 15) |
      util_bitpack_uint(values->XOffsetforVCr, 16, 28);
}

#define GFX9_MFX_VC1_DIRECTMODE_STATE_length      7
#define GFX9_MFX_VC1_DIRECTMODE_STATE_length_bias      2
#define GFX9_MFX_VC1_DIRECTMODE_STATE_header    \
   .DWordLength                         =      5,  \
   .SubOpcodeB                          =      2,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      2,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_VC1_DIRECTMODE_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   __gen_address_type                   DirectMVWriteBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  DirectMVWriteBufferAttributes;
   __gen_address_type                   DirectMVReadBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  DirectMVReadBufferAttributes;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_VC1_DIRECTMODE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                   __attribute__((unused)) void * restrict dst,
                                   __attribute__((unused)) const struct GFX9_MFX_VC1_DIRECTMODE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->DirectMVWriteBufferAddress, 0, 0, 63);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[3], &values->DirectMVWriteBufferAttributes);

   const uint64_t v4_address =
      __gen_address(data, &dw[4], values->DirectMVReadBufferAddress, 0, 0, 63);
   dw[4] = v4_address;
   dw[5] = v4_address >> 32;

   GFX9_MEMORYADDRESSATTRIBUTES_pack(data, &dw[6], &values->DirectMVReadBufferAttributes);
}

#define GFX9_MFX_VC1_PRED_PIPE_STATE_length      6
#define GFX9_MFX_VC1_PRED_PIPE_STATE_length_bias      2
#define GFX9_MFX_VC1_PRED_PIPE_STATE_header     \
   .DWordLength                         =      4,  \
   .SubOpcodeB                          =      1,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      2,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_VC1_PRED_PIPE_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             ReferenceFrameBoundaryReplicationMode;
   uint32_t                             Vin_intensitycomp_Single_BWDen;
   uint32_t                             Vin_intensitycomp_Single_FWDen;
   uint32_t                             Vin_intensitycomp_Double_BWDen;
   uint32_t                             Vin_intensitycomp_Double_FWDen;
   uint32_t                             LumScale1singleFWD;
   uint32_t                             LumScale2singleFWD;
   uint32_t                             LumShift1singleFWD;
   uint32_t                             LumShift2singleFWD;
   uint32_t                             LumScale1doubleFWD;
   uint32_t                             LumScale2doubleFWD;
   uint32_t                             LumShift1doubleFWD;
   uint32_t                             LumShift2doubleFWD;
   uint32_t                             LumScale1singleBWD;
   uint32_t                             LumScale2singleBWD;
   uint32_t                             LumShift1singleBWD;
   uint32_t                             LumShift2singleBWD;
   uint32_t                             LumScale1doubleBWD;
   uint32_t                             LumScale2doubleBWD;
   uint32_t                             LumShift1doubleBWD;
   uint32_t                             LumShift2doubleBWD;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_VC1_PRED_PIPE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_MFX_VC1_PRED_PIPE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ReferenceFrameBoundaryReplicationMode, 4, 7) |
      util_bitpack_uint(values->Vin_intensitycomp_Single_BWDen, 8, 9) |
      util_bitpack_uint(values->Vin_intensitycomp_Single_FWDen, 10, 11) |
      util_bitpack_uint(values->Vin_intensitycomp_Double_BWDen, 12, 13) |
      util_bitpack_uint(values->Vin_intensitycomp_Double_FWDen, 14, 15);

   dw[2] =
      util_bitpack_uint(values->LumScale1singleFWD, 0, 5) |
      util_bitpack_uint(values->LumScale2singleFWD, 8, 13) |
      util_bitpack_uint(values->LumShift1singleFWD, 16, 21) |
      util_bitpack_uint(values->LumShift2singleFWD, 24, 29);

   dw[3] =
      util_bitpack_uint(values->LumScale1doubleFWD, 0, 5) |
      util_bitpack_uint(values->LumScale2doubleFWD, 8, 13) |
      util_bitpack_uint(values->LumShift1doubleFWD, 16, 21) |
      util_bitpack_uint(values->LumShift2doubleFWD, 24, 29);

   dw[4] =
      util_bitpack_uint(values->LumScale1singleBWD, 0, 5) |
      util_bitpack_uint(values->LumScale2singleBWD, 8, 13) |
      util_bitpack_uint(values->LumShift1singleBWD, 16, 21) |
      util_bitpack_uint(values->LumShift2singleBWD, 24, 29);

   dw[5] =
      util_bitpack_uint(values->LumScale1doubleBWD, 0, 5) |
      util_bitpack_uint(values->LumScale2doubleBWD, 8, 13) |
      util_bitpack_uint(values->LumShift1doubleBWD, 16, 21) |
      util_bitpack_uint(values->LumShift2doubleBWD, 24, 29);
}

#define GFX9_MFX_VP8_BSP_BUF_BASE_ADDR_STATE_length      2
#define GFX9_MFX_VP8_BSP_BUF_BASE_ADDR_STATE_length_bias      2
#define GFX9_MFX_VP8_BSP_BUF_BASE_ADDR_STATE_header\
   .DWordLength                         =      0,  \
   .SubOpcodeB                          =      3,  \
   .SubOpcodeA                          =      2,  \
   .MediaCommandOpcode                  =      4,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_VP8_BSP_BUF_BASE_ADDR_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   __gen_address_type                   FrameHeaderAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  FrameHeaderAttributes;
   __gen_address_type                   IntermediateBufferAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  IntermediateBufferAttributes;
   uint64_t                             IntermediateBufferPartitionOffset;
   uint32_t                             IntermediateBufferMaxSize;
   __gen_address_type                   FinalFrameAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  FinalFrameAttributes;
   uint32_t                             FinalFrameByteOffset;
   __gen_address_type                   StreamOutAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  StreamOutAttributes;
   __gen_address_type                   CoeffProbsStreamInSurfaceAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  CoeffProbsStreamInSurfaceAttributes;
   __gen_address_type                   TokenStatisticsSurfaceAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  TokenStatisticsSurfaceAttributes;
   __gen_address_type                   MPCRowStoreSurfaceAddress;
   struct GFX9_MEMORYADDRESSATTRIBUTES  MPCRowStoreSurfaceAttributes;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_VP8_BSP_BUF_BASE_ADDR_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                          __attribute__((unused)) void * restrict dst,
                                          __attribute__((unused)) const struct GFX9_MFX_VP8_BSP_BUF_BASE_ADDR_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->FrameHeaderAddress, 0, 0, 63);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;
}

#define GFX9_MFX_VP8_ENCODER_CFG_length        2
#define GFX9_MFX_VP8_ENCODER_CFG_length_bias      2
#define GFX9_MFX_VP8_ENCODER_CFG_header         \
   .DWordLength                         =      0,  \
   .SubOpcodeB                          =      1,  \
   .SubOpcodeA                          =      2,  \
   .MediaCommandOpcode                  =      4,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_VP8_ENCODER_CFG {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   bool                                 PerformanceCounterEnable;
   bool                                 FinalBitstreamOutputDisable;
   bool                                 TokenStatisticsOutputEnable;
   bool                                 BitstreamStatisticsOutputEnable;
   bool                                 UpdateSegmentFeatureDataFlag;
   bool                                 SkipFinalBitstreamwhenOverUnderflow;
   bool                                 RateControlInitialPass;
   bool                                 PerSegmentDeltaQindexLoopFilterDisable;
   bool                                 FinerBRCEnable;
   bool                                 CompressedBitstreamOutputDisable;
   bool                                 VBSPUnitPowerClockGatingDisable;
   bool                                 MaxFrameBitcountRateControlEnable;
   bool                                 MinFrameBitCountRateControlEnable;
   bool                                 MaxInterMBBitCountCheckEnable;
   bool                                 MaxIntraMBBitCountCheckEnable;
   bool                                 IntermediateBitBufferOverrunEnable;
   bool                                 FinalBitstreamBufferOverrunEnable;
   bool                                 QIndexClampHighforUnderflow;
   bool                                 QIndexClampHighforOverflow;
   uint32_t                             MaxInterMBBitCount;
   uint32_t                             MaxIntraMBBitCountLimit;
   uint32_t                             FrameBitrateMax;
   uint32_t                             FrameBitrateMaxUnit;
   uint32_t                             FrameBitrateMaxUnitMode;
#define CompatibilityMode                        0
#define NewMode                                  1
   uint32_t                             FrameBitrateMin;
   uint32_t                             FrameBitrateMinUnit;
   uint32_t                             FrameBitrateMinUnitMode;
#define CompatibilityMode                        0
#define NewMode                                  1
   uint32_t                             FrameDeltaQIndexMax0;
   uint32_t                             FrameDeltaQIndexMax1;
   uint32_t                             FrameDeltaQIndexMax2;
   uint32_t                             FrameDeltaQIndexMax3;
   uint32_t                             FrameDeltaQIndexMin0;
   uint32_t                             FrameDeltaQIndexMin1;
   uint32_t                             FrameDeltaQIndexMin2;
   uint32_t                             FrameDeltaQIndexMin3;
   uint32_t                             PerSegmentFrameDeltaQIndexMax1;
   uint32_t                             PerSegmentFrameDeltaQIndexMin1;
   uint32_t                             PerSegmentFrameDeltaQIndexMax2;
   uint32_t                             PerSegmentFrameDeltaQIndexMin2;
   uint32_t                             PerSegmentFrameDeltaQIndexMax3;
   uint32_t                             PerSegmentFrameDeltaQIndexMin3;
   uint32_t                             FrameDeltaLoopFilterMax0;
   uint32_t                             FrameDeltaLoopFilterMax1;
   uint32_t                             FrameDeltaLoopFilterMax2;
   uint32_t                             FrameDeltaLoopFilterMax3;
   uint32_t                             FrameDeltaLoopFilterMin0;
   uint32_t                             FrameDeltaLoopFilterMin1;
   uint32_t                             FrameDeltaLoopFilterMin2;
   uint32_t                             FrameDeltaLoopFilterMin3;
   uint32_t                             PerSegmentFrameDeltaLoopFilterMax1;
   uint32_t                             PerSegmentFrameDeltaLoopFilterMin1;
   uint32_t                             PerSegmentFrameDeltaLoopFilterMax2;
   uint32_t                             PerSegmentFrameDeltaLoopFilterMin2;
   uint32_t                             PerSegmentFrameDeltaLoopFilterMax3;
   uint32_t                             PerSegmentFrameDeltaLoopFilterMin3;
   uint32_t                             FrameBitrateMaxDelta;
   uint32_t                             FrameBitrateMinDelta;
   uint32_t                             MinimumFrameSize;
   uint32_t                             MinimumFrameSizeUnit;
#define CompatibilityMode                        0
#define NewMode                                  1
   uint32_t                             BitstreamFormatVersion;
   uint32_t                             ShowFrame;
   uint32_t                             Horizontal_Size_Code;
   uint32_t                             Vertical_Size_Code;
   uint32_t                             FrameHeaderBitCount;
   uint32_t                             FrameHeaderBinBufferQIndexUpdatePointer;
   uint32_t                             FrameHeaderBinBufferLoopFilterUpdatePointer;
   uint32_t                             FrameHeaderBinBufferTokenUpdatePointer;
   uint32_t                             FrameHeaderBinBufferMVUpdatePointer;
   uint32_t                             CV0;
   uint32_t                             CV1;
   uint32_t                             CV2;
   uint32_t                             CV3;
   uint32_t                             CV4;
   uint32_t                             CV5;
   uint32_t                             CV6;
   uint32_t                             CV7;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_VP8_ENCODER_CFG_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_MFX_VP8_ENCODER_CFG * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->PerformanceCounterEnable, 0, 0) |
      util_bitpack_uint(values->FinalBitstreamOutputDisable, 1, 1) |
      util_bitpack_uint(values->TokenStatisticsOutputEnable, 2, 2) |
      util_bitpack_uint(values->BitstreamStatisticsOutputEnable, 3, 3) |
      util_bitpack_uint(values->UpdateSegmentFeatureDataFlag, 4, 4) |
      util_bitpack_uint(values->SkipFinalBitstreamwhenOverUnderflow, 5, 5) |
      util_bitpack_uint(values->RateControlInitialPass, 6, 6) |
      util_bitpack_uint(values->PerSegmentDeltaQindexLoopFilterDisable, 7, 7) |
      util_bitpack_uint(values->FinerBRCEnable, 8, 8) |
      util_bitpack_uint(values->CompressedBitstreamOutputDisable, 9, 9) |
      util_bitpack_uint(values->VBSPUnitPowerClockGatingDisable, 10, 10);
}

#define GFX9_MFX_VP8_PAK_OBJECT_length         7
#define GFX9_MFX_VP8_PAK_OBJECT_length_bias      2
#define GFX9_MFX_VP8_PAK_OBJECT_header          \
   .DWordLength                         =      5,  \
   .SubOpcodeB                          =      9,  \
   .SubOpcodeA                          =      2,  \
   .MediaCommandOpcode                  =      4,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_VP8_PAK_OBJECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             IndirectPAKMVDataLength;
   bool                                 EnableInlineMVdata;
   uint64_t                             IndirectPAKMVDataStartAddressOffset;
   uint64_t                             InlineData;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_VP8_PAK_OBJECT_pack(__attribute__((unused)) __gen_user_data *data,
                             __attribute__((unused)) void * restrict dst,
                             __attribute__((unused)) const struct GFX9_MFX_VP8_PAK_OBJECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpcode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->IndirectPAKMVDataLength, 0, 9) |
      util_bitpack_uint(values->EnableInlineMVdata, 29, 29);

   dw[2] =
      __gen_offset(values->IndirectPAKMVDataStartAddressOffset, 0, 28);

   const uint64_t v3 =
      util_bitpack_uint(values->InlineData, 0, 127);
   dw[3] = v3;
   dw[4] = v3 >> 32;
}

#define GFX9_MFX_VP8_PIC_STATE_length          2
#define GFX9_MFX_VP8_PIC_STATE_length_bias      2
#define GFX9_MFX_VP8_PIC_STATE_header           \
   .DWordLength                         =      0,  \
   .SubOpcodeB                          =      0,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpCode                  =      4,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_MFX_VP8_PIC_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpCode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             FrameWidth;
   uint32_t                             FrameHeight;
   uint32_t                             MCFilterSelect;
   uint32_t                             ChromaFullPixelMCFilterMode;
   uint32_t                             DBLKFilterType;
   bool                                 KeyFrame;
   bool                                 SegmentationIDStreamOutEnable;
   bool                                 SegmentationIDStreamInEnable;
   bool                                 SegmentEnable;
   bool                                 UpdateMBSegmentMap;
   bool                                 MBNoCoeffSkip;
   bool                                 ModeReferenceLoopFilterDeltaEnable;
   bool                                 GoldenRefPictureMVSignBias;
   bool                                 AlternateRefPicMVSignBias;
   uint32_t                             DeblockSharpnessLevel;
   uint32_t                             Log2NumofPartition;
#define _1Tokenpartition                         0
#define _2Tokenpartition                         1
#define _4Tokenpartition                         2
#define _8Tokenpartition                         3
   uint32_t                             DBLKFilterLevelforSegment0;
   uint32_t                             DBLKFilterLevelforSegment1;
   uint32_t                             DBLKFilterLevelforSegment2;
   uint32_t                             DBLKFilterLevelforSegment3;
   uint32_t                             Segment0QIndex;
   uint32_t                             Segment1QIndex;
   uint32_t                             Segment2QIndex;
   uint32_t                             Segment3QIndex;
   uint32_t                             Y2DCQIndexDelta;
   uint32_t                             Y2ACQIndexDeltaSign;
   uint32_t                             Y2ACQIndexDelta;
   uint32_t                             Y2ACQIndexSign;
   uint32_t                             UVDCQIndexDelta;
   uint32_t                             UVDCQIndexDeltaSign;
   uint32_t                             UVACQIndexDelta;
   uint32_t                             UVACQIndexDeltaSign;
   uint32_t                             Y1DCQIndexDelta;
   uint32_t                             Y1DCQIndexDeltaSign;
   uint32_t                             ClampQIndexLow;
   uint32_t                             ClampQIndexHigh;
   uint32_t                             QuantizerValue1UVDC;
   uint32_t                             QuantizerValue1UVAC;
   uint32_t                             QuantizerValue1Y2DC;
   uint32_t                             QuantizerValue1Y2AC;
   uint32_t                             QuantizerValue2Y1DC;
   uint32_t                             QuantizerValue2Y1AC;
   uint32_t                             QuantizerValue2UVDC;
   uint32_t                             QuantizerValue2UVAC;
   uint32_t                             QuantizerValue2Y2DC;
   uint32_t                             QuantizerValue2Y2AC;
   uint32_t                             QuantizerValue3Y1DC;
   uint32_t                             QuantizerValue3Y1AC;
   uint32_t                             QuantizerValue3UVDC;
   uint32_t                             QuantizerValue3UVAC;
   uint32_t                             QuantizerValue3Y2DC;
   uint32_t                             QuantizerValue3Y2AC;
   uint64_t                             CoeffProbabilityStreamInAddress;
   uint32_t                             CoeffProbabilityStreamInMOCSEncoderonly;
   uint32_t                             CoeffProbabilityStreamInArbitrationPriorityControl;
#define Highestpriority                          0
#define Secondhighestpriority                    1
#define Thirdhighestpriority                     2
#define Lowestpriority                           3
   bool                                 CoeffProbabilityStreamInMemoryCompressionEnable;
   uint32_t                             CoeffProbabilityStreamInMemoryCompressionMode;
   uint32_t                             CoeffProbabilityStreamInTiledResourceMode;
#define TRMODE_NONE                              0
#define TRMODE_TILEYF                            1
#define TRMODE_TILEYS                            2
   uint32_t                             MBSegmentIDTreeProbs0;
   uint32_t                             MBSegmentIDTreeProbs1;
   uint32_t                             MBSegmentIDTreeProbs2;
   uint32_t                             InterPredFromGRefRefProb;
   uint32_t                             InterPredFromLastRefProb;
   uint32_t                             IntraMBProb;
   uint32_t                             MBNoCoeffSkipFalseProb;
   uint32_t                             YModeProb0;
   uint32_t                             YModeProb1;
   uint32_t                             YModeProb2;
   uint32_t                             YModeProb3;
   uint32_t                             UVModeProb0;
   uint32_t                             UVModeProb1;
   uint32_t                             UVModeProb2;
   uint32_t                             MVUpdateProbs00;
   uint32_t                             MVUpdateProbs01;
   uint32_t                             MVUpdateProbs02;
   uint32_t                             MVUpdateProbs03;
   uint32_t                             MVUpdateProbs04;
   uint32_t                             MVUpdateProbs05;
   uint32_t                             MVUpdateProbs06;
   uint32_t                             MVUpdateProbs07;
   uint32_t                             MVUpdateProbs08;
   uint32_t                             MVUpdateProbs09;
   uint32_t                             MVUpdateProbs010;
   uint32_t                             MVUpdateProbs011;
   uint32_t                             MVUpdateProbs012;
   uint32_t                             MVUpdateProbs013;
   uint32_t                             MVUpdateProbs014;
   uint32_t                             MVUpdateProbs015;
   uint32_t                             MVUpdateProbs016;
   uint32_t                             MVUpdateProbs017;
   uint32_t                             MVUpdateProbs018;
   uint32_t                             MVUpdateProbs10;
   uint32_t                             MVUpdateProbs11;
   uint32_t                             MVUpdateProbs12;
   uint32_t                             MVUpdateProbs13;
   uint32_t                             MVUpdateProbs14;
   uint32_t                             MVUpdateProbs15;
   uint32_t                             MVUpdateProbs16;
   uint32_t                             MVUpdateProbs17;
   uint32_t                             MVUpdateProbs18;
   uint32_t                             MVUpdateProbs19;
   uint32_t                             MVUpdateProbs110;
   uint32_t                             MVUpdateProbs111;
   uint32_t                             MVUpdateProbs112;
   uint32_t                             MVUpdateProbs113;
   uint32_t                             MVUpdateProbs114;
   uint32_t                             MVUpdateProbs115;
   uint32_t                             MVUpdateProbs116;
   uint32_t                             MVUpdateProbs117;
   uint32_t                             MVUpdateProbs118;
   int32_t                              RefLFDelta0;
   int32_t                              RefLFDelta1;
   int32_t                              RefLFDelta2;
   int32_t                              RefLFDelta3;
   int32_t                              ModeLFDelta0;
   int32_t                              ModeLFDelta1;
   int32_t                              ModeLFDelta2;
   int32_t                              ModeLFDelta3;
   uint64_t                             SegmentationIDStreamAddress;
   uint32_t                             CoeffProbabilityStreamInMOCS;
   uint32_t                             SegmentationIDStreamArbitrationPriorityControl;
#define Highestpriority                          0
#define Secondhighestpriority                    1
#define Thirdhighestpriority                     2
#define Lowestpriority                           3
   bool                                 SegmentationIDStreamMemoryCompressionEnable;
   uint32_t                             SegmentationIDStreamMemoryCompressionMode;
   uint32_t                             SegmentationIDStreamTiledResourceMode;
#define TRMODE_NONE                              0
#define TRMODE_TILEYF                            1
#define TRMODE_TILEYS                            2
};

static inline __attribute__((always_inline)) void
GFX9_MFX_VP8_PIC_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_MFX_VP8_PIC_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 23) |
      util_bitpack_uint(values->MediaCommandOpCode, 24, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->FrameWidth, 0, 7) |
      util_bitpack_uint(values->FrameHeight, 16, 23);
}

#define GFX9_MFX_WAIT_length                   1
#define GFX9_MFX_WAIT_length_bias              1
#define GFX9_MFX_WAIT_header                    \
   .DWordLength                         =      0,  \
   .SubOpcode                           =      0,  \
   .CommandSubtype                      =      1,  \
   .CommandType                         =      3

struct GFX9_MFX_WAIT {
   uint32_t                             DWordLength;
   uint32_t                             MFXSyncControlFlag;
   uint32_t                             SubOpcode;
   uint32_t                             CommandSubtype;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_MFX_WAIT_pack(__attribute__((unused)) __gen_user_data *data,
                   __attribute__((unused)) void * restrict dst,
                   __attribute__((unused)) const struct GFX9_MFX_WAIT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 5) |
      util_bitpack_uint(values->MFXSyncControlFlag, 8, 8) |
      util_bitpack_uint(values->SubOpcode, 16, 26) |
      util_bitpack_uint(values->CommandSubtype, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_MI_ARB_CHECK_length               1
#define GFX9_MI_ARB_CHECK_length_bias          1
#define GFX9_MI_ARB_CHECK_header                \
   .MICommandOpcode                     =      5,  \
   .CommandType                         =      0

struct GFX9_MI_ARB_CHECK {
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_MI_ARB_CHECK_pack(__attribute__((unused)) __gen_user_data *data,
                       __attribute__((unused)) void * restrict dst,
                       __attribute__((unused)) const struct GFX9_MI_ARB_CHECK * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_MI_ARB_ON_OFF_length              1
#define GFX9_MI_ARB_ON_OFF_length_bias         1
#define GFX9_MI_ARB_ON_OFF_header               \
   .ArbitrationEnable                   =      1,  \
   .MICommandOpcode                     =      8,  \
   .CommandType                         =      0

struct GFX9_MI_ARB_ON_OFF {
   bool                                 ArbitrationEnable;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_MI_ARB_ON_OFF_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_MI_ARB_ON_OFF * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->ArbitrationEnable, 0, 0) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_MI_ATOMIC_length                  3
#define GFX9_MI_ATOMIC_length_bias             2
#define GFX9_MI_ATOMIC_header                   \
   .DWordLength                         =      1,  \
   .MICommandOpcode                     =     47,  \
   .CommandType                         =      0

struct GFX9_MI_ATOMIC {
   uint32_t                             DWordLength;
   enum GFX9_Atomic_OPCODE              ATOMICOPCODE;
   bool                                 ReturnDataControl;
   bool                                 CSSTALL;
   bool                                 InlineData;
   uint32_t                             DataSize;
#define MI_ATOMIC_DWORD                          0
#define MI_ATOMIC_QWORD                          1
#define MI_ATOMIC_OCTWORD                        2
#define MI_ATOMIC_RESERVED                       3
   bool                                 PostSyncOperation;
   uint32_t                             MemoryType;
#define PerProcessGraphicsAddress                0
#define GlobalGraphicsAddress                    1
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   __gen_address_type                   MemoryAddress;
   uint32_t                             Operand1DataDword0;
   uint32_t                             Operand2DataDword0;
   uint32_t                             Operand1DataDword1;
   uint32_t                             Operand2DataDword1;
   uint32_t                             Operand1DataDword2;
   uint32_t                             Operand2DataDword2;
   uint32_t                             Operand1DataDword3;
   uint32_t                             Operand2DataDword3;
};

static inline __attribute__((always_inline)) void
GFX9_MI_ATOMIC_pack(__attribute__((unused)) __gen_user_data *data,
                    __attribute__((unused)) void * restrict dst,
                    __attribute__((unused)) const struct GFX9_MI_ATOMIC * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->ATOMICOPCODE, 8, 15) |
      util_bitpack_uint(values->ReturnDataControl, 16, 16) |
      util_bitpack_uint(values->CSSTALL, 17, 17) |
      util_bitpack_uint(values->InlineData, 18, 18) |
      util_bitpack_uint(values->DataSize, 19, 20) |
      util_bitpack_uint(values->PostSyncOperation, 21, 21) |
      util_bitpack_uint(values->MemoryType, 22, 22) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->MemoryAddress, 0, 2, 47);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;
}

#define GFX9_MI_BATCH_BUFFER_END_length        1
#define GFX9_MI_BATCH_BUFFER_END_length_bias      1
#define GFX9_MI_BATCH_BUFFER_END_header         \
   .MICommandOpcode                     =     10,  \
   .CommandType                         =      0

struct GFX9_MI_BATCH_BUFFER_END {
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_MI_BATCH_BUFFER_END_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_MI_BATCH_BUFFER_END * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_MI_BATCH_BUFFER_START_length      3
#define GFX9_MI_BATCH_BUFFER_START_length_bias      2
#define GFX9_MI_BATCH_BUFFER_START_header       \
   .DWordLength                         =      1,  \
   .MICommandOpcode                     =     49,  \
   .CommandType                         =      0

struct GFX9_MI_BATCH_BUFFER_START {
   uint32_t                             DWordLength;
   uint32_t                             AddressSpaceIndicator;
#define ASI_GGTT                                 0
#define ASI_PPGTT                                1
   bool                                 ResourceStreamerEnable;
   bool                                 PredicationEnable;
   bool                                 AddOffsetEnable;
   uint32_t                             SecondLevelBatchBuffer;
#define Firstlevelbatch                          0
#define Secondlevelbatch                         1
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   __gen_address_type                   BatchBufferStartAddress;
};

static inline __attribute__((always_inline)) void
GFX9_MI_BATCH_BUFFER_START_pack(__attribute__((unused)) __gen_user_data *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GFX9_MI_BATCH_BUFFER_START * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->AddressSpaceIndicator, 8, 8) |
      util_bitpack_uint(values->ResourceStreamerEnable, 10, 10) |
      util_bitpack_uint(values->PredicationEnable, 15, 15) |
      util_bitpack_uint(values->AddOffsetEnable, 16, 16) |
      util_bitpack_uint(values->SecondLevelBatchBuffer, 22, 22) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->BatchBufferStartAddress, 0, 2, 63);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;
}

#define GFX9_MI_CLFLUSH_length_bias            2
#define GFX9_MI_CLFLUSH_header                  \
   .DWordLength                         =      1,  \
   .MICommandOpcode                     =     39,  \
   .CommandType                         =      0

struct GFX9_MI_CLFLUSH {
   uint32_t                             DWordLength;
   bool                                 UseGlobalGTT;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint32_t                             StartingCachelineOffset;
   __gen_address_type                   PageBaseAddress;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_MI_CLFLUSH_pack(__attribute__((unused)) __gen_user_data *data,
                     __attribute__((unused)) void * restrict dst,
                     __attribute__((unused)) const struct GFX9_MI_CLFLUSH * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 9) |
      util_bitpack_uint(values->UseGlobalGTT, 22, 22) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1 =
      util_bitpack_uint(values->StartingCachelineOffset, 6, 11);
   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->PageBaseAddress, v1, 12, 47);
   dw[1] = v1_address;
   dw[2] = (v1_address >> 32) | (v1 >> 32);
}

#define GFX9_MI_CONDITIONAL_BATCH_BUFFER_END_length      4
#define GFX9_MI_CONDITIONAL_BATCH_BUFFER_END_length_bias      2
#define GFX9_MI_CONDITIONAL_BATCH_BUFFER_END_header\
   .DWordLength                         =      2,  \
   .CompareSemaphore                    =      0,  \
   .MICommandOpcode                     =     54,  \
   .CommandType                         =      0

struct GFX9_MI_CONDITIONAL_BATCH_BUFFER_END {
   uint32_t                             DWordLength;
   uint32_t                             CompareMaskMode;
#define CompareMaskModeDisabled                  0
#define CompareMaskModeEnabled                   1
   uint32_t                             CompareSemaphore;
   bool                                 UseGlobalGTT;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint32_t                             CompareDataDword;
   __gen_address_type                   CompareAddress;
};

static inline __attribute__((always_inline)) void
GFX9_MI_CONDITIONAL_BATCH_BUFFER_END_pack(__attribute__((unused)) __gen_user_data *data,
                                          __attribute__((unused)) void * restrict dst,
                                          __attribute__((unused)) const struct GFX9_MI_CONDITIONAL_BATCH_BUFFER_END * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->CompareMaskMode, 19, 19) |
      util_bitpack_uint(values->CompareSemaphore, 21, 21) |
      util_bitpack_uint(values->UseGlobalGTT, 22, 22) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->CompareDataDword, 0, 31);

   const uint64_t v2_address =
      __gen_address(data, &dw[2], values->CompareAddress, 0, 3, 63);
   dw[2] = v2_address;
   dw[3] = v2_address >> 32;
}

#define GFX9_MI_COPY_MEM_MEM_length            5
#define GFX9_MI_COPY_MEM_MEM_length_bias       2
#define GFX9_MI_COPY_MEM_MEM_header             \
   .DWordLength                         =      3,  \
   .MICommandOpcode                     =     46,  \
   .CommandType                         =      0

struct GFX9_MI_COPY_MEM_MEM {
   uint32_t                             DWordLength;
   bool                                 UseGlobalGTTDestination;
   bool                                 UseGlobalGTTSource;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   __gen_address_type                   DestinationMemoryAddress;
   __gen_address_type                   SourceMemoryAddress;
};

static inline __attribute__((always_inline)) void
GFX9_MI_COPY_MEM_MEM_pack(__attribute__((unused)) __gen_user_data *data,
                          __attribute__((unused)) void * restrict dst,
                          __attribute__((unused)) const struct GFX9_MI_COPY_MEM_MEM * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->UseGlobalGTTDestination, 21, 21) |
      util_bitpack_uint(values->UseGlobalGTTSource, 22, 22) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->DestinationMemoryAddress, 0, 2, 63);
   dw[1] = v1_address;
   dw[2] = v1_address >> 32;

   const uint64_t v3_address =
      __gen_address(data, &dw[3], values->SourceMemoryAddress, 0, 2, 63);
   dw[3] = v3_address;
   dw[4] = v3_address >> 32;
}

#define GFX9_MI_DISPLAY_FLIP_length            3
#define GFX9_MI_DISPLAY_FLIP_length_bias       2
#define GFX9_MI_DISPLAY_FLIP_header             \
   .DWordLength                         =      1,  \
   .MICommandOpcode                     =     20,  \
   .CommandType                         =      0

struct GFX9_MI_DISPLAY_FLIP {
   uint32_t                             DWordLength;
   uint32_t                             DisplayPlaneSelect;
#define DisplayPlane1                            0
#define DisplayPlane2                            1
#define DisplayPlane3                            2
#define DisplayPlane4                            4
#define DisplayPlane5                            5
#define DisplayPlane6                            6
#define DisplayPlane7                            7
#define DisplayPlane8                            8
#define DisplayPlane9                            9
#define DisplayPlane10                           10
#define DisplayPlane11                           11
#define DisplayPlane12                           12
   bool                                 AsyncFlipIndicator;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint32_t                             TileParameter;
   uint32_t                             DisplayBufferPitch;
   bool                                 Stereoscopic3DMode;
   uint32_t                             FlipType;
#define SyncFlip                                 0
#define AsyncFlip                                1
#define Stereo3DFlip                             2
   __gen_address_type                   DisplayBufferBaseAddress;
   __gen_address_type                   LeftEyeDisplayBufferBaseAddress;
};

static inline __attribute__((always_inline)) void
GFX9_MI_DISPLAY_FLIP_pack(__attribute__((unused)) __gen_user_data *data,
                          __attribute__((unused)) void * restrict dst,
                          __attribute__((unused)) const struct GFX9_MI_DISPLAY_FLIP * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->DisplayPlaneSelect, 8, 12) |
      util_bitpack_uint(values->AsyncFlipIndicator, 22, 22) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->TileParameter, 0, 2) |
      util_bitpack_uint(values->DisplayBufferPitch, 6, 15) |
      util_bitpack_uint(values->Stereoscopic3DMode, 31, 31);

   const uint32_t v2 =
      util_bitpack_uint(values->FlipType, 0, 1);
   dw[2] = __gen_address(data, &dw[2], values->DisplayBufferBaseAddress, v2, 12, 31);
}

#define GFX9_MI_FLUSH_DW_length                5
#define GFX9_MI_FLUSH_DW_length_bias           2
#define GFX9_MI_FLUSH_DW_header                 \
   .DWordLength                         =      3,  \
   .MICommandOpcode                     =     38,  \
   .CommandType                         =      0

struct GFX9_MI_FLUSH_DW {
   uint32_t                             DWordLength;
   bool                                 VideoPipelineCacheInvalidate;
   bool                                 NotifyEnable;
   bool                                 FlushLLC;
   uint32_t                             PostSyncOperation;
   bool                                 TLBInvalidate;
   uint32_t                             StoreDataIndex;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint32_t                             DestinationAddressType;
#define DAT_PPGTT                                0
#define DAT_GGTT                                 1
   __gen_address_type                   Address;
   uint64_t                             ImmediateData;
};

static inline __attribute__((always_inline)) void
GFX9_MI_FLUSH_DW_pack(__attribute__((unused)) __gen_user_data *data,
                      __attribute__((unused)) void * restrict dst,
                      __attribute__((unused)) const struct GFX9_MI_FLUSH_DW * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 5) |
      util_bitpack_uint(values->VideoPipelineCacheInvalidate, 7, 7) |
      util_bitpack_uint(values->NotifyEnable, 8, 8) |
      util_bitpack_uint(values->FlushLLC, 9, 9) |
      util_bitpack_uint(values->PostSyncOperation, 14, 15) |
      util_bitpack_uint(values->TLBInvalidate, 18, 18) |
      util_bitpack_uint(values->StoreDataIndex, 21, 21) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1 =
      util_bitpack_uint(values->DestinationAddressType, 2, 2);
   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->Address, v1, 3, 47);
   dw[1] = v1_address;
   dw[2] = (v1_address >> 32) | (v1 >> 32);

   const uint64_t v3 =
      util_bitpack_uint(values->ImmediateData, 0, 63);
   dw[3] = v3;
   dw[4] = v3 >> 32;
}

#define GFX9_MI_FORCE_WAKEUP_length            2
#define GFX9_MI_FORCE_WAKEUP_length_bias       2
#define GFX9_MI_FORCE_WAKEUP_header             \
   .DWordLength                         =      0,  \
   .MICommandOpcode                     =     29,  \
   .CommandType                         =      0

struct GFX9_MI_FORCE_WAKEUP {
   uint32_t                             DWordLength;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint32_t                             ForceMediaAwake;
   uint32_t                             ForceRenderAwake;
   uint32_t                             MaskBits;
};

static inline __attribute__((always_inline)) void
GFX9_MI_FORCE_WAKEUP_pack(__attribute__((unused)) __gen_user_data *data,
                          __attribute__((unused)) void * restrict dst,
                          __attribute__((unused)) const struct GFX9_MI_FORCE_WAKEUP * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->ForceMediaAwake, 0, 0) |
      util_bitpack_uint(values->ForceRenderAwake, 1, 1) |
      util_bitpack_uint(values->MaskBits, 16, 31);
}

#define GFX9_MI_LOAD_REGISTER_IMM_length       3
#define GFX9_MI_LOAD_REGISTER_IMM_length_bias      2
#define GFX9_MI_LOAD_REGISTER_IMM_header        \
   .DWordLength                         =      1,  \
   .MICommandOpcode                     =     34,  \
   .CommandType                         =      0

struct GFX9_MI_LOAD_REGISTER_IMM {
   uint32_t                             DWordLength;
   uint32_t                             ByteWriteDisables;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint64_t                             RegisterOffset;
   uint32_t                             DataDWord;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_MI_LOAD_REGISTER_IMM_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_MI_LOAD_REGISTER_IMM * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->ByteWriteDisables, 8, 11) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->RegisterOffset, 2, 22);

   dw[2] =
      util_bitpack_uint(values->DataDWord, 0, 31);
}

#define GFX9_MI_LOAD_REGISTER_MEM_length       4
#define GFX9_MI_LOAD_REGISTER_MEM_length_bias      2
#define GFX9_MI_LOAD_REGISTER_MEM_header        \
   .DWordLength                         =      2,  \
   .MICommandOpcode                     =     41,  \
   .CommandType                         =      0

struct GFX9_MI_LOAD_REGISTER_MEM {
   uint32_t                             DWordLength;
   bool                                 AsyncModeEnable;
   bool                                 UseGlobalGTT;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint64_t                             RegisterAddress;
   __gen_address_type                   MemoryAddress;
};

static inline __attribute__((always_inline)) void
GFX9_MI_LOAD_REGISTER_MEM_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_MI_LOAD_REGISTER_MEM * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->AsyncModeEnable, 21, 21) |
      util_bitpack_uint(values->UseGlobalGTT, 22, 22) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->RegisterAddress, 2, 22);

   const uint64_t v2_address =
      __gen_address(data, &dw[2], values->MemoryAddress, 0, 2, 63);
   dw[2] = v2_address;
   dw[3] = v2_address >> 32;
}

#define GFX9_MI_LOAD_REGISTER_REG_length       3
#define GFX9_MI_LOAD_REGISTER_REG_length_bias      2
#define GFX9_MI_LOAD_REGISTER_REG_header        \
   .DWordLength                         =      1,  \
   .MICommandOpcode                     =     42,  \
   .CommandType                         =      0

struct GFX9_MI_LOAD_REGISTER_REG {
   uint32_t                             DWordLength;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint64_t                             SourceRegisterAddress;
   uint64_t                             DestinationRegisterAddress;
};

static inline __attribute__((always_inline)) void
GFX9_MI_LOAD_REGISTER_REG_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_MI_LOAD_REGISTER_REG * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->SourceRegisterAddress, 2, 22);

   dw[2] =
      __gen_offset(values->DestinationRegisterAddress, 2, 22);
}

#define GFX9_MI_LOAD_SCAN_LINES_EXCL_length      2
#define GFX9_MI_LOAD_SCAN_LINES_EXCL_length_bias      2
#define GFX9_MI_LOAD_SCAN_LINES_EXCL_header     \
   .DWordLength                         =      0,  \
   .MICommandOpcode                     =     19,  \
   .CommandType                         =      0

struct GFX9_MI_LOAD_SCAN_LINES_EXCL {
   uint32_t                             DWordLength;
   uint32_t                             DisplayPlaneSelect;
#define DisplayPlaneA                            0
#define DisplayPlaneB                            1
#define DisplayPlaneC                            4
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint32_t                             EndScanLineNumber;
   uint32_t                             StartScanLineNumber;
};

static inline __attribute__((always_inline)) void
GFX9_MI_LOAD_SCAN_LINES_EXCL_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_MI_LOAD_SCAN_LINES_EXCL * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 5) |
      util_bitpack_uint(values->DisplayPlaneSelect, 19, 21) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->EndScanLineNumber, 0, 12) |
      util_bitpack_uint(values->StartScanLineNumber, 16, 28);
}

#define GFX9_MI_LOAD_SCAN_LINES_INCL_length      2
#define GFX9_MI_LOAD_SCAN_LINES_INCL_length_bias      2
#define GFX9_MI_LOAD_SCAN_LINES_INCL_header     \
   .DWordLength                         =      0,  \
   .MICommandOpcode                     =     18,  \
   .CommandType                         =      0

struct GFX9_MI_LOAD_SCAN_LINES_INCL {
   uint32_t                             DWordLength;
   uint32_t                             ScanLineEventDoneForward;
   uint32_t                             DisplayPlaneSelect;
#define DisplayPlane1A                           0
#define DisplayPlane1B                           1
#define DisplayPlane1C                           4
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint32_t                             EndScanLineNumber;
   uint32_t                             StartScanLineNumber;
};

static inline __attribute__((always_inline)) void
GFX9_MI_LOAD_SCAN_LINES_INCL_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_MI_LOAD_SCAN_LINES_INCL * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 5) |
      util_bitpack_uint(values->ScanLineEventDoneForward, 17, 18) |
      util_bitpack_uint(values->DisplayPlaneSelect, 19, 21) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->EndScanLineNumber, 0, 12) |
      util_bitpack_uint(values->StartScanLineNumber, 16, 28);
}

#define GFX9_MI_LOAD_URB_MEM_length            4
#define GFX9_MI_LOAD_URB_MEM_length_bias       2
#define GFX9_MI_LOAD_URB_MEM_header             \
   .DWordLength                         =      2,  \
   .MICommandOpcode                     =     44,  \
   .CommandType                         =      0

struct GFX9_MI_LOAD_URB_MEM {
   uint32_t                             DWordLength;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint32_t                             URBAddress;
   __gen_address_type                   MemoryAddress;
};

static inline __attribute__((always_inline)) void
GFX9_MI_LOAD_URB_MEM_pack(__attribute__((unused)) __gen_user_data *data,
                          __attribute__((unused)) void * restrict dst,
                          __attribute__((unused)) const struct GFX9_MI_LOAD_URB_MEM * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->URBAddress, 2, 14);

   const uint64_t v2_address =
      __gen_address(data, &dw[2], values->MemoryAddress, 0, 6, 63);
   dw[2] = v2_address;
   dw[3] = v2_address >> 32;
}

#define GFX9_MI_MATH_length_bias               2
#define GFX9_MI_MATH_header                     \
   .DWordLength                         =      0,  \
   .MICommandOpcode                     =     26,  \
   .CommandType                         =      0

struct GFX9_MI_MATH {
   uint32_t                             DWordLength;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   /* variable length fields follow */
};

static inline __attribute__((always_inline)) void
GFX9_MI_MATH_pack(__attribute__((unused)) __gen_user_data *data,
                  __attribute__((unused)) void * restrict dst,
                  __attribute__((unused)) const struct GFX9_MI_MATH * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_MI_NOOP_length                    1
#define GFX9_MI_NOOP_length_bias               1
#define GFX9_MI_NOOP_header                     \
   .MICommandOpcode                     =      0,  \
   .CommandType                         =      0

struct GFX9_MI_NOOP {
   uint32_t                             IdentificationNumber;
   bool                                 IdentificationNumberRegisterWriteEnable;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_MI_NOOP_pack(__attribute__((unused)) __gen_user_data *data,
                  __attribute__((unused)) void * restrict dst,
                  __attribute__((unused)) const struct GFX9_MI_NOOP * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->IdentificationNumber, 0, 21) |
      util_bitpack_uint(values->IdentificationNumberRegisterWriteEnable, 22, 22) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_MI_PREDICATE_length               1
#define GFX9_MI_PREDICATE_length_bias          1
#define GFX9_MI_PREDICATE_header                \
   .MICommandOpcode                     =     12,  \
   .CommandType                         =      0

struct GFX9_MI_PREDICATE {
   uint32_t                             CompareOperation;
#define COMPARE_TRUE                             0
#define COMPARE_FALSE                            1
#define COMPARE_SRCS_EQUAL                       2
#define COMPARE_DELTAS_EQUAL                     3
   uint32_t                             CombineOperation;
#define COMBINE_SET                              0
#define COMBINE_AND                              1
#define COMBINE_OR                               2
#define COMBINE_XOR                              3
   uint32_t                             LoadOperation;
#define LOAD_KEEP                                0
#define LOAD_LOAD                                2
#define LOAD_LOADINV                             3
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_MI_PREDICATE_pack(__attribute__((unused)) __gen_user_data *data,
                       __attribute__((unused)) void * restrict dst,
                       __attribute__((unused)) const struct GFX9_MI_PREDICATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->CompareOperation, 0, 1) |
      util_bitpack_uint(values->CombineOperation, 3, 4) |
      util_bitpack_uint(values->LoadOperation, 6, 7) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_MI_REPORT_HEAD_length             1
#define GFX9_MI_REPORT_HEAD_length_bias        1
#define GFX9_MI_REPORT_HEAD_header              \
   .MICommandOpcode                     =      7,  \
   .CommandType                         =      0

struct GFX9_MI_REPORT_HEAD {
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_MI_REPORT_HEAD_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_MI_REPORT_HEAD * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_MI_REPORT_PERF_COUNT_length       4
#define GFX9_MI_REPORT_PERF_COUNT_length_bias      2
#define GFX9_MI_REPORT_PERF_COUNT_header        \
   .DWordLength                         =      2,  \
   .MICommandOpcode                     =     40,  \
   .CommandType                         =      0

struct GFX9_MI_REPORT_PERF_COUNT {
   uint32_t                             DWordLength;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   bool                                 UseGlobalGTT;
   uint32_t                             CoreModeEnable;
   __gen_address_type                   MemoryAddress;
   uint32_t                             ReportID;
};

static inline __attribute__((always_inline)) void
GFX9_MI_REPORT_PERF_COUNT_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_MI_REPORT_PERF_COUNT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 5) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1 =
      util_bitpack_uint(values->UseGlobalGTT, 0, 0) |
      util_bitpack_uint(values->CoreModeEnable, 4, 4);
   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->MemoryAddress, v1, 6, 63);
   dw[1] = v1_address;
   dw[2] = (v1_address >> 32) | (v1 >> 32);

   dw[3] =
      util_bitpack_uint(values->ReportID, 0, 31);
}

#define GFX9_MI_RS_CONTEXT_length              1
#define GFX9_MI_RS_CONTEXT_length_bias         1
#define GFX9_MI_RS_CONTEXT_header               \
   .MICommandOpcode                     =     15,  \
   .CommandType                         =      0

struct GFX9_MI_RS_CONTEXT {
   uint32_t                             ResourceStreamerSave;
#define RS_Restore                               0
#define RS_Save                                  1
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_MI_RS_CONTEXT_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_MI_RS_CONTEXT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->ResourceStreamerSave, 0, 0) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_MI_RS_CONTROL_length              1
#define GFX9_MI_RS_CONTROL_length_bias         1
#define GFX9_MI_RS_CONTROL_header               \
   .MICommandOpcode                     =      6,  \
   .CommandType                         =      0

struct GFX9_MI_RS_CONTROL {
   uint32_t                             ResourceStreamerControl;
#define RS_Stop                                  0
#define RS_Start                                 1
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_MI_RS_CONTROL_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_MI_RS_CONTROL * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->ResourceStreamerControl, 0, 0) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_MI_RS_STORE_DATA_IMM_length       4
#define GFX9_MI_RS_STORE_DATA_IMM_length_bias      2
#define GFX9_MI_RS_STORE_DATA_IMM_header        \
   .DWordLength                         =      2,  \
   .MICommandOpcode                     =     43,  \
   .CommandType                         =      0

struct GFX9_MI_RS_STORE_DATA_IMM {
   uint32_t                             DWordLength;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint32_t                             CoreModeEnable;
   __gen_address_type                   DestinationAddress;
   uint32_t                             DataDWord0;
};

static inline __attribute__((always_inline)) void
GFX9_MI_RS_STORE_DATA_IMM_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_MI_RS_STORE_DATA_IMM * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1 =
      util_bitpack_uint(values->CoreModeEnable, 0, 0);
   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->DestinationAddress, v1, 2, 63);
   dw[1] = v1_address;
   dw[2] = (v1_address >> 32) | (v1 >> 32);

   dw[3] =
      util_bitpack_uint(values->DataDWord0, 0, 31);
}

#define GFX9_MI_SEMAPHORE_SIGNAL_length        2
#define GFX9_MI_SEMAPHORE_SIGNAL_length_bias      2
#define GFX9_MI_SEMAPHORE_SIGNAL_header         \
   .DWordLength                         =      0,  \
   .MICommandOpcode                     =     27,  \
   .CommandType                         =      0

struct GFX9_MI_SEMAPHORE_SIGNAL {
   uint32_t                             DWordLength;
   uint32_t                             TargetEngineSelect;
#define RCS                                      0
#define VCS0                                     1
#define BCS                                      2
#define VECS                                     3
#define VCS1                                     4
   bool                                 PostSyncOperation;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint32_t                             TargetContextID;
};

static inline __attribute__((always_inline)) void
GFX9_MI_SEMAPHORE_SIGNAL_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_MI_SEMAPHORE_SIGNAL * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->TargetEngineSelect, 15, 17) |
      util_bitpack_uint(values->PostSyncOperation, 21, 21) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->TargetContextID, 0, 31);
}

#define GFX9_MI_SEMAPHORE_WAIT_length          4
#define GFX9_MI_SEMAPHORE_WAIT_length_bias      2
#define GFX9_MI_SEMAPHORE_WAIT_header           \
   .DWordLength                         =      2,  \
   .MICommandOpcode                     =     28,  \
   .CommandType                         =      0

struct GFX9_MI_SEMAPHORE_WAIT {
   uint32_t                             DWordLength;
   uint32_t                             CompareOperation;
#define COMPARE_SAD_GREATER_THAN_SDD             0
#define COMPARE_SAD_GREATER_THAN_OR_EQUAL_SDD    1
#define COMPARE_SAD_LESS_THAN_SDD                2
#define COMPARE_SAD_LESS_THAN_OR_EQUAL_SDD       3
#define COMPARE_SAD_EQUAL_SDD                    4
#define COMPARE_SAD_NOT_EQUAL_SDD                5
   uint32_t                             WaitMode;
#define PollingMode                              1
#define SignalMode                               0
   bool                                 RegisterPollMode;
   uint32_t                             MemoryType;
#define PerProcessGraphicsAddress                0
#define GlobalGraphicsAddress                    1
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint32_t                             SemaphoreDataDword;
   __gen_address_type                   SemaphoreAddress;
};

static inline __attribute__((always_inline)) void
GFX9_MI_SEMAPHORE_WAIT_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_MI_SEMAPHORE_WAIT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->CompareOperation, 12, 14) |
      util_bitpack_uint(values->WaitMode, 15, 15) |
      util_bitpack_uint(values->RegisterPollMode, 16, 16) |
      util_bitpack_uint(values->MemoryType, 22, 22) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->SemaphoreDataDword, 0, 31);

   const uint64_t v2_address =
      __gen_address(data, &dw[2], values->SemaphoreAddress, 0, 2, 63);
   dw[2] = v2_address;
   dw[3] = v2_address >> 32;
}

#define GFX9_MI_SET_CONTEXT_length             2
#define GFX9_MI_SET_CONTEXT_length_bias        2
#define GFX9_MI_SET_CONTEXT_header              \
   .DWordLength                         =      0,  \
   .MICommandOpcode                     =     24,  \
   .CommandType                         =      0

struct GFX9_MI_SET_CONTEXT {
   uint32_t                             DWordLength;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint32_t                             RestoreInhibit;
   uint32_t                             ForceRestore;
   bool                                 ResourceStreamerStateRestoreEnable;
   bool                                 ResourceStreamerStateSaveEnable;
   bool                                 CoreModeEnable;
   uint32_t                             ReservedMustbe1;
   __gen_address_type                   LogicalContextAddress;
};

static inline __attribute__((always_inline)) void
GFX9_MI_SET_CONTEXT_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_MI_SET_CONTEXT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint32_t v1 =
      util_bitpack_uint(values->RestoreInhibit, 0, 0) |
      util_bitpack_uint(values->ForceRestore, 1, 1) |
      util_bitpack_uint(values->ResourceStreamerStateRestoreEnable, 2, 2) |
      util_bitpack_uint(values->ResourceStreamerStateSaveEnable, 3, 3) |
      util_bitpack_uint(values->CoreModeEnable, 4, 4) |
      util_bitpack_uint(values->ReservedMustbe1, 8, 8);
   dw[1] = __gen_address(data, &dw[1], values->LogicalContextAddress, v1, 12, 31);
}

#define GFX9_MI_SET_PREDICATE_length           1
#define GFX9_MI_SET_PREDICATE_length_bias      1
#define GFX9_MI_SET_PREDICATE_header            \
   .MICommandOpcode                     =      1,  \
   .CommandType                         =      0

struct GFX9_MI_SET_PREDICATE {
   uint32_t                             PREDICATEENABLE;
#define NOOPNever                                0
#define NOOPonResult2clear                       1
#define NOOPonResult2set                         2
#define NOOPonResultclear                        3
#define NOOPonResultset                          4
#define Executewhenonesliceenabled               5
#define Executewhentwoslicesareenabled           6
#define Executewhenthreeslicesareenabled         7
#define NOOPAlways                               15
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_MI_SET_PREDICATE_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_MI_SET_PREDICATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->PREDICATEENABLE, 0, 3) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_MI_STORE_DATA_IMM_length          4
#define GFX9_MI_STORE_DATA_IMM_length_bias      2
#define GFX9_MI_STORE_DATA_IMM_header           \
   .DWordLength                         =      2,  \
   .MICommandOpcode                     =     32,  \
   .CommandType                         =      0

struct GFX9_MI_STORE_DATA_IMM {
   uint32_t                             DWordLength;
   uint32_t                             StoreQword;
   bool                                 UseGlobalGTT;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint32_t                             CoreModeEnable;
   __gen_address_type                   Address;
   uint64_t                             ImmediateData;
};

static inline __attribute__((always_inline)) void
GFX9_MI_STORE_DATA_IMM_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_MI_STORE_DATA_IMM * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 9) |
      util_bitpack_uint(values->StoreQword, 21, 21) |
      util_bitpack_uint(values->UseGlobalGTT, 22, 22) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1 =
      util_bitpack_uint(values->CoreModeEnable, 0, 0);
   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->Address, v1, 2, 47);
   dw[1] = v1_address;
   dw[2] = (v1_address >> 32) | (v1 >> 32);

   const uint64_t v3 =
      util_bitpack_uint(values->ImmediateData, 0, 63);
   dw[3] = v3;
   dw[4] = v3 >> 32;
}

#define GFX9_MI_STORE_DATA_INDEX_length        3
#define GFX9_MI_STORE_DATA_INDEX_length_bias      2
#define GFX9_MI_STORE_DATA_INDEX_header         \
   .DWordLength                         =      1,  \
   .MICommandOpcode                     =     33,  \
   .CommandType                         =      0

struct GFX9_MI_STORE_DATA_INDEX {
   uint32_t                             DWordLength;
   uint32_t                             UsePerProcessHardwareStatusPage;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint32_t                             Offset;
   uint32_t                             DataDWord0;
   uint32_t                             DataDWord1;
};

static inline __attribute__((always_inline)) void
GFX9_MI_STORE_DATA_INDEX_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_MI_STORE_DATA_INDEX * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->UsePerProcessHardwareStatusPage, 21, 21) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->Offset, 2, 11);

   dw[2] =
      util_bitpack_uint(values->DataDWord0, 0, 31);
}

#define GFX9_MI_STORE_REGISTER_MEM_length      4
#define GFX9_MI_STORE_REGISTER_MEM_length_bias      2
#define GFX9_MI_STORE_REGISTER_MEM_header       \
   .DWordLength                         =      2,  \
   .MICommandOpcode                     =     36,  \
   .CommandType                         =      0

struct GFX9_MI_STORE_REGISTER_MEM {
   uint32_t                             DWordLength;
   bool                                 PredicateEnable;
   bool                                 UseGlobalGTT;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint64_t                             RegisterAddress;
   __gen_address_type                   MemoryAddress;
};

static inline __attribute__((always_inline)) void
GFX9_MI_STORE_REGISTER_MEM_pack(__attribute__((unused)) __gen_user_data *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GFX9_MI_STORE_REGISTER_MEM * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->PredicateEnable, 21, 21) |
      util_bitpack_uint(values->UseGlobalGTT, 22, 22) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      __gen_offset(values->RegisterAddress, 2, 22);

   const uint64_t v2_address =
      __gen_address(data, &dw[2], values->MemoryAddress, 0, 2, 63);
   dw[2] = v2_address;
   dw[3] = v2_address >> 32;
}

#define GFX9_MI_STORE_URB_MEM_length           4
#define GFX9_MI_STORE_URB_MEM_length_bias      2
#define GFX9_MI_STORE_URB_MEM_header            \
   .DWordLength                         =      2,  \
   .MICommandOpcode                     =     45,  \
   .CommandType                         =      0

struct GFX9_MI_STORE_URB_MEM {
   uint32_t                             DWordLength;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
   uint32_t                             URBAddress;
   __gen_address_type                   MemoryAddress;
};

static inline __attribute__((always_inline)) void
GFX9_MI_STORE_URB_MEM_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_MI_STORE_URB_MEM * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->URBAddress, 2, 14);

   const uint64_t v2_address =
      __gen_address(data, &dw[2], values->MemoryAddress, 0, 6, 63);
   dw[2] = v2_address;
   dw[3] = v2_address >> 32;
}

#define GFX9_MI_SUSPEND_FLUSH_length           1
#define GFX9_MI_SUSPEND_FLUSH_length_bias      1
#define GFX9_MI_SUSPEND_FLUSH_header            \
   .MICommandOpcode                     =     11,  \
   .CommandType                         =      0

struct GFX9_MI_SUSPEND_FLUSH {
   bool                                 SuspendFlush;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_MI_SUSPEND_FLUSH_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_MI_SUSPEND_FLUSH * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->SuspendFlush, 0, 0) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_MI_TOPOLOGY_FILTER_length         1
#define GFX9_MI_TOPOLOGY_FILTER_length_bias      1
#define GFX9_MI_TOPOLOGY_FILTER_header          \
   .MICommandOpcode                     =     13,  \
   .CommandType                         =      0

struct GFX9_MI_TOPOLOGY_FILTER {
   enum GFX9_3D_Prim_Topo_Type          TopologyFilterValue;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_MI_TOPOLOGY_FILTER_pack(__attribute__((unused)) __gen_user_data *data,
                             __attribute__((unused)) void * restrict dst,
                             __attribute__((unused)) const struct GFX9_MI_TOPOLOGY_FILTER * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->TopologyFilterValue, 0, 5) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_MI_URB_ATOMIC_ALLOC_length        1
#define GFX9_MI_URB_ATOMIC_ALLOC_length_bias      1
#define GFX9_MI_URB_ATOMIC_ALLOC_header         \
   .MICommandOpcode                     =      9,  \
   .CommandType                         =      0

struct GFX9_MI_URB_ATOMIC_ALLOC {
   uint32_t                             URBAtomicStorageSize;
   uint32_t                             URBAtomicStorageOffset;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_MI_URB_ATOMIC_ALLOC_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_MI_URB_ATOMIC_ALLOC * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->URBAtomicStorageSize, 0, 8) |
      util_bitpack_uint(values->URBAtomicStorageOffset, 12, 19) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_MI_USER_INTERRUPT_length          1
#define GFX9_MI_USER_INTERRUPT_length_bias      1
#define GFX9_MI_USER_INTERRUPT_header           \
   .MICommandOpcode                     =      2,  \
   .CommandType                         =      0

struct GFX9_MI_USER_INTERRUPT {
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_MI_USER_INTERRUPT_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_MI_USER_INTERRUPT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_MI_WAIT_FOR_EVENT_length          1
#define GFX9_MI_WAIT_FOR_EVENT_length_bias      1
#define GFX9_MI_WAIT_FOR_EVENT_header           \
   .MICommandOpcode                     =      3,  \
   .CommandType                         =      0

struct GFX9_MI_WAIT_FOR_EVENT {
   bool                                 DisplayPlnae1AScanLineWaitEnable;
   bool                                 DisplayPlane1FlipPendingWaitEnable;
   bool                                 DisplayPlane4FlipPendingWaitEnable;
   bool                                 DisplayPlane1AVerticalBlankWaitEnable;
   bool                                 DisplayPlane7FlipPendingWaitEnable;
   bool                                 DisplayPlane8FlipPendingWaitEnable;
   bool                                 DisplayPlane1BScanLineWaitEnable;
   bool                                 DisplayPlane2FlipPendingWaitEnable;
   bool                                 DisplayPlane5FlipPendingWaitEnable;
   bool                                 DisplayPlane1BVerticalBlankWaitEnable;
   bool                                 DisplayPlane1CScanLineWaitEnable;
   bool                                 DisplayPlane3FlipPendingWaitEnable;
   bool                                 DisplayPlane9FlipPendingWaitEnable;
   bool                                 DisplayPlane10FlipPendingWaitEnable;
   bool                                 DisplayPlane11FlipPendingWaitEnable;
   bool                                 DisplayPlane12FlipPendingWaitEnable;
   bool                                 DisplayPlane6FlipPendingWaitEnable;
   bool                                 DisplayPlane1CVerticalBlankWaitEnable;
   uint32_t                             MICommandOpcode;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_MI_WAIT_FOR_EVENT_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_MI_WAIT_FOR_EVENT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DisplayPlnae1AScanLineWaitEnable, 0, 0) |
      util_bitpack_uint(values->DisplayPlane1FlipPendingWaitEnable, 1, 1) |
      util_bitpack_uint(values->DisplayPlane4FlipPendingWaitEnable, 2, 2) |
      util_bitpack_uint(values->DisplayPlane1AVerticalBlankWaitEnable, 3, 3) |
      util_bitpack_uint(values->DisplayPlane7FlipPendingWaitEnable, 6, 6) |
      util_bitpack_uint(values->DisplayPlane8FlipPendingWaitEnable, 7, 7) |
      util_bitpack_uint(values->DisplayPlane1BScanLineWaitEnable, 8, 8) |
      util_bitpack_uint(values->DisplayPlane2FlipPendingWaitEnable, 9, 9) |
      util_bitpack_uint(values->DisplayPlane5FlipPendingWaitEnable, 10, 10) |
      util_bitpack_uint(values->DisplayPlane1BVerticalBlankWaitEnable, 11, 11) |
      util_bitpack_uint(values->DisplayPlane1CScanLineWaitEnable, 14, 14) |
      util_bitpack_uint(values->DisplayPlane3FlipPendingWaitEnable, 15, 15) |
      util_bitpack_uint(values->DisplayPlane9FlipPendingWaitEnable, 16, 16) |
      util_bitpack_uint(values->DisplayPlane10FlipPendingWaitEnable, 17, 17) |
      util_bitpack_uint(values->DisplayPlane11FlipPendingWaitEnable, 18, 18) |
      util_bitpack_uint(values->DisplayPlane12FlipPendingWaitEnable, 19, 19) |
      util_bitpack_uint(values->DisplayPlane6FlipPendingWaitEnable, 20, 20) |
      util_bitpack_uint(values->DisplayPlane1CVerticalBlankWaitEnable, 21, 21) |
      util_bitpack_uint(values->MICommandOpcode, 23, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_PIPELINE_SELECT_length            1
#define GFX9_PIPELINE_SELECT_length_bias       1
#define GFX9_PIPELINE_SELECT_header             \
   ._3DCommandSubOpcode                 =      4,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      1,  \
   .CommandType                         =      3

struct GFX9_PIPELINE_SELECT {
   uint32_t                             PipelineSelection;
#define _3D                                      0
#define Media                                    1
#define GPGPU                                    2
   bool                                 MediaSamplerDOPClockGateEnable;
   bool                                 ForceMediaAwake;
   uint32_t                             MaskBits;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
};

static inline __attribute__((always_inline)) void
GFX9_PIPELINE_SELECT_pack(__attribute__((unused)) __gen_user_data *data,
                          __attribute__((unused)) void * restrict dst,
                          __attribute__((unused)) const struct GFX9_PIPELINE_SELECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->PipelineSelection, 0, 1) |
      util_bitpack_uint(values->MediaSamplerDOPClockGateEnable, 4, 4) |
      util_bitpack_uint(values->ForceMediaAwake, 5, 5) |
      util_bitpack_uint(values->MaskBits, 8, 15) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);
}

#define GFX9_PIPE_CONTROL_length               6
#define GFX9_PIPE_CONTROL_length_bias          2
#define GFX9_PIPE_CONTROL_header                \
   .DWordLength                         =      4,  \
   ._3DCommandSubOpcode                 =      0,  \
   ._3DCommandOpcode                    =      2,  \
   .CommandSubType                      =      3,  \
   .CommandType                         =      3

struct GFX9_PIPE_CONTROL {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   bool                                 DepthCacheFlushEnable;
   bool                                 StallAtPixelScoreboard;
   bool                                 StateCacheInvalidationEnable;
   bool                                 ConstantCacheInvalidationEnable;
   bool                                 VFCacheInvalidationEnable;
   bool                                 DCFlushEnable;
   bool                                 PipeControlFlushEnable;
   bool                                 NotifyEnable;
   bool                                 IndirectStatePointersDisable;
   bool                                 TextureCacheInvalidationEnable;
   bool                                 InstructionCacheInvalidateEnable;
   bool                                 RenderTargetCacheFlushEnable;
   bool                                 DepthStallEnable;
   uint32_t                             PostSyncOperation;
#define NoWrite                                  0
#define WriteImmediateData                       1
#define WritePSDepthCount                        2
#define WriteTimestamp                           3
   bool                                 GenericMediaStateClear;
   bool                                 TLBInvalidate;
   bool                                 GlobalSnapshotCountReset;
   bool                                 CommandStreamerStallEnable;
   uint32_t                             StoreDataIndex;
   uint32_t                             LRIPostSyncOperation;
#define NoLRIOperation                           0
#define MMIOWriteImmediateData                   1
   uint32_t                             DestinationAddressType;
#define DAT_PPGTT                                0
#define DAT_GGTT                                 1
   bool                                 FlushLLC;
   __gen_address_type                   Address;
   uint64_t                             ImmediateData;
};

static inline __attribute__((always_inline)) void
GFX9_PIPE_CONTROL_pack(__attribute__((unused)) __gen_user_data *data,
                       __attribute__((unused)) void * restrict dst,
                       __attribute__((unused)) const struct GFX9_PIPE_CONTROL * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->DepthCacheFlushEnable, 0, 0) |
      util_bitpack_uint(values->StallAtPixelScoreboard, 1, 1) |
      util_bitpack_uint(values->StateCacheInvalidationEnable, 2, 2) |
      util_bitpack_uint(values->ConstantCacheInvalidationEnable, 3, 3) |
      util_bitpack_uint(values->VFCacheInvalidationEnable, 4, 4) |
      util_bitpack_uint(values->DCFlushEnable, 5, 5) |
      util_bitpack_uint(values->PipeControlFlushEnable, 7, 7) |
      util_bitpack_uint(values->NotifyEnable, 8, 8) |
      util_bitpack_uint(values->IndirectStatePointersDisable, 9, 9) |
      util_bitpack_uint(values->TextureCacheInvalidationEnable, 10, 10) |
      util_bitpack_uint(values->InstructionCacheInvalidateEnable, 11, 11) |
      util_bitpack_uint(values->RenderTargetCacheFlushEnable, 12, 12) |
      util_bitpack_uint(values->DepthStallEnable, 13, 13) |
      util_bitpack_uint(values->PostSyncOperation, 14, 15) |
      util_bitpack_uint(values->GenericMediaStateClear, 16, 16) |
      util_bitpack_uint(values->TLBInvalidate, 18, 18) |
      util_bitpack_uint(values->GlobalSnapshotCountReset, 19, 19) |
      util_bitpack_uint(values->CommandStreamerStallEnable, 20, 20) |
      util_bitpack_uint(values->StoreDataIndex, 21, 21) |
      util_bitpack_uint(values->LRIPostSyncOperation, 23, 23) |
      util_bitpack_uint(values->DestinationAddressType, 24, 24) |
      util_bitpack_uint(values->FlushLLC, 26, 26);

   const uint64_t v2_address =
      __gen_address(data, &dw[2], values->Address, 0, 2, 47);
   dw[2] = v2_address;
   dw[3] = v2_address >> 32;

   const uint64_t v4 =
      util_bitpack_uint(values->ImmediateData, 0, 63);
   dw[4] = v4;
   dw[5] = v4 >> 32;
}

#define GFX9_SFC_AVS_CHROMA_COEFF_TABLE_length     65
#define GFX9_SFC_AVS_CHROMA_COEFF_TABLE_length_bias      2
#define GFX9_SFC_AVS_CHROMA_COEFF_TABLE_header  \
   .DWordLength                         =     63,  \
   .SubOpcodeB                          =      6,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =     10,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_SFC_AVS_CHROMA_COEFF_TABLE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   struct GFX9_SFC_AVS_CHROMA_COEFF_TABLE_BODY AVSCHROMACoefficientTableBody;
};

static inline __attribute__((always_inline)) void
GFX9_SFC_AVS_CHROMA_COEFF_TABLE_pack(__attribute__((unused)) __gen_user_data *data,
                                     __attribute__((unused)) void * restrict dst,
                                     __attribute__((unused)) const struct GFX9_SFC_AVS_CHROMA_COEFF_TABLE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   GFX9_SFC_AVS_CHROMA_COEFF_TABLE_BODY_pack(data, &dw[1], &values->AVSCHROMACoefficientTableBody);
}

#define GFX9_SFC_AVS_LUMA_COEFF_TABLE_length    129
#define GFX9_SFC_AVS_LUMA_COEFF_TABLE_length_bias      2
#define GFX9_SFC_AVS_LUMA_COEFF_TABLE_header    \
   .DWordLength                         =    127,  \
   .SubOpcodeB                          =      5,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =     10,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_SFC_AVS_LUMA_COEFF_TABLE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   struct GFX9_SFC_AVS_LUMA_COEFF_TABLE_BODY AVSLUMACoefficientTableBody;
};

static inline __attribute__((always_inline)) void
GFX9_SFC_AVS_LUMA_COEFF_TABLE_pack(__attribute__((unused)) __gen_user_data *data,
                                   __attribute__((unused)) void * restrict dst,
                                   __attribute__((unused)) const struct GFX9_SFC_AVS_LUMA_COEFF_TABLE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   GFX9_SFC_AVS_LUMA_COEFF_TABLE_BODY_pack(data, &dw[1], &values->AVSLUMACoefficientTableBody);
}

#define GFX9_SFC_AVS_STATE_length              3
#define GFX9_SFC_AVS_STATE_length_bias         2
#define GFX9_SFC_AVS_STATE_header               \
   .DWordLength                         =      1,  \
   .SubOpcodeB                          =      2,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =     10,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_SFC_AVS_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   struct GFX9_SFC_AVS_STATE_BODY       AVSStateBody;
};

static inline __attribute__((always_inline)) void
GFX9_SFC_AVS_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_SFC_AVS_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   GFX9_SFC_AVS_STATE_BODY_pack(data, &dw[1], &values->AVSStateBody);
}

#define GFX9_SFC_FRAME_START_length            2
#define GFX9_SFC_FRAME_START_length_bias       2
#define GFX9_SFC_FRAME_START_header             \
   .DWordLength                         =      0,  \
   .SubOpcodeB                          =      4,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =     10,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_SFC_FRAME_START {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             FrameStartBody;
};

static inline __attribute__((always_inline)) void
GFX9_SFC_FRAME_START_pack(__attribute__((unused)) __gen_user_data *data,
                          __attribute__((unused)) void * restrict dst,
                          __attribute__((unused)) const struct GFX9_SFC_FRAME_START * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->FrameStartBody, 0, 31);
}

#define GFX9_SFC_IEF_STATE_length             24
#define GFX9_SFC_IEF_STATE_length_bias         2
#define GFX9_SFC_IEF_STATE_header               \
   .DWordLength                         =     22,  \
   .SubOpcodeB                          =      3,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =     10,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_SFC_IEF_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   struct GFX9_SFC_IEF_STATE_BODY       SFCIEFStateBody;
};

static inline __attribute__((always_inline)) void
GFX9_SFC_IEF_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_SFC_IEF_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   GFX9_SFC_IEF_STATE_BODY_pack(data, &dw[1], &values->SFCIEFStateBody);
}

#define GFX9_SFC_LOCK_length                   2
#define GFX9_SFC_LOCK_length_bias              2
#define GFX9_SFC_LOCK_header                    \
   .DWordLength                         =      0,  \
   .SubOpcodeB                          =      0,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =     10,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_SFC_LOCK {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   struct GFX9_SFC_LOCK_BODY            SFCLockBody;
};

static inline __attribute__((always_inline)) void
GFX9_SFC_LOCK_pack(__attribute__((unused)) __gen_user_data *data,
                   __attribute__((unused)) void * restrict dst,
                   __attribute__((unused)) const struct GFX9_SFC_LOCK * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   GFX9_SFC_LOCK_BODY_pack(data, &dw[1], &values->SFCLockBody);
}

#define GFX9_SFC_STATE_length                 32
#define GFX9_SFC_STATE_length_bias             2
#define GFX9_SFC_STATE_header                   \
   .DWordLength                         =     30,  \
   .SubOpcodeB                          =      1,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =     10,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_SFC_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             SFCPipeMode;
   uint32_t                             SFCInputChromaSubSampling;
#define _400                                     0
#define _420                                     1
#define _422Horizonatal                          2
#define _444ProgressiveInterleaved               4
   uint32_t                             VDVEInputOrderingMode;
   uint32_t                             InputFrameResolutionWidth;
   uint32_t                             InputFrameResolutionHeight;
   uint32_t                             OutputSurfaceFormatType;
   bool                                 RGBAChannelSwapEnable;
   uint32_t                             PreAVSChromaDownsamplingEnable;
   uint32_t                             PreAVSChromaDownsamplingCositingPositionVerticalDirection;
   uint32_t                             PreAVSChromaDownsamplingCositingPositionHorizontalDirection;
   bool                                 IEFEnable;
   bool                                 SkinToneTunedIEF_Enable;
   bool                                 IEF4SmoothEnable;
   uint32_t                             AVSFilterMode;
#define _5x5PolyphasefilterBilinear              0
#define _8x8polyphasefilterBilinear              1
#define Bilinearfilteronly                       2
   bool                                 AdaptiveFilterforallChannels;
   bool                                 AVSScalingEnable;
   bool                                 BypassYAdaptiveFiltering;
   bool                                 BypassXAdaptiveFiltering;
   bool                                 ChromaUpsamplingEnable;
   uint32_t                             RotationMode;
#define _0                                       0
#define _90CW                                    1
#define _180CW                                   2
#define _270CW                                   3
   bool                                 ColorFillEnable;
   bool                                 CSCEnable;
   uint32_t                             SourceRegionWidth;
   uint32_t                             SourceRegionHeight;
   uint32_t                             SourceRegionHorizontalOffset;
   uint32_t                             SourceRegionVerticalOffset;
   uint32_t                             OutputFrameWidth;
   uint32_t                             OutputFrameHeight;
   uint32_t                             ScaledRegionSizeWidth;
   uint32_t                             ScaledRegionSizeHeight;
   int32_t                              ScaledRegionHorizontalOffset;
   int32_t                              ScaledRegionVerticalOffset;
   uint32_t                             GrayBarPixelUG;
   uint32_t                             GrayBarPixelYR;
   uint32_t                             GrayBarPixelA;
   uint32_t                             GrayBarPixelVB;
   uint32_t                             UVDefaultvalueforUchannel;
   uint32_t                             UVDefaultvalueforVchannel;
   uint32_t                             AlphaDefaultValue;
   float                                ScalingFactorHeight;
   float                                ScalingFactorWidth;
   uint64_t                             OutputFrameAddress;
   uint32_t                             OutputFrameMOCS;
   struct GFX9_HEVC_ARBITRATION_PRIORITY OutputFrameArbitrationPriorityControl;
   bool                                 OutputFrameMemoryCompressionEnable;
   uint32_t                             OutputFrameMemoryCompressionMode;
   bool                                 OutputFrameCacheSelect;
   uint32_t                             OutputFrameTiledMode;
#define TRMODE_NONE                              0
#define TRMODE_TILEYF                            1
#define TRMODE_TILEYS                            2
   uint64_t                             AVSLineBufferAddress;
   uint32_t                             AVSLineBufferMOCS;
   struct GFX9_HEVC_ARBITRATION_PRIORITY AVSLineBufferArbitrationPriorityControl;
   bool                                 AVSLineBufferMemoryCompressionEnable;
   uint32_t                             AVSLineBufferMemoryCompressionMode;
#define HorizontalCompressionMode                0
   uint32_t                             AVSLineBufferCacheSelect;
#define LLC                                      0
   uint32_t                             AVSLineBufferTiledMode;
#define TRMODE_NONE                              0
#define TRMODE_TILEYF                            1
#define TRMODE_TILEYS                            2
   uint64_t                             IEFLineBufferAddress;
   uint32_t                             IEFLineBufferMOCS;
   struct GFX9_HEVC_ARBITRATION_PRIORITY IEFLineBufferArbitrationPriorityControl;
   bool                                 IEFLineBufferMemoryCompressionEnable;
   uint32_t                             IEFLineBufferMemoryCompressionMode;
   uint32_t                             IEFLineBufferCacheSelect;
   uint32_t                             IEFLineBufferTiledMode;
#define TRMODE_NONE                              0
#define TRMODE_TILEYF                            1
#define TRMODE_TILEYS                            2
   uint32_t                             OutputSurfaceTileWalk;
#define TW_XMAJOR                                0
#define TW_YMAJOR                                1
   bool                                 OutputSurfaceTiled;
   bool                                 OutputSurfaceHalfPitchforChroma;
   uint32_t                             OutputSurfacePitch;
   bool                                 OutputSurfaceInterleaveChromaEnable;
   uint32_t                             OutputSurfaceFormat;
   uint32_t                             OutputSurfaceYOffsetforU;
   uint32_t                             OutputSurfaceXOffsetforU;
   uint32_t                             OutputSurfaceYOffsetforV;
   uint32_t                             OutputSurfaceXOffsetforV;
};

static inline __attribute__((always_inline)) void
GFX9_SFC_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                    __attribute__((unused)) void * restrict dst,
                    __attribute__((unused)) const struct GFX9_SFC_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->SFCPipeMode, 0, 3) |
      util_bitpack_uint(values->SFCInputChromaSubSampling, 4, 7) |
      util_bitpack_uint(values->VDVEInputOrderingMode, 8, 10);

   dw[2] =
      util_bitpack_uint(values->InputFrameResolutionWidth, 0, 11) |
      util_bitpack_uint(values->InputFrameResolutionHeight, 16, 27);

   dw[3] =
      util_bitpack_uint(values->OutputSurfaceFormatType, 0, 3) |
      util_bitpack_uint(values->RGBAChannelSwapEnable, 5, 5) |
      util_bitpack_uint(values->PreAVSChromaDownsamplingEnable, 6, 7) |
      util_bitpack_uint(values->PreAVSChromaDownsamplingCositingPositionVerticalDirection, 8, 10) |
      util_bitpack_uint(values->PreAVSChromaDownsamplingCositingPositionHorizontalDirection, 12, 14);

   dw[4] =
      util_bitpack_uint(values->IEFEnable, 0, 0) |
      util_bitpack_uint(values->SkinToneTunedIEF_Enable, 1, 1) |
      util_bitpack_uint(values->IEF4SmoothEnable, 2, 2) |
      util_bitpack_uint(values->AVSFilterMode, 4, 5) |
      util_bitpack_uint(values->AdaptiveFilterforallChannels, 6, 6) |
      util_bitpack_uint(values->AVSScalingEnable, 7, 7) |
      util_bitpack_uint(values->BypassYAdaptiveFiltering, 8, 8) |
      util_bitpack_uint(values->BypassXAdaptiveFiltering, 9, 9) |
      util_bitpack_uint(values->ChromaUpsamplingEnable, 12, 12) |
      util_bitpack_uint(values->RotationMode, 16, 17) |
      util_bitpack_uint(values->ColorFillEnable, 18, 18) |
      util_bitpack_uint(values->CSCEnable, 19, 19);

   dw[5] =
      util_bitpack_uint(values->SourceRegionWidth, 0, 11) |
      util_bitpack_uint(values->SourceRegionHeight, 16, 27);

   dw[6] =
      util_bitpack_uint(values->SourceRegionHorizontalOffset, 0, 11) |
      util_bitpack_uint(values->SourceRegionVerticalOffset, 16, 27);

   dw[7] =
      util_bitpack_uint(values->OutputFrameWidth, 0, 11) |
      util_bitpack_uint(values->OutputFrameHeight, 16, 27);

   dw[8] =
      util_bitpack_uint(values->ScaledRegionSizeWidth, 0, 11) |
      util_bitpack_uint(values->ScaledRegionSizeHeight, 16, 27);

   dw[9] =
      util_bitpack_sint(values->ScaledRegionHorizontalOffset, 0, 12) |
      util_bitpack_sint(values->ScaledRegionVerticalOffset, 16, 28);

   dw[10] =
      util_bitpack_uint(values->GrayBarPixelUG, 0, 9) |
      util_bitpack_uint(values->GrayBarPixelYR, 16, 25);

   dw[11] =
      util_bitpack_uint(values->GrayBarPixelA, 0, 9) |
      util_bitpack_uint(values->GrayBarPixelVB, 16, 25);

   dw[12] =
      util_bitpack_uint(values->UVDefaultvalueforUchannel, 0, 9) |
      util_bitpack_uint(values->UVDefaultvalueforVchannel, 16, 25);

   dw[13] =
      util_bitpack_uint(values->AlphaDefaultValue, 0, 9);

   dw[14] =
      util_bitpack_ufixed(values->ScalingFactorHeight, 0, 20, 17);

   dw[15] =
      util_bitpack_ufixed(values->ScalingFactorWidth, 0, 20, 17);

   dw[16] = 0;

   const uint64_t v17 =
      util_bitpack_uint(values->OutputFrameAddress, 12, 47);
   dw[17] = v17;
   dw[18] = v17 >> 32;

   uint32_t v19_0;
   GFX9_HEVC_ARBITRATION_PRIORITY_pack(data, &v19_0, &values->OutputFrameArbitrationPriorityControl);

   dw[19] =
      util_bitpack_uint_nonzero(values->OutputFrameMOCS, 1, 6) |
      util_bitpack_uint(v19_0, 7, 8) |
      util_bitpack_uint(values->OutputFrameMemoryCompressionEnable, 9, 9) |
      util_bitpack_uint(values->OutputFrameMemoryCompressionMode, 10, 10) |
      util_bitpack_uint(values->OutputFrameCacheSelect, 12, 12) |
      util_bitpack_uint(values->OutputFrameTiledMode, 13, 14);

   const uint64_t v20 =
      util_bitpack_uint(values->AVSLineBufferAddress, 12, 47);
   dw[20] = v20;
   dw[21] = v20 >> 32;

   uint32_t v22_0;
   GFX9_HEVC_ARBITRATION_PRIORITY_pack(data, &v22_0, &values->AVSLineBufferArbitrationPriorityControl);

   dw[22] =
      util_bitpack_uint_nonzero(values->AVSLineBufferMOCS, 1, 6) |
      util_bitpack_uint(v22_0, 7, 8) |
      util_bitpack_uint(values->AVSLineBufferMemoryCompressionEnable, 9, 9) |
      util_bitpack_uint(values->AVSLineBufferMemoryCompressionMode, 10, 10) |
      util_bitpack_uint(values->AVSLineBufferCacheSelect, 12, 12) |
      util_bitpack_uint(values->AVSLineBufferTiledMode, 13, 14);

   const uint64_t v23 =
      util_bitpack_uint(values->IEFLineBufferAddress, 12, 47);
   dw[23] = v23;
   dw[24] = v23 >> 32;

   uint32_t v25_0;
   GFX9_HEVC_ARBITRATION_PRIORITY_pack(data, &v25_0, &values->IEFLineBufferArbitrationPriorityControl);

   dw[25] =
      util_bitpack_uint_nonzero(values->IEFLineBufferMOCS, 1, 6) |
      util_bitpack_uint(v25_0, 7, 8) |
      util_bitpack_uint(values->IEFLineBufferMemoryCompressionEnable, 9, 9) |
      util_bitpack_uint(values->IEFLineBufferMemoryCompressionMode, 10, 10) |
      util_bitpack_uint(values->IEFLineBufferCacheSelect, 12, 12) |
      util_bitpack_uint(values->IEFLineBufferTiledMode, 13, 14);

   dw[26] = 0;

   dw[27] = 0;

   dw[28] = 0;

   dw[29] =
      util_bitpack_uint(values->OutputSurfaceTileWalk, 0, 0) |
      util_bitpack_uint(values->OutputSurfaceTiled, 1, 1) |
      util_bitpack_uint(values->OutputSurfaceHalfPitchforChroma, 2, 2) |
      util_bitpack_uint(values->OutputSurfacePitch, 3, 19) |
      util_bitpack_uint(values->OutputSurfaceInterleaveChromaEnable, 27, 27) |
      util_bitpack_uint(values->OutputSurfaceFormat, 28, 31);

   dw[30] =
      util_bitpack_uint(values->OutputSurfaceYOffsetforU, 0, 13) |
      util_bitpack_uint(values->OutputSurfaceXOffsetforU, 16, 29);

   dw[31] =
      util_bitpack_uint(values->OutputSurfaceYOffsetforV, 0, 13) |
      util_bitpack_uint(values->OutputSurfaceXOffsetforV, 16, 29);
}

#define GFX9_STATE_BASE_ADDRESS_length        19
#define GFX9_STATE_BASE_ADDRESS_length_bias      2
#define GFX9_STATE_BASE_ADDRESS_header          \
   .DWordLength                         =     17,  \
   ._3DCommandSubOpcode                 =      1,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      0,  \
   .CommandType                         =      3

struct GFX9_STATE_BASE_ADDRESS {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   bool                                 GeneralStateBaseAddressModifyEnable;
   uint32_t                             GeneralStateMOCS;
   __gen_address_type                   GeneralStateBaseAddress;
   uint32_t                             StatelessDataPortAccessMOCS;
   bool                                 SurfaceStateBaseAddressModifyEnable;
   uint32_t                             SurfaceStateMOCS;
   __gen_address_type                   SurfaceStateBaseAddress;
   bool                                 DynamicStateBaseAddressModifyEnable;
   uint32_t                             DynamicStateMOCS;
   __gen_address_type                   DynamicStateBaseAddress;
   bool                                 IndirectObjectBaseAddressModifyEnable;
   uint32_t                             IndirectObjectMOCS;
   __gen_address_type                   IndirectObjectBaseAddress;
   bool                                 InstructionBaseAddressModifyEnable;
   uint32_t                             InstructionMOCS;
   __gen_address_type                   InstructionBaseAddress;
   bool                                 GeneralStateBufferSizeModifyEnable;
   uint32_t                             GeneralStateBufferSize;
   bool                                 DynamicStateBufferSizeModifyEnable;
   uint32_t                             DynamicStateBufferSize;
   bool                                 IndirectObjectBufferSizeModifyEnable;
   uint32_t                             IndirectObjectBufferSize;
   bool                                 InstructionBuffersizeModifyEnable;
   uint32_t                             InstructionBufferSize;
   bool                                 BindlessSurfaceStateBaseAddressModifyEnable;
   uint32_t                             BindlessSurfaceStateMOCS;
   __gen_address_type                   BindlessSurfaceStateBaseAddress;
   uint32_t                             BindlessSurfaceStateSize;
};

static inline __attribute__((always_inline)) void
GFX9_STATE_BASE_ADDRESS_pack(__attribute__((unused)) __gen_user_data *data,
                             __attribute__((unused)) void * restrict dst,
                             __attribute__((unused)) const struct GFX9_STATE_BASE_ADDRESS * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1 =
      util_bitpack_uint(values->GeneralStateBaseAddressModifyEnable, 0, 0) |
      util_bitpack_uint_nonzero(values->GeneralStateMOCS, 4, 10);
   const uint64_t v1_address =
      __gen_address(data, &dw[1], values->GeneralStateBaseAddress, v1, 12, 63);
   dw[1] = v1_address;
   dw[2] = (v1_address >> 32) | (v1 >> 32);

   dw[3] =
      util_bitpack_uint_nonzero(values->StatelessDataPortAccessMOCS, 16, 22);

   const uint64_t v4 =
      util_bitpack_uint(values->SurfaceStateBaseAddressModifyEnable, 0, 0) |
      util_bitpack_uint_nonzero(values->SurfaceStateMOCS, 4, 10);
   const uint64_t v4_address =
      __gen_address(data, &dw[4], values->SurfaceStateBaseAddress, v4, 12, 63);
   dw[4] = v4_address;
   dw[5] = (v4_address >> 32) | (v4 >> 32);

   const uint64_t v6 =
      util_bitpack_uint(values->DynamicStateBaseAddressModifyEnable, 0, 0) |
      util_bitpack_uint_nonzero(values->DynamicStateMOCS, 4, 10);
   const uint64_t v6_address =
      __gen_address(data, &dw[6], values->DynamicStateBaseAddress, v6, 12, 63);
   dw[6] = v6_address;
   dw[7] = (v6_address >> 32) | (v6 >> 32);

   const uint64_t v8 =
      util_bitpack_uint(values->IndirectObjectBaseAddressModifyEnable, 0, 0) |
      util_bitpack_uint_nonzero(values->IndirectObjectMOCS, 4, 10);
   const uint64_t v8_address =
      __gen_address(data, &dw[8], values->IndirectObjectBaseAddress, v8, 12, 63);
   dw[8] = v8_address;
   dw[9] = (v8_address >> 32) | (v8 >> 32);

   const uint64_t v10 =
      util_bitpack_uint(values->InstructionBaseAddressModifyEnable, 0, 0) |
      util_bitpack_uint_nonzero(values->InstructionMOCS, 4, 10);
   const uint64_t v10_address =
      __gen_address(data, &dw[10], values->InstructionBaseAddress, v10, 12, 63);
   dw[10] = v10_address;
   dw[11] = (v10_address >> 32) | (v10 >> 32);

   dw[12] =
      util_bitpack_uint(values->GeneralStateBufferSizeModifyEnable, 0, 0) |
      util_bitpack_uint(values->GeneralStateBufferSize, 12, 31);

   dw[13] =
      util_bitpack_uint(values->DynamicStateBufferSizeModifyEnable, 0, 0) |
      util_bitpack_uint(values->DynamicStateBufferSize, 12, 31);

   dw[14] =
      util_bitpack_uint(values->IndirectObjectBufferSizeModifyEnable, 0, 0) |
      util_bitpack_uint(values->IndirectObjectBufferSize, 12, 31);

   dw[15] =
      util_bitpack_uint(values->InstructionBuffersizeModifyEnable, 0, 0) |
      util_bitpack_uint(values->InstructionBufferSize, 12, 31);

   const uint64_t v16 =
      util_bitpack_uint(values->BindlessSurfaceStateBaseAddressModifyEnable, 0, 0) |
      util_bitpack_uint_nonzero(values->BindlessSurfaceStateMOCS, 4, 10);
   const uint64_t v16_address =
      __gen_address(data, &dw[16], values->BindlessSurfaceStateBaseAddress, v16, 12, 63);
   dw[16] = v16_address;
   dw[17] = (v16_address >> 32) | (v16 >> 32);

   dw[18] =
      util_bitpack_uint(values->BindlessSurfaceStateSize, 12, 31);
}

#define GFX9_STATE_PREFETCH_length             2
#define GFX9_STATE_PREFETCH_length_bias        2
#define GFX9_STATE_PREFETCH_header              \
   .DWordLength                         =      0,  \
   ._3DCommandSubOpcode                 =      3,  \
   ._3DCommandOpcode                    =      0,  \
   .CommandSubType                      =      0,  \
   .CommandType                         =      3

struct GFX9_STATE_PREFETCH {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint32_t                             PrefetchCount;
   __gen_address_type                   PrefetchPointer;
};

static inline __attribute__((always_inline)) void
GFX9_STATE_PREFETCH_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_STATE_PREFETCH * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint32_t v1 =
      util_bitpack_uint(values->PrefetchCount, 0, 2);
   dw[1] = __gen_address(data, &dw[1], values->PrefetchPointer, v1, 6, 31);
}

#define GFX9_STATE_SIP_length                  3
#define GFX9_STATE_SIP_length_bias             2
#define GFX9_STATE_SIP_header                   \
   .DWordLength                         =      1,  \
   ._3DCommandSubOpcode                 =      2,  \
   ._3DCommandOpcode                    =      1,  \
   .CommandSubType                      =      0,  \
   .CommandType                         =      3

struct GFX9_STATE_SIP {
   uint32_t                             DWordLength;
   uint32_t                             _3DCommandSubOpcode;
   uint32_t                             _3DCommandOpcode;
   uint32_t                             CommandSubType;
   uint32_t                             CommandType;
   uint64_t                             SystemInstructionPointer;
};

static inline __attribute__((always_inline)) void
GFX9_STATE_SIP_pack(__attribute__((unused)) __gen_user_data *data,
                    __attribute__((unused)) void * restrict dst,
                    __attribute__((unused)) const struct GFX9_STATE_SIP * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 7) |
      util_bitpack_uint(values->_3DCommandSubOpcode, 16, 23) |
      util_bitpack_uint(values->_3DCommandOpcode, 24, 26) |
      util_bitpack_uint(values->CommandSubType, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   const uint64_t v1 =
      __gen_offset(values->SystemInstructionPointer, 4, 63);
   dw[1] = v1;
   dw[2] = v1 >> 32;
}

#define GFX9_VDENC_CONST_QPT_STATE_length     62
#define GFX9_VDENC_CONST_QPT_STATE_length_bias      2
#define GFX9_VDENC_CONST_QPT_STATE_header       \
   .DWordLength                         =     60,  \
   .SubOpcodeB                          =      6,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_VDENC_CONST_QPT_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             QPLambdaArrayIndexn;
   uint32_t                             SkipThresholdArrayIndexn;
   uint32_t                             SICForwardTransformCoeffThresholdMatrix0ArrayIndexn;
   uint32_t                             SICForwardTransformCoeffThresholdMatrix135ArrayIndexn;
   uint32_t                             SICForwardTransformCoeffThresholdMatrix2ArrayIndexn;
   uint32_t                             SICForwardTransformCoeffThresholdMatrix46ArrayIndexn;
};

static inline __attribute__((always_inline)) void
GFX9_VDENC_CONST_QPT_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GFX9_VDENC_CONST_QPT_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->QPLambdaArrayIndexn, 0, 7);

   dw[2] = 0;

   dw[3] = 0;

   dw[4] = 0;

   dw[5] = 0;

   dw[6] = 0;

   dw[7] = 0;

   dw[8] = 0;

   dw[9] = 0;

   dw[10] = 0;

   dw[11] = 0;

   dw[12] =
      util_bitpack_uint(values->SkipThresholdArrayIndexn, 0, 15);

   dw[13] = 0;

   dw[14] = 0;

   dw[15] = 0;

   dw[16] = 0;

   dw[17] = 0;

   dw[18] = 0;

   dw[19] = 0;

   dw[20] = 0;

   dw[21] = 0;

   dw[22] = 0;

   dw[23] = 0;

   dw[24] = 0;

   dw[25] = 0;

   dw[26] =
      util_bitpack_uint(values->SICForwardTransformCoeffThresholdMatrix0ArrayIndexn, 0, 15);

   dw[27] = 0;

   dw[28] = 0;

   dw[29] = 0;

   dw[30] = 0;

   dw[31] = 0;

   dw[32] = 0;

   dw[33] = 0;

   dw[34] = 0;

   dw[35] = 0;

   dw[36] = 0;

   dw[37] = 0;

   dw[38] = 0;

   dw[39] = 0;

   dw[40] =
      util_bitpack_uint(values->SICForwardTransformCoeffThresholdMatrix135ArrayIndexn, 0, 7);

   dw[41] = 0;

   dw[42] = 0;

   dw[43] = 0;

   dw[44] = 0;

   dw[45] = 0;

   dw[46] = 0;

   dw[47] =
      util_bitpack_uint(values->SICForwardTransformCoeffThresholdMatrix2ArrayIndexn, 0, 7);

   dw[48] = 0;

   dw[49] = 0;

   dw[50] = 0;

   dw[51] = 0;

   dw[52] = 0;

   dw[53] = 0;

   dw[54] =
      util_bitpack_uint(values->SICForwardTransformCoeffThresholdMatrix46ArrayIndexn, 0, 7);

   dw[55] = 0;

   dw[56] = 0;

   dw[57] = 0;

   dw[58] = 0;

   dw[59] = 0;

   dw[60] = 0;

   dw[61] = 0;
}

#define GFX9_VDENC_DS_REF_SURFACE_STATE_length      6
#define GFX9_VDENC_DS_REF_SURFACE_STATE_length_bias      2
#define GFX9_VDENC_DS_REF_SURFACE_STATE_header  \
   .DWordLength                         =      4,  \
   .SubOpcodeB                          =      3,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_VDENC_DS_REF_SURFACE_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   struct GFX9_VDENC_SURFACE_STATE_FIELDS _8XSurfaceState;
};

static inline __attribute__((always_inline)) void
GFX9_VDENC_DS_REF_SURFACE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                     __attribute__((unused)) void * restrict dst,
                                     __attribute__((unused)) const struct GFX9_VDENC_DS_REF_SURFACE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] = 0;

   GFX9_VDENC_SURFACE_STATE_FIELDS_pack(data, &dw[2], &values->_8XSurfaceState);
}

#define GFX9_VDENC_IMG_STATE_length           36
#define GFX9_VDENC_IMG_STATE_length_bias       2
#define GFX9_VDENC_IMG_STATE_header             \
   .DWordLength                         =     34,  \
   .SubOpcodeB                          =      5,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_VDENC_IMG_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   bool                                 BidirectionalMixDisable;
   bool                                 VDEncExtendedPAK_OBJ_CommandEnable;
   bool                                 Transform8x8;
   uint32_t                             VDEncL1CachePriority;
   uint32_t                             LambdaValueforTrellis;
   bool                                 UnidirectionalMixDisable;
   uint32_t                             PictureWidth;
   uint32_t                             SubPelMode;
   bool                                 ForwardTransformSkipCheckEnable;
   bool                                 BlockBasedSkipEnable;
   uint32_t                             InterSADMeasureAdjustment;
#define ISMA_None                                0
#define ISMA_HaarTransformAdjusted               2
   uint32_t                             IntraSADMeasureAdjustment;
#define ISMA_None                                0
#define ISMA_HaarTransformAdjusted               2
   uint32_t                             SubMBSubPartitionMask;
   uint32_t                             BlockBasedSkipType;
   uint32_t                             PictureHeight;
   bool                                 CREPrefetchEnable;
   bool                                 HMERef1Disable;
   uint32_t                             MBSliceThresholdValue;
   bool                                 ConstrainedIntraPrediction;
   uint32_t                             PictureType;
#define PI_I                                     0
#define PI_P                                     1
   uint32_t                             SliceMBHeight;
   int32_t                              HME1YOffset;
   uint32_t                             LumaIntraPartitionMask;
   uint32_t                             NonSkipZeroMVCostAdded;
   uint32_t                             NonSkipMBModeCostAdded;
   uint32_t                             MVCostScalingFactor;
#define Qpel                                     0
#define Hpel                                     1
#define Pel                                      2
#define _2pel                                    3
   bool                                 BiLinearFilterEnable;
   uint32_t                             RefIDCostModeSelect;
   uint32_t                             Mode0Cost;
   uint32_t                             Mode1Cost;
   uint32_t                             Mode2Cost;
   uint32_t                             Mode3Cost;
   uint32_t                             Mode4Cost;
   uint32_t                             Mode5Cost;
   uint32_t                             Mode6Cost;
   uint32_t                             Mode7Cost;
   uint32_t                             Mode8Cost;
   uint32_t                             Mode9Cost;
   uint32_t                             RefIDCost;
   uint32_t                             ChromaIntraModeCost;
   uint64_t                             MVCost;
   uint32_t                             QpPrimeY;
   uint32_t                             TargetSizeInWord;
   uint32_t                             AVCIntra4x4ModeMask;
   uint32_t                             AVCIntra8x8ModeMask;
   uint32_t                             AVCIntra16x16ModeMask;
   uint32_t                             AVCIntraChromaModeMask;
   uint32_t                             IntraComputeType;
   uint32_t                             PenaltyforIntra16x16NonDCPrediction;
   uint32_t                             PenaltyforIntra8x8NonDCPrediction;
   uint32_t                             PenaltyforIntra4x4NonDCPrediction;
   uint32_t                             IntraRefreshMBPosition;
   uint32_t                             IntraRefreshMBSize;
   bool                                 IntraRefreshEnableRollingIEnable;
   uint32_t                             IntraRefreshMode;
#define RowBased                                 0
#define ColumnBased                              1
   int32_t                              QPAdjustmentforRollingI;
   uint32_t                             PanicModeMBThreshold;
   uint32_t                             SmallMbSizeInWord;
   uint32_t                             LargeMbSizeInWord;
   int32_t                              L0NumberofReferences;
   int32_t                              L1NumberofReferences;
   uint32_t                             HMERefWindowsCombiningThreshold;
   uint32_t                             MaxHorizontalMVRange;
   uint32_t                             MaxVerticalMVRange;
   uint64_t                             HMEMVCost;
   int32_t                              ROIQPAdjustmentforZone0;
   int32_t                              ROIQPAdjustmentforZone1;
   int32_t                              ROIQPAdjustmentforZone2;
   int32_t                              ROIQPAdjustmentforZone3;
   int32_t                              QPAdjustmentforShapeBestIntra4x4Winner;
   int32_t                              QPAdjustmentforShapeBestIntra8x8Winner;
   int32_t                              QPAdjustmentforShapeBestIntra16x16Winner;
   int32_t                              BestDistortionQPAdjustmentforZone0;
   int32_t                              BestDistortionQPAdjustmentforZone1;
   int32_t                              BestDistortionQPAdjustmentforZone2;
   int32_t                              BestDistortionQPAdjustmentforZone3;
   uint32_t                             SadHaarThreshold0;
   uint32_t                             SadHaarThreshold1;
   uint32_t                             SadHaarThreshold2;
   uint32_t                             MinQP;
   uint32_t                             MaxQP;
   uint32_t                             MaxDeltaQP;
   bool                                 ROIEnable;
   bool                                 FwdPredictor0MVEnable;
   bool                                 BwdPredictor1MVEnable;
   bool                                 MBLevelQPEnable;
   bool                                 TargetSizeinWordsMBMaxSizeinWordsMBEnable;
   bool                                 PPMVDisable;
   bool                                 CoefficientClampEnable;
   bool                                 LongTermReferenceFrameBwdRef0Indicator;
   bool                                 LongTermReferenceFrameFwdRef2Indicator;
   bool                                 LongTermReferenceFrameFwdRef1Indicator;
   bool                                 LongTermReferenceFrameFwdRef0Indicator;
   uint32_t                             MidpointSadHaar;
};

static inline __attribute__((always_inline)) void
GFX9_VDENC_IMG_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                          __attribute__((unused)) void * restrict dst,
                          __attribute__((unused)) const struct GFX9_VDENC_IMG_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->BidirectionalMixDisable, 2, 2) |
      util_bitpack_uint(values->VDEncExtendedPAK_OBJ_CommandEnable, 6, 6) |
      util_bitpack_uint(values->Transform8x8, 7, 7) |
      util_bitpack_uint(values->VDEncL1CachePriority, 8, 9) |
      util_bitpack_uint(values->LambdaValueforTrellis, 16, 31);

   dw[2] =
      util_bitpack_uint(values->UnidirectionalMixDisable, 28, 28);

   dw[3] =
      util_bitpack_uint(values->PictureWidth, 16, 31);

   dw[4] =
      util_bitpack_uint(values->SubPelMode, 12, 13) |
      util_bitpack_uint(values->ForwardTransformSkipCheckEnable, 17, 17) |
      util_bitpack_uint(values->BlockBasedSkipEnable, 19, 19) |
      util_bitpack_uint(values->InterSADMeasureAdjustment, 20, 21) |
      util_bitpack_uint(values->IntraSADMeasureAdjustment, 22, 23) |
      util_bitpack_uint(values->SubMBSubPartitionMask, 24, 30) |
      util_bitpack_uint(values->BlockBasedSkipType, 31, 31);

   dw[5] =
      util_bitpack_uint(values->PictureHeight, 0, 15) |
      util_bitpack_uint(values->CREPrefetchEnable, 16, 16) |
      util_bitpack_uint(values->HMERef1Disable, 17, 17) |
      util_bitpack_uint(values->MBSliceThresholdValue, 18, 21) |
      util_bitpack_uint(values->ConstrainedIntraPrediction, 26, 26) |
      util_bitpack_uint(values->PictureType, 29, 30);

   dw[6] =
      util_bitpack_uint(values->SliceMBHeight, 0, 15);

   dw[7] =
      util_bitpack_sint(values->HME1YOffset, 24, 31);

   dw[8] =
      util_bitpack_uint(values->LumaIntraPartitionMask, 0, 4) |
      util_bitpack_uint(values->NonSkipZeroMVCostAdded, 5, 5) |
      util_bitpack_uint(values->NonSkipMBModeCostAdded, 6, 6) |
      util_bitpack_uint(values->MVCostScalingFactor, 16, 17) |
      util_bitpack_uint(values->BiLinearFilterEnable, 18, 18) |
      util_bitpack_uint(values->RefIDCostModeSelect, 22, 22);

   dw[9] =
      util_bitpack_uint(values->Mode0Cost, 0, 7) |
      util_bitpack_uint(values->Mode1Cost, 8, 15) |
      util_bitpack_uint(values->Mode2Cost, 16, 23) |
      util_bitpack_uint(values->Mode3Cost, 24, 31);

   dw[10] =
      util_bitpack_uint(values->Mode4Cost, 0, 7) |
      util_bitpack_uint(values->Mode5Cost, 8, 15) |
      util_bitpack_uint(values->Mode6Cost, 16, 23) |
      util_bitpack_uint(values->Mode7Cost, 24, 31);

   dw[11] =
      util_bitpack_uint(values->Mode8Cost, 0, 7) |
      util_bitpack_uint(values->Mode9Cost, 8, 15) |
      util_bitpack_uint(values->RefIDCost, 16, 23) |
      util_bitpack_uint(values->ChromaIntraModeCost, 24, 31);

   const uint64_t v12 =
      util_bitpack_uint(values->MVCost, 0, 63);
   dw[12] = v12;
   dw[13] = v12 >> 32;

   dw[14] =
      util_bitpack_uint(values->QpPrimeY, 0, 7) |
      util_bitpack_uint(values->TargetSizeInWord, 24, 31);

   dw[15] = 0;

   dw[16] = 0;

   dw[17] =
      util_bitpack_uint(values->AVCIntra4x4ModeMask, 0, 8) |
      util_bitpack_uint(values->AVCIntra8x8ModeMask, 16, 24);

   dw[18] =
      util_bitpack_uint(values->AVCIntra16x16ModeMask, 0, 3) |
      util_bitpack_uint(values->AVCIntraChromaModeMask, 4, 7) |
      util_bitpack_uint(values->IntraComputeType, 8, 9);

   dw[19] = 0;

   dw[20] =
      util_bitpack_uint(values->PenaltyforIntra16x16NonDCPrediction, 0, 7) |
      util_bitpack_uint(values->PenaltyforIntra8x8NonDCPrediction, 8, 15) |
      util_bitpack_uint(values->PenaltyforIntra4x4NonDCPrediction, 16, 23);

   dw[21] =
      util_bitpack_uint(values->IntraRefreshMBPosition, 0, 7) |
      util_bitpack_uint(values->IntraRefreshMBSize, 8, 15) |
      util_bitpack_uint(values->IntraRefreshEnableRollingIEnable, 16, 16) |
      util_bitpack_uint(values->IntraRefreshMode, 17, 17) |
      util_bitpack_sint(values->QPAdjustmentforRollingI, 24, 31);

   dw[22] =
      util_bitpack_uint(values->PanicModeMBThreshold, 0, 15) |
      util_bitpack_uint(values->SmallMbSizeInWord, 16, 23) |
      util_bitpack_uint(values->LargeMbSizeInWord, 24, 31);

   dw[23] =
      util_bitpack_sint(values->L0NumberofReferences, 0, 7) |
      util_bitpack_sint(values->L1NumberofReferences, 16, 23);

   dw[24] = 0;

   dw[25] = 0;

   dw[26] =
      util_bitpack_uint(values->HMERefWindowsCombiningThreshold, 8, 15);

   dw[27] =
      util_bitpack_uint(values->MaxHorizontalMVRange, 0, 15) |
      util_bitpack_uint(values->MaxVerticalMVRange, 16, 31);

   const uint64_t v28 =
      util_bitpack_uint(values->HMEMVCost, 0, 63);
   dw[28] = v28;
   dw[29] = v28 >> 32;

   dw[30] =
      util_bitpack_sint(values->ROIQPAdjustmentforZone0, 0, 3) |
      util_bitpack_sint(values->ROIQPAdjustmentforZone1, 4, 7) |
      util_bitpack_sint(values->ROIQPAdjustmentforZone2, 8, 11) |
      util_bitpack_sint(values->ROIQPAdjustmentforZone3, 12, 15) |
      util_bitpack_sint(values->QPAdjustmentforShapeBestIntra4x4Winner, 16, 19) |
      util_bitpack_sint(values->QPAdjustmentforShapeBestIntra8x8Winner, 20, 23) |
      util_bitpack_sint(values->QPAdjustmentforShapeBestIntra16x16Winner, 24, 27);

   dw[31] =
      util_bitpack_sint(values->BestDistortionQPAdjustmentforZone0, 0, 3) |
      util_bitpack_sint(values->BestDistortionQPAdjustmentforZone1, 4, 7) |
      util_bitpack_sint(values->BestDistortionQPAdjustmentforZone2, 8, 11) |
      util_bitpack_sint(values->BestDistortionQPAdjustmentforZone3, 12, 15) |
      util_bitpack_uint(values->SadHaarThreshold0, 16, 31);

   dw[32] =
      util_bitpack_uint(values->SadHaarThreshold1, 0, 15) |
      util_bitpack_uint(values->SadHaarThreshold2, 16, 31);

   dw[33] =
      util_bitpack_uint(values->MinQP, 0, 7) |
      util_bitpack_uint(values->MaxQP, 8, 15) |
      util_bitpack_uint(values->MaxDeltaQP, 24, 27);

   dw[34] =
      util_bitpack_uint(values->ROIEnable, 0, 0) |
      util_bitpack_uint(values->FwdPredictor0MVEnable, 1, 1) |
      util_bitpack_uint(values->BwdPredictor1MVEnable, 2, 2) |
      util_bitpack_uint(values->MBLevelQPEnable, 3, 3) |
      util_bitpack_uint(values->TargetSizeinWordsMBMaxSizeinWordsMBEnable, 4, 4) |
      util_bitpack_uint(values->PPMVDisable, 8, 8) |
      util_bitpack_uint(values->CoefficientClampEnable, 9, 9) |
      util_bitpack_uint(values->LongTermReferenceFrameBwdRef0Indicator, 10, 10) |
      util_bitpack_uint(values->LongTermReferenceFrameFwdRef2Indicator, 11, 11) |
      util_bitpack_uint(values->LongTermReferenceFrameFwdRef1Indicator, 12, 12) |
      util_bitpack_uint(values->LongTermReferenceFrameFwdRef0Indicator, 13, 13) |
      util_bitpack_uint(values->MidpointSadHaar, 16, 31);

   dw[35] = 0;
}

#define GFX9_VDENC_PIPE_BUF_ADDR_STATE_length     38
#define GFX9_VDENC_PIPE_BUF_ADDR_STATE_length_bias      2
#define GFX9_VDENC_PIPE_BUF_ADDR_STATE_header   \
   .DWordLength                         =     36,  \
   .SubOpcodeB                          =      4,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_VDENC_PIPE_BUF_ADDR_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   struct GFX9_VDENC_PICTURE            DSFWDREF0;
   struct GFX9_VDENC_PICTURE            DSFWDREF1;
   struct GFX9_VDENC_PICTURE            OriginalUncompressedPicture;
   struct GFX9_VDENC_PICTURE            StreamInDataPicture;
   struct GFX9_VDENC_PICTURE            RowStoreScratchBuffer;
   struct GFX9_VDENC_PICTURE            ColocatedMVReadBuffer;
   struct GFX9_VDENC_PICTURE            FWDREF0;
   struct GFX9_VDENC_PICTURE            FWDREF1;
   struct GFX9_VDENC_PICTURE            FWDREF2;
   struct GFX9_VDENC_PICTURE            BWDREF0;
   struct GFX9_VDENC_PICTURE            VDEncStatisticsStreamOut;
};

static inline __attribute__((always_inline)) void
GFX9_VDENC_PIPE_BUF_ADDR_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                    __attribute__((unused)) void * restrict dst,
                                    __attribute__((unused)) const struct GFX9_VDENC_PIPE_BUF_ADDR_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   GFX9_VDENC_PICTURE_pack(data, &dw[1], &values->DSFWDREF0);

   GFX9_VDENC_PICTURE_pack(data, &dw[4], &values->DSFWDREF1);

   dw[7] = 0;

   dw[8] = 0;

   dw[9] = 0;

   GFX9_VDENC_PICTURE_pack(data, &dw[10], &values->OriginalUncompressedPicture);

   GFX9_VDENC_PICTURE_pack(data, &dw[13], &values->StreamInDataPicture);

   GFX9_VDENC_PICTURE_pack(data, &dw[16], &values->RowStoreScratchBuffer);

   GFX9_VDENC_PICTURE_pack(data, &dw[19], &values->ColocatedMVReadBuffer);

   GFX9_VDENC_PICTURE_pack(data, &dw[22], &values->FWDREF0);

   GFX9_VDENC_PICTURE_pack(data, &dw[25], &values->FWDREF1);

   GFX9_VDENC_PICTURE_pack(data, &dw[28], &values->FWDREF2);

   GFX9_VDENC_PICTURE_pack(data, &dw[31], &values->BWDREF0);

   GFX9_VDENC_PICTURE_pack(data, &dw[34], &values->VDEncStatisticsStreamOut);

   dw[37] = 0;
}

#define GFX9_VDENC_PIPE_MODE_SELECT_length      2
#define GFX9_VDENC_PIPE_MODE_SELECT_length_bias      2
#define GFX9_VDENC_PIPE_MODE_SELECT_header      \
   .DWordLength                         =      0,  \
   .SubOpcodeB                          =      0,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_VDENC_PIPE_MODE_SELECT {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             StandardSelect;
#define SS_AVC                                   2
   bool                                 FrameStatisticsStreamOutEnable;
   bool                                 TLBPrefetchEnable;
   bool                                 PAKThresholdCheckEnable;
   bool                                 VDEncStreamInEnable;
   uint32_t                             PAKChromaSubSamplingType;
#define _420                                     1
#define _444                                     3
   bool                                 OutputRangeControlAfterColorSpaceConversion;
};

static inline __attribute__((always_inline)) void
GFX9_VDENC_PIPE_MODE_SELECT_pack(__attribute__((unused)) __gen_user_data *data,
                                 __attribute__((unused)) void * restrict dst,
                                 __attribute__((unused)) const struct GFX9_VDENC_PIPE_MODE_SELECT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->StandardSelect, 0, 3) |
      util_bitpack_uint(values->FrameStatisticsStreamOutEnable, 5, 5) |
      util_bitpack_uint(values->TLBPrefetchEnable, 7, 7) |
      util_bitpack_uint(values->PAKThresholdCheckEnable, 8, 8) |
      util_bitpack_uint(values->VDEncStreamInEnable, 9, 9) |
      util_bitpack_uint(values->PAKChromaSubSamplingType, 15, 16) |
      util_bitpack_uint(values->OutputRangeControlAfterColorSpaceConversion, 17, 17);
}

#define GFX9_VDENC_REF_SURFACE_STATE_length      6
#define GFX9_VDENC_REF_SURFACE_STATE_length_bias      2
#define GFX9_VDENC_REF_SURFACE_STATE_header     \
   .DWordLength                         =      4,  \
   .SubOpcodeB                          =      2,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_VDENC_REF_SURFACE_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   struct GFX9_VDENC_SURFACE_STATE_FIELDS SurfaceState;
};

static inline __attribute__((always_inline)) void
GFX9_VDENC_REF_SURFACE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_VDENC_REF_SURFACE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] = 0;

   GFX9_VDENC_SURFACE_STATE_FIELDS_pack(data, &dw[2], &values->SurfaceState);
}

#define GFX9_VDENC_SRC_SURFACE_STATE_length      6
#define GFX9_VDENC_SRC_SURFACE_STATE_length_bias      2
#define GFX9_VDENC_SRC_SURFACE_STATE_header     \
   .DWordLength                         =      4,  \
   .SubOpcodeB                          =      1,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_VDENC_SRC_SURFACE_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   struct GFX9_VDENC_SURFACE_STATE_FIELDS SurfaceState;
};

static inline __attribute__((always_inline)) void
GFX9_VDENC_SRC_SURFACE_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_VDENC_SRC_SURFACE_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] = 0;

   GFX9_VDENC_SURFACE_STATE_FIELDS_pack(data, &dw[2], &values->SurfaceState);
}

#define GFX9_VDENC_WALKER_STATE_length         2
#define GFX9_VDENC_WALKER_STATE_length_bias      2
#define GFX9_VDENC_WALKER_STATE_header          \
   .DWordLength                         =      0,  \
   .SubOpcodeB                          =      7,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =      1,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_VDENC_WALKER_STATE {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   uint32_t                             MBLCUStartYPosition;
   uint32_t                             MBLCUStartXPosition;
   bool                                 FirstSuperSlice;
   bool                                 TileStreamInOffsetEnable;
   uint32_t                             TileStreamInOffset;
   bool                                 TileRowStoreOffsetEnable;
   uint32_t                             TileRowStoreOffset;
   bool                                 TileStreamOutOffsetEnable;
   uint32_t                             TileStreamOutOffset;
   bool                                 TileLCUStreamOutOffsetEnable;
   uint32_t                             TileLCUStreamOutOffset;
};

static inline __attribute__((always_inline)) void
GFX9_VDENC_WALKER_STATE_pack(__attribute__((unused)) __gen_user_data *data,
                             __attribute__((unused)) void * restrict dst,
                             __attribute__((unused)) const struct GFX9_VDENC_WALKER_STATE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->MBLCUStartYPosition, 0, 8) |
      util_bitpack_uint(values->MBLCUStartXPosition, 16, 24) |
      util_bitpack_uint(values->FirstSuperSlice, 28, 28);
}

#define GFX9_VD_PIPELINE_FLUSH_length          2
#define GFX9_VD_PIPELINE_FLUSH_length_bias      2
#define GFX9_VD_PIPELINE_FLUSH_header           \
   .DWordLength                         =      0,  \
   .SubOpcodeB                          =      0,  \
   .SubOpcodeA                          =      0,  \
   .MediaCommandOpcode                  =     15,  \
   .Pipeline                            =      2,  \
   .CommandType                         =      3

struct GFX9_VD_PIPELINE_FLUSH {
   uint32_t                             DWordLength;
   uint32_t                             SubOpcodeB;
   uint32_t                             SubOpcodeA;
   uint32_t                             MediaCommandOpcode;
   uint32_t                             Pipeline;
   uint32_t                             CommandType;
   bool                                 HEVCPipelineDone;
   bool                                 VDENCPipelineDone;
   bool                                 MFXPipelineDone;
   bool                                 VDCommandMessageParserDone;
   bool                                 HEVCPipelineCommandFlush;
   bool                                 VDENCPipelineCommandFlush;
   bool                                 MFXPipelineCommandFlush;
};

static inline __attribute__((always_inline)) void
GFX9_VD_PIPELINE_FLUSH_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_VD_PIPELINE_FLUSH * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->DWordLength, 0, 11) |
      util_bitpack_uint(values->SubOpcodeB, 16, 20) |
      util_bitpack_uint(values->SubOpcodeA, 21, 22) |
      util_bitpack_uint(values->MediaCommandOpcode, 23, 26) |
      util_bitpack_uint(values->Pipeline, 27, 28) |
      util_bitpack_uint(values->CommandType, 29, 31);

   dw[1] =
      util_bitpack_uint(values->HEVCPipelineDone, 0, 0) |
      util_bitpack_uint(values->VDENCPipelineDone, 1, 1) |
      util_bitpack_uint(values->MFXPipelineDone, 3, 3) |
      util_bitpack_uint(values->VDCommandMessageParserDone, 4, 4) |
      util_bitpack_uint(values->HEVCPipelineCommandFlush, 16, 16) |
      util_bitpack_uint(values->VDENCPipelineCommandFlush, 17, 17) |
      util_bitpack_uint(values->MFXPipelineCommandFlush, 19, 19);
}

#define GFX9_ACTHD_UDW_num                0x205c
#define GFX9_ACTHD_UDW_length                  1
struct GFX9_ACTHD_UDW {
   uint32_t                             HeadPointerUpperDWORD;
};

static inline __attribute__((always_inline)) void
GFX9_ACTHD_UDW_pack(__attribute__((unused)) __gen_user_data *data,
                    __attribute__((unused)) void * restrict dst,
                    __attribute__((unused)) const struct GFX9_ACTHD_UDW * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->HeadPointerUpperDWORD, 0, 15);
}

#define GFX9_BCS_ACTHD_UDW_num            0x2205c
#define GFX9_BCS_ACTHD_UDW_length              1
struct GFX9_BCS_ACTHD_UDW {
   uint32_t                             HeadPointerUpperDWORD;
};

static inline __attribute__((always_inline)) void
GFX9_BCS_ACTHD_UDW_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_BCS_ACTHD_UDW * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->HeadPointerUpperDWORD, 0, 15);
}

#define GFX9_BCS_INSTDONE_num             0x2206c
#define GFX9_BCS_INSTDONE_length               1
struct GFX9_BCS_INSTDONE {
   bool                                 RingEnable;
   bool                                 BlitterIDLE;
   bool                                 GABIDLE;
   bool                                 BCSDone;
};

static inline __attribute__((always_inline)) void
GFX9_BCS_INSTDONE_pack(__attribute__((unused)) __gen_user_data *data,
                       __attribute__((unused)) void * restrict dst,
                       __attribute__((unused)) const struct GFX9_BCS_INSTDONE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->RingEnable, 0, 0) |
      util_bitpack_uint(values->BlitterIDLE, 1, 1) |
      util_bitpack_uint(values->GABIDLE, 2, 2) |
      util_bitpack_uint(values->BCSDone, 3, 3);
}

#define GFX9_BCS_RING_BUFFER_CTL_num      0x2203c
#define GFX9_BCS_RING_BUFFER_CTL_length        1
struct GFX9_BCS_RING_BUFFER_CTL {
   bool                                 RingBufferEnable;
   uint32_t                             AutomaticReportHeadPointer;
#define MI_AUTOREPORT_OFF                        0
#define MI_AUTOREPORT_64KB                       1
#define MI_AUTOREPORT_4KB                        2
#define MI_AUTOREPORT_128KB                      3
   bool                                 DisableRegisterAccesses;
   bool                                 SemaphoreWait;
   bool                                 RBWait;
   uint32_t                             BufferLengthinpages1;
};

static inline __attribute__((always_inline)) void
GFX9_BCS_RING_BUFFER_CTL_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_BCS_RING_BUFFER_CTL * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->RingBufferEnable, 0, 0) |
      util_bitpack_uint(values->AutomaticReportHeadPointer, 1, 2) |
      util_bitpack_uint(values->DisableRegisterAccesses, 8, 8) |
      util_bitpack_uint(values->SemaphoreWait, 10, 10) |
      util_bitpack_uint(values->RBWait, 11, 11) |
      util_bitpack_uint(values->BufferLengthinpages1, 12, 20);
}

#define GFX9_CACHE_MODE_0_num             0x7000
#define GFX9_CACHE_MODE_0_length               1
struct GFX9_CACHE_MODE_0 {
   bool                                 Nulltilefixdisable;
   bool                                 Disableclockgatinginthepixelbackend;
   bool                                 HierarchicalZRAWStallOptimizationDisable;
   bool                                 RCCEvictionPolicy;
   bool                                 STCPMAOptimizationEnable;
   uint32_t                             SamplerL2RequestArbitration;
#define RoundRobin                               0
#define FetchareHighestPriority                  1
#define ConstantsareHighestPriority              2
   bool                                 SamplerL2TLBPrefetchEnable;
   bool                                 SamplerSetRemappingfor3DDisable;
   uint32_t                             MSAACompressionPlaneNumberThresholdforeLLC;
   bool                                 SamplerL2Disable;
   bool                                 NulltilefixdisableMask;
   bool                                 DisableclockgatinginthepixelbackendMask;
   bool                                 HierarchicalZRAWStallOptimizationDisableMask;
   bool                                 RCCEvictionPolicyMask;
   bool                                 STCPMAOptimizationEnableMask;
   uint32_t                             SamplerL2RequestArbitrationMask;
   bool                                 SamplerL2TLBPrefetchEnableMask;
   bool                                 SamplerSetRemappingfor3DDisableMask;
   uint32_t                             MSAACompressionPlaneNumberThresholdforeLLCMask;
   bool                                 SamplerL2DisableMask;
};

static inline __attribute__((always_inline)) void
GFX9_CACHE_MODE_0_pack(__attribute__((unused)) __gen_user_data *data,
                       __attribute__((unused)) void * restrict dst,
                       __attribute__((unused)) const struct GFX9_CACHE_MODE_0 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->Nulltilefixdisable, 0, 0) |
      util_bitpack_uint(values->Disableclockgatinginthepixelbackend, 1, 1) |
      util_bitpack_uint(values->HierarchicalZRAWStallOptimizationDisable, 2, 2) |
      util_bitpack_uint(values->RCCEvictionPolicy, 4, 4) |
      util_bitpack_uint(values->STCPMAOptimizationEnable, 5, 5) |
      util_bitpack_uint(values->SamplerL2RequestArbitration, 6, 7) |
      util_bitpack_uint(values->SamplerL2TLBPrefetchEnable, 9, 9) |
      util_bitpack_uint(values->SamplerSetRemappingfor3DDisable, 11, 11) |
      util_bitpack_uint(values->MSAACompressionPlaneNumberThresholdforeLLC, 12, 14) |
      util_bitpack_uint(values->SamplerL2Disable, 15, 15) |
      util_bitpack_uint(values->NulltilefixdisableMask, 16, 16) |
      util_bitpack_uint(values->DisableclockgatinginthepixelbackendMask, 17, 17) |
      util_bitpack_uint(values->HierarchicalZRAWStallOptimizationDisableMask, 18, 18) |
      util_bitpack_uint(values->RCCEvictionPolicyMask, 20, 20) |
      util_bitpack_uint(values->STCPMAOptimizationEnableMask, 21, 21) |
      util_bitpack_uint(values->SamplerL2RequestArbitrationMask, 22, 23) |
      util_bitpack_uint(values->SamplerL2TLBPrefetchEnableMask, 25, 25) |
      util_bitpack_uint(values->SamplerSetRemappingfor3DDisableMask, 27, 27) |
      util_bitpack_uint(values->MSAACompressionPlaneNumberThresholdforeLLCMask, 28, 30) |
      util_bitpack_uint(values->SamplerL2DisableMask, 31, 31);
}

#define GFX9_CACHE_MODE_1_num             0x7004
#define GFX9_CACHE_MODE_1_length               1
struct GFX9_CACHE_MODE_1 {
   bool                                 PartialResolveDisableInVC;
   bool                                 RCZReadafterexpansioncontrolfix2;
   bool                                 DepthReadHitWriteOnlyOptimizationDisable;
   bool                                 FloatBlendOptimizationEnable;
   bool                                 MCSCacheDisable;
   bool                                 _4X4RCPFESTCOptimizationDisable;
   uint32_t                             SamplerCacheSetXORselection;
   bool                                 MSCRAWHazardAvoidanceBit;
   uint32_t                             NPPMAFixEnable;
   uint32_t                             HIZEvictionPolicy;
   uint32_t                             NPEarlyZFailsDisable;
   bool                                 BlendOptimizationFixDisable;
   bool                                 ColorCompressionDisable;
   bool                                 PartialResolveDisableInVCMask;
   bool                                 RCZReadafterexpansioncontrolfix2Mask;
   bool                                 DepthReadHitWriteOnlyOptimizationDisableMask;
   bool                                 FloatBlendOptimizationEnableMask;
   bool                                 MCSCacheDisableMask;
   bool                                 _4X4RCPFESTCOptimizationDisableMask;
   uint32_t                             SamplerCacheSetXORselectionMask;
   bool                                 MSCRAWHazardAvoidanceBitMask;
   bool                                 NPPMAFixEnableMask;
   bool                                 HIZEvictionPolicyMask;
   bool                                 NPEarlyZFailsDisableMask;
   bool                                 BlendOptimizationFixDisableMask;
   bool                                 ColorCompressionDisableMask;
};

static inline __attribute__((always_inline)) void
GFX9_CACHE_MODE_1_pack(__attribute__((unused)) __gen_user_data *data,
                       __attribute__((unused)) void * restrict dst,
                       __attribute__((unused)) const struct GFX9_CACHE_MODE_1 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->PartialResolveDisableInVC, 1, 1) |
      util_bitpack_uint(values->RCZReadafterexpansioncontrolfix2, 2, 2) |
      util_bitpack_uint(values->DepthReadHitWriteOnlyOptimizationDisable, 3, 3) |
      util_bitpack_uint(values->FloatBlendOptimizationEnable, 4, 4) |
      util_bitpack_uint(values->MCSCacheDisable, 5, 5) |
      util_bitpack_uint(values->_4X4RCPFESTCOptimizationDisable, 6, 6) |
      util_bitpack_uint(values->SamplerCacheSetXORselection, 7, 8) |
      util_bitpack_uint(values->MSCRAWHazardAvoidanceBit, 9, 9) |
      util_bitpack_uint(values->NPPMAFixEnable, 11, 11) |
      util_bitpack_uint(values->HIZEvictionPolicy, 12, 12) |
      util_bitpack_uint(values->NPEarlyZFailsDisable, 13, 13) |
      util_bitpack_uint(values->BlendOptimizationFixDisable, 14, 14) |
      util_bitpack_uint(values->ColorCompressionDisable, 15, 15) |
      util_bitpack_uint(values->PartialResolveDisableInVCMask, 17, 17) |
      util_bitpack_uint(values->RCZReadafterexpansioncontrolfix2Mask, 18, 18) |
      util_bitpack_uint(values->DepthReadHitWriteOnlyOptimizationDisableMask, 19, 19) |
      util_bitpack_uint(values->FloatBlendOptimizationEnableMask, 20, 20) |
      util_bitpack_uint(values->MCSCacheDisableMask, 21, 21) |
      util_bitpack_uint(values->_4X4RCPFESTCOptimizationDisableMask, 22, 22) |
      util_bitpack_uint(values->SamplerCacheSetXORselectionMask, 23, 24) |
      util_bitpack_uint(values->MSCRAWHazardAvoidanceBitMask, 25, 25) |
      util_bitpack_uint(values->NPPMAFixEnableMask, 27, 27) |
      util_bitpack_uint(values->HIZEvictionPolicyMask, 28, 28) |
      util_bitpack_uint(values->NPEarlyZFailsDisableMask, 29, 29) |
      util_bitpack_uint(values->BlendOptimizationFixDisableMask, 30, 30) |
      util_bitpack_uint(values->ColorCompressionDisableMask, 31, 31);
}

#define GFX9_CL_INVOCATION_COUNT_num      0x2338
#define GFX9_CL_INVOCATION_COUNT_length        2
struct GFX9_CL_INVOCATION_COUNT {
   uint64_t                             CLInvocationCountReport;
};

static inline __attribute__((always_inline)) void
GFX9_CL_INVOCATION_COUNT_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_CL_INVOCATION_COUNT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->CLInvocationCountReport, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_CL_PRIMITIVES_COUNT_num      0x2340
#define GFX9_CL_PRIMITIVES_COUNT_length        2
struct GFX9_CL_PRIMITIVES_COUNT {
   uint64_t                             CLPrimitivesCountReport;
};

static inline __attribute__((always_inline)) void
GFX9_CL_PRIMITIVES_COUNT_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_CL_PRIMITIVES_COUNT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->CLPrimitivesCountReport, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_CS_CHICKEN1_num              0x2580
#define GFX9_CS_CHICKEN1_length                1
struct GFX9_CS_CHICKEN1 {
   uint32_t                             ReplayMode;
#define MidcmdbufferPreemption                   0
#define ObjectLevelPreemption                    1
   bool                                 ReplayModeMask;
};

static inline __attribute__((always_inline)) void
GFX9_CS_CHICKEN1_pack(__attribute__((unused)) __gen_user_data *data,
                      __attribute__((unused)) void * restrict dst,
                      __attribute__((unused)) const struct GFX9_CS_CHICKEN1 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->ReplayMode, 0, 0) |
      util_bitpack_uint(values->ReplayModeMask, 16, 16);
}

#define GFX9_CS_DEBUG_MODE2_num           0x20d8
#define GFX9_CS_DEBUG_MODE2_length             1
struct GFX9_CS_DEBUG_MODE2 {
   bool                                 _3DRenderingInstructionDisable;
   bool                                 MediaInstructionDisable;
   bool                                 CONSTANT_BUFFERAddressOffsetDisable;
   bool                                 _3DRenderingInstructionDisableMask;
   bool                                 MediaInstructionDisableMask;
   bool                                 CONSTANT_BUFFERAddressOffsetDisableMask;
};

static inline __attribute__((always_inline)) void
GFX9_CS_DEBUG_MODE2_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_CS_DEBUG_MODE2 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->_3DRenderingInstructionDisable, 0, 0) |
      util_bitpack_uint(values->MediaInstructionDisable, 1, 1) |
      util_bitpack_uint(values->CONSTANT_BUFFERAddressOffsetDisable, 4, 4) |
      util_bitpack_uint(values->_3DRenderingInstructionDisableMask, 16, 16) |
      util_bitpack_uint(values->MediaInstructionDisableMask, 17, 17) |
      util_bitpack_uint(values->CONSTANT_BUFFERAddressOffsetDisableMask, 20, 20);
}

#define GFX9_CS_INVOCATION_COUNT_num      0x2290
#define GFX9_CS_INVOCATION_COUNT_length        2
struct GFX9_CS_INVOCATION_COUNT {
   uint64_t                             CSInvocationCountReport;
};

static inline __attribute__((always_inline)) void
GFX9_CS_INVOCATION_COUNT_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_CS_INVOCATION_COUNT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->CSInvocationCountReport, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_DS_INVOCATION_COUNT_num      0x2308
#define GFX9_DS_INVOCATION_COUNT_length        2
struct GFX9_DS_INVOCATION_COUNT {
   uint64_t                             DSInvocationCountReport;
};

static inline __attribute__((always_inline)) void
GFX9_DS_INVOCATION_COUNT_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_DS_INVOCATION_COUNT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->DSInvocationCountReport, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_FAULT_REG_num                0x4094
#define GFX9_FAULT_REG_length                  1
struct GFX9_FAULT_REG {
   bool                                 ValidBit;
   uint32_t                             FaultType;
#define InvalidPTEFault                          0
#define InvalidPDEFault                          1
#define InvalidPDPEFault                         2
#define InvalidPML4EFault                        3
   uint32_t                             SRCIDofFault;
   uint32_t                             GTTSEL;
#define PPGTT                                    0
#define GGTT                                     1
   uint32_t                             EngineID;
#define GFX                                      0
#define MFX0                                     1
#define MFX1                                     2
#define VEBX                                     3
#define BLT                                      4
#define GUC                                      5
};

static inline __attribute__((always_inline)) void
GFX9_FAULT_REG_pack(__attribute__((unused)) __gen_user_data *data,
                    __attribute__((unused)) void * restrict dst,
                    __attribute__((unused)) const struct GFX9_FAULT_REG * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->ValidBit, 0, 0) |
      util_bitpack_uint(values->FaultType, 1, 2) |
      util_bitpack_uint(values->SRCIDofFault, 3, 10) |
      util_bitpack_uint(values->GTTSEL, 11, 11) |
      util_bitpack_uint(values->EngineID, 12, 14);
}

#define GFX9_GFX_ARB_ERROR_RPT_num        0x40a0
#define GFX9_GFX_ARB_ERROR_RPT_length          1
struct GFX9_GFX_ARB_ERROR_RPT {
   bool                                 TLBPageFaultError;
   bool                                 RSTRMPAVPReadInvalid;
   bool                                 InvalidPageDirectoryEntryError;
   bool                                 ROSTRMPAVPInvalidPhysicalAddress;
   bool                                 TLBPageVTDTranslationError;
   bool                                 WRDPPAVPInvalid;
   bool                                 PageDirectoryEntryVTDTranslationError;
   bool                                 UnloadedPDError;
   bool                                 GuCVTdtranslationPageFault2ndlevelUndefineddoorbell;
   bool                                 NonWBmemorytypeforAdvancedContext;
   bool                                 PASIDNotEnabled;
   bool                                 PASIDBoundaryViolation;
   bool                                 PASIDNotValid;
   bool                                 PASIDWasZeroForUntranslatedRequest;
   bool                                 ContextWasNotMarkedAsPresentWhenDoingDMA;
};

static inline __attribute__((always_inline)) void
GFX9_GFX_ARB_ERROR_RPT_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_GFX_ARB_ERROR_RPT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->TLBPageFaultError, 0, 0) |
      util_bitpack_uint(values->RSTRMPAVPReadInvalid, 1, 1) |
      util_bitpack_uint(values->InvalidPageDirectoryEntryError, 2, 2) |
      util_bitpack_uint(values->ROSTRMPAVPInvalidPhysicalAddress, 3, 3) |
      util_bitpack_uint(values->TLBPageVTDTranslationError, 4, 4) |
      util_bitpack_uint(values->WRDPPAVPInvalid, 5, 5) |
      util_bitpack_uint(values->PageDirectoryEntryVTDTranslationError, 6, 6) |
      util_bitpack_uint(values->UnloadedPDError, 8, 8) |
      util_bitpack_uint(values->GuCVTdtranslationPageFault2ndlevelUndefineddoorbell, 9, 9) |
      util_bitpack_uint(values->NonWBmemorytypeforAdvancedContext, 10, 10) |
      util_bitpack_uint(values->PASIDNotEnabled, 11, 11) |
      util_bitpack_uint(values->PASIDBoundaryViolation, 12, 12) |
      util_bitpack_uint(values->PASIDNotValid, 13, 13) |
      util_bitpack_uint(values->PASIDWasZeroForUntranslatedRequest, 14, 14) |
      util_bitpack_uint(values->ContextWasNotMarkedAsPresentWhenDoingDMA, 15, 15);
}

#define GFX9_GS_INVOCATION_COUNT_num      0x2328
#define GFX9_GS_INVOCATION_COUNT_length        2
struct GFX9_GS_INVOCATION_COUNT {
   uint64_t                             GSInvocationCountReport;
};

static inline __attribute__((always_inline)) void
GFX9_GS_INVOCATION_COUNT_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_GS_INVOCATION_COUNT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->GSInvocationCountReport, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_GS_PRIMITIVES_COUNT_num      0x2330
#define GFX9_GS_PRIMITIVES_COUNT_length        2
struct GFX9_GS_PRIMITIVES_COUNT {
   uint64_t                             GSPrimitivesCountReport;
};

static inline __attribute__((always_inline)) void
GFX9_GS_PRIMITIVES_COUNT_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_GS_PRIMITIVES_COUNT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->GSPrimitivesCountReport, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_GT_MODE_num                  0x7008
#define GFX9_GT_MODE_length                    1
struct GFX9_GT_MODE {
   uint32_t                             SubsliceHashing;
#define _8x8                                     0
#define _16x4                                    1
#define _8x4                                     2
#define _16x16                                   3
   uint32_t                             SliceHashing;
#define NORMAL                                   0
#define DISABLED                                 1
#define _32x16                                   2
#define _32x32                                   3
   int32_t                              SubsliceHashingMask;
   int32_t                              SliceHashingMask;
};

static inline __attribute__((always_inline)) void
GFX9_GT_MODE_pack(__attribute__((unused)) __gen_user_data *data,
                  __attribute__((unused)) void * restrict dst,
                  __attribute__((unused)) const struct GFX9_GT_MODE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->SubsliceHashing, 8, 9) |
      util_bitpack_uint(values->SliceHashing, 11, 12) |
      util_bitpack_sint(values->SubsliceHashingMask, 24, 25) |
      util_bitpack_sint(values->SliceHashingMask, 27, 28);
}

#define GFX9_HS_INVOCATION_COUNT_num      0x2300
#define GFX9_HS_INVOCATION_COUNT_length        2
struct GFX9_HS_INVOCATION_COUNT {
   uint64_t                             HSInvocationCountReport;
};

static inline __attribute__((always_inline)) void
GFX9_HS_INVOCATION_COUNT_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_HS_INVOCATION_COUNT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->HSInvocationCountReport, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_IA_PRIMITIVES_COUNT_num      0x2318
#define GFX9_IA_PRIMITIVES_COUNT_length        2
struct GFX9_IA_PRIMITIVES_COUNT {
   uint64_t                             IAPrimitivesCountReport;
};

static inline __attribute__((always_inline)) void
GFX9_IA_PRIMITIVES_COUNT_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_IA_PRIMITIVES_COUNT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->IAPrimitivesCountReport, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_IA_VERTICES_COUNT_num        0x2310
#define GFX9_IA_VERTICES_COUNT_length          2
struct GFX9_IA_VERTICES_COUNT {
   uint64_t                             IAVerticesCountReport;
};

static inline __attribute__((always_inline)) void
GFX9_IA_VERTICES_COUNT_pack(__attribute__((unused)) __gen_user_data *data,
                            __attribute__((unused)) void * restrict dst,
                            __attribute__((unused)) const struct GFX9_IA_VERTICES_COUNT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->IAVerticesCountReport, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_INSTDONE_1_num               0x206c
#define GFX9_INSTDONE_1_length                 1
struct GFX9_INSTDONE_1 {
   bool                                 PRB0RingEnable;
   bool                                 VFGDone;
   bool                                 VSDone;
   bool                                 HSDone;
   bool                                 TEDone;
   bool                                 DSDone;
   bool                                 GSDone;
   bool                                 SOLDone;
   bool                                 CLDone;
   bool                                 SFDone;
   bool                                 TDGDone;
   bool                                 URBMDone;
   bool                                 SVGDone;
   bool                                 GAFSDone;
   bool                                 VFEDone;
   bool                                 TSGDone;
   bool                                 GAFMDone;
   bool                                 GAMDone;
   bool                                 RSDone;
   bool                                 CSDone;
   bool                                 SDEDone;
   bool                                 RCCFBCCSDone;
};

static inline __attribute__((always_inline)) void
GFX9_INSTDONE_1_pack(__attribute__((unused)) __gen_user_data *data,
                     __attribute__((unused)) void * restrict dst,
                     __attribute__((unused)) const struct GFX9_INSTDONE_1 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->PRB0RingEnable, 0, 0) |
      util_bitpack_uint(values->VFGDone, 1, 1) |
      util_bitpack_uint(values->VSDone, 2, 2) |
      util_bitpack_uint(values->HSDone, 3, 3) |
      util_bitpack_uint(values->TEDone, 4, 4) |
      util_bitpack_uint(values->DSDone, 5, 5) |
      util_bitpack_uint(values->GSDone, 6, 6) |
      util_bitpack_uint(values->SOLDone, 7, 7) |
      util_bitpack_uint(values->CLDone, 8, 8) |
      util_bitpack_uint(values->SFDone, 9, 9) |
      util_bitpack_uint(values->TDGDone, 12, 12) |
      util_bitpack_uint(values->URBMDone, 13, 13) |
      util_bitpack_uint(values->SVGDone, 14, 14) |
      util_bitpack_uint(values->GAFSDone, 15, 15) |
      util_bitpack_uint(values->VFEDone, 16, 16) |
      util_bitpack_uint(values->TSGDone, 17, 17) |
      util_bitpack_uint(values->GAFMDone, 18, 18) |
      util_bitpack_uint(values->GAMDone, 19, 19) |
      util_bitpack_uint(values->RSDone, 20, 20) |
      util_bitpack_uint(values->CSDone, 21, 21) |
      util_bitpack_uint(values->SDEDone, 22, 22) |
      util_bitpack_uint(values->RCCFBCCSDone, 23, 23);
}

#define GFX9_L3CNTLREG_num                0x7034
#define GFX9_L3CNTLREG_length                  1
struct GFX9_L3CNTLREG {
   bool                                 SLMEnable;
   uint32_t                             URBAllocation;
   uint32_t                             ROAllocation;
   uint32_t                             DCAllocation;
   uint32_t                             AllAllocation;
};

static inline __attribute__((always_inline)) void
GFX9_L3CNTLREG_pack(__attribute__((unused)) __gen_user_data *data,
                    __attribute__((unused)) void * restrict dst,
                    __attribute__((unused)) const struct GFX9_L3CNTLREG * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->SLMEnable, 0, 0) |
      util_bitpack_uint(values->URBAllocation, 1, 7) |
      util_bitpack_uint(values->ROAllocation, 11, 17) |
      util_bitpack_uint(values->DCAllocation, 18, 24) |
      util_bitpack_uint(values->AllAllocation, 25, 31);
}

#define GFX9_PERFCNT1_num                 0x91b8
#define GFX9_PERFCNT1_length                   2
struct GFX9_PERFCNT1 {
   uint64_t                             Value;
   uint32_t                             EventSelection;
   bool                                 CounterClear;
   bool                                 EdgeDetect;
   bool                                 OverflowEnable;
   bool                                 CounterEnable;
};

static inline __attribute__((always_inline)) void
GFX9_PERFCNT1_pack(__attribute__((unused)) __gen_user_data *data,
                   __attribute__((unused)) void * restrict dst,
                   __attribute__((unused)) const struct GFX9_PERFCNT1 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->Value, 0, 43) |
      util_bitpack_uint(values->EventSelection, 52, 59) |
      util_bitpack_uint(values->CounterClear, 60, 60) |
      util_bitpack_uint(values->EdgeDetect, 61, 61) |
      util_bitpack_uint(values->OverflowEnable, 62, 62) |
      util_bitpack_uint(values->CounterEnable, 63, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_PERFCNT2_num                 0x91c0
#define GFX9_PERFCNT2_length                   2
struct GFX9_PERFCNT2 {
   uint64_t                             Value;
   uint32_t                             EventSelection;
   bool                                 CounterClear;
   bool                                 EdgeDetect;
   bool                                 OverflowEnable;
   bool                                 CounterEnable;
};

static inline __attribute__((always_inline)) void
GFX9_PERFCNT2_pack(__attribute__((unused)) __gen_user_data *data,
                   __attribute__((unused)) void * restrict dst,
                   __attribute__((unused)) const struct GFX9_PERFCNT2 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->Value, 0, 43) |
      util_bitpack_uint(values->EventSelection, 52, 59) |
      util_bitpack_uint(values->CounterClear, 60, 60) |
      util_bitpack_uint(values->EdgeDetect, 61, 61) |
      util_bitpack_uint(values->OverflowEnable, 62, 62) |
      util_bitpack_uint(values->CounterEnable, 63, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_PS_INVOCATION_COUNT_num      0x2348
#define GFX9_PS_INVOCATION_COUNT_length        2
struct GFX9_PS_INVOCATION_COUNT {
   uint64_t                             PSInvocationCountReport;
};

static inline __attribute__((always_inline)) void
GFX9_PS_INVOCATION_COUNT_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_PS_INVOCATION_COUNT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->PSInvocationCountReport, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_RCS_RING_BUFFER_CTL_num      0x203c
#define GFX9_RCS_RING_BUFFER_CTL_length        1
struct GFX9_RCS_RING_BUFFER_CTL {
   bool                                 RingBufferEnable;
   uint32_t                             AutomaticReportHeadPointer;
#define MI_AUTOREPORT_OFF                        0
#define MI_AUTOREPORT_64KB                       1
#define MI_AUTOREPORT_4KB                        2
#define MI_AUTOREPORT_128KB                      3
   bool                                 SemaphoreWait;
   bool                                 RBWait;
   uint32_t                             BufferLengthinpages1;
};

static inline __attribute__((always_inline)) void
GFX9_RCS_RING_BUFFER_CTL_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_RCS_RING_BUFFER_CTL * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->RingBufferEnable, 0, 0) |
      util_bitpack_uint(values->AutomaticReportHeadPointer, 1, 2) |
      util_bitpack_uint(values->SemaphoreWait, 10, 10) |
      util_bitpack_uint(values->RBWait, 11, 11) |
      util_bitpack_uint(values->BufferLengthinpages1, 12, 20);
}

#define GFX9_ROW_INSTDONE_num             0xe164
#define GFX9_ROW_INSTDONE_length               1
struct GFX9_ROW_INSTDONE {
   bool                                 BCDone;
   bool                                 PSDDone;
   bool                                 DAPRDone;
   bool                                 TDLDone;
   bool                                 ICDone;
   bool                                 MA0Done;
   bool                                 EU00DoneSS0;
   bool                                 EU01DoneSS0;
   bool                                 EU02DoneSS0;
   bool                                 EU03DoneSS0;
   bool                                 EU10DoneSS0;
   bool                                 EU11DoneSS0;
   bool                                 EU12DoneSS0;
   bool                                 EU13DoneSS0;
   bool                                 MA1DoneSS0;
};

static inline __attribute__((always_inline)) void
GFX9_ROW_INSTDONE_pack(__attribute__((unused)) __gen_user_data *data,
                       __attribute__((unused)) void * restrict dst,
                       __attribute__((unused)) const struct GFX9_ROW_INSTDONE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->BCDone, 0, 0) |
      util_bitpack_uint(values->PSDDone, 1, 1) |
      util_bitpack_uint(values->DAPRDone, 3, 3) |
      util_bitpack_uint(values->TDLDone, 6, 6) |
      util_bitpack_uint(values->ICDone, 12, 12) |
      util_bitpack_uint(values->MA0Done, 15, 15) |
      util_bitpack_uint(values->EU00DoneSS0, 16, 16) |
      util_bitpack_uint(values->EU01DoneSS0, 17, 17) |
      util_bitpack_uint(values->EU02DoneSS0, 18, 18) |
      util_bitpack_uint(values->EU03DoneSS0, 19, 19) |
      util_bitpack_uint(values->EU10DoneSS0, 21, 21) |
      util_bitpack_uint(values->EU11DoneSS0, 22, 22) |
      util_bitpack_uint(values->EU12DoneSS0, 23, 23) |
      util_bitpack_uint(values->EU13DoneSS0, 24, 24) |
      util_bitpack_uint(values->MA1DoneSS0, 26, 26);
}

#define GFX9_RPSTAT0_num                  0xa01c
#define GFX9_RPSTAT0_length                    1
struct GFX9_RPSTAT0 {
   uint32_t                             PreviousGTFrequency;
   uint32_t                             CurrentGTFrequency;
};

static inline __attribute__((always_inline)) void
GFX9_RPSTAT0_pack(__attribute__((unused)) __gen_user_data *data,
                  __attribute__((unused)) void * restrict dst,
                  __attribute__((unused)) const struct GFX9_RPSTAT0 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->PreviousGTFrequency, 0, 8) |
      util_bitpack_uint(values->CurrentGTFrequency, 23, 31);
}

#define GFX9_SAMPLER_INSTDONE_num         0xe160
#define GFX9_SAMPLER_INSTDONE_length           1
struct GFX9_SAMPLER_INSTDONE {
   bool                                 IMEDone;
   bool                                 PL0Done;
   bool                                 SO0Done;
   bool                                 DG0Done;
   bool                                 FT0Done;
   bool                                 DM0Done;
   bool                                 SCDone;
   bool                                 FL0Done;
   bool                                 QCDone;
   bool                                 SVSMDone;
   bool                                 SI0Done;
   bool                                 MT0Done;
   bool                                 AVSDone;
   bool                                 IEFDone;
   bool                                 CREDone;
   bool                                 SVSMARB3;
   bool                                 SVSMARB2;
   bool                                 SVSMARB1;
   bool                                 SVSMAdapter;
   bool                                 BDMDone;
};

static inline __attribute__((always_inline)) void
GFX9_SAMPLER_INSTDONE_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_SAMPLER_INSTDONE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->IMEDone, 0, 0) |
      util_bitpack_uint(values->PL0Done, 1, 1) |
      util_bitpack_uint(values->SO0Done, 2, 2) |
      util_bitpack_uint(values->DG0Done, 3, 3) |
      util_bitpack_uint(values->FT0Done, 4, 4) |
      util_bitpack_uint(values->DM0Done, 5, 5) |
      util_bitpack_uint(values->SCDone, 6, 6) |
      util_bitpack_uint(values->FL0Done, 7, 7) |
      util_bitpack_uint(values->QCDone, 8, 8) |
      util_bitpack_uint(values->SVSMDone, 9, 9) |
      util_bitpack_uint(values->SI0Done, 10, 10) |
      util_bitpack_uint(values->MT0Done, 11, 11) |
      util_bitpack_uint(values->AVSDone, 12, 12) |
      util_bitpack_uint(values->IEFDone, 13, 13) |
      util_bitpack_uint(values->CREDone, 14, 14) |
      util_bitpack_uint(values->SVSMARB3, 15, 15) |
      util_bitpack_uint(values->SVSMARB2, 16, 16) |
      util_bitpack_uint(values->SVSMARB1, 17, 17) |
      util_bitpack_uint(values->SVSMAdapter, 18, 18) |
      util_bitpack_uint(values->BDMDone, 19, 19);
}

#define GFX9_SC_INSTDONE_num              0x7100
#define GFX9_SC_INSTDONE_length                1
struct GFX9_SC_INSTDONE {
   bool                                 SVLDone;
   bool                                 WMFEDone;
   bool                                 WMBEDone;
   bool                                 HIZDone;
   bool                                 STCDone;
   bool                                 IZDone;
   bool                                 SBEDone;
   bool                                 RCZDone;
   bool                                 RCCDone;
   bool                                 RCPBEDone;
   bool                                 RCPFEDone;
   bool                                 DAPBDone;
   bool                                 DAPRBEDone;
   bool                                 SARBDone;
   bool                                 DC0Done;
   bool                                 DC1Done;
   bool                                 DC2Done;
   bool                                 DC3Done;
   bool                                 GW0Done;
   bool                                 GW1Done;
   bool                                 GW2Done;
   bool                                 GW3Done;
   bool                                 TDCDone;
};

static inline __attribute__((always_inline)) void
GFX9_SC_INSTDONE_pack(__attribute__((unused)) __gen_user_data *data,
                      __attribute__((unused)) void * restrict dst,
                      __attribute__((unused)) const struct GFX9_SC_INSTDONE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->SVLDone, 0, 0) |
      util_bitpack_uint(values->WMFEDone, 1, 1) |
      util_bitpack_uint(values->WMBEDone, 2, 2) |
      util_bitpack_uint(values->HIZDone, 3, 3) |
      util_bitpack_uint(values->STCDone, 4, 4) |
      util_bitpack_uint(values->IZDone, 5, 5) |
      util_bitpack_uint(values->SBEDone, 6, 6) |
      util_bitpack_uint(values->RCZDone, 8, 8) |
      util_bitpack_uint(values->RCCDone, 9, 9) |
      util_bitpack_uint(values->RCPBEDone, 10, 10) |
      util_bitpack_uint(values->RCPFEDone, 11, 11) |
      util_bitpack_uint(values->DAPBDone, 12, 12) |
      util_bitpack_uint(values->DAPRBEDone, 13, 13) |
      util_bitpack_uint(values->SARBDone, 15, 15) |
      util_bitpack_uint(values->DC0Done, 16, 16) |
      util_bitpack_uint(values->DC1Done, 17, 17) |
      util_bitpack_uint(values->DC2Done, 18, 18) |
      util_bitpack_uint(values->DC3Done, 19, 19) |
      util_bitpack_uint(values->GW0Done, 20, 20) |
      util_bitpack_uint(values->GW1Done, 21, 21) |
      util_bitpack_uint(values->GW2Done, 22, 22) |
      util_bitpack_uint(values->GW3Done, 23, 23) |
      util_bitpack_uint(values->TDCDone, 24, 24);
}

#define GFX9_SLICE_COMMON_ECO_CHICKEN1_num 0x731c
#define GFX9_SLICE_COMMON_ECO_CHICKEN1_length      1
struct GFX9_SLICE_COMMON_ECO_CHICKEN1 {
   uint32_t                             GLKBarrierMode;
#define GLK_BARRIER_MODE_GPGPU                   0
#define GLK_BARRIER_MODE_3D_HULL                 1
   bool                                 GLKBarrierModeMask;
};

static inline __attribute__((always_inline)) void
GFX9_SLICE_COMMON_ECO_CHICKEN1_pack(__attribute__((unused)) __gen_user_data *data,
                                    __attribute__((unused)) void * restrict dst,
                                    __attribute__((unused)) const struct GFX9_SLICE_COMMON_ECO_CHICKEN1 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->GLKBarrierMode, 7, 7) |
      util_bitpack_uint(values->GLKBarrierModeMask, 23, 23);
}

#define GFX9_SO_NUM_PRIMS_WRITTEN0_num    0x5200
#define GFX9_SO_NUM_PRIMS_WRITTEN0_length      2
struct GFX9_SO_NUM_PRIMS_WRITTEN0 {
   uint64_t                             NumPrimsWrittenCount;
};

static inline __attribute__((always_inline)) void
GFX9_SO_NUM_PRIMS_WRITTEN0_pack(__attribute__((unused)) __gen_user_data *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GFX9_SO_NUM_PRIMS_WRITTEN0 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->NumPrimsWrittenCount, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_SO_NUM_PRIMS_WRITTEN1_num    0x5208
#define GFX9_SO_NUM_PRIMS_WRITTEN1_length      2
struct GFX9_SO_NUM_PRIMS_WRITTEN1 {
   uint64_t                             NumPrimsWrittenCount;
};

static inline __attribute__((always_inline)) void
GFX9_SO_NUM_PRIMS_WRITTEN1_pack(__attribute__((unused)) __gen_user_data *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GFX9_SO_NUM_PRIMS_WRITTEN1 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->NumPrimsWrittenCount, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_SO_NUM_PRIMS_WRITTEN2_num    0x5210
#define GFX9_SO_NUM_PRIMS_WRITTEN2_length      2
struct GFX9_SO_NUM_PRIMS_WRITTEN2 {
   uint64_t                             NumPrimsWrittenCount;
};

static inline __attribute__((always_inline)) void
GFX9_SO_NUM_PRIMS_WRITTEN2_pack(__attribute__((unused)) __gen_user_data *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GFX9_SO_NUM_PRIMS_WRITTEN2 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->NumPrimsWrittenCount, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_SO_NUM_PRIMS_WRITTEN3_num    0x5218
#define GFX9_SO_NUM_PRIMS_WRITTEN3_length      2
struct GFX9_SO_NUM_PRIMS_WRITTEN3 {
   uint64_t                             NumPrimsWrittenCount;
};

static inline __attribute__((always_inline)) void
GFX9_SO_NUM_PRIMS_WRITTEN3_pack(__attribute__((unused)) __gen_user_data *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GFX9_SO_NUM_PRIMS_WRITTEN3 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->NumPrimsWrittenCount, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_SO_PRIM_STORAGE_NEEDED0_num  0x5240
#define GFX9_SO_PRIM_STORAGE_NEEDED0_length      2
struct GFX9_SO_PRIM_STORAGE_NEEDED0 {
   uint64_t                             PrimStorageNeededCount;
};

static inline __attribute__((always_inline)) void
GFX9_SO_PRIM_STORAGE_NEEDED0_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_SO_PRIM_STORAGE_NEEDED0 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->PrimStorageNeededCount, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_SO_PRIM_STORAGE_NEEDED1_num  0x5248
#define GFX9_SO_PRIM_STORAGE_NEEDED1_length      2
struct GFX9_SO_PRIM_STORAGE_NEEDED1 {
   uint64_t                             PrimStorageNeededCount;
};

static inline __attribute__((always_inline)) void
GFX9_SO_PRIM_STORAGE_NEEDED1_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_SO_PRIM_STORAGE_NEEDED1 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->PrimStorageNeededCount, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_SO_PRIM_STORAGE_NEEDED2_num  0x5250
#define GFX9_SO_PRIM_STORAGE_NEEDED2_length      2
struct GFX9_SO_PRIM_STORAGE_NEEDED2 {
   uint64_t                             PrimStorageNeededCount;
};

static inline __attribute__((always_inline)) void
GFX9_SO_PRIM_STORAGE_NEEDED2_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_SO_PRIM_STORAGE_NEEDED2 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->PrimStorageNeededCount, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_SO_PRIM_STORAGE_NEEDED3_num  0x5258
#define GFX9_SO_PRIM_STORAGE_NEEDED3_length      2
struct GFX9_SO_PRIM_STORAGE_NEEDED3 {
   uint64_t                             PrimStorageNeededCount;
};

static inline __attribute__((always_inline)) void
GFX9_SO_PRIM_STORAGE_NEEDED3_pack(__attribute__((unused)) __gen_user_data *data,
                                  __attribute__((unused)) void * restrict dst,
                                  __attribute__((unused)) const struct GFX9_SO_PRIM_STORAGE_NEEDED3 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->PrimStorageNeededCount, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#define GFX9_SO_WRITE_OFFSET0_num         0x5280
#define GFX9_SO_WRITE_OFFSET0_length           1
struct GFX9_SO_WRITE_OFFSET0 {
   uint64_t                             WriteOffset;
};

static inline __attribute__((always_inline)) void
GFX9_SO_WRITE_OFFSET0_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_SO_WRITE_OFFSET0 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      __gen_offset(values->WriteOffset, 2, 31);
}

#define GFX9_SO_WRITE_OFFSET1_num         0x5284
#define GFX9_SO_WRITE_OFFSET1_length           1
struct GFX9_SO_WRITE_OFFSET1 {
   uint64_t                             WriteOffset;
};

static inline __attribute__((always_inline)) void
GFX9_SO_WRITE_OFFSET1_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_SO_WRITE_OFFSET1 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      __gen_offset(values->WriteOffset, 2, 31);
}

#define GFX9_SO_WRITE_OFFSET2_num         0x5288
#define GFX9_SO_WRITE_OFFSET2_length           1
struct GFX9_SO_WRITE_OFFSET2 {
   uint64_t                             WriteOffset;
};

static inline __attribute__((always_inline)) void
GFX9_SO_WRITE_OFFSET2_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_SO_WRITE_OFFSET2 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      __gen_offset(values->WriteOffset, 2, 31);
}

#define GFX9_SO_WRITE_OFFSET3_num         0x528c
#define GFX9_SO_WRITE_OFFSET3_length           1
struct GFX9_SO_WRITE_OFFSET3 {
   uint64_t                             WriteOffset;
};

static inline __attribute__((always_inline)) void
GFX9_SO_WRITE_OFFSET3_pack(__attribute__((unused)) __gen_user_data *data,
                           __attribute__((unused)) void * restrict dst,
                           __attribute__((unused)) const struct GFX9_SO_WRITE_OFFSET3 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      __gen_offset(values->WriteOffset, 2, 31);
}

#define GFX9_VCS2_RING_BUFFER_CTL_num     0x1203c
#define GFX9_VCS2_RING_BUFFER_CTL_length       1
struct GFX9_VCS2_RING_BUFFER_CTL {
   bool                                 RingBufferEnable;
   uint32_t                             AutomaticReportHeadPointer;
#define MI_AUTOREPORT_OFF                        0
#define MI_AUTOREPORT_64KB                       1
#define MI_AUTOREPORT_4KB                        2
#define MI_AUTOREPORT_128KB                      3
   bool                                 DisableRegisterAccesses;
   bool                                 SemaphoreWait;
   bool                                 RBWait;
   uint32_t                             BufferLengthinpages1;
};

static inline __attribute__((always_inline)) void
GFX9_VCS2_RING_BUFFER_CTL_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_VCS2_RING_BUFFER_CTL * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->RingBufferEnable, 0, 0) |
      util_bitpack_uint(values->AutomaticReportHeadPointer, 1, 2) |
      util_bitpack_uint(values->DisableRegisterAccesses, 8, 8) |
      util_bitpack_uint(values->SemaphoreWait, 10, 10) |
      util_bitpack_uint(values->RBWait, 11, 11) |
      util_bitpack_uint(values->BufferLengthinpages1, 12, 20);
}

#define GFX9_VCS_ACTHD_UDW_num            0x1205c
#define GFX9_VCS_ACTHD_UDW_length              1
struct GFX9_VCS_ACTHD_UDW {
   uint32_t                             HeadPointerUpperDWORD;
};

static inline __attribute__((always_inline)) void
GFX9_VCS_ACTHD_UDW_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_VCS_ACTHD_UDW * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->HeadPointerUpperDWORD, 0, 15);
}

#define GFX9_VCS_INSTDONE_num             0x1206c
#define GFX9_VCS_INSTDONE_length               1
struct GFX9_VCS_INSTDONE {
   bool                                 RingEnable;
   bool                                 USBDone;
   bool                                 QRCDone;
   bool                                 SECDone;
   bool                                 MPCDone;
   bool                                 VFTDone;
   bool                                 BSPDone;
   bool                                 VLFDone;
   bool                                 VOPDone;
   bool                                 VMCDone;
   bool                                 VIPDone;
   bool                                 VITDone;
   bool                                 VDSDone;
   bool                                 VMXDone;
   bool                                 VCPDone;
   bool                                 VCDDone;
   bool                                 VADDone;
   bool                                 VMDDone;
   bool                                 VISDone;
   bool                                 VACDone;
   bool                                 VAMDone;
   bool                                 JPGDone;
   bool                                 VBPDone;
   bool                                 VHRDone;
   bool                                 VCIDone;
   bool                                 VCRDone;
   bool                                 VINDone;
   bool                                 VPRDone;
   bool                                 VTQDone;
   bool                                 Reserved;
   bool                                 VCSDone;
   bool                                 GACDone;
};

static inline __attribute__((always_inline)) void
GFX9_VCS_INSTDONE_pack(__attribute__((unused)) __gen_user_data *data,
                       __attribute__((unused)) void * restrict dst,
                       __attribute__((unused)) const struct GFX9_VCS_INSTDONE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->RingEnable, 0, 0) |
      util_bitpack_uint(values->USBDone, 1, 1) |
      util_bitpack_uint(values->QRCDone, 2, 2) |
      util_bitpack_uint(values->SECDone, 3, 3) |
      util_bitpack_uint(values->MPCDone, 4, 4) |
      util_bitpack_uint(values->VFTDone, 5, 5) |
      util_bitpack_uint(values->BSPDone, 6, 6) |
      util_bitpack_uint(values->VLFDone, 7, 7) |
      util_bitpack_uint(values->VOPDone, 8, 8) |
      util_bitpack_uint(values->VMCDone, 9, 9) |
      util_bitpack_uint(values->VIPDone, 10, 10) |
      util_bitpack_uint(values->VITDone, 11, 11) |
      util_bitpack_uint(values->VDSDone, 12, 12) |
      util_bitpack_uint(values->VMXDone, 13, 13) |
      util_bitpack_uint(values->VCPDone, 14, 14) |
      util_bitpack_uint(values->VCDDone, 15, 15) |
      util_bitpack_uint(values->VADDone, 16, 16) |
      util_bitpack_uint(values->VMDDone, 17, 17) |
      util_bitpack_uint(values->VISDone, 18, 18) |
      util_bitpack_uint(values->VACDone, 19, 19) |
      util_bitpack_uint(values->VAMDone, 20, 20) |
      util_bitpack_uint(values->JPGDone, 21, 21) |
      util_bitpack_uint(values->VBPDone, 22, 22) |
      util_bitpack_uint(values->VHRDone, 23, 23) |
      util_bitpack_uint(values->VCIDone, 24, 24) |
      util_bitpack_uint(values->VCRDone, 25, 25) |
      util_bitpack_uint(values->VINDone, 26, 26) |
      util_bitpack_uint(values->VPRDone, 27, 27) |
      util_bitpack_uint(values->VTQDone, 28, 28) |
      util_bitpack_uint(values->Reserved, 29, 29) |
      util_bitpack_uint(values->VCSDone, 30, 30) |
      util_bitpack_uint(values->GACDone, 31, 31);
}

#define GFX9_VCS_RING_BUFFER_CTL_num      0x1203c
#define GFX9_VCS_RING_BUFFER_CTL_length        1
struct GFX9_VCS_RING_BUFFER_CTL {
   bool                                 RingBufferEnable;
   uint32_t                             AutomaticReportHeadPointer;
#define MI_AUTOREPORT_OFF                        0
#define MI_AUTOREPORT_64KB                       1
#define MI_AUTOREPORT_4KB                        2
#define MI_AUTOREPORT_128KB                      3
   bool                                 DisableRegisterAccesses;
   bool                                 SemaphoreWait;
   bool                                 RBWait;
   uint32_t                             BufferLengthinpages1;
};

static inline __attribute__((always_inline)) void
GFX9_VCS_RING_BUFFER_CTL_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_VCS_RING_BUFFER_CTL * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->RingBufferEnable, 0, 0) |
      util_bitpack_uint(values->AutomaticReportHeadPointer, 1, 2) |
      util_bitpack_uint(values->DisableRegisterAccesses, 8, 8) |
      util_bitpack_uint(values->SemaphoreWait, 10, 10) |
      util_bitpack_uint(values->RBWait, 11, 11) |
      util_bitpack_uint(values->BufferLengthinpages1, 12, 20);
}

#define GFX9_VECS_ACTHD_UDW_num           0x1a05c
#define GFX9_VECS_ACTHD_UDW_length             1
struct GFX9_VECS_ACTHD_UDW {
   uint32_t                             HeadPointerUpperDWORD;
};

static inline __attribute__((always_inline)) void
GFX9_VECS_ACTHD_UDW_pack(__attribute__((unused)) __gen_user_data *data,
                         __attribute__((unused)) void * restrict dst,
                         __attribute__((unused)) const struct GFX9_VECS_ACTHD_UDW * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->HeadPointerUpperDWORD, 0, 15);
}

#define GFX9_VECS_INSTDONE_num            0x1a06c
#define GFX9_VECS_INSTDONE_length              1
struct GFX9_VECS_INSTDONE {
   bool                                 RingEnable;
   bool                                 VECSDone;
   bool                                 GAMDone;
};

static inline __attribute__((always_inline)) void
GFX9_VECS_INSTDONE_pack(__attribute__((unused)) __gen_user_data *data,
                        __attribute__((unused)) void * restrict dst,
                        __attribute__((unused)) const struct GFX9_VECS_INSTDONE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->RingEnable, 0, 0) |
      util_bitpack_uint(values->VECSDone, 30, 30) |
      util_bitpack_uint(values->GAMDone, 31, 31);
}

#define GFX9_VECS_RING_BUFFER_CTL_num     0x1a03c
#define GFX9_VECS_RING_BUFFER_CTL_length       1
struct GFX9_VECS_RING_BUFFER_CTL {
   bool                                 RingBufferEnable;
   uint32_t                             AutomaticReportHeadPointer;
#define MI_AUTOREPORT_OFF                        0
#define MI_AUTOREPORT_64KB                       1
#define MI_AUTOREPORT_4KB                        2
#define MI_AUTOREPORT_128KB                      3
   bool                                 DisableRegisterAccesses;
   bool                                 SemaphoreWait;
   bool                                 RBWait;
   uint32_t                             BufferLengthinpages1;
};

static inline __attribute__((always_inline)) void
GFX9_VECS_RING_BUFFER_CTL_pack(__attribute__((unused)) __gen_user_data *data,
                               __attribute__((unused)) void * restrict dst,
                               __attribute__((unused)) const struct GFX9_VECS_RING_BUFFER_CTL * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      util_bitpack_uint(values->RingBufferEnable, 0, 0) |
      util_bitpack_uint(values->AutomaticReportHeadPointer, 1, 2) |
      util_bitpack_uint(values->DisableRegisterAccesses, 8, 8) |
      util_bitpack_uint(values->SemaphoreWait, 10, 10) |
      util_bitpack_uint(values->RBWait, 11, 11) |
      util_bitpack_uint(values->BufferLengthinpages1, 12, 20);
}

#define GFX9_VS_INVOCATION_COUNT_num      0x2320
#define GFX9_VS_INVOCATION_COUNT_length        2
struct GFX9_VS_INVOCATION_COUNT {
   uint64_t                             VSInvocationCountReport;
};

static inline __attribute__((always_inline)) void
GFX9_VS_INVOCATION_COUNT_pack(__attribute__((unused)) __gen_user_data *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GFX9_VS_INVOCATION_COUNT * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      util_bitpack_uint(values->VSInvocationCountReport, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;
}

#endif /* GFX9_SKL_PACK_H */
