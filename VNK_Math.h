#ifndef __VNK_MATH_H
#define __VNK_MATH_H

#include "VNK_System.h"

/**
 * VNK_Min
 */
i8 VNK_MinI8(i8 a, i8 b);
u8 VNK_MinU8(u8 a, u8 b);
i16 VNK_MinI16(i16 a, i16 b);
u16 VNK_MinU16(u16 a, u16 b);
i32 VNK_MinI32(i32 a, i32 b);
u32 VNK_MinU32(u32 a, u32 b);
f32 VNK_MinF32(f32 a, f32 b);
f64 VNK_MinF64(f64 a, f64 b);

/**
 * VNK_Max
 */
i8 VNK_MaxI8(i8 a, i8 b);
u8 VNK_MaxU8(u8 a, u8 b);
i16 VNK_MaxI16(i16 a, i16 b);
u16 VNK_MaxU16(u16 a, u16 b);
i32 VNK_MaxI32(i32 a, i32 b);
u32 VNK_MaxU32(u32 a, u32 b);
f32 VNK_MaxF32(f32 a, f32 b);
f64 VNK_MaxF64(f64 a, f64 b);

/**
 * VNK_Abs
 */
i8 VNK_AbsI8(i8 a);
u8 VNK_AbsU8(u8 a);
u16 VNK_AbsU16(u16 a);
i16 VNK_AbsI16(i16 a);
u32 VNK_AbsU32(u32 a);
i32 VNK_AbsI32(i32 a);
f32 VNK_AbsF32(f32 a);
f64 VNK_AbsF64(f64 a);

f32 VNK_CeilF32(f32 a);

f32 VNK_SinF32(f32 a);
f32 VNK_CosF32(f32 a);

#endif