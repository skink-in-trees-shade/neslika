#include <stdlib.h>
#include "bus.h"
#include "cpu/cpu.h"
#include "ppu/ppu.h"
#include "ppu/screen.h"
#include "apu/apu.h"
#include "dma/dma.h"
#include "cartridge/cartridge.h"
#include "controller/controller.h"
#include "neslika.h"

struct neslika {
	struct bus *cpu_bus;
	struct bus *ppu_bus;
	struct screen *screen;
	struct cpu *cpu;
	struct ppu *ppu;
	struct apu *apu;
	struct dma *dma;
	struct cartridge *cartridge;
	struct controller *controller;
};

struct neslika *neslika_new(void) {
	struct neslika *nes = calloc(1, sizeof(struct neslika));

	nes->screen = screen_new();

	nes->cpu_bus = bus_new();
	nes->ppu_bus = bus_new();

	nes->cpu = cpu_new(nes->cpu_bus);

	nes->apu = apu_new(nes->cpu_bus);

	nes->cartridge = cartridge_new(nes->cpu_bus, nes->ppu_bus);

	nes->ppu = ppu_new(nes->cpu_bus, nes->ppu_bus);
	nes->ppu->screen = nes->screen;
	nes->ppu->cartridge = nes->cartridge;

	nes->dma = dma_new(nes->cpu_bus);
	nes->dma->cpu = nes->cpu;

	nes->controller = controller_new(nes->cpu_bus);
	nes->controller->screen = nes->screen;

	return nes;
}

void neslika_load(struct neslika *nes, const char *filename) {
	cartridge_load(nes->cartridge, filename);
}

void neslika_run(struct neslika *nes) {
	cpu_reset(nes->cpu);
	
	while (!screen_done(nes->screen)) {
		unsigned long old_cycle = nes->cpu->cycle;

		dma_tick(nes->dma);
		if (!nes->dma->write_toggle) {
			cpu_tick(nes->cpu);
		}

		if (nes->ppu->nmi_occured) {
			nes->ppu->nmi_occured = false;
			cpu_nmi(nes->cpu);
		}

		unsigned long current_cycle = nes->cpu->cycle;

		for (unsigned long i = 0; i < (current_cycle - old_cycle) * 3; i++) {
			ppu_tick(nes->ppu);
		}

		apu_tick(nes->apu);
		cartridge_tick(nes->cartridge);
		controller_tick(nes->controller);

		if (nes->ppu->frame_completed) {
			nes->ppu->frame_completed = false;
			screen_update(nes->screen);
		}
	}
}

void neslika_destroy(struct neslika *nes) {
	controller_destroy(nes->controller);
	cartridge_destroy(nes->cartridge);
	dma_destroy(nes->dma);
	apu_destroy(nes->apu);
	ppu_destroy(nes->ppu);
	cpu_destroy(nes->cpu);
	screen_destroy(nes->screen);
	bus_destroy(nes->ppu_bus);
	bus_destroy(nes->cpu_bus);
	free(nes);
}