#include "load_shifters.h"

void load_shifters(struct ppu *ppu) {
	ppu->tile_shift_low = (ppu->tile_shift_low & 0xFF00) | ppu->tile_low;
	ppu->tile_shift_high = (ppu->tile_shift_high & 0xFF00) | ppu->tile_high;

	ppu->palette_shift_low = (ppu->palette_shift_low & 0xFF00) | ((ppu->palette_id & 0x01) ? 0xFF : 0x00);
	ppu->palette_shift_high = (ppu->palette_shift_high & 0xFF00) | ((ppu->palette_id & 0x02) ? 0xFF : 0x00);
}