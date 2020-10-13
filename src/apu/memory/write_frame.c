#include "apu/apu.h"
#include "write_frame.h"

void write_frame(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct apu *apu = device;
	apu->irq_inhibit = (value & 0x40) == 0x40;
	if (apu->irq_inhibit) {
		apu->irq_occured = false;
	}
	apu->extra_frame_step = (value & 0x80) == 0x80;
	if (apu->extra_frame_step) {
		apu->cycle = 37282;
	}
	apu->reset_cycle = 3;
}