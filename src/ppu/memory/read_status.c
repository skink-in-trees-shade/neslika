#include "ppu/ppu.h"
#include "read_status.h"

uint8_t read_status(void *device, uint16_t address) {
	(void)address;

	struct ppu *ppu = device;

	uint8_t value = (ppu->status & 0xE0) | (ppu->last_value & 0x1F);
	ppu->status &= 0x7F;
	ppu->write_toggle = false;
	ppu->last_value = value;

	if (ppu->scanline == 241 && ppu->cycle == 2) {
		value &= 0x7F;
	}

	if (ppu->scanline == 241 && ppu->cycle >= 2 && ppu->cycle <= 4) {
		ppu->nmi_occured = false;
	}

	return value;
}