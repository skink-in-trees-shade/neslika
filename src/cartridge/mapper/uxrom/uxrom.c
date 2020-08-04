#include "memory/read_character_rom.h"
#include "memory/read_program_rom.h"
#include "memory/select_bank.h"
#include "memory/write_character_rom.h"
#include "uxrom.h"

void uxrom_load(struct cartridge *cartridge) {
	bus_register(cartridge->cpu_bus, cartridge, 0x8000, 0xFFFF, &uxrom_read_program_rom, &uxrom_select_bank);
	bus_register(cartridge->ppu_bus, cartridge, 0x0000, 0x1FFF, &uxrom_read_character_rom, &uxrom_write_character_rom);
}