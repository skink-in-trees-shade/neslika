#ifndef AXROM_H
#define AXROM_H

#include <stdint.h>
#include "cartridge/cartridge.h"

struct axrom {
	uint8_t *name_table;

	uint8_t prg_rom_bank;
	uint8_t name_table_bank;
};

void axrom_load(struct cartridge *cartridge);

#endif