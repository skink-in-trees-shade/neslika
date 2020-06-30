#ifndef NROM_H
#define NROM_H

#include <stdint.h>
#include "cartridge/cartridge.h"

uint8_t nrom_cpu_read(struct cartridge *cartridge, uint16_t address);
void nrom_cpu_write(struct cartridge *cartridge, uint16_t address, uint8_t value);
uint8_t nrom_ppu_read(struct cartridge *cartridge, uint16_t address);
void nrom_ppu_write(struct cartridge *cartridge, uint16_t address, uint8_t value);

#endif