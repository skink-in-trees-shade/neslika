#include "apu/apu.h"
#include "read_control.h"

uint8_t read_control(void *device, uint16_t address) {
	(void)address;

	struct apu *apu = device;
	uint8_t status = 0
		| ((apu->pulse[0]->length->counter > 0) << 0)
		| ((apu->pulse[1]->length->counter > 0) << 1)
		| ((apu->triangle->length->counter > 0) << 2)
		| ((apu->noise->length->counter > 0) << 3)
		| (0 << 4)
		| (0 << 5)
		| (apu->irq_occured << 6)
		| (0 << 7);
	apu->irq_occured = false;
	return status;
}