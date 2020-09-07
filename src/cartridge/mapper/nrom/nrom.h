#ifndef NROM_H
#define NROM_H

#include <stdint.h>
#include "cartridge/cartridge.h"

struct nrom {
	uint8_t *name_table;
};

void nrom_load(struct cartridge *cartridge);

#endif