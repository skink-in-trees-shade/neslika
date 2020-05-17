#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <stdint.h>
#include "device.h"

struct cartridge {
	struct device device;

	uint8_t *prg_rom;
};

struct cartridge *cartridge_new(void);
void cartridge_load(struct cartridge *cartridge, const char *filename);
void cartridge_destroy(struct cartridge *cartridge);

#endif