#ifndef EVENT_H
#define EVENT_H

#include "ppu/ppu.h"

extern void (*events[262][342][4])(struct ppu *);

#endif