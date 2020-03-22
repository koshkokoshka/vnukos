#include "VNK_System.h"

#include "VNK_String.h"
#include "VNK_Screen.h"
#include "VNK_Timer.h"
#include "VNK_Draw.h"
#include "UI_Widget.h"
#include "UI_Menu.h"
#include "VNK_Math.h"
#include "VNK_Interrupts.h"
#include "VNK_Keyboard.h"

//
// Taken from "VESA Tutorial" by BrightLight
// https://forum.osdev.org/viewtopic.php?f=2&t=30186
//
extern struct vbe_mode_info_structure
{
    u16 attributes;         // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
    u8 window_a;            // deprecated
    u8 window_b;            // deprecated
    u16 granularity;        // deprecated; used while calculating bank numbers
    u16 window_size;
    u16 segment_a;
    u16 segment_b;
    u32 win_func_ptr;       // deprecated; used to switch banks from protected mode without returning to real mode
    u16 step;               // number of bytes per horizontal line
    u16 w;                  // width in pixels
    u16 h;                  // height in pixels
    u8 w_char;              // unused...
    u8 y_char;              // ...
    u8 planes;
    u8 bpp;                 // bits per pixel in this mode
    u8 banks;               // deprecated; total number of banks in this mode
    u8 memory_model;
    u8 bank_size;           // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
    u8 image_pages;
    u8 reserved0;

    u8 red_mask;
    u8 red_position;
    u8 green_mask;
    u8 green_position;
    u8 blue_mask;
    u8 blue_position;
    u8 reserved_mask;
    u8 reserved_position;
    u8 direct_color_attributes;

    u32 framebuffer;        // physical address of the linear frame buffer; write here to draw to the screen
    u32 off_screen_mem_off;
    u16 off_screen_mem_size;    // size of memory in the framebuffer but not being displayed on the screen
    u8 reserved1[206];

} VNK_VESA_info;

UI_Widget UI_LoadingScreen_Prototype;

typedef struct
{
    f32 x, y, z, w;

} VNK_Vector;

typedef struct
{
    f32 x, y, z;

} VNK_MeshVertex;

typedef struct
{
    int v0, v1, v2;

} VNK_MeshFace;

typedef struct
{
    VNK_Collection *vertices;
    VNK_Collection *faces;

} VNK_Mesh;

VNK_Mesh VNK_mesh;

