#ifndef UXROM_H
#define UXROM_H

#include <stdint.h>
#include "cartridge/cartridge.h"

struct uxrom {
	uint8_t *name_table;

	uint8_t prg_rom_bank;
};

void uxrom_load(struct cartridge *cartridge);

#endif