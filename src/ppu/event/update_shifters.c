#include "update_shifters.h"

void update_shifters(struct ppu *ppu) {
	if ((ppu->mask & 0x08) == 0x08) {
		ppu->tile_shift_low <<= 1;
		ppu->tile_shift_high <<= 1;

		ppu->palette_shift_low <<= 1;
		ppu->palette_shift_high <<= 1;
	}
}