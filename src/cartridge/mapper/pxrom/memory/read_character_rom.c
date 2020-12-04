#include "cartridge/cartridge.h"
#include "cartridge/mapper/pxrom/pxrom.h"
#include "read_character_rom.h"

uint8_t pxrom_read_character_rom(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct pxrom *pxrom = cartridge->mapper_data;

	uint8_t latch = pxrom->chr_rom_latch[(address & 0x1000) >> 12];
	uint8_t bank = pxrom->chr_rom_bank[(address & 0x1000) >> 12][latch];
	uint8_t value = cartridge->chr_rom[(bank << 12) | (address & 0x0FFF)];

	switch (address) {
		case 0x0FD8:
			pxrom->chr_rom_latch[0] = false;
		break;
		case 0x0FE8:
			pxrom->chr_rom_latch[0] = true;
		break;
		case 0x1FD8:
		case 0x1FD9:
		case 0x1FDA:
		case 0x1FDB:
		case 0x1FDC:
		case 0x1FDD:
		case 0x1FDE:
		case 0x1FDF:
			pxrom->chr_rom_latch[1] = false;
		break;
		case 0x1FE8:
		case 0x1FE9:
		case 0x1FEA:
		case 0x1FEB:
		case 0x1FEC:
		case 0x1FED:
		case 0x1FEE:
		case 0x1FEF:
			pxrom->chr_rom_latch[1] = true;
		break;
	}

	return value;
}