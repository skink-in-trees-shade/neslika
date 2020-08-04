#ifndef UXROM_WRITE_CHARACTER_ROM_H
#define UXROM_WRITE_CHARACTER_ROM_H

#include <stdint.h>

void uxrom_write_character_rom(void *device, uint16_t address, uint8_t value);

#endif