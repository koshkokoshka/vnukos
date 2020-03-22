#include "VNK_Screen.h"

/* Mode 0x02 (vga-text) screen buffer */
VNK_Surface VNK_screen = {
    .data = (void **)0xB8000,       // frame buffer offset
    .step = 80,                     // width
    .size = 80 * 25,
    .bits = 2,                      // 8-bit
    .w = 80,
    .h = 25
};

/* Mode 0x13 (vga-graphics) screen buffer */
//VNK_Surface VNK_screen = {
//    .data = (void **)0xA0000,
//    .step = 320,
//    .size = 320 * 240,
//    .bits = 2,
//    .w = 320,
//    .h = 240
//};
//