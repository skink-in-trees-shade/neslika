#ifndef PULSE_H
#define PULSE_H

#include <stdbool.h>
#include "apu/length/length.h"
#include "bus.h"

struct pulse {
	struct bus *bus;
	struct length *length;

	bool enabled;
	uint16_t timer;
	uint16_t reload;
	uint8_t volume;
	uint8_t duty;
	double dutycycle;
};

struct pulse *pulse_new(struct bus *bus, int channel);
void pulse_tick(struct pulse *pulse);
void pulse_half_frame_tick(struct pulse *pulse);
double pulse_sample(struct pulse *pulse, double time);
void pulse_destroy(struct pulse *pulse);

#endif