#ifndef MAPPER_H
#define MAPPER_H

#include <stdint.h>
#include "cartridge/cartridge.h"

struct mapper {
	uint8_t (*cpu_read)(struct cartridge *cartridge, uint16_t address);
	void (*cpu_write)(struct cartridge *cartridge, uint16_t address, uint8_t value);
	uint8_t (*ppu_read)(struct cartridge *cartridge, uint16_t address);
	void (*ppu_write)(struct cartridge *cartridge, uint16_t address, uint8_t value);
};

extern struct mapper mappers[0x100];

#endif