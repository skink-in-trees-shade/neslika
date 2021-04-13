#define _POSIX_C_SOURCE 199309L
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
	bool nmi_extra_tick;
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

	if (clock->dma->write_toggle) {
		dma_tick(clock->dma);
		clock->cpu->cycle++;
	} else {
		cpu_tick(clock->cpu);
	}

	if (clock->ppu->nmi_occured) {
		clock->ppu->nmi_occured = false;
		cpu_tick(clock->cpu);
		if (clock->nmi_extra_tick) {
			cpu_tick(clock->cpu);
		}
		cpu_nmi(clock->cpu);
	}

	if (clock->cartridge->irq_occured && !clock->cpu->interrupt_disable) {
		clock->cartridge->irq_occured = false;
		cpu_irq(clock->cpu);
	}

	if (clock->apu->irq_occured && !clock->cpu->interrupt_disable) {
		clock->apu->irq_occured = false;
		cpu_irq(clock->cpu);
	}

	unsigned long current_cycle = clock->cpu->cycle;

	unsigned long nmi_occured_at = 0;
	for (unsigned long i = 0; i < (current_cycle - old_cycle) * 3; i++) {
		ppu_tick(clock->ppu);
		if (clock->ppu->nmi_occured && nmi_occured_at == 0) {
			nmi_occured_at = i;
		}
	}
	clock->nmi_extra_tick = nmi_occured_at / 3 == current_cycle - old_cycle - 1;

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

		struct timespec ts_delta;
		clock_gettime(CLOCK_REALTIME, &ts_delta);
		ts_delta.tv_sec = clock->frame_time.tv_sec - ts_delta.tv_sec;
		ts_delta.tv_nsec = clock->frame_time.tv_nsec - ts_delta.tv_nsec;
		if (ts_delta.tv_nsec < 0) {
			ts_delta.tv_sec = ts_delta.tv_sec - 1;
			ts_delta.tv_nsec = ts_delta.tv_nsec + 1000000000;
		}
		nanosleep(&ts_delta, NULL);

		clock_gettime(CLOCK_REALTIME, &clock->frame_time);
	}
}

bool clock_done(struct clock *clock) {
	return clock->done;
}

void clock_destroy(struct clock *clock) {
	free(clock);
}