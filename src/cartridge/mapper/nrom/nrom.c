#include <stdlib.h>
#include "memory/read_character_rom.h"
#include "memory/read_name_table.h"
#include "memory/read_program_rom.h"
#include "memory/write_character_rom.h"
#include "memory/write_name_table.h"
#include "nrom.h"

void nrom_load(struct cartridge *cartridge) {
	struct nrom *nrom = calloc(1, sizeof(struct nrom));
	nrom->name_table = calloc(0x0800, sizeof(uint8_t));
	cartridge->mapper_data = nrom;

	bus_register(cartridge->cpu_bus, cartridge, 0x8000, 0xFFFF, &nrom_read_program_rom, NULL);
	bus_register(cartridge->ppu_bus, cartridge, 0x0000, 0x1FFF, &nrom_read_character_rom, &nrom_write_character_rom);
	bus_register(cartridge->ppu_bus, cartridge, 0x2000, 0x3EFF, &nrom_read_name_table, &nrom_write_name_table);
}