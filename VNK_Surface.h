#ifndef __VNK_SURFACE_H
#define __VNK_SURFACE_H

#include "VNK_System.h"

typedef struct
{
    void **data;
    u32 step;
    u32 size;
    u8  bits;
    u16 w, h;

} VNK_Surface;

void VNK_CreateSurface(u16 w, u16 h, u8 d);

void VNK_DestroySurface(VNK_Surface *s);

#endif