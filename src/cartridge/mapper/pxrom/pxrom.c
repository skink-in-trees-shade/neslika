#include <stdlib.h>
#include "memory/read_character_rom.h"
#include "memory/read_name_table.h"
#include "memory/read_program_ram.h"
#include "memory/read_program_rom.h"
#include "memory/select_chr_rom_bank.h"
#include "memory/select_prg_rom_bank.h"
#include "memory/write_control.h"
#include "memory/write_name_table.h"
#include "memory/write_program_ram.h"
#include "pxrom.h"

void pxrom_load(struct cartridge *cartridge) {
	struct pxrom *pxrom = calloc(1, sizeof(struct pxrom));
	pxrom->name_table = calloc(0x0800, sizeof(uint8_t));
	pxrom->prg_ram = calloc(0x2000, sizeof(uint8_t));
	pxrom->prg_rom_bank[1] = cartridge->prg_rom_count * 2 - 3;
	pxrom->prg_rom_bank[2] = cartridge->prg_rom_count * 2 - 2;
	pxrom->prg_rom_bank[3] = cartridge->prg_rom_count * 2 - 1;
	cartridge->mapper_data = pxrom;

	bus_register(cartridge->cpu_bus, cartridge, 0x6000, 0x7FFF, &pxrom_read_program_ram, &pxrom_write_program_ram);
	bus_register(cartridge->cpu_bus, cartridge, 0x8000, 0x9FFF, &pxrom_read_program_rom, NULL);
	bus_register(cartridge->cpu_bus, cartridge, 0xA000, 0xAFFF, &pxrom_read_program_rom, &pxrom_select_prg_rom_bank);
	bus_register(cartridge->cpu_bus, cartridge, 0xB000, 0xEFFF, &pxrom_read_program_rom, &pxrom_select_chr_rom_bank);
	bus_register(cartridge->cpu_bus, cartridge, 0xF000, 0xFFFF, &pxrom_read_program_rom, &pxrom_write_control);
	bus_register(cartridge->ppu_bus, cartridge, 0x0000, 0x1FFF, &pxrom_read_character_rom, NULL);
	bus_register(cartridge->ppu_bus, cartridge, 0x2000, 0x3EFF, &pxrom_read_name_table, &pxrom_write_name_table);
}