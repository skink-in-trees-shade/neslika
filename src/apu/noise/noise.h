#ifndef NOISE_H
#define NOISE_H

#include <stdbool.h>
#include "bus.h"

struct noise {
	struct bus *bus;

	bool enabled;
	bool mode;
	uint16_t timer;
	uint16_t reload;
	uint16_t shift;
	uint8_t volume;
};

struct noise *noise_new(struct bus *bus);
void noise_tick(struct noise *noise);
double noise_sample(struct noise *noise);
void noise_destroy(struct noise *noise);

#endif