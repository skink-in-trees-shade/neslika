#ifndef NROM_H
#define NROM_H

#include <stdint.h>
#include "cartridge/cartridge.h"

uint16_t nrom_cpu(struct cartridge *cartridge, uint16_t address);
uint16_t nrom_ppu(struct cartridge *cartridge, uint16_t address);

#endif