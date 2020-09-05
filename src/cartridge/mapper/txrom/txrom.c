#include <stdlib.h>
#include "memory/read_character_rom.h"
#include "memory/read_name_table.h"
#include "memory/read_program_ram.h"
#include "memory/read_program_rom.h"
#include "memory/select_bank.h"
#include "memory/write_character_rom.h"
#include "memory/write_control.h"
#include "memory/write_irq_control.h"
#include "memory/write_irq_counter.h"
#include "memory/write_name_table.h"
#include "memory/write_program_ram.h"
#include "txrom.h"

void txrom_load(struct cartridge *cartridge) {
	struct txrom *txrom = calloc(1, sizeof(struct txrom));
	txrom->name_table = calloc(0x0800, sizeof(uint8_t));
	txrom->prg_ram = calloc(0x2000, sizeof(uint8_t));
	for (size_t i = 0; i < 8; i++) {
		txrom->chr_rom_bank[i] = i;
	}
	txrom->prg_rom_bank[0] = cartridge->prg_rom_count * 2 - 2;
	txrom->prg_rom_bank[1] = cartridge->prg_rom_count * 2 - 1;
	txrom->prg_rom_bank[2] = cartridge->prg_rom_count * 2 - 2;
	txrom->prg_rom_bank[3] = cartridge->prg_rom_count * 2 - 1;
	cartridge->mapper_data = txrom;

	bus_register(cartridge->cpu_bus, cartridge, 0x6000, 0x7FFF, &txrom_read_program_ram, &txrom_write_program_ram);
	bus_register(cartridge->cpu_bus, cartridge, 0x8000, 0x9FFF, &txrom_read_program_rom, &txrom_select_bank);
	bus_register(cartridge->cpu_bus, cartridge, 0xA000, 0xBFFF, &txrom_read_program_rom, &txrom_write_control);
	bus_register(cartridge->cpu_bus, cartridge, 0xC000, 0xDFFF, &txrom_read_program_rom, &txrom_write_irq_counter);
	bus_register(cartridge->cpu_bus, cartridge, 0xE000, 0xFFFF, &txrom_read_program_rom, &txrom_write_irq_control);
	bus_register(cartridge->ppu_bus, cartridge, 0x0000, 0x1FFF, &txrom_read_character_rom, &txrom_write_character_rom);
	bus_register(cartridge->ppu_bus, cartridge, 0x2000, 0x3EFF, &txrom_read_name_table, &txrom_write_name_table);
}