#include "VNK_Timer.h"

void VNK_Sleep(f64 time)
{
    /* fixme: high CPU load - should be implemented using interrupts */
    u64 ticks = (u64)(time * 1000000);
    while (--ticks) {
        asm volatile ("NOP");
        asm volatile ("NOP");
        asm volatile ("NOP");
        asm volatile ("NOP");
        asm volatile ("NOP");
        asm volatile ("NOP");
        asm volatile ("NOP");
        asm volatile ("NOP");
    }
}