void VNK_Kernel_Entry()
{
//    for (int i = 0; i < 0xFF; ++i) {
//        VNK_IDT[i].offsetLow = 0;
//        VNK_IDT[i].segment = 0;
//        VNK_IDT[i].flags.zero = 0;
//        VNK_IDT[i].flags.typeAttr = 0;
//        VNK_IDT[i].offsetHigh = 0;
//    }
//    VNK_IDT_Init();
//    VNK_IDT_RegisterHandler(33, (u32)VNK_Keyboard_IRQ);

//    gdt_install();
//    VNK_IDT_Init();
/*    idt_install();
    isrs_install();
    irq_install();*/
//    init_video();
/*    timer_install();
    keyboard_install();*/

//    VNK_screen.w = VNK_VESA_info.w;
//    VNK_screen.h = VNK_VESA_info.h;
//    VNK_screen.bits = VNK_VESA_info.bpp / 8;
//    VNK_screen.size = VNK_screen.w * VNK_screen.h * VNK_screen.bits;
//    VNK_screen.step = VNK_VESA_info.step / VNK_screen.bits;
//    VNK_screen.data = (void**)VNK_VESA_info.framebuffer;

    /* Change buffer background/foreground colors */
    for (int i = 0; i < VNK_screen.size; ++i) {
        ((u8 *)VNK_screen.data)[(i * 2) + 1] = 0xCF;
    }
//    for (int i = 0; i < VNK_screen.size; ++i) {
//        ((u8 *)VNK_screen.data)[i] = 0x00;
//    }

//    for (int y = 0; y < VNK_screen.h; ++y) {
//        for (int x = 0; x < VNK_screen.w; ++x) {
//            u8 *p = &((u8 *)VNK_screen.data)[(x + y * VNK_screen.step) * VNK_screen.bits];
//
//            i16 z = VNK_AbsI16(y - (VNK_screen.h / 2));
//            u8  g = (int)((f32)VNK_AbsI16(x - (VNK_screen.w / 2)) / z * 32) % 32
//                                               + (int)(((f32)y / z) * 32) % 32;
//
//            p[0] = g;
//            p[1] = g;
//            p[2] = g;
//        }
//    }

    {
        VNK_mesh.vertices = VNK_CreateCollection(8, sizeof(VNK_MeshVertex));
        VNK_mesh.vertices->length = 8;
        VNK_MeshVertex *v = VNK_mesh.vertices->data;

        v[0].x = 0; v[0].y = 1; v[0].z = 1;
        v[1].x = 0; v[1].y = 0; v[1].z = 1;
        v[2].x = 1; v[2].y = 1; v[2].z = 1;
        v[3].x = 1; v[3].y = 0; v[3].z = 1;
        v[4].x = 1; v[4].y = 1; v[4].z = 0;
        v[5].x = 1; v[5].y = 0; v[5].z = 0;
        v[6].x = 0; v[6].y = 1; v[6].z = 0;
        v[7].x = 0; v[7].y = 0; v[7].z = 0;

        VNK_mesh.faces = VNK_CreateCollection(12, sizeof(VNK_MeshFace));
        VNK_mesh.faces->length = 12;
        VNK_MeshFace *f = VNK_mesh.faces->data;

        f[ 0].v0 = 0; f[ 0].v1 = 1; f[ 0].v2 = 2;
        f[ 1].v0 = 1; f[ 1].v1 = 3; f[ 1].v2 = 2;
        f[ 2].v0 = 2; f[ 2].v1 = 3; f[ 2].v2 = 4;
        f[ 3].v0 = 3; f[ 3].v1 = 5; f[ 3].v2 = 4;
        f[ 4].v0 = 4; f[ 4].v1 = 5; f[ 4].v2 = 6;
        f[ 5].v0 = 5; f[ 5].v1 = 7; f[ 5].v2 = 6;
        f[ 6].v0 = 6; f[ 6].v1 = 7; f[ 6].v2 = 0;
        f[ 7].v0 = 7; f[ 7].v1 = 1; f[ 7].v2 = 0;
        f[ 8].v0 = 6; f[ 8].v1 = 0; f[ 8].v2 = 4;
        f[ 9].v0 = 0; f[ 9].v1 = 2; f[ 9].v2 = 4;
        f[10].v0 = 1; f[10].v1 = 7; f[10].v2 = 3;
        f[11].v0 = 7; f[11].v1 = 5; f[11].v2 = 3;
    }

    /* Build TUI interface */
    UI_Widget *root = UI_CreateWidget(&UI_Widget_Prototype);
    root->w = VNK_screen.w;
    root->h = VNK_screen.h;
    UI_Widget *menu = UI_CreateWidget(&UI_Menu_Prototype);
    menu->w = root->w;
    menu->h = 1;
    UI_Widget *loadingScreen = UI_CreateWidget(&UI_LoadingScreen_Prototype);
    loadingScreen->w = root->w;
    loadingScreen->h = root->h - menu->h;
    loadingScreen->y = menu->y + menu->h;

    VNK_Collection_Push(root->childs, &menu);
    VNK_Collection_Push(root->childs, &loadingScreen);

    VNK_Event event = { .type = VNK_EVENT_DRAW, .surface = &VNK_screen };
    root->HandleEvent(root, root->super, &event);

//    VNK_DrawLine(&VNK_screen, 0, 0, VNK_screen.w, VNK_screen.h, 0);

//    asm("sti");

    while (1) {
        asm("hlt");
    }
}

typedef struct { VNK_Vector p, r; } VNK_Camera;

void VNK_RotateX(VNK_Vector *p, f32 r)
{
    f32 s = VNK_SinF32(r);
    f32 c = VNK_CosF32(r);

    f32 a = (p->y * c) - (p->z * s);
    f32 b = (p->y * s) + (p->z * c);

    p->y = a;
    p->z = b;
}

void VNK_RotateY(VNK_Vector *p, f32 r)
{
    f32 s = VNK_SinF32(r);
    f32 c = VNK_CosF32(r);

    f32 a = (p->z * s) + (p->x * c);
    f32 b = (p->z * c) - (p->x * s);

    p->x = a;
    p->z = b;
}

void VNK_RotateZ(VNK_Vector *p, f32 r)
{

    f32 s = VNK_SinF32(r);
    f32 c = VNK_CosF32(r);

    f32 a = (p->x * c) - (p->y * s);
    f32 b = (p->x * s) + (p->y * c);

    p->x = a;
    p->y = b;
}

