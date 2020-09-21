#include "bus.h"
#include "load_sprite.h"

static uint8_t invert(uint8_t byte) {
	uint8_t result = 0x00;
	for (int i = 7; i >= 0; i--) {
		result |= (byte & 0x01) << i;
		byte >>= 1;
	}
	return result;
}

void load_sprite(struct ppu *ppu) {
	if ((ppu->mask & 0x10) == 0x10) {
		uint8_t sprite_index = (ppu->cycle - 257) / 8;
		if (sprite_index < ppu->secondary_oam_address / 4) {
			uint8_t *sprite = &ppu->secondary_oam[sprite_index * 4];
			uint8_t sprite_x = sprite[3];
			uint8_t sprite_y = sprite[0];
			uint8_t sprite_tile_id = sprite[1];
			uint8_t sprite_attribute = sprite[2];

			uint8_t page;
			uint8_t tile;
			if ((ppu->control & 0x20) == 0x00) {
				page = (ppu->control & 0x08) >> 3;
				tile = sprite_tile_id;
			} else {
				page = sprite_tile_id & 0x01;
				tile = (sprite_tile_id & 0xFE) + (((ppu->scanline - sprite_y) / 8) ^ ((sprite_attribute & 0x80) == 0x80));
			}

			uint8_t row = ppu->scanline - sprite_y;
			if ((sprite_attribute & 0x80) == 0x80) {
				row = 7 - row;
			}

			uint16_t address = (page << 12) | (tile << 4) | (row & 0x07);
			uint8_t sprite_low = bus_read(ppu->ppu_bus, address);
			uint8_t sprite_high = bus_read(ppu->ppu_bus, address + 0x08);

			if ((sprite_attribute & 0x40) == 0x40) {
				sprite_low = invert(sprite_low);
				sprite_high = invert(sprite_high);
			}

			ppu->sprite_shift_low[sprite_index] = sprite_low;
			ppu->sprite_shift_high[sprite_index] = sprite_high;
			ppu->sprite_shift_x[sprite_index] = sprite_x;
			ppu->sprite_shift_attribute[sprite_index] = sprite_attribute;
			ppu->sprite_zero_hit_possible = ppu->sprite_zero_evaluated;
		} else {
			bus_read(ppu->ppu_bus, 0x1FFF);
			bus_read(ppu->ppu_bus, 0x1FFF);

			ppu->sprite_shift_low[sprite_index] = 0x00;
			ppu->sprite_shift_high[sprite_index] = 0x00;
			ppu->sprite_shift_x[sprite_index] = 0x00;
			ppu->sprite_shift_attribute[sprite_index] = 0x00;
		}
	}

	if (ppu->cycle == 313) {
		ppu->primary_oam_address = 0x00;
		ppu->secondary_oam_address = 0x00;
	}
}