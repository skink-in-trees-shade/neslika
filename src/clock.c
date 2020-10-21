#include <SDL.h>
#include <stdlib.h>
#include "clock.h"

const uint64_t master_clock_hz = 21477272;
const uint64_t cpu_clock_ns = 1000000000 / (master_clock_hz / 12.0);
const uint64_t ppu_clock_ns = 1000000000 / (master_clock_hz / 4.0);
const uint64_t apu_clock_ns = 1000000000 / (master_clock_hz / 12.0);
const uint64_t seq_clock_ns = 1000000000 / (master_clock_hz / 89490.0);

struct clock {
	struct cpu *cpu;
	struct ppu *ppu;
	struct apu *apu;
	struct dma *dma;
	struct cartridge *cartridge;
	struct controller *controller;

	bool done;
};

static uint32_t _cpu_tick(uint32_t interval, void *param) {
	struct clock *clock = param;

	uint32_t old_cycle = clock->cpu->cycle;

	dma_tick(clock->dma);
	if (!clock->dma->write_toggle) {
		cpu_tick(clock->cpu);
	}

	if (clock->ppu->nmi_occured) {
		clock->ppu->nmi_occured = false;
		cpu_tick(clock->cpu);
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

	uint32_t current_cycle = clock->cpu->cycle;

	return interval * (current_cycle - old_cycle - 1);
}

static uint32_t _ppu_tick(uint32_t interval, void *param) {
	struct clock *clock = param;

	ppu_tick(clock->ppu);

	if (clock->ppu->frame_completed) {
		clock->ppu->frame_completed = false;
		screen_update(clock->ppu->screen);

		clock->done = keyboard_pressed(clock->controller->keyboard, key_escape);
	}

	return interval;
}

static uint32_t _apu_tick(uint32_t interval, void *param) {
	struct clock *clock = param;
	apu_tick(clock->apu);
	return interval;
}

static uint32_t _seq_tick(uint32_t interval, void *param) {
	struct clock *clock = param;
	(void)clock;
	return interval;
}

static uint32_t kek(uint32_t interval, void *param) {
	struct clock *clock = param;

	for (int i = 0; i < 340500; i++) {
		_cpu_tick(interval, clock);
		_ppu_tick(interval, clock);
		_ppu_tick(interval, clock);
		_ppu_tick(interval, clock);
		_apu_tick(interval, clock);
		(void)_seq_tick;
	}

	return interval;
}

struct clock *clock_new(struct cpu *cpu, struct ppu *ppu, struct apu *apu, struct dma *dma, struct cartridge *cartridge, struct controller *controller) {
	struct clock *clock = calloc(1, sizeof(struct clock));
	clock->cpu = cpu;
	clock->ppu = ppu;
	clock->apu = apu;
	clock->dma = dma;
	clock->cartridge = cartridge;
	clock->controller = controller;

	SDL_InitSubSystem(SDL_INIT_TIMER);
	SDL_AddTimer(190, &kek, clock);

	return clock;
}

void clock_tick(struct clock *clock) {
	(void)clock;
	SDL_Delay(1);
}

bool clock_done(struct clock *clock) {
	return clock->done;
}

void clock_destroy(struct clock *clock) {
	SDL_QuitSubSystem(SDL_INIT_TIMER);
	free(clock);
}