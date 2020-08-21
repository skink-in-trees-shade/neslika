#include "cartridge/cartridge.h"
#include "cartridge/mapper/cnrom/cnrom.h"
#include "read_character_rom.h"

uint8_t cnrom_read_character_rom(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct cnrom *cnrom = cartridge->mapper_data;

	return cartridge->chr_rom[(cnrom->chr_rom_bank << 13) | (address & 0x1FFF)];
}