#include <stddef.h>
#include "mapper/axrom/axrom.h"
#include "mapper/cnrom/cnrom.h"
#include "mapper/nrom/nrom.h"
#include "mapper/sxrom/sxrom.h"
#include "mapper/txrom/txrom.h"
#include "mapper/uxrom/uxrom.h"
#include "mapper.h"

void (*mappers[0x08])(struct cartridge *cartridge) = {
/* 0x00 */ &nrom_load,
/* 0x01 */ &sxrom_load,
/* 0x02 */ &uxrom_load,
/* 0x03 */ &cnrom_load,
/* 0x04 */ &txrom_load,
/* 0x05 */ NULL,
/* 0x06 */ NULL,
/* 0x07 */ &axrom_load,
};