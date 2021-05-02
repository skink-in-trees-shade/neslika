#ifndef EXROM_H
#define EXROM_H

#include <stdint.h>
#include <stdbool.h>
#include "cartridge/cartridge.h"

struct exrom {
	uint8_t *name_table;

	uint8_t fill_tile;
	uint8_t fill_palette;
	uint8_t mirroring[4];

	uint8_t *prg_ram;
	uint8_t prg_mode;
	uint8_t chr_mode;
	uint8_t prg_ram_bank;
	uint8_t prg_rom_bank[4];
	bool prg_rom_writable[4];
	uint8_t chr_rom_bank[12];
	bool use_background_banks;

	bool in_frame;
	uint8_t scanline_counter;
	bool irq_enabled;
	bool irq_pending;
	uint8_t irq_scanline;
	uint16_t last_address;
	uint8_t address_match_count;
	uint8_t name_table_fetch_count;
};

void exrom_load(struct cartridge *cartridge);

#endif 