#include "VNK_Collection.h"

#include "VNK_Memory.h"

VNK_Collection *VNK_CreateCollection(reg initialCapacity, reg elementSize)
{
    VNK_Collection *collection = VNK_AllocateMemory(sizeof(VNK_Collection));
    if (collection) {
        collection->data = VNK_AllocateMemory(initialCapacity * elementSize);
        if (collection->data) {
            collection->elementSize = elementSize;
            collection->capacity = initialCapacity;
            collection->length = 0;
            return collection;
        }
        VNK_FreeMemory(collection);
    }
    return nil;
}

void VNK_DestroyCollection(VNK_Collection *collection)
{
    if (collection) {
        if (collection->data) {
            VNK_FreeMemory(collection->data);
        }
        VNK_FreeMemory(collection);
    }
}

void *VNK_Collection_Push(VNK_Collection *self, void *element)
{
    if (self->capacity <= self->length) { /* if collection is overflowed */
        if (self->capacity <= 0) {
            self->capacity  = 1;
        } else {
            self->capacity *= 2;
        }

        if (!(self->data = VNK_ReallocateMemory(self->data, self->elementSize * self->capacity))) {
            return nil;
        }
    }
	void *newElement = &((u8*)self->data)[self->elementSize * self->length];
    VNK_CopyMemory(newElement, element, self->elementSize);
    self->length++;
    return newElement;
}
