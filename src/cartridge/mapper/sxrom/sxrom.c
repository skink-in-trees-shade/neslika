#include <stdlib.h>
#include "memory/read_character_rom.h"
#include "memory/read_program_ram.h"
#include "memory/read_program_rom.h"
#include "memory/select_chr_rom_bank.h"
#include "memory/select_prg_rom_bank.h"
#include "memory/write_character_rom.h"
#include "memory/write_control.h"
#include "memory/write_program_ram.h"
#include "sxrom.h"

void sxrom_load(struct cartridge *cartridge) {
	struct sxrom *sxrom = calloc(1, sizeof(struct sxrom));
	sxrom->prg_ram = calloc(0x2000, sizeof(uint8_t));
	sxrom->prg_rom_bank[1] = cartridge->prg_rom_count - 1;
	cartridge->mapper_data = sxrom;

	bus_register(cartridge->cpu_bus, cartridge, 0x6000, 0x7FFF, &sxrom_read_program_ram, &sxrom_write_program_ram);
	bus_register(cartridge->cpu_bus, cartridge, 0x8000, 0x9FFF, &sxrom_read_program_rom, &sxrom_write_control);
	bus_register(cartridge->cpu_bus, cartridge, 0xA000, 0xDFFF, &sxrom_read_program_rom, &sxrom_select_chr_rom_bank);
	bus_register(cartridge->cpu_bus, cartridge, 0xE000, 0xFFFF, &sxrom_read_program_rom, &sxrom_select_prg_rom_bank);
	bus_register(cartridge->ppu_bus, cartridge, 0x0000, 0x1FFF, &sxrom_read_character_rom, &sxrom_write_character_rom);
}