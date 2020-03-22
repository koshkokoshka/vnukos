#include "UI_Widget.h"

#include "VNK_Memory.h"
#include "VNK_Math.h"

UI_Widget *UI_CreateWidget(UI_Widget *prototype)
{
    UI_Widget *widget = VNK_AllocateMemory(sizeof(UI_Widget));
    if (widget) {
        *widget = *prototype;
        if (widget->HandleEvent) {
            VNK_Event event;
            event.type = VNK_EVENT_INIT;
            if (widget->HandleEvent(widget, widget->super, &event) != 0) {
                VNK_FreeMemory(widget);
                widget = nil;
            }
        }
        return widget;
    }
    return nil;
}

void UI_DestroyWidget(UI_Widget *widget)
{
    if (widget) {
        if (widget->HandleEvent) {
            VNK_Event event;
            event.type = VNK_EVENT_QUIT;
            widget->HandleEvent(widget, widget->super, &event);
        }
        VNK_FreeMemory(widget);
    }
}

int UI_Widget_HandleEvent(UI_Widget *self, UI_Widget *super, VNK_Event *event)
{
    switch (event->type) {
        case VNK_EVENT_INIT:
            self->childs = VNK_CreateCollection(0, sizeof(UI_Widget*));
            if (!self->childs) {
                return 1;
            }
            break;
        case VNK_EVENT_QUIT:
            if (self->childs) {
                VNK_DestroyCollection(self->childs);
            }
            break;
        case VNK_EVENT_DRAW: {
            VNK_Surface *surface = event->surface;
            for (reg i = 0; i < self->childs->length; ++i) {
                UI_Widget *child = ((UI_Widget **)self->childs->data)[i];
                if (child && child->HandleEvent) {
                    VNK_Surface chunk;
                    chunk = *surface;
                    chunk.w = VNK_MinI32(child->w, surface->w - child->x);
                    chunk.h = VNK_MinI32(child->h, surface->h - child->y);
                    chunk.data = (void **)(((u8 *)chunk.data) + (child->x + child->y * chunk.step) * chunk.bits);
//                    chunk.data += child->x + child->y * chunk.w;
                    event->surface = &chunk;
                    child->HandleEvent(child, child->super, event);
                }
            }
            event->surface = surface;
            break;
        }
//        case VNK_EVENT_MOUSE_BUTTON_UP:
//        case VNK_EVENT_MOUSE_BUTTON_DOWN:
//        case VNK_EVENT_MOUSE_MOVE:
//            for (reg i = 0; i < self->childs->length; ++i) {
//                VNK_Widget *child = ((VNK_Widget **)self->childs->data)[i];
//                if (child && child->HandleEvent) {
//                    int x = event->mouse->x;
//                    int y = event->mouse->y;
//                    int x0 = child->x;
//                    int y0 = child->y;
//                    int x1 = x0 + child->w;
//                    int y1 = y0 + child->h;
//                    if (x >= x0 && x < x1 && y >= y0 && y < y1) {
//                        VNK_Mouse* mouse = event->mouse;
//                        VNK_Mouse mouse2 = *mouse;
//                        mouse2.x -= child->x;
//                        mouse2.y -= child->y;
//                        event->mouse = &mouse2;
//                        child->HandleEvent(child, child->super, event);
//                        event->mouse = mouse;
//                    }
//                }
//            }
//            break;
        default:
            for (reg i = 0; i < self->childs->length; ++i) {
                UI_Widget *child = ((UI_Widget **)self->childs->data)[i];
                if (child && child->HandleEvent) {
                    child->HandleEvent(child, child->super, event);
                }
            }
            break;
    }
    return 0;
}

UI_Widget UI_Widget_Prototype = {
        0,
        .HandleEvent = UI_Widget_HandleEvent
};
