#include "cartridge/cartridge.h"
#include "cartridge/mapper/sxrom/sxrom.h"
#include "write_character_rom.h"

void sxrom_write_character_rom(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct sxrom *sxrom = cartridge->mapper_data;

	switch ((sxrom->control & 0x10) >> 4) {
		case 0x00:
			cartridge->chr_rom[((sxrom->chr_rom_bank[0] >> 1) << 13) + (address & 0x1FFF)] = value;
		break;

		case 0x01:
			if (address <= 0x0FFF) {
				cartridge->chr_rom[(sxrom->chr_rom_bank[0] << 12) + (address & 0x0FFF)] = value;
			} else {
				cartridge->chr_rom[(sxrom->chr_rom_bank[1] << 12) + (address & 0x0FFF)] = value;
			}
		break;
	}
}