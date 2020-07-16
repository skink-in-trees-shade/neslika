#ifndef APU_H
#define APU_H

#include "bus.h"

struct apu;

struct apu *apu_new(struct bus *bus);
void apu_tick(struct apu *apu);
void apu_destroy(struct apu *apu);

#endif