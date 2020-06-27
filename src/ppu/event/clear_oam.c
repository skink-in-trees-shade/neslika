#include <string.h>
#include "clear_oam.h"

void clear_oam(struct ppu *ppu) {
	if ((ppu->mask & 0x10) == 0x10 || (ppu->mask & 0x08) == 0x08) {
		memset(ppu->secondary_oam, 0xFF, 0x20);
		ppu->primary_sprite = 0x00;
		ppu->secondary_sprite = 0x00;
		ppu->sprite_zero_evaluated = false;
	}
}