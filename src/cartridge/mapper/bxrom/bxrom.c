#include <stdlib.h>
#include "memory/read_character_rom.h"
#include "memory/read_name_table.h"
#include "memory/read_program_ram.h"
#include "memory/read_program_rom.h"
#include "memory/select_chr_rom_bank.h"
#include "memory/select_prg_rom_bank.h"
#include "memory/write_character_rom.h"
#include "memory/write_program_ram.h"
#include "memory/write_name_table.h"
#include "bxrom.h"

void bxrom_load(struct cartridge *cartridge) {
	struct bxrom *bxrom = calloc(1, sizeof(struct bxrom));
	bxrom->name_table = calloc(0x0800, sizeof(uint8_t));
	bxrom->chr_rom_bank[1] = 1;
	bxrom->prg_ram = calloc(0x2000, sizeof(uint8_t));
	cartridge->mapper_data = bxrom;

	if (cartridge->chr_rom_count == 1) {
		bus_register(cartridge->cpu_bus, cartridge, 0x6000, 0x7FFF, &bxrom_read_program_ram, &bxrom_write_program_ram);
		bus_register(cartridge->cpu_bus, cartridge, 0x8000, 0xFFFF, &bxrom_read_program_rom, &bxrom_select_prg_rom_bank);
	} else {
		bus_register(cartridge->cpu_bus, cartridge, 0x6000, 0x7FFC, &bxrom_read_program_ram, &bxrom_write_program_ram);
		bus_register(cartridge->cpu_bus, cartridge, 0x7FFD, 0x7FFD, NULL, &bxrom_select_prg_rom_bank);
		bus_register(cartridge->cpu_bus, cartridge, 0x7FFE, 0x7FFF, NULL, &bxrom_select_chr_rom_bank);
		bus_register(cartridge->cpu_bus, cartridge, 0x8000, 0xFFFF, &bxrom_read_program_rom, NULL);
	}
	bus_register(cartridge->ppu_bus, cartridge, 0x0000, 0x1FFF, &bxrom_read_character_rom, &bxrom_write_character_rom);
	bus_register(cartridge->ppu_bus, cartridge, 0x2000, 0x3EFF, &bxrom_read_name_table, &bxrom_write_name_table);
}