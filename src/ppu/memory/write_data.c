#include "ppu/ppu.h"
#include "write_data.h"

void write_data(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct ppu *ppu = device;
	bus_write(ppu->ppu_bus, ppu->vram_address, value);
	ppu->vram_address += (ppu->control & 0x04) == 0x04 ? 32 : 1;
	bus_read(ppu->ppu_bus, ppu->vram_address);
	ppu->last_value = value;
}