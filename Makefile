#truncate -s 1440KB floppy.img

all:
	gcc -g -O0 -ffreestanding -nostdlib -m32 -Wl,-T,vnukos.ld -o vnukos \
	VNK_Boot.S VNK_System.c VNK_Math.c VNK_Timer.c VNK_Memory.c VNK_String.c VNK_Collection.c VNK_Surface.c \
	VNK_Screen.c VNK_Draw.c UI_Widget.c UI_Menu.c VNK_Ports.c VNK_Keyboard.c VNK_Interrupts.c VNK_Interrupts.S
	objcopy --strip-debug -O binary vnukos.exe vnukos.img
	objcopy --only-keep-debug vnukos.exe vnukos.dbg

run:
	qemu-system-i386 -drive format=raw,file=vnukos.img

debug:
	qemu-system-i386 -drive format=raw,file=vnukos.img -s -S

clean:
	rm vnukos.img vnukos.exe vnukos.dbg
