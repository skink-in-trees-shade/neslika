#ifndef CNROM_SELECT_CHR_ROM_BANK_H
#define CNROM_SELECT_CHR_ROM_BANK_H

#include <stdint.h>

void cnrom_select_chr_rom_bank(void *device, uint16_t address, uint8_t value);

#endif