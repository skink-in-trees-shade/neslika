#include "cartridge/cartridge.h"
#include "cartridge/mapper/txrom/txrom.h"
#include "select_bank.h"

void txrom_select_bank(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct txrom *txrom = cartridge->mapper_data;

	if ((address & 0x0001) == 0x0000) {
		txrom->bank_select = value;
	} else {
		if ((txrom->bank_select & 0x06) != 0x06) {
			if ((txrom->bank_select & 0x06) == 0x00) {
				uint8_t bank = ((txrom->bank_select & 0x80) >> 5) | ((txrom->bank_select & 0x01) << 1);
				txrom->chr_rom_bank[bank] = value & 0xFE;
				txrom->chr_rom_bank[bank + 1] = txrom->chr_rom_bank[bank] + 1;
			} else {
				uint8_t bank = ((~txrom->bank_select & 0x80) >> 5) | ((txrom->bank_select & 0x07) - 0x02);
				txrom->chr_rom_bank[bank] = value;
			}
		} else {
			if ((txrom->bank_select & 0x01) == 0x00) {
				uint8_t bank = (txrom->bank_select & 0x40) >> 5;
				txrom->prg_rom_bank[bank] = (value & 0x3F) % (cartridge->prg_rom_count * 2);
				txrom->prg_rom_bank[(bank + 2) & 0x03] = cartridge->prg_rom_count * 2 - 2;
			} else {
				txrom->prg_rom_bank[1] = (value & 0x3F) % (cartridge->prg_rom_count * 2);
			}
		}
	}
}