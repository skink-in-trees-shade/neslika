#include "cartridge/cartridge.h"
#include "cartridge/mapper/exrom/exrom.h"
#include "read_program_rom.h"

uint8_t exrom_read_program_rom(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct exrom *exrom = cartridge->mapper_data;

	if (address == 0xFFFA) {
		exrom->in_frame = false;
	}

	switch (exrom->prg_mode) {
		case 0x00:
			return cartridge->prg_rom[(exrom->prg_rom_bank[3] << 15) | (address & 0x7FFF)];
		break;

		case 0x01:
			if (address < 0xC000) {
				return cartridge->prg_rom[(exrom->prg_rom_bank[1] << 14) | (address & 0x3FFF)];
			} else {
				return cartridge->prg_rom[(exrom->prg_rom_bank[3] << 14) | (address & 0x3FFF)];
			}
		break;

		case 0x02:
			if (address < 0xC000) {
				return cartridge->prg_rom[(exrom->prg_rom_bank[1] << 14) | (address & 0x3FFF)];
			} else if (address < 0xE000) {
				return cartridge->prg_rom[(exrom->prg_rom_bank[2] << 13) | (address & 0x1FFF)];
			} else {
				return cartridge->prg_rom[(exrom->prg_rom_bank[3] << 13) | (address & 0x1FFF)];
			}
		break;

		case 0x03:
			if (address < 0xA000) {
				return cartridge->prg_rom[(exrom->prg_rom_bank[0] << 13) | (address & 0x1FFF)];
			} else if (address < 0xC000) {
				return cartridge->prg_rom[(exrom->prg_rom_bank[1] << 13) | (address & 0x1FFF)];
			} else if (address < 0xE000) {
				return cartridge->prg_rom[(exrom->prg_rom_bank[2] << 13) | (address & 0x1FFF)];
			} else {
				return cartridge->prg_rom[(exrom->prg_rom_bank[3] << 13) | (address & 0x1FFF)];
			}
		break;
	}

	return 0x00;
}