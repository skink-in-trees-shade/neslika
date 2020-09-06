#include "apu/apu.h"
#include "write_frame.h"

void write_frame(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct apu *apu = device;
	apu->extra_frame_step = (value & 0x80) == 0x80;
	if (apu->extra_frame_step) {
		apu->cycle = 18641;
	}
}