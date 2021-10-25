#ifndef BXROM_H
#define BXROM_H

#include <stdint.h>
#include "cartridge/cartridge.h"

struct bxrom {
	uint8_t *name_table;

	uint8_t *prg_ram;
	uint8_t prg_rom_bank;
	uint8_t chr_rom_bank[2];
};

void bxrom_load(struct cartridge *cartridge);

#endif