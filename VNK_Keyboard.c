#include "VNK_Keyboard.h"

#include "VNK_Ports.h"

#include "VNK_Screen.h"

void VNK_Keyboard_IRQ()
{
    asm volatile("pusha");
    u16 key = VNK_Port_InU16(0x60);
//    VNK_Screen_PrintChar(&VNK_screen, key);
    asm volatile("popa");
    asm volatile("iret");
}
