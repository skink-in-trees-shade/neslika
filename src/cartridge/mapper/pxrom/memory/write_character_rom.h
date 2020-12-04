#ifndef PXROM_WRITE_CHARACTER_ROM_H
#define PXROM_WRITE_CHARACTER_ROM_H

#include <stdint.h>

void pxrom_write_character_rom(void *device, uint16_t address, uint8_t value);

#endif