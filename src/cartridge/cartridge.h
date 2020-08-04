#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <stdint.h>
#include <stdbool.h>
#include "bus.h"

struct cartridge {
	struct bus *cpu_bus;
	struct bus *ppu_bus;

	uint8_t mapper;
	bool vertical_mirroring;
	uint8_t prg_rom_count;
	uint8_t prg_rom_bank;
	uint8_t *prg_rom;
	uint8_t chr_rom_count;
	uint8_t *chr_rom;
};

struct cartridge *cartridge_new(struct bus *cpu_bus, struct bus *ppu_bus);
void cartridge_load(struct cartridge *cartridge, const char *filename);
void cartridge_tick(struct cartridge *cartridge);
void cartridge_destroy(struct cartridge *cartridge);

#endif