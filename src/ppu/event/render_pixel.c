#include "ppu/screen.h"
#include "render_pixel.h"

void render_pixel(struct ppu *ppu) {
	if ((ppu->mask & 0x08) == 0x08) {
		uint16_t shift = ppu->fine_x ^ 0x0F;

		uint8_t bg_palette_low = ppu->palette_shift_low >> shift;
		uint8_t bg_palette_high = ppu->palette_shift_high >> shift;
		uint8_t bg_palette = (bg_palette_high << 1) | bg_palette_low;

		uint8_t bg_pixel_low = ppu->tile_shift_low >> shift;
		uint8_t bg_pixel_high = ppu->tile_shift_high >> shift;
		uint8_t bg_pixel = (bg_pixel_high << 1) | bg_pixel_low;

		uint8_t color_id = ppu->palette_table[(bg_palette << 2) | bg_pixel];
		screen_pixel(ppu->screen, ppu->cycle, ppu->scanline, color_id);
	}
}