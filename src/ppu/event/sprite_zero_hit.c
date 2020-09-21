#include "sprite_zero_hit.h"

void sprite_zero_hit(struct ppu *ppu) {
	if (!ppu->sprite_zero_hit_occured && ppu->sprite_zero_hit_delay) {
		ppu->sprite_zero_hit_occured = true;
		ppu->sprite_zero_hit_delay = false;
		ppu->status |= 0x40;
	}
}