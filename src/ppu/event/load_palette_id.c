#include "bus.h"
#include "load_palette_id.h"

void load_palette_id(struct ppu *ppu) {
	uint16_t address = 0x23C0 | (ppu->vram_address & 0x0C00) | ((ppu->vram_address & 0x0380) >> 4) | ((ppu->vram_address & 0x001C) >> 2);
	uint8_t attribute = bus_read(ppu->bus, address);
	uint8_t shift = (((ppu->vram_address >> 5) & 0x02) << 1) | (ppu->vram_address & 0x02);
	ppu->palette_id = (attribute >> shift) & 0x03;
}