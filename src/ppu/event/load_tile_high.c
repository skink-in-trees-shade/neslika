#include "bus.h"
#include "load_tile_high.h"

void load_tile_high(struct ppu *ppu) {
	uint16_t address = ((ppu->control & 0x10) << 8) | (ppu->tile_id << 4) | ((ppu->vram_address & 0x7000) >> 12) | 0x0008;
	ppu->tile_high = bus_read(ppu->bus, address);
}