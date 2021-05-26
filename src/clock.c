#include <stdlib.h>
#include "clock.h"

struct clock {
	struct thread *thread;
	struct cpu *cpu;
	struct ppu *ppu;
	struct apu *apu;
	struct dma *dma;
	struct cartridge *cartridge;
	struct controller *controller;

	bool done;
	bool nmi_extra_tick;
};

struct clock *clock_new(struct thread *thread, struct cpu *cpu, struct ppu *ppu, struct apu *apu, struct dma *dma, struct cartridge *cartridge, struct controller *controller) {
	struct clock *clock = calloc(1, sizeof(struct clock));
	clock->thread = thread;
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

	if (clock->cartridge->irq_occured || clock->apu->irq_occured) {
		clock->cpu->irq_occured = true;
	}

	if (clock->ppu->frame_completed) {
		clock->ppu->frame_completed = false;
		screen_update(clock->ppu->screen);
		audio_update(clock->apu->audio);

		clock->done = keyboard_pressed(clock->controller->keyboard, key_escape);

		thread_sleep(clock->thread);
	}
}

bool clock_done(struct clock *clock) {
	return clock->done;
}

void clock_destroy(struct clock *clock) {
	free(clock);
}