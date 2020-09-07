#ifndef CNROM_H
#define CNROM_H

#include <stdint.h>
#include "cartridge/cartridge.h"

struct cnrom {
	uint8_t *name_table;

	uint8_t chr_rom_bank;
};

void cnrom_load(struct cartridge *cartridge);

#endif