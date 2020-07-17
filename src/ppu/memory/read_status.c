#include "ppu/ppu.h"
#include "read_status.h"

uint8_t read_status(void *device, uint16_t address) {
	(void)address;

	struct ppu *ppu = device;
	uint8_t value = (ppu->status & 0xE0) | (ppu->read_buffer & 0x1F);
	ppu->status &= 0x7F;
	ppu->write_toggle = false;
	return value;
}