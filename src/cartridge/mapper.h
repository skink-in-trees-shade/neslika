#ifndef MAPPER_H
#define MAPPER_H

#include <stdint.h>
#include "cartridge/cartridge.h"

struct mapper {
	uint16_t (*cpu)(struct cartridge *cartridge, uint16_t address);
	uint16_t (*ppu)(struct cartridge *cartridge, uint16_t address);
};

extern struct mapper mappers[0x100];

#endif