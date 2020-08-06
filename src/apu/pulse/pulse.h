#ifndef PULSE_H
#define PULSE_H

#include <stdbool.h>
#include "bus.h"

struct pulse {
	struct bus *bus;

	bool enabled;
	uint16_t timer;
	uint16_t reload;
	uint8_t volume;
	uint8_t duty;
};

struct pulse *pulse_new(struct bus *bus, int channel);
void pulse_tick(struct pulse *pulse);
double pulse_sample(struct pulse *pulse);
void pulse_destroy(struct pulse *pulse);

#endif