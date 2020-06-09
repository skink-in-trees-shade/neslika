#include <stdlib.h>
#include "bus.h"
#include "device.h"
#include "cpu/cpu.h"
#include "ppu/ppu.h"
#include "ppu/screen.h"
#include "apu/apu.h"
#include "cartridge/cartridge.h"
#include "neslika.h"

struct neslika {
	struct bus *cpu_bus;
	struct bus *ppu_bus;
	struct cpu *cpu;
	struct ppu *ppu;
	struct apu *apu;
	struct cartridge *cartridge;
	struct screen *screen;
};

struct neslika *neslika_new(void) {
	struct neslika *nes = calloc(1, sizeof(struct neslika));

	nes->cpu_bus = bus_new();
	nes->ppu_bus = bus_new();

	nes->cpu = cpu_new();
	nes->cpu->bus = nes->cpu_bus;
	bus_attach(nes->cpu_bus, &nes->cpu->device);

	nes->ppu = ppu_new();
	nes->ppu->bus = nes->ppu_bus;
	bus_attach(nes->cpu_bus, &nes->ppu->cpu_device);
	bus_attach(nes->ppu_bus, &nes->ppu->ppu_device);

	nes->apu = apu_new();
	bus_attach(nes->cpu_bus, &nes->apu->device);

	nes->cartridge = cartridge_new();
	bus_attach(nes->cpu_bus, &nes->cartridge->cpu_device);
	bus_attach(nes->ppu_bus, &nes->cartridge->ppu_device);

	nes->screen = screen_new();
	nes->ppu->screen = nes->screen;

	return nes;
}

void neslika_load(struct neslika *nes, const char *filename) {
	cartridge_load(nes->cartridge, filename);
}

void neslika_run(struct neslika *nes) {
	cpu_reset(nes->cpu);
	
	while (!screen_done(nes->screen)) {
		ppu_tick(nes->ppu);
		ppu_tick(nes->ppu);
		ppu_tick(nes->ppu);
		cpu_tick(nes->cpu);
		apu_tick(nes->apu);
		cartridge_tick(nes->cartridge);

		if (nes->ppu->nmi_occured) {
			nes->ppu->nmi_occured = false;
			cpu_nmi(nes->cpu);
		}

		if (nes->ppu->frame_completed) {
			nes->ppu->frame_completed = false;
			screen_update(nes->screen);
		}
	}
}

void neslika_destroy(struct neslika *nes) {
	screen_destroy(nes->screen);
	cartridge_destroy(nes->cartridge);
	apu_destroy(nes->apu);
	ppu_destroy(nes->ppu);
	cpu_destroy(nes->cpu);
	bus_destroy(nes->ppu_bus);
	bus_destroy(nes->cpu_bus);
	free(nes);
}