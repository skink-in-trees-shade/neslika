#ifndef SXROM_H
#define SXROM_H

#include <stdint.h>
#include "cartridge/cartridge.h"

struct sxrom {
	uint8_t shift;
	uint8_t control;

	uint8_t *prg_ram;
	uint8_t prg_rom_bank[2];
	uint8_t chr_rom_bank[2];
};

void sxrom_load(struct cartridge *cartridge);

#endif