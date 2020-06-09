#include "bus.h"
#include "load_tile_low.h"

void load_tile_low(struct ppu *ppu) {
	uint16_t address = ((ppu->control & 0x10) << 8) | (ppu->tile_id << 4) | ((ppu->vram_address & 0x7000) >> 12);
	ppu->tile_low = bus_read(ppu->bus, address);
}