#include <stddef.h>
#include "mapper/cnrom/cnrom.h"
#include "mapper/nrom/nrom.h"
#include "mapper/sxrom/sxrom.h"
#include "mapper/uxrom/uxrom.h"
#include "mapper.h"

void (*mappers[0x08])(struct cartridge *cartridge) = {
/* 0x00 */ &nrom_load,
/* 0x01 */ &sxrom_load,
/* 0x02 */ &uxrom_load,
/* 0x03 */ &cnrom_load,
};