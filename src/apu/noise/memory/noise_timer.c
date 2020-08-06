#include "apu/noise/noise.h"
#include "noise_timer.h"

static uint16_t reload[16] = {
	0x0004, 0x0008, 0x000F, 0x0020, 0x0040, 0x0060, 0x0080, 0x00A0,
	0x00CA, 0x00FE, 0x017C, 0x01FC, 0x02FA, 0x03F8, 0x07F2, 0x0FE4
};

void noise_timer(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct noise *noise = device;
	noise->reload = reload[value & 0x0F];
	noise->mode = (value & 0x80) == 0x80;
}