#include "mapper/nrom/nrom.h"
#include "mapper.h"

void (*mappers[0x100])(struct cartridge *cartridge) = {
/* 0x00 */ &nrom_load,
};