void VNK_CameraTransform(VNK_Vector *p, VNK_Camera *camera)
{
    p->x += camera->p.x;
    p->y += camera->p.y;
    p->z += camera->p.z;

    VNK_RotateX(p, camera->r.x);
    VNK_RotateY(p, camera->r.y);
    VNK_RotateZ(p, camera->r.z);
}

void VNK_PerspectiveDivide(VNK_Vector *p)
{
    p->x /= p->z;
    p->y /= p->z;
}

void VNK_ScreenSpaceTransform(VNK_Vector *p, f32 w, f32 h)
{
    p->x = (p->x + 0.5f) * w;
    p->y = (p->y + 0.5f) * h;
}

void VNK_TransformPoint(VNK_Vector *p, VNK_Camera *camera, f32 w, f32 h)
{
    VNK_CameraTransform(p, camera);
    VNK_PerspectiveDivide(p);
    VNK_ScreenSpaceTransform(p, w, h);
}

const char VNK_avatar[] = {
        15,7,0xB1,'\n',
        10,5,0xB1,1,0xB0,3,0xB1,1,0xB0,2,0xB1,1,0xB0,3,0xB1,1,0xB0,'\n',
        7,4,0xB1,2,0xB0,1,0xB1,2,0xB0,3,0xB1,4,0xB0,1,0xB1,1,0xB0,4,0xB1,1,0xB0,1,0xDC,'\n',
        6,1,0xDE,1,0xB0,1,0xB1,5,0xB0,1,0xDD,3,0xB1,1,0xB0,4,0xB1,8,0xB0,'\n',
        5,1,0xB0,1,0xFF,1,0xDD,1,0xB0,4,0xFF,5,0xB0,1,0xFF,4,0xB0,3,0xDF,2,0xFF,3,0xB0,'\n',
        4,1,0xDE,2,0xFF,3,0xB0,1,0xFF,1,0xDF,1,0xB1,2,0xDF,1,0xB1,2,0xB0,2,0xFF,2,0xB0,1,0xDB,1,0xB1,1,0xDB,1,0xB1,1,0xB0,1,0xDC,4,0xB0,'\n',
        7,4,0xB0,1,0xB1,2,0xDB,1,0xB2,2,0xB1,2,0xFF,1,0xB0,1,0xFF,1,0xB0,1,0xB1,2,0xDB,1,0xB2,6,0xB0,2,0xDB,1,0xB1,'\n',
        1,1,0xDC,2,0xDB,1,0xDE,4,0xB0,1,0xFF,6,0xB0,3,0xFF,4,0xB0,3,0xB1,3,0xB0,1,0xFF,3,0xB0,1,0xB1,1,0xDC,1,0xB1,'\n',
        0,1,0xDE,5,0xFF,1,0xB0,4,0xFF,1,0xB0,8,0xFF,1,0xB0,3,0xFF,5,0xB0,1,0xFF,3,0xB0,1,0xFF,1,0xDD,'\n',
        1,1,0xDF,4,0xFF,2,0xB0,2,0xFF,1,0xB0,2,0xFF,1,0xB0,3,0xDF,8,0xB0,1,0xFF,2,0xB0,3,0xFF,1,0xB1,1,0xDF,1,0xB0,1,0xB1,'\n',
        2,1,0xDE,4,0xFF,3,0xB0,4,0xB1,3,0xB2,1,0xB1,1,0xB0,1,0xDD,2,0xB1,3,0xB1,1,0xDC,2,0xB1,1,0xB0,1,0xFF,1,0xDD,1,0xB1,1,0xDB,1,0xB0,'\n',
        3,1,0xDE,2,0xB1,1,0xDF,3,0xB0,1,0xFF,1,0xB1,1,0xB2,1,0xB1,1,0xDC,2,0xDB,5,0xFF,1,0xDB,1,0xFF,6,0xB0,1,0xFF,1,0xB1,'\n',
        8,1,0xB0,2,0xFF,1,0xDC,1,0xB0,2,0xFF,1,0xFF,1,0xDB,5,0xFF,1,0xDB,2,0xFF,4,0xB0,1,0xFF,1,0xDF,'\n',
        9,1,0xB0,1,0xFF,2,0xB0,2,0xFF,7,0xB0,6,0xFF,1,0xB0,'\n',
        10,1,0xDF,5,0xB0,1,0xB1,4,0xDB,1,0xDE,4,0xDF,'\n',
        9,1,0xDC,2,0xB2,1,0xDB,1,0xB1,4,0xDB,2,0xB2,5,0xDB,2,0xDC,1,0xB1,'\n',
        9,1,0xB1,2,0xDB,5,0xB1,1,0xDB,3,0xDC,3,0xB0,1,0xB1,3,0xB0,'\n',
        13,8,0xB1,2,0xB0,2,0xB1,'\0'
};

