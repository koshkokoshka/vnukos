#ifndef __UI_WIDGET_H
#define __UI_WIDGET_H

#include "VNK_System.h"
#include "VNK_Collection.h"
#include "VNK_Event.h"

typedef struct UI_Widget UI_Widget;

struct UI_Widget
{
    UI_Widget *super;
    int (*HandleEvent)(UI_Widget *self, UI_Widget *super, VNK_Event *event);

    void *data;

    VNK_Collection *childs;
    int x;
    int y;
    int w;
    int h;
};

UI_Widget *UI_CreateWidget(UI_Widget *prototype);

void UI_DestroyWidget(UI_Widget *widget);

extern UI_Widget UI_Widget_Prototype;

#endif