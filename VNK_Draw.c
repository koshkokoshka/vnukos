#include "VNK_Draw.h"

#include "VNK_Math.h"

void VNK_DrawLine(VNK_Surface *surface, u16 x0, u16 y0, u16 x1, u16 y1, u32 color)
{
    u16 dx = x1 - x0;
    u16 dy = y1 - y0;

    u16 length = VNK_MaxI16(VNK_AbsI16(dx), VNK_AbsI16(dy));
    if (length > 0) {
        f32 sx = (f32)dx / length;
        f32 sy = (f32)dy / length;

        f32 px = (f32)x0;
        f32 py = (f32)y0;

        for (i16 i = 0; i < length; ++i) {
            u8  d = surface->bits;
            u8 *c =  ((u8 *)&color);
            u8 *p = &((u8 *)surface->data)[((u32)px + (u32)py * surface->step) * d];
            for (int j = 0; j < d; ++j) {
                p[j] = c[j];
            }

            px += sx;
            py += sy;
        }
    }
}

void VNK_DrawChar(VNK_Surface *surface, char ch, int x, int y)
{
    ((u8 *)surface->data)[(x + y * surface->step) * 2] = ch;
}

void VNK_DrawString(VNK_Surface *surface, const char *s, int x, int y)
{
    while (*s != '\0') {
        VNK_DrawChar(surface, *s, x, y);
        s++;
        x++;
    }
}

void VNK_Screen_DrawRect(VNK_Surface *surface, int x0, int y0, int x1, int y1)
{
    VNK_DrawChar(surface, 218, x0, y0);
    VNK_DrawChar(surface, 191, x1, y0);
    for (int y = y0 + 1; y < y1; ++y) {
        VNK_DrawChar(surface, 179, x0, y);
        VNK_DrawChar(surface, 179, x1, y);
    }
    VNK_DrawChar(surface, 192, x0, y1);
    for (int x = x0 + 1; x < x1; ++x) {
        VNK_DrawChar(surface, 196, x, y0);
        VNK_DrawChar(surface, 196, x, y1);
    }
    VNK_DrawChar(surface, 217, x1, y1);
}
