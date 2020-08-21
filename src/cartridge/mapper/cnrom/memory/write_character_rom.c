#include "cartridge/cartridge.h"
#include "cartridge/mapper/cnrom/cnrom.h"
#include "write_character_rom.h"

void cnrom_write_character_rom(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct cnrom *cnrom = cartridge->mapper_data;

	cartridge->chr_rom[(cnrom->chr_rom_bank << 13) | (address & 0x1FFF)] = value;
}