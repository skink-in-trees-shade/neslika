#include "apu/noise/noise.h"
#include "noise_length.h"

void noise_length(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct noise *noise = device;
	length_reload(noise->length, (value & 0xF8) >> 3);
}