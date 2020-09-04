#include "ppu/ppu.h"
#include "write_scroll.h"

void write_scroll(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct ppu *ppu = device;
	if (!ppu->write_toggle) {
		ppu->fine_x = value & 0x07;
		ppu->temp_vram_address = (ppu->temp_vram_address & 0x7FE0) | (value >> 3);
	} else {
		ppu->temp_vram_address = (ppu->temp_vram_address & 0x0C1F) | ((value & 0x07) << 12) | ((value >> 3) << 5);
	}
	ppu->write_toggle = !ppu->write_toggle;
	ppu->last_value = value;
}