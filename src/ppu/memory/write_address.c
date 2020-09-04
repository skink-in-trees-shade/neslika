#include "ppu/ppu.h"
#include "write_address.h"

void write_address(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct ppu *ppu = device;
	if (!ppu->write_toggle) {
		ppu->temp_vram_address = (ppu->temp_vram_address & 0x00FF) | ((value & 0x3F) << 8);
	} else {
		ppu->temp_vram_address = (ppu->temp_vram_address & 0xFF00) | value;
		ppu->vram_address = ppu->temp_vram_address;
	}
	ppu->write_toggle = !ppu->write_toggle;
	ppu->last_value = value;
}