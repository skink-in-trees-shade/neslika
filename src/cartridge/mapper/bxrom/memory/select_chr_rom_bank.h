#ifndef BXROM_SELECT_CHR_ROM_BANK_H
#define BXROM_SELECT_CHR_ROM_BANK_H

#include <stdint.h>

void bxrom_select_chr_rom_bank(void *device, uint16_t address, uint8_t value);

#endif