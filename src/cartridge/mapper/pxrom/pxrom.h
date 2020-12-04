#ifndef PXROM_H
#define PXROM_H

#include <stdint.h>
#include <stdbool.h>
#include "cartridge/cartridge.h"

struct pxrom {
	uint8_t *name_table;

	uint8_t *prg_ram;
	uint8_t prg_rom_bank[4];
	uint8_t chr_rom_bank[2][2];
	bool chr_rom_latch[2];
};

void pxrom_load(struct cartridge *cartridge);

#endif