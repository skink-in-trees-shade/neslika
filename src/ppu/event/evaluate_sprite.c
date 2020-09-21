#include "evaluate_sprite.h"

void evaluate_sprite(struct ppu *ppu) {
	if ((ppu->mask & 0x10) == 0x10 || (ppu->mask & 0x08) == 0x08) {
		if ((ppu->cycle & 0x01) == 0x01) {
			ppu->oam_data = ppu->primary_oam[ppu->primary_oam_address & 0xFF];
			ppu->primary_oam_address++;

			if (ppu->secondary_oam_address == 0x21) {
				ppu->status |= 0x20;
			}
		} else {
			if (ppu->primary_oam_address < 0x0101) {
				if (ppu->secondary_oam_address < 0x20) {
					ppu->secondary_oam[ppu->secondary_oam_address] = ppu->oam_data;
				}

				if (ppu->oam_counter == 0) {
					uint8_t sprite_height = 0x08 << ((ppu->control & 0x20) >> 5);
					bool in_range = ppu->scanline >= ppu->oam_data && ppu->scanline < ppu->oam_data + sprite_height;
					if (ppu->primary_oam_address == 0x01) {
						ppu->sprite_zero_evaluated = in_range;
					}
					if (in_range) {
						ppu->secondary_oam_address++;
						ppu->oam_counter = 3;
						if (ppu->secondary_oam_address >= 0x20) {
							ppu->primary_oam_address += 3;
						}
					} else {
						if (ppu->secondary_oam_address >= 0x20 && ppu->primary_oam_address >= 0x20) {
							ppu->primary_oam_address--;
							ppu->primary_oam_address = ((ppu->primary_oam_address / 4) + 1) * 4 + (((ppu->primary_oam_address % 4) + 1) % 4);
						} else {
							ppu->primary_oam_address += 3;
						}
					}
				} else {
					ppu->secondary_oam_address++;
					ppu->oam_counter--;
				}
			}
		}
	}
}