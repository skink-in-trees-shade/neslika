#include <stdlib.h>
#include "memory/read_character_rom.h"
#include "memory/read_irq_status.h"
#include "memory/read_name_table.h"
#include "memory/read_program_ram.h"
#include "memory/read_program_rom.h"
#include "memory/select_character_rom_bank.h"
#include "memory/select_irq_scanline.h"
#include "memory/select_program_ram_bank.h"
#include "memory/select_program_rom_bank.h"
#include "memory/write_character_mode.h"
#include "memory/write_fill_palette.h"
#include "memory/write_fill_tile.h"
#include "memory/write_irq_status.h"
#include "memory/write_mirroring.h"
#include "memory/write_name_table.h"
#include "memory/write_program_mode.h"
#include "memory/write_program_ram.h"
#include "memory/write_program_rom.h"
#include "exrom.h"

void exrom_load(struct cartridge *cartridge) {
	struct exrom *exrom = calloc(1, sizeof(struct exrom));
	exrom->name_table = calloc(0x0800, sizeof(uint8_t));
	exrom->prg_ram = calloc(0x10000, sizeof(uint8_t));
	exrom->prg_mode = 0x03;
	exrom->prg_rom_bank[3] = cartridge->prg_rom_count * 2 - 1;
	cartridge->mapper_data = exrom;

	bus_register(cartridge->cpu_bus, cartridge, 0x5100, 0x5100, NULL, &exrom_write_program_mode);
	bus_register(cartridge->cpu_bus, cartridge, 0x5101, 0x5101, NULL, &exrom_write_character_mode);
	bus_register(cartridge->cpu_bus, cartridge, 0x5105, 0x5105, NULL, &exrom_write_mirroring);
	bus_register(cartridge->cpu_bus, cartridge, 0x5106, 0x5106, NULL, &exrom_write_fill_tile);
	bus_register(cartridge->cpu_bus, cartridge, 0x5107, 0x5107, NULL, &exrom_write_fill_palette);
	bus_register(cartridge->cpu_bus, cartridge, 0x5113, 0x5113, NULL, &exrom_select_program_ram_bank);
	bus_register(cartridge->cpu_bus, cartridge, 0x5114, 0x5117, NULL, &exrom_select_program_rom_bank);
	bus_register(cartridge->cpu_bus, cartridge, 0x5120, 0x512B, NULL, &exrom_select_character_rom_bank);
	bus_register(cartridge->cpu_bus, cartridge, 0x5203, 0x5203, NULL, &exrom_select_irq_scanline);
	bus_register(cartridge->cpu_bus, cartridge, 0x5204, 0x5204, &exrom_read_irq_status, &exrom_write_irq_status);
	bus_register(cartridge->cpu_bus, cartridge, 0x6000, 0x7FFF, &exrom_read_program_ram, &exrom_write_program_ram);
	bus_register(cartridge->cpu_bus, cartridge, 0x8000, 0xFFFF, &exrom_read_program_rom, &exrom_write_program_rom);
	bus_register(cartridge->ppu_bus, cartridge, 0x0000, 0x1FFF, &exrom_read_character_rom, NULL);
	bus_register(cartridge->ppu_bus, cartridge, 0x2000, 0x3EFF, &exrom_read_name_table, &exrom_write_name_table);
}