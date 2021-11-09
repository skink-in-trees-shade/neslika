#include <stdlib.h>
#include "memory/read_character_rom.h"
#include "memory/read_name_table.h"
#include "memory/read_program_rom.h"
#include "memory/select_chr_rom_bank.h"
#include "memory/write_name_table.h"
#include "cnrom.h"

void cnrom_load(struct cartridge *cartridge) {
	struct cnrom *cnrom = calloc(1, sizeof(struct cnrom));
	cnrom->name_table = calloc(0x0800, sizeof(uint8_t));
	cartridge->mapper_data = cnrom;

	bus_register(cartridge->cpu_bus, cartridge, 0x8000, 0xFFFF, &cnrom_read_program_rom, &cnrom_select_chr_rom_bank);
	bus_register(cartridge->ppu_bus, cartridge, 0x0000, 0x1FFF, &cnrom_read_character_rom, NULL);
	bus_register(cartridge->ppu_bus, cartridge, 0x2000, 0x3EFF, &cnrom_read_name_table, &cnrom_write_name_table);
}