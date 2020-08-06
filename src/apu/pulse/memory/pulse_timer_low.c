#include "apu/pulse/pulse.h"
#include "pulse_timer_low.h"

void pulse_timer_low(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct pulse *pulse = device;
	pulse->reload = (pulse->reload & 0xFF00) | value;
}