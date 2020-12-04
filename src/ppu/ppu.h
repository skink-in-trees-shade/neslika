#ifndef PPU_H
#define PPU_H

#include <stdint.h>
#include <stdbool.h>
#include "platform/screen.h"
#include "bus.h"

struct ppu {
	struct bus *cpu_bus;
	struct bus *ppu_bus;
	struct screen *screen;

	uint16_t scanline;
	uint16_t cycle;

	uint8_t control;
	uint8_t mask;
	uint8_t status;
	uint8_t last_value;
	uint32_t last_value_decay;

	bool nmi_occured;
	bool write_toggle;
	bool frame_completed;
	bool odd_frame;

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

	uint8_t oam_address;
	uint8_t oam_data;
	uint8_t oam_counter;
	uint16_t primary_oam_address;
	uint8_t secondary_oam_address;
	uint8_t sprite_shift_low[8];
	uint8_t sprite_shift_high[8];
	uint8_t sprite_shift_x[8];
	uint8_t sprite_shift_attribute[8];

	bool sprite_zero_evaluated;
	bool sprite_zero_hit_possible;
	bool sprite_zero_hit_occured;
	bool sprite_zero_hit_delay;
};

struct ppu *ppu_new(struct bus *cpu_bus, struct bus *ppu_bus, struct screen *screen);
void ppu_tick(struct ppu *ppu);
void ppu_destroy(struct ppu *ppu);

#endif