#include "bus.h"
#include "load_sprite.h"

void load_sprite(struct ppu *ppu) {
	if ((ppu->mask & 0x10) == 0x10) {
		if (ppu->secondary_sprite > 0x00 && ppu->secondary_sprite <= 0x08) {
			ppu->secondary_sprite--;

			uint8_t *sprite = &ppu->secondary_oam[(ppu->secondary_sprite) * 4];
			uint8_t sprite_x = sprite[3];
			uint8_t sprite_y = sprite[0];
			uint8_t sprite_tile_id = sprite[1];
			uint8_t sprite_attribute = sprite[2];

			uint16_t address = ((ppu->control & 0x08) << 9) | (sprite_tile_id << 4) | (ppu->scanline - sprite_y);
			uint8_t sprite_low = bus_read(ppu->bus, address);
			uint8_t sprite_high = bus_read(ppu->bus, address + 0x08);

			ppu->sprite_shift_low[ppu->secondary_sprite] = sprite_low;
			ppu->sprite_shift_high[ppu->secondary_sprite] = sprite_high;
			ppu->sprite_shift_x[ppu->secondary_sprite] = sprite_x;
			ppu->sprite_shift_attribute[ppu->secondary_sprite] = sprite_attribute;
		}
	}
}