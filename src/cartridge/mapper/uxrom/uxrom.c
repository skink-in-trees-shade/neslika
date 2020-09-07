#include <stdlib.h>
#include "memory/read_character_rom.h"
#include "memory/read_name_table.h"
#include "memory/read_program_rom.h"
#include "memory/select_bank.h"
#include "memory/write_character_rom.h"
#include "memory/write_name_table.h"
#include "uxrom.h"

void uxrom_load(struct cartridge *cartridge) {
	struct uxrom *uxrom = calloc(1, sizeof(struct uxrom));
	uxrom->name_table = calloc(0x0800, sizeof(uint8_t));
	cartridge->mapper_data = uxrom;

	bus_register(cartridge->cpu_bus, cartridge, 0x8000, 0xFFFF, &uxrom_read_program_rom, &uxrom_select_bank);
	bus_register(cartridge->ppu_bus, cartridge, 0x0000, 0x1FFF, &uxrom_read_character_rom, &uxrom_write_character_rom);
	bus_register(cartridge->ppu_bus, cartridge, 0x2000, 0x3EFF, &uxrom_read_name_table, &uxrom_write_name_table);
}