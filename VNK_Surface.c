#include "VNK_Surface.h"

#include "VNK_Memory.h"

VNK_Surface* KT_CreateSurface(u16 w, u16 h, u8 d)
{
    VNK_Surface* s = VNK_AllocateMemory(sizeof(VNK_Surface));
    if (s) {
        s->size = (u32)w * (u32)h * (u32)d;
        if ((s->data = VNK_AllocateMemory(s->size))) {
            s->step = w;
            s->bits = d;
            s->w = w;
            s->h = h;
            return s;
        }
        VNK_FreeMemory(s);
    }
    return nil;
}

void KT_DestroySurface(VNK_Surface *s)
{
    if (s) {
        if (s->data) {
            VNK_FreeMemory(s->data);
        }
        VNK_FreeMemory(s);
    }
}
