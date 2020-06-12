#include "update_sprite_shifters.h"

void update_sprite_shifters(struct ppu *ppu) {
	if ((ppu->mask & 0x10) == 0x10) {
		for (int i = 0; i < 8; i++) {
			if (ppu->sprite_shift_x[i] > 0) {
				ppu->sprite_shift_x[i]--;
			} else {
				ppu->sprite_shift_low[i] <<= 1;
				ppu->sprite_shift_high[i] <<= 1;
			}
		}
	}
}