#include <stdlib.h>
#include "memory/read_character_rom.h"
#include "memory/read_name_table.h"
#include "memory/read_program_rom.h"
#include "memory/select_bank.h"
#include "memory/write_character_rom.h"
#include "memory/write_name_table.h"
#include "axrom.h"

void axrom_load(struct cartridge *cartridge) {
	struct axrom *axrom = calloc(1, sizeof(struct axrom));
	axrom->name_table = calloc(0x0800, sizeof(uint8_t));
	cartridge->mapper_data = axrom;

	bus_register(cartridge->cpu_bus, cartridge, 0x8000, 0xFFFF, &axrom_read_program_rom, &axrom_select_bank);
	bus_register(cartridge->ppu_bus, cartridge, 0x0000, 0x1FFF, &axrom_read_character_rom, &axrom_write_character_rom);
	bus_register(cartridge->ppu_bus, cartridge, 0x2000, 0x3EFF, &axrom_read_name_table, &axrom_write_name_table);
}