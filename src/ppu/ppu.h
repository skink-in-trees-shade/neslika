#ifndef PPU_H
#define PPU_H

#include <stdint.h>
#include <stdbool.h>
#include "device.h"
#include "screen.h"
#include "bus.h"

struct ppu {
	struct device cpu_device;
	struct device ppu_device;
	struct bus *bus;
	struct screen *screen;

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

	uint16_t vram_address;
	uint16_t temp_vram_address;
	uint8_t fine_x;

	uint8_t tile_id;
	uint8_t tile_low;
	uint8_t tile_high;
	uint16_t tile_shift_low;
	uint16_t tile_shift_high;

	uint8_t palette_id;
	uint16_t palette_shift_low;
	uint16_t palette_shift_high;
};

struct ppu *ppu_new(void);
void ppu_tick(struct ppu *ppu);
void ppu_destroy(struct ppu *ppu);

#endif