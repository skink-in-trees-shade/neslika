#include "apu/noise/noise.h"
#include "noise_status.h"

void noise_status(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct noise *noise = device;
	noise->volume = value & 0x0F;
}