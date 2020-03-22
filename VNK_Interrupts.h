//
// Some code taken from Bran's Kernel Development Tutorial by Brandon Friesen (bkerndev.net)
// http://www.osdever.net/bkerndev/Docs/gdt.htm
//
#ifndef __VNK_IRQ_H
#define __VNK_IRQ_H

#include "VNK_System.h"

typedef struct
{
    u16 offsetLow;
    u16 segment;
    struct {
        u8 zero;
        u8 typeAttr;
    } flags;
    u16 offsetHigh;

} __attribute__((packed)) VNK_IDT_Descriptor;

typedef struct
{
    u16 size;
    u32 base;

} __attribute__((packed)) VNK_ITD_Register;

extern VNK_IDT_Descriptor VNK_IDT[0xFF];

extern VNK_ITD_Register VNK_ITD_register;

void VNK_IDT_RegisterHandler(u8 i, u32 handler);

void VNK_IDT_Init();








void gdt_install();
void idt_install();
void isrs_install();
void irq_install();
//void init_video();
void timer_install();
void keyboard_install();


#endif