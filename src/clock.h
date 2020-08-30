#ifndef CLOCK_H
#define CLOCK_H

#include <stdbool.h>
#include "cpu/cpu.h"
#include "ppu/ppu.h"
#include "apu/apu.h"
#include "dma/dma.h"
#include "cartridge/cartridge.h"
#include "controller/controller.h"

struct clock;

struct clock *clock_new(struct cpu *cpu, struct ppu *ppu, struct apu *apu, struct dma *dma, struct cartridge *cartridge, struct controller *controller);
void clock_tick(struct clock *clock);
bool clock_done(struct clock *clock);
void clock_destroy(struct clock *clock);

#endif