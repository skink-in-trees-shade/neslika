#include <stdlib.h>
#include "memory/noise_length.h"
#include "memory/noise_status.h"
#include "memory/noise_timer.h"
#include "noise.h"

struct noise *noise_new(struct bus *bus) {
	struct noise *noise = calloc(1, sizeof(struct noise));
	noise->bus = bus;
	noise->length = length_new();

	bus_register(noise->bus, noise, 0x400C, 0x400C, NULL, &noise_status);
	bus_register(noise->bus, noise, 0x400E, 0x400E, NULL, &noise_timer);
	bus_register(noise->bus, noise, 0x400F, 0x400F, NULL, &noise_length);

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

void noise_half_frame_tick(struct noise *noise) {
	length_tick(noise->length);
}

uint8_t noise_sample(struct noise *noise) {
	if (!noise->enabled || (noise->shift & 0x01) == 0x01 || noise->length->counter == 0x00) {
		return 0x00;
	}

	return noise->volume;
}

void noise_destroy(struct noise *noise) {
	length_destroy(noise->length);
	free(noise);
}