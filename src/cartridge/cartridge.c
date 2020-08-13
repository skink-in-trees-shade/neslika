#include <stdlib.h>
#include "mapper.h"
#include "format/ines.h"
#include "error.h"
#include "cartridge.h"

struct cartridge *cartridge_new(struct bus *cpu_bus, struct bus *ppu_bus) {
	struct cartridge *cartridge = calloc(1, sizeof(struct cartridge));
	cartridge->cpu_bus = cpu_bus;
	cartridge->ppu_bus = ppu_bus;
	return cartridge;
}

void cartridge_load(struct cartridge *cartridge, const char *filename) {
	if (!ines_load(cartridge, filename)) {
		error("Unknown cartridge format.");
	}

	void (*mapper_load)(struct cartridge *cartridge) = mappers[cartridge->mapper];
	if (!mapper_load) {
		error("Unknown mapper %02X.", cartridge->mapper);
	}

	mapper_load(cartridge);
}

void cartridge_tick(struct cartridge *cartridge) {
	(void)cartridge;
}

void cartridge_destroy(struct cartridge *cartridge) {
	free(cartridge->mapper_data);
	free(cartridge->chr_rom);
	free(cartridge->prg_rom);
	free(cartridge);
}