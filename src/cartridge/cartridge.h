#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <stdint.h>
#include "device.h"

struct cartridge {
	struct device cpu_device;
	struct device ppu_device;

	uint8_t mapper;
	uint8_t prg_rom_count;
	uint8_t *prg_rom;
	uint8_t chr_rom_count;
	uint8_t *chr_rom;
};

struct cartridge *cartridge_new(void);
void cartridge_load(struct cartridge *cartridge, const char *filename);
void cartridge_tick(struct cartridge *cartridge);
void cartridge_destroy(struct cartridge *cartridge);

#endif