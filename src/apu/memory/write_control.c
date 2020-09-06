#include "apu/apu.h"
#include "write_control.h"

void write_control(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct apu *apu = device;

	apu->pulse[0]->enabled = (value & 0x01) == 0x01;
	length_toggle(apu->pulse[0]->length, !apu->pulse[0]->enabled);

	apu->pulse[1]->enabled = (value & 0x02) == 0x02;
	length_toggle(apu->pulse[1]->length, !apu->pulse[1]->enabled);

	apu->triangle->enabled = (value & 0x04) == 0x04;
	length_toggle(apu->triangle->length, !apu->triangle->enabled);

	apu->noise->enabled = (value & 0x08) == 0x08;
	length_toggle(apu->noise->length, !apu->noise->enabled);
}