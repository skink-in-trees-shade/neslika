#ifndef AXROM_WRITE_CHARACTER_ROM_H
#define AXROM_WRITE_CHARACTER_ROM_H

#include <stdint.h>

void axrom_write_character_rom(void *device, uint16_t address, uint8_t value);

#endif