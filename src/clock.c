#include <stdlib.h>
#include "sleep.h"
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

	static int audio_frame_delta = 0;
	if (audio_frame_ready(clock->apu->audio)) {
		audio_frame_delta++;
		audio_frame_commit(clock->apu->audio);
		screen_commit(clock->ppu->screen);
	}

	static int video_frame_delta = 0;
	if (clock->ppu->frame_completed) {
		video_frame_delta++;
		clock->ppu->frame_completed = false;
	}

	if (audio_frame_delta > 0 && video_frame_delta > 0) {
		video_frame_delta--;
		audio_frame_delta--;
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