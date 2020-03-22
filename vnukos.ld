OUTPUT_ARCH(i386)
ENTRY(_VNK_Kernel_Entry)

SECTIONS
{
    . = 0x7C00; /* bootloader address in RAM */

    bootloader : {
        .begin = .;
        *(.boot_text);
        *(.boot_data);
        . = 508;
        *(.boot_sign);
    }

    .text : {
        *(.text);
    }
    .data : {
        *(.data);
    }
}
