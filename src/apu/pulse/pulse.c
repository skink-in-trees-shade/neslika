#include <stdlib.h>
#include "memory/pulse_status.h"
#include "memory/pulse_timer_low.h"
#include "memory/pulse_timer_high.h"
#include "pulse.h"

struct pulse *pulse_new(struct bus *bus, int channel) {
	struct pulse *pulse = calloc(1, sizeof(struct pulse));
	pulse->bus = bus;
	pulse->length = length_new();

	uint8_t offset = (channel - 1) << 2;
	bus_register(pulse->bus, pulse, 0x4000 + offset, 0x4000 + offset, NULL, &pulse_status);
	bus_register(pulse->bus, pulse, 0x4002 + offset, 0x4002 + offset, NULL, &pulse_timer_low);
	bus_register(pulse->bus, pulse, 0x4003 + offset, 0x4003 + offset, NULL, &pulse_timer_high);

	return pulse;
}

void pulse_tick(struct pulse *pulse) {
	if (pulse->enabled) {
		pulse->timer--;
		if (pulse->timer == 0xFFFF) {
			pulse->timer = pulse->reload + 1;
			pulse->duty = ((pulse->duty & 0x01) << 7) | ((pulse->duty & 0xFE) >> 1);
		}
	}
}

void pulse_half_frame_tick(struct pulse *pulse) {
	length_tick(pulse->length);
}

/*static const double harmonics = 3;
static float approxsin(float t) {
	float j = t * 0.15915;
	j = j - (int)j;
	return 20.785 * j * (j - 0.5) * (j - 1.0f);
}*/

double pulse_sample(struct pulse *pulse, double time) {
	if (!pulse->enabled || (pulse->duty & 0x01) == 0x00 || pulse->length->counter == 0x00) {
		return 0.0;
	}

	/*double a = 0;
	double b = 0;
	double p = pulse->dutycycle * 2.0 * 3.14159;
	double amplitude = (pulse->volume - 1.0) / 16.0;
	double frequency = 1789773.0 / (16.0 * (pulse->reload + 1.0));
	for (double n = 1; n < harmonics; n++) {
		double c = n * frequency * 2.0 * 3.14159 * time;
		a += -approxsin(c) / n;
		b += -approxsin(c - p * n) / n;
	}
	return (2.0 * amplitude / 3.14159) * (a - b);*/
	(void)time;
	return 0.125 * pulse->volume;
}

void pulse_destroy(struct pulse *pulse) {
	length_destroy(pulse->length);
	free(pulse);
}