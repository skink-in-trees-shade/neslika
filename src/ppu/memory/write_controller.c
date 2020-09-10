#include "ppu/ppu.h"
#include "write_controller.h"

void write_controller(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct ppu *ppu = device;

	if ((ppu->status & 0x80) == 0x80 && (ppu->control & 0x80) == 0x00 && (value & 0x80) == 0x80) {
		ppu->nmi_occured = true;
	}

	ppu->control = value;
	ppu->temp_vram_address = (ppu->temp_vram_address & 0x73FF) | ((value & 0x03) << 10);
	ppu->last_value = value;
}