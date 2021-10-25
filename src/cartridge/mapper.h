#ifndef MAPPER_H
#define MAPPER_H

#include "cartridge/cartridge.h"

extern void (*mappers[0xFF])(struct cartridge *cartridge);

#endif