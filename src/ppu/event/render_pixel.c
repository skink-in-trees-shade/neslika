#include "platform/screen.h"
#include "render_pixel.h"

void render_pixel(struct ppu *ppu) {
	uint8_t bg_palette = 0x00;
	uint8_t bg_pixel = 0x00;
	if ((ppu->mask & 0x08) == 0x08) {
		uint16_t shift = ppu->fine_x ^ 0x0F;

		uint8_t bg_pixel_low = (ppu->tile_shift_low >> shift) & 0x01;
		uint8_t bg_pixel_high = (ppu->tile_shift_high >> shift) & 0x01;
		bg_pixel = (bg_pixel_high << 1) | bg_pixel_low;

		uint8_t bg_palette_low = (ppu->palette_shift_low >> shift) & 0x01;
		uint8_t bg_palette_high = (ppu->palette_shift_high >> shift) & 0x01;
		bg_palette = (bg_palette_high << 1) | bg_palette_low;
	}

	if ((ppu->mask & 0x08) == 0x00 && (ppu->mask & 0x10) == 0x00 && (ppu->vram_address & 0x3F00) == 0x3F00) {
		bg_pixel = ppu->vram_address & 0x1F;
	}

	uint8_t fg_palette = 0x00;
	uint8_t fg_pixel = 0x00;
	bool fg_priority = false;
	if ((ppu->mask & 0x10) == 0x10) {
		for (int i = 0; i < 8; i++) {
			if (ppu->sprite_shift_x[i] == 0) {
				uint8_t fg_pixel_low = ppu->sprite_shift_low[i] >> 7;
				uint8_t fg_pixel_high = ppu->sprite_shift_high[i] >> 7;
				fg_pixel = (fg_pixel_high << 1) | fg_pixel_low;

				if (fg_pixel > 0x00) {
					fg_palette = (ppu->sprite_shift_attribute[i] & 0x03) + 0x04;
					fg_priority = (ppu->sprite_shift_attribute[i] & 0x20) == 0x00;

					if (ppu->sprite_zero_evaluated && i == 0 && bg_pixel > 0x00) {
						ppu->status |= 0x40;
					}

					break;
				}
			}
		}
	}

	uint8_t palette = 0x00;
	uint8_t pixel = 0x00;
	if ((bg_pixel == 0x00 && fg_pixel > 0x00) || (bg_pixel > 0x00 && fg_pixel > 0x00 && fg_priority)) {
		palette = fg_palette;
		pixel = fg_pixel;
	} else if ((bg_pixel > 0x00 && fg_pixel == 0x00) || (bg_pixel > 0x00 && fg_pixel > 0x00 && !fg_priority)) {
		palette = bg_palette;
		pixel = bg_pixel;
	}

	uint8_t color_id = ppu->palette_table[(palette << 2) | pixel];
	screen_pixel(ppu->screen, ppu->cycle - 1, ppu->scanline, color_id);
}