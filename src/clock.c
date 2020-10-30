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

static const double time_per_system_sample = 1.0 / 48000.0;
static const double time_per_nes_clock = 1.0 / 1789773.0;
#define SAMPLES 4096
static double audio_sync_time;
static double audio_nes_time;
static size_t sound_buffer_pos;
static double sound_buffer[SAMPLES];

void clock_tick(struct clock *clock) {
	unsigned long old_cycle = clock->cpu->cycle;

	dma_tick(clock->dma);
	if (!clock->dma->write_toggle) {
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

		audio_sync_time += time_per_nes_clock;
		audio_nes_time += time_per_nes_clock;
		if (audio_sync_time >= time_per_system_sample) {
			audio_sync_time -= time_per_system_sample;
			sound_buffer[sound_buffer_pos++] = apu_sample(clock->apu, audio_nes_time);
			if (sound_buffer_pos == SAMPLES) {
				sound_buffer_pos = 0;
				audio_samples(clock->apu->audio, sound_buffer, SAMPLES);
			}
		}
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