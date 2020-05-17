#ifndef INES_H
#define INES_H

#include <stdbool.h>
#include "cartridge/cartridge.h"

bool ines_load(struct cartridge *cartridge, const char *filename);

#endif