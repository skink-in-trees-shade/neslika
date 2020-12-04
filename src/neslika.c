#include <stdlib.h>
#include "clock.h"
#include "bus.h"
#include "platform/screen.h"
#include "platform/audio.h"
#include "platform/keyboard.h"
#include "cpu/cpu.h"
#include "ppu/ppu.h"
#include "apu/apu.h"
#include "dma/dma.h"
#include "cartridge/cartridge.h"
#include "controller/controller.h"
#include "neslika.h"

struct neslika {
	struct clock *clock;
	struct bus *cpu_bus;
	struct bus *ppu_bus;
	struct screen *screen;
	struct audio *audio;
	struct keyboard *keyboard;
	struct cpu *cpu;
	struct ppu *ppu;
	struct apu *apu;
	struct dma *dma;
	struct cartridge *cartridge;
	struct controller *controller;
};

struct neslika *neslika_new(void) {
	struct neslika *nes = calloc(1, sizeof(struct neslika));

	nes->screen = screen_new("Neslika", 256, 240);
	nes->audio = audio_new(1, 48000);
	nes->keyboard = keyboard_new();

	nes->cpu_bus = bus_new(0x10000);
	nes->ppu_bus = bus_new(0x4000);

	nes->cpu = cpu_new(nes->cpu_bus);

	nes->apu = apu_new(nes->cpu_bus, nes->audio);

	nes->cartridge = cartridge_new(nes->cpu_bus, nes->ppu_bus);

	nes->ppu = ppu_new(nes->cpu_bus, nes->ppu_bus, nes->screen);

	nes->dma = dma_new(nes->cpu_bus);
	nes->dma->cpu = nes->cpu;

	nes->controller = controller_new(nes->cpu_bus, nes->keyboard);

	nes->clock = clock_new(nes->cpu, nes->ppu, nes->apu, nes->dma, nes->cartridge, nes->controller);

	return nes;
}

void neslika_load(struct neslika *nes, const char *filename) {
	cartridge_load(nes->cartridge, filename);
}

void neslika_run(struct neslika *nes) {
	cpu_reset(nes->cpu);

	while (!clock_done(nes->clock)) {
		clock_tick(nes->clock);
	}
}

void neslika_destroy(struct neslika *nes) {
	clock_destroy(nes->clock);
	controller_destroy(nes->controller);
	cartridge_destroy(nes->cartridge);
	dma_destroy(nes->dma);
	apu_destroy(nes->apu);
	ppu_destroy(nes->ppu);
	cpu_destroy(nes->cpu);
	keyboard_destroy(nes->keyboard);
	audio_destroy(nes->audio);
	screen_destroy(nes->screen);
	bus_destroy(nes->ppu_bus);
	bus_destroy(nes->cpu_bus);
	free(nes);
}