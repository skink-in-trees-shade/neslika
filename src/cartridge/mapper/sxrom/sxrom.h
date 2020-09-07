#ifndef SXROM_H
#define SXROM_H

#include <stdint.h>
#include "cartridge/cartridge.h"

enum sxrom_mirroring {
	sxrom_mirroring_one_screen_lower,
	sxrom_mirroring_one_screen_upper,
	sxrom_mirroring_vertical,
	sxrom_mirroring_horizontal
};

struct sxrom {
	uint8_t shift;
	uint8_t control;
	enum sxrom_mirroring mirroring;

	uint8_t *name_table;

	uint8_t *prg_ram;
	uint8_t prg_rom_bank[2];
	uint8_t chr_rom_bank[2];
};

void sxrom_load(struct cartridge *cartridge);

#endif