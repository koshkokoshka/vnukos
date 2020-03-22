#ifndef __VNK_DRAW_H
#define __VNK_DRAW_H

#include "VNK_System.h"
#include "VNK_Surface.h"

void VNK_DrawLine(VNK_Surface *surface, u16 x0, u16 y0, u16 x1, u16 y1, u32 color);

void VNK_DrawChar(VNK_Surface *surface, char ch, int x, int y);

void VNK_DrawString(VNK_Surface *surface, const char *s, int x, int y);

void VNK_Screen_DrawRect(VNK_Surface *surface, int x0, int y0, int x1, int y1);

#endif
