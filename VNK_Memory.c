#include "VNK_Memory.h"

typedef struct
{
    void *start;
    void *end;

    void *current;

} VNK_MemoryRegion;

VNK_MemoryRegion VNK_memory[] = {
    // guaranteed free for use memory
    { .current = (void *)0x00000500, .start = (void *)0x00000500, .end = (void *)0x00007BFF }, // 30463 bytes (29.7 KB)
    { .current = (void *)0x00007E00, .start = (void *)0x00007E00, .end = (void *)0x0007FFFF }  // 492031 bytes (480.5 KB)
};

void *VNK_AllocateMemory(reg size)
{
    VNK_MemoryRegion *region = &VNK_memory[0];
    int length = region->end - region->current;
    if (length > size) {
        void *free = region->current;
        region->current += size;
        return free;
    }
    return nil;
}

void  VNK_FreeMemory(void *memory)
{
    /* todo */
}

void *VNK_ReallocateMemory(void *memory, reg size)
{
    void *newMemory = VNK_AllocateMemory(size);
    reg oldMemorySize = size; /* fixme */
    VNK_CopyMemory(newMemory, memory, oldMemorySize);
    return newMemory;
}

void VNK_CopyMemory(void *dst, const void *src, reg size)
{
    asm volatile ("cld; rep movsb" : "+c" (size), "+S" (src), "+D" (dst) :: "memory");
}
