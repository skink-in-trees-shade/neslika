#ifndef EVENT_H
#define EVENT_H

#include "ppu/ppu.h"

enum { max_events = 6 };

extern void (*events[262][342][max_events])(struct ppu *);

#endif