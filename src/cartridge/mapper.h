#ifndef MAPPER_H
#define MAPPER_H

#include <stdint.h>
#include "cartridge/cartridge.h"

struct mapper {
	uint16_t (*map)(struct cartridge *cartridge, uint16_t address);
};

extern struct mapper mappers[0x100];

#endif