#include <stdlib.h>
#include "memory/noise_status.h"
#include "memory/noise_timer.h"
#include "noise.h"

struct noise *noise_new(struct bus *bus) {
	struct noise *noise = calloc(1, sizeof(struct noise));
	noise->bus = bus;

	bus_register(noise->bus, noise, 0x400C, 0x400C, NULL, &noise_status);
	bus_register(noise->bus, noise, 0x400E, 0x400E, NULL, &noise_timer);

	return noise;
}

void noise_tick(struct noise *noise) {
	if (noise->enabled) {
		noise->timer--;
		if (noise->timer == 0xFFFF) {
			noise->timer = noise->reload;

			uint8_t feedback = (noise->shift & 0x01) ^ (noise->shift >> (noise->mode ? 6 : 1) & 0x01);
			noise->shift = (feedback << 14) | (noise->shift >> 1);
		}
	}
}

double noise_sample(struct noise *noise) {
	if (!noise->enabled || (noise->shift & 0x01) == 0x01) {
		return 0x00;
	}

	return noise->volume;
}

void noise_destroy(struct noise *noise) {
	free(noise);
}