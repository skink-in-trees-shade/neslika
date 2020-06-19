#ifndef PPU_H
#define PPU_H

#include <stdint.h>
#include <stdbool.h>
#include "device.h"
#include "screen.h"
#include "bus.h"
#include "cartridge/cartridge.h"

struct ppu {
	struct device cpu_device;
	struct device ppu_device;
	struct bus *bus;
	struct screen *screen;
	struct cartridge *cartridge;

	uint16_t scanline;
	uint16_t cycle;

	uint8_t control;
	uint8_t mask;
	uint8_t status;

	bool nmi_occured;
	bool write_toggle;
	bool frame_completed;

	uint8_t *name_table;
	uint8_t *palette_table;
	uint8_t *primary_oam;
	uint8_t *secondary_oam;

	uint16_t vram_address;
	uint16_t temp_vram_address;
	uint8_t fine_x;
	uint8_t read_buffer;

	uint8_t tile_id;
	uint8_t tile_low;
	uint8_t tile_high;
	uint16_t tile_shift_low;
	uint16_t tile_shift_high;

	uint8_t palette_id;
	uint16_t palette_shift_low;
	uint16_t palette_shift_high;

	uint8_t primary_sprite;
	uint8_t secondary_sprite;
	uint8_t sprite_shift_low[8];
	uint8_t sprite_shift_high[8];
	uint8_t sprite_shift_x[8];
	uint8_t sprite_shift_attribute[8];
};

struct ppu *ppu_new(void);
void ppu_tick(struct ppu *ppu);
void ppu_destroy(struct ppu *ppu);

#endif