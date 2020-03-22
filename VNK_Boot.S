# BOOTLOADER DATA
# -----------------------------------------------------------------------------
.SECTION .boot_data

MSG_LOADING:
    .ASCIZ "LOADING VNUK..."
MSG_SUCCESS:
    .ASCIZ " OK!"
MSG_FAILURE:
    .ASCIZ " FAILURE.\r\nERROR CODE: 0x"
MSG_ANYKEY:
    .ASCIZ "\r\n\r\nPRESS ANY KEY TO REBOOT..."

GDT_START:

GDT_NULL:                       # NULL DESCRIPTOR
    .WORD 0, 0, 0, 0

GDT_CODE:                       # CODE DESCRIPTOR
    .WORD 0xFFFF                #   limit low
    .WORD 0x0000                #   base low
    .BYTE 0x00                  #   base middle
    .BYTE 0b10011010            #     access
    .BYTE 0b11001111            #     granularity
    .BYTE 0x00                  #   base high

GDT_DATA:                       # DATA DESCRIPTOR
    .WORD 0xFFFF                # same as the code descriptor...
    .WORD 0x0000
    .BYTE 0x00
    .BYTE 0b10010010            # ... except for RW bit
    .BYTE 0b11001111
    .BYTE 0x00

GDT_END:

GDT_DESCRIPTOR:
    .WORD GDT_END - GDT_START - 1
    .LONG GDT_START

.SET CODE_SEG, GDT_CODE - GDT_START
.SET DATA_SEG, GDT_DATA - GDT_START

.GLOBAL VNK_VESA_info
VNK_VESA_info:
.BYTE 0x00

# BOOTLOADER CODE
# -----------------------------------------------------------------------------
.SECTION .boot_text
.CODE16
BOOT:
    # 1. Set video mode
#    MOVW $0x4F02, %AX           # set function (set VBE mode)
#    MOVW $0x4112, %BX           # set video mode (640x480x32)
#    INT  $0x10                  # call BIOS interrupt
#    CMP  $0x004F, %AX           # if %ZF == 1
#    JE   1f                     #   then jump to 1
#
    MOVB $0x00, %AH             # set function (set video mode)
    MOVB $0x02, %AL             # set video mode (80x45 vga-text)
    INT  $0x10                  # call BIOS interrupt
#    JMP  2f
#1:
#    MOVW $0x4F01, %AX
#    MOVW %BX, %CX
#    MOVW $VNK_VESA_info, %DI
#    INT  $0x10                  # call BIOS interrupt
#2:

    LEA  MSG_LOADING, %SI       # display "loading" message
    CALL PRINT

    # 2. Load kernel from disk
    MOVB $0x02, %AH             # set function
   #MOVB $0x80, %AL             # set sectors to read
    MOVB $0x2A, %AL             # set sectors to read
    MOVB $0x00, %CH             # set cylinder
    MOVB $0x02, %CL             # set sector
    MOVB $0x00, %DH             # set head
    MOVW $_VNK_Kernel_Entry, %BX # set kernel offset
    INT  $0x13                  # call BIOS interrupt
    JC   DISK_ERROR

    LEA  MSG_SUCCESS, %SI       # if this code is reached - reading was successfull
    CALL PRINT

    CLI                         # disable interrupts

    # 3. Load the GDT descriptor
    LGDT GDT_DESCRIPTOR

    # 4. Enable protected mode
    MOV  %CR0, %EAX             # set PE (Protection Enabled) bit in %CR0
    OR   $1,   %AL
    MOV  %EAX, %CR0

    # 5. Pass control to the kernel
    LJMP $CODE_SEG, $_VNK_Kernel_Entry

#
# Prints the value of %SI to the screen
#
PRINT:
    MOVB $0x0E, %AH             # set function (teletype output)
    MOVB $0x0F, %BL             # set color
1:
    LODSB                       # load next byte from %SI to %AL
    OR  %AL, %AL                # if %AL == 0
    JZ  2f                      #   then jump to 2
    INT $0x10
    JMP 1b
2:
    RET

#
# Prints disk error message and reboots the machine
#
# Errors:
# 0x00 - Success
# 0x01 - Invalid Command
# 0x02 - Cannot Find Address Mark
# 0x03 - Attempted Write On Write Protected Disk
# 0x04 - Sector Not Found
# 0x05 - Reset Failed
# 0x06 - Disk change line 'active'
# 0x07 - Drive parameter activity failed
# 0x08 - DMA overrun
# 0x09 - Attempt to DMA over 64kb boundary
# 0x0A - Bad sector detected
# 0x0B - Bad cylinder (track) detected
# 0x0C - Media type not found
# 0x0D - Invalid number of sectors
# 0x0E - Control data address mark detected
# 0x0F - DMA out of range
# 0x10 - CRC/ECC data error
# 0x11 - ECC corrected data error
# 0x20 - Controller failure
# 0x40 - Seek failure
# 0x80 - Drive timed out, assumed not ready
# 0xAA - Drive not ready
# 0xBB - Undefined error
# 0xCC - Write fault
# 0xE0 - Status error
# 0xFF - Sense operation failed
DISK_ERROR:
    LEA  MSG_FAILURE, %SI       # display "disk error" message
    CALL PRINT

    MOVB   %AH, %BH             # print %AH (last error) as a hex value
    MOVB $0x0E, %AH             # set function (teletype output)
    MOVW $0x02, %CX             # set loop counter (2 digits)
1:
    MOVB   %BH, %AL             # %AL = %BX
    SHR  $0x04, %AL             # %AL >> 4
    CMP  $0x0A, %AL             # if %AL < 0x0A
    JB   2f                     #   then jump to 2
    ADD  $0x07, %AL             # %AL += 0x07 (ACII chars between numbers and letters)
2:
    ADD  $0x30, %AL             # %AL += 0x07 (Index of the '0' character)
    INT  $0x10                  # call BIOS interrupt
    SHL  $0x04, %BX             # %BX << 4
    LOOP 1b

    LEA  MSG_ANYKEY, %SI        # print "press any key" message
    CALL PRINT

    MOVB $0x00, %AH             # wait until a keypress
    INT  $0x16

    LJMP $0xFFFF, $0            # jump to the end of memory causing reboot

# BOOTLOADER SIGNATURE
# -----------------------------------------------------------------------------
.SECTION .boot_sign
.BYTE 0
.BYTE 0
.BYTE 0b01010101
.BYTE 0b10101010
