#include "UI_Menu.h"

#include "VNK_Draw.h"
#include "VNK_String.h"

int UI_Menu_HandleEvent(UI_Widget *self, UI_Widget *super, VNK_Event *event)
{
    switch (event->type) {
        case VNK_EVENT_DRAW: {
            for (reg x = 0; x < event->surface->w; ++x) {
                ((u8 *)event->surface->data)[(x * 2) + 1] = 0xFC;
            }
            const char *str = "RAM: 0B/510KB [SYSTEM]";
            VNK_DrawString(event->surface, str, event->surface->w - VNK_StringLength(str), 0);
            super->HandleEvent(self, self->super, event);
            break;
        }
        default:
            return super->HandleEvent(self, self->super, event);
    }
    return 0;
}

UI_Widget UI_Menu_Prototype = {
        0,
        .super = &UI_Widget_Prototype,
        .HandleEvent = UI_Menu_HandleEvent
};
