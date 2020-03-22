//
// Some code taken from Bran's Kernel Development Tutorial by Brandon Friesen (bkerndev.net)
// http://www.osdever.net/bkerndev/Docs/gdt.htm
//
#include "VNK_Interrupts.h"
#include "VNK_Ports.h"
#include "VNK_Draw.h"
#include "VNK_Screen.h"

//VNK_IDT_Descriptor VNK_IDT[0xFF];

//VNK_ITD_Register VNK_ITD_register;

//void VNK_IDT_RegisterHandler(u8 i, u32 handler)
//{
//    VNK_IDT[i].offsetLow = (handler & 0xFFFF);
//    VNK_IDT[i].segment = 0x8;
//    VNK_IDT[i].flags.zero = 0;
//    VNK_IDT[i].flags.typeAttr = 0x8e;
//    VNK_IDT[i].offsetHigh = (handler >> 16) & 0xFFFF;
//
////    *((u16 *)ITD_location + 8 * i + 0) = (u16)((handler & 0x0000FFFF));
////    *((u16 *)ITD_location + 8 * i + 2) = (u16)0x8;
////    *((u8  *)ITD_location + 8 * i + 4) = (u8)0x00;
////    *((u8  *)ITD_location + 8 * i + 5) = (u8)0x8e;
////    *((u16 *)ITD_location + 8 * i + 6) = (u16)((handler & 0xFFFF0000) >> 16);
//}
//
//void VNK_IDT_Init()
//{
//    VNK_ITD_register.size = (sizeof(VNK_IDT_Descriptor) * 0xFF) - 1;
//    VNK_ITD_register.base = (u32)&VNK_IDT;
//
//    asm("lidt %0" :: "m"(VNK_ITD_register)); /* load table */
//
////    irq_install();
//}


unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void *memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};

/* Defines an IDT entry */
struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;

} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;

} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

void idt_load()
{
    idtp.limit = sizeof(struct idt_entry) * 256;
    idtp.base  = (unsigned int) idt;

    asm ( "lidt %0" : : "m"(idtp) );
}

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_install()
{
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = (unsigned int) &idt;
    memset(&idt, 0, sizeof(struct idt_entry) * 256);
    idt_load();
}

extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();

void isrs_install()
{
//    idt_set_gate(0, (unsigned)_isr0, 0x08, 0x8E);
//    idt_set_gate(1, (unsigned)_isr1, 0x08, 0x8E);
//    idt_set_gate(2, (unsigned)_isr2, 0x08, 0x8E);
//    idt_set_gate(3, (unsigned)_isr3, 0x08, 0x8E);
//    idt_set_gate(4, (unsigned)_isr4, 0x08, 0x8E);
//    idt_set_gate(5, (unsigned)_isr5, 0x08, 0x8E);
//    idt_set_gate(6, (unsigned)_isr6, 0x08, 0x8E);
//    idt_set_gate(7, (unsigned)_isr7, 0x08, 0x8E);
//
//    idt_set_gate(8, (unsigned)_isr8, 0x08, 0x8E);
//    idt_set_gate(9, (unsigned)_isr9, 0x08, 0x8E);
//    idt_set_gate(10, (unsigned)_isr10, 0x08, 0x8E);
//    idt_set_gate(11, (unsigned)_isr11, 0x08, 0x8E);
//    idt_set_gate(12, (unsigned)_isr12, 0x08, 0x8E);
//    idt_set_gate(13, (unsigned)_isr13, 0x08, 0x8E);
//    idt_set_gate(14, (unsigned)_isr14, 0x08, 0x8E);
//    idt_set_gate(15, (unsigned)_isr15, 0x08, 0x8E);
//
//    idt_set_gate(16, (unsigned)_isr16, 0x08, 0x8E);
//    idt_set_gate(17, (unsigned)_isr17, 0x08, 0x8E);
//    idt_set_gate(18, (unsigned)_isr18, 0x08, 0x8E);
//    idt_set_gate(19, (unsigned)_isr19, 0x08, 0x8E);
//    idt_set_gate(20, (unsigned)_isr20, 0x08, 0x8E);
//    idt_set_gate(21, (unsigned)_isr21, 0x08, 0x8E);
//    idt_set_gate(22, (unsigned)_isr22, 0x08, 0x8E);
//    idt_set_gate(23, (unsigned)_isr23, 0x08, 0x8E);
//
//    idt_set_gate(24, (unsigned)_isr24, 0x08, 0x8E);
//    idt_set_gate(25, (unsigned)_isr25, 0x08, 0x8E);
//    idt_set_gate(26, (unsigned)_isr26, 0x08, 0x8E);
//    idt_set_gate(27, (unsigned)_isr27, 0x08, 0x8E);
//    idt_set_gate(28, (unsigned)_isr28, 0x08, 0x8E);
//    idt_set_gate(29, (unsigned)_isr29, 0x08, 0x8E);
//    idt_set_gate(30, (unsigned)_isr30, 0x08, 0x8E);
//    idt_set_gate(31, (unsigned)_isr31, 0x08, 0x8E);
}

