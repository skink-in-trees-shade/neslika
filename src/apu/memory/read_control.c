#include "apu/apu.h"
#include "read_control.h"

uint8_t read_control(void *device, uint16_t address) {
	(void)address;

	struct apu *apu = device;
	uint8_t status = 0
		| (apu->pulse[0]->enabled << 0)
		| (apu->pulse[1]->enabled << 1)
		| (apu->triangle->enabled << 2)
		| (apu->noise->enabled << 3);
	return status;
}