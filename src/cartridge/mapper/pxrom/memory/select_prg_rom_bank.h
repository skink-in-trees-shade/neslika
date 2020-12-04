#ifndef PXROM_SELECT_PRG_ROM_BANK_H
#define PXROM_SELECT_PRG_ROM_BANK_H

#include <stdint.h>

void pxrom_select_prg_rom_bank(void *device, uint16_t address, uint8_t value);

#endif