void VNK_DrawASCII(VNK_Surface *surface, const char *s, int x, int y)
{
    int xx = x + *s;
    s++;
    while (*s != '\0') {
        u8 i = *s;
        s++;
        while (i--) {
            VNK_DrawChar(surface, *s, xx++, y);
//            VNK_Sleep(1.0);
        }
        s++;
        if (*s == '\n') {
            xx = x + *++s;
            s++;
            y++;
        }
    }
}

void VNK_DrawMesh(VNK_Surface *surface, VNK_Mesh *mesh, VNK_Camera *camera)
{
    for (reg i = 0; i < mesh->faces->length; ++i) {
        VNK_MeshFace *f = &((VNK_MeshFace *)mesh->faces->data)[i];
        VNK_MeshVertex *vx0 = &((VNK_MeshVertex *)mesh->vertices->data)[f->v0];
        VNK_MeshVertex *vx1 = &((VNK_MeshVertex *)mesh->vertices->data)[f->v1];
        VNK_MeshVertex *vx2 = &((VNK_MeshVertex *)mesh->vertices->data)[f->v2];

        VNK_Vector v0 = { vx0->x, vx0->y, vx0->z, 1 };
        VNK_Vector v1 = { vx1->x, vx1->y, vx1->z, 1 };
        VNK_Vector v2 = { vx2->x, vx2->y, vx2->z, 1 };

        VNK_TransformPoint(&v0, camera, surface->w, surface->h);
        VNK_TransformPoint(&v1, camera, surface->w, surface->h);
        VNK_TransformPoint(&v2, camera, surface->w, surface->h);

        VNK_DrawLine(surface, VNK_CeilF32(v0.x), VNK_CeilF32(v0.y), VNK_CeilF32(v1.x), VNK_CeilF32(v1.y), 0);
        VNK_DrawLine(surface, VNK_CeilF32(v1.x), VNK_CeilF32(v1.y), VNK_CeilF32(v2.x), VNK_CeilF32(v2.y), 0);
        VNK_DrawLine(surface, VNK_CeilF32(v2.x), VNK_CeilF32(v2.y), VNK_CeilF32(v0.x), VNK_CeilF32(v0.y), 0);
    }
}

int UI_LoadingScreen_HandleEvent(UI_Widget *self, UI_Widget *super, VNK_Event *event)
{
    switch (event->type) {
        case VNK_EVENT_DRAW: {
            VNK_Surface *surface = event->surface;

            int w2 = surface->w / 2;
            int x, y, l;

            /* draw subtitle */
            const char *subtitle = "W E L C O M E   T O   T H E   D I G I T A L   H E L L";
            l = VNK_StringLength(subtitle);
            x = w2 - (l / 2);
            y = 20;
            VNK_Screen_DrawRect(event->surface, x - 4, y - 1, x + l + 4, y + 1);
            VNK_DrawString(event->surface, subtitle, x, y);

            /* draw "Now Loading" label */
            const char *message = " NOW LOADING... ";
            l = VNK_StringLength(message);
            x = w2 - (l / 2);
            y = 22;
            for (int i = -1; i < l + 1; ++i) {
                ((u8 *)event->surface->data)[((x + i) + y * event->surface->step) * 2 + 1] = 0xFC;
            }
            VNK_DrawString(event->surface, message, x, y);

            /* draw avatar */
            VNK_DrawASCII(event->surface, VNK_avatar, w2 - (38 / 2), 1);

//            static VNK_Camera VNK_camera = {
//                .p = { -0.5f, -0.5f, -3.0f, 1 },
//                .r = { 0, 0, 0, 1 }
//            };
//            VNK_DrawMesh(surface, &VNK_mesh, &VNK_camera);
//
//            super->HandleEvent(self, self->super, event);
            break;
        }
        default:
            return super->HandleEvent(self, self->super, event);
    }
    return 0;
}

UI_Widget UI_LoadingScreen_Prototype = {
    0,
    .super = &UI_Widget_Prototype,
    .HandleEvent = UI_LoadingScreen_HandleEvent
};
