#include "ppu/ppu.h"
#include "read_data.h"

uint8_t read_data(void *device, uint16_t address) {
	(void)address;

	struct ppu *ppu = device;

	uint8_t value;
	if ((ppu->vram_address & 0x3F00) == 0x3F00) {
		value = (ppu->last_value & 0xC0) | (bus_read(ppu->ppu_bus, ppu->vram_address));
		ppu->read_buffer = bus_read(ppu->ppu_bus, ppu->vram_address & 0x2FFF);
	} else {
		value = ppu->read_buffer;
		ppu->read_buffer = bus_read(ppu->ppu_bus, ppu->vram_address);
	}

	ppu->vram_address = (ppu->vram_address + ((ppu->control & 0x04) == 0x04 ? 32 : 1)) & 0x3FFF;
	bus_read(ppu->ppu_bus, ppu->vram_address);
	ppu->last_value = value;
	return value;
}