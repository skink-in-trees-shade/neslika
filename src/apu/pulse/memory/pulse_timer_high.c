#include "apu/pulse/pulse.h"
#include "pulse_timer_high.h"

void pulse_timer_high(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct pulse *pulse = device;
	pulse->reload = ((uint16_t)(value & 0x07) << 8) | (pulse->reload & 0x00FF);
	pulse->timer = pulse->reload;
}