const char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void fault_handler(struct regs *r)
{
    if (r->int_no < 32)
    {
        VNK_DrawString(&VNK_screen, exception_messages[r->int_no], 0, 4);
        VNK_DrawString(&VNK_screen, "Exception. System Halted!\n", 0, 5);
        for (;;);
    }
}

extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15();

void *irq_routines[16] =
        {
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0
        };

void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}

void irq_remap(void)
{
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

void irq_install()
{
    irq_remap();

//    idt_set_gate(32, (unsigned)_irq0, 0x08, 0x8E);
//    idt_set_gate(33, (unsigned)_irq1, 0x08, 0x8E);
//    idt_set_gate(34, (unsigned)_irq2, 0x08, 0x8E);
//    idt_set_gate(35, (unsigned)_irq3, 0x08, 0x8E);
//    idt_set_gate(36, (unsigned)_irq4, 0x08, 0x8E);
//    idt_set_gate(37, (unsigned)_irq5, 0x08, 0x8E);
//    idt_set_gate(38, (unsigned)_irq6, 0x08, 0x8E);
//    idt_set_gate(39, (unsigned)_irq7, 0x08, 0x8E);
//
//    idt_set_gate(40, (unsigned)_irq8, 0x08, 0x8E);
//    idt_set_gate(41, (unsigned)_irq9, 0x08, 0x8E);
//    idt_set_gate(42, (unsigned)_irq10, 0x08, 0x8E);
//    idt_set_gate(43, (unsigned)_irq11, 0x08, 0x8E);
//    idt_set_gate(44, (unsigned)_irq12, 0x08, 0x8E);
//    idt_set_gate(45, (unsigned)_irq13, 0x08, 0x8E);
//    idt_set_gate(46, (unsigned)_irq14, 0x08, 0x8E);
//    idt_set_gate(47, (unsigned)_irq15, 0x08, 0x8E);
}

void irq_handler(struct regs *r)
{
    void (*handler)(struct regs *r);

    handler = irq_routines[r->int_no - 32];
    if (handler) {
        handler(r);
    }

    if (r->int_no >= 40) {
        outportb(0xA0, 0x20);
    }

    outportb(0x20, 0x20);
}

struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_ptr gp;

extern void gdt_flush();

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void gdt_install()
{
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (unsigned int) &gdt;
    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
//    gdt_flush();
}

int timer_ticks = 0;

void timer_handler(struct regs *r)
{
    timer_ticks++;

    if (timer_ticks % 18 == 0) {
        VNK_DrawString(&VNK_screen, "One second has passed\n", 1, 1);
    }
}

void timer_wait(int ticks)
{
    unsigned long eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}

void timer_install()
{
    irq_install_handler(0, timer_handler);
}

void keyboard_handler(struct regs *r)
{
    VNK_DrawChar(&VNK_screen, inportb(0x60), 2, 2);
}

void keyboard_install()
{
    irq_install_handler(1, keyboard_handler);
}


