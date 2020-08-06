#include <stdlib.h>
#include "memory/pulse_status.h"
#include "memory/pulse_timer_low.h"
#include "memory/pulse_timer_high.h"
#include "pulse.h"

struct pulse *pulse_new(struct bus *bus, int channel) {
	struct pulse *pulse = calloc(1, sizeof(struct pulse));
	pulse->bus = bus;

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

double pulse_sample(struct pulse *pulse) {
	if (!pulse->enabled || (pulse->duty & 0x01) == 0x00) {
		return 0x00;
	}

	return pulse->volume;
}

void pulse_destroy(struct pulse *pulse) {
	free(pulse);
}