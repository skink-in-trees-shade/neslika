#include "bus.h"
#include "load_tile_id.h"

void load_tile_id(struct ppu *ppu) {
	uint16_t address = 0x2000 | (ppu->vram_address & 0x0FFF);
	ppu->tile_id = bus_read(ppu->ppu_bus, address);
}