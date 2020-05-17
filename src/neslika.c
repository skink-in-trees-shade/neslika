#include <stdlib.h>
#include "bus.h"
#include "clock.h"
#include "device.h"
#include "cpu/cpu.h"
#include "ppu/ppu.h"
#include "apu/apu.h"
#include "cartridge/cartridge.h"
#include "neslika.h"

struct neslika {
	struct clock *clock;
	struct bus *bus;
	struct cpu *cpu;
	struct ppu *ppu;
	struct apu *apu;
	struct cartridge *cartridge;
};

static void _neslika_tick(void *system) {
	struct neslika *nes = system;

	cpu_tick(nes->cpu);
	ppu_tick(nes->ppu);
	apu_tick(nes->apu);
	cartridge_tick(nes->cartridge);

	if (!cpu_running(nes->cpu)) {
		clock_stop(nes->clock);
	}
}

struct neslika *neslika_new(void) {
	struct neslika *nes = calloc(1, sizeof(struct neslika));

	nes->clock = clock_new();
	clock_on_tick(nes->clock, &_neslika_tick, nes);

	nes->bus = bus_new();

	nes->cpu = cpu_new();
	nes->cpu->bus = nes->bus;
	bus_attach(nes->bus, &nes->cpu->device);

	nes->ppu = ppu_new();
	bus_attach(nes->bus, &nes->ppu->device);

	nes->apu = apu_new();
	bus_attach(nes->bus, &nes->apu->device);

	nes->cartridge = cartridge_new();
	bus_attach(nes->bus, &nes->cartridge->device);

	return nes;
}

void neslika_load(struct neslika *nes, const char *filename) {
	cartridge_load(nes->cartridge, filename);
}

void neslika_run(struct neslika *nes) {
	cpu_reset(nes->cpu);
	clock_start(nes->clock);
}

void neslika_destroy(struct neslika *nes) {
	cartridge_destroy(nes->cartridge);
	apu_destroy(nes->apu);
	ppu_destroy(nes->ppu);
	cpu_destroy(nes->cpu);
	bus_destroy(nes->bus);
	clock_destroy(nes->clock);
	free(nes);
}