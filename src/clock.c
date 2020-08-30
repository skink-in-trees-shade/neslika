#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <time.h>
#include "clock.h"

const long fps = 60;
const long nsps = 1000000000;

struct clock {
	struct cpu *cpu;
	struct ppu *ppu;
	struct apu *apu;
	struct dma *dma;
	struct cartridge *cartridge;
	struct controller *controller;

	bool done;
	struct timespec frame_time;
};

struct clock *clock_new(struct cpu *cpu, struct ppu *ppu, struct apu *apu, struct dma *dma, struct cartridge *cartridge, struct controller *controller) {
	struct clock *clock = calloc(1, sizeof(struct clock));
	clock->cpu = cpu;
	clock->ppu = ppu;
	clock->apu = apu;
	clock->dma = dma;
	clock->cartridge = cartridge;
	clock->controller = controller;
	return clock;
}

void clock_tick(struct clock *clock) {
	unsigned long old_cycle = clock->cpu->cycle;

	dma_tick(clock->dma);
	if (!clock->dma->write_toggle) {
		cpu_tick(clock->cpu);
	}

	if (clock->ppu->nmi_occured) {
		clock->ppu->nmi_occured = false;
		cpu_nmi(clock->cpu);
	}

	unsigned long current_cycle = clock->cpu->cycle;

	for (unsigned long i = 0; i < (current_cycle - old_cycle) * 3; i++) {
		ppu_tick(clock->ppu);
	}

	for (unsigned long i = 0; i < current_cycle - old_cycle; i++) {
		apu_tick(clock->apu);
	}
	cartridge_tick(clock->cartridge);
	controller_tick(clock->controller);

	if (clock->ppu->frame_completed) {
		clock->ppu->frame_completed = false;
		screen_update(clock->ppu->screen);

		clock->done = keyboard_pressed(clock->controller->keyboard, key_escape);

		clock->frame_time.tv_nsec += nsps / fps;
		if (clock->frame_time.tv_nsec > nsps) {
			clock->frame_time.tv_nsec -= nsps;
			clock->frame_time.tv_sec++;
		}
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &clock->frame_time, NULL);
		clock_gettime(CLOCK_REALTIME, &clock->frame_time);
	}
}

bool clock_done(struct clock *clock) {
	return clock->done;
}

void clock_destroy(struct clock *clock) {
	free(clock);
}