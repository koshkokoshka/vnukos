#include "VNK_Ports.h"

u8 VNK_Port_InU8(u16 port)
{
    u8 result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void VNK_Port_OutU8(u16 port, u8 data)
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

u16 VNK_Port_InU16(u16 port)
{
    u16 result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void VNK_Port_OutU16(u16 port, u16 data)
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}
