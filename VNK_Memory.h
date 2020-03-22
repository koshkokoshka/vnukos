#ifndef __VNK_MEMORY_H
#define __VNK_MEMORY_H

#include "VNK_System.h"

void *VNK_AllocateMemory(reg size);

void VNK_FreeMemory(void *memory);

void *VNK_ReallocateMemory(void *memory, reg size);

void VNK_CopyMemory(void *dst, const void *src, reg size);

#endif
