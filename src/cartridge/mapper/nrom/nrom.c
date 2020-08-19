#include <stddef.h>
#include "memory/read_character_rom.h"
#include "memory/read_program_rom.h"
#include "memory/write_character_rom.h"
#include "nrom.h"

void nrom_load(struct cartridge *cartridge) {
	bus_register(cartridge->cpu_bus, cartridge, 0x8000, 0xFFFF, &nrom_read_program_rom, NULL);
	bus_register(cartridge->ppu_bus, cartridge, 0x0000, 0x1FFF, &nrom_read_character_rom, &nrom_write_character_rom);
}