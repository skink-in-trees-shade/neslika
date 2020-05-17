#ifndef NROM_H
#define NROM_H

#include <stdint.h>
#include "cartridge/cartridge.h"

uint16_t nrom(struct cartridge *cartridge, uint16_t address);

#endif