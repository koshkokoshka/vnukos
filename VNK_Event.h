#ifndef __VNK_EVENT_H
#define __VNK_EVENT_H

#include "VNK_Surface.h"

typedef enum
{
    VNK_EVENT_UNKNOWN,
    VNK_EVENT_INIT,
    VNK_EVENT_TICK,
    VNK_EVENT_DRAW,
    VNK_EVENT_QUIT

} VNK_EventType;

typedef struct
{
    VNK_EventType type;
    union {
        VNK_Surface *surface;
    };

} VNK_Event;

#endif
