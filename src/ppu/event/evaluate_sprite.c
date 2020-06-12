#include <string.h>
#include "evaluate_sprite.h"

void evaluate_sprite(struct ppu *ppu) {
	if ((ppu->mask & 0x10) == 0x10) {
		if (ppu->secondary_sprite < 0x08 && ppu->primary_sprite < 0x40) {
			uint8_t *sprite = &ppu->primary_oam[ppu->primary_sprite * 4];
			uint8_t sprite_height = 0x08;
			uint8_t sprite_y = sprite[0];
			if (ppu->scanline >= sprite_y && ppu->scanline < sprite_y + sprite_height) {
				memcpy(&ppu->secondary_oam[ppu->secondary_sprite * 4], sprite, 4);
				ppu->secondary_sprite++;
			}
			ppu->primary_sprite++;
		}
	}
}