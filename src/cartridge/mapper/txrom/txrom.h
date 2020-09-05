#ifndef TXROM_H
#define TXROM_H

#include <stdint.h>
#include <stdbool.h>
#include "cartridge/cartridge.h"

struct txrom {
	uint8_t bank_select;

	uint8_t *name_table;

	bool a12;
	bool irq_enabled;
	uint8_t irq_reload;
	uint8_t irq_counter;

	uint8_t *prg_ram;
	uint8_t prg_rom_bank[4];
	uint8_t chr_rom_bank[8];
};

void txrom_load(struct cartridge *cartridge);

#endif