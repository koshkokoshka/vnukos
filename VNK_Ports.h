#ifndef __VNK_PORTS_H
#define __VNK_PORTS_H

#include "VNK_System.h"

u8 VNK_Port_InU8(u16 port);

void VNK_Port_OutU8(u16 port, u8 data);

u16 VNK_Port_InU16(u16 port);

void VNK_Port_OutU16(u16 port, u16 data);

#endif
