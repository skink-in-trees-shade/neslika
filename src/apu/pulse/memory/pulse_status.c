#include "apu/pulse/pulse.h"
#include "pulse_status.h"

static uint8_t duty[0x04] = { 0x01, 0x03, 0x0F, 0xFC };
static double dutycycle[0x04] = { 0.0125, 0.250, 0.500, 0.750 };

void pulse_status(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct pulse *pulse = device;
	pulse->duty = duty[(value & 0xC0) >> 6];
	pulse->dutycycle = dutycycle[(value & 0xC0) >> 6];
	pulse->volume = value & 0x0F;
	pulse->length->enabled = (value & 0x20) == 0x00;
}