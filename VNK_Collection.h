#ifndef __VNK_COLLECTION_H
#define __VNK_COLLECTION_H

#include "VNK_System.h"

typedef struct
{
    void *data;
    reg elementSize;
    reg capacity;
    reg length;

} VNK_Collection;

VNK_Collection *VNK_CreateCollection(reg initialCapacity, reg elementSize);

void VNK_DestroyCollection(VNK_Collection *collection);

void *VNK_Collection_Push(VNK_Collection *self, void *element);

#endif