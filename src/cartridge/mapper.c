#include <stddef.h>
#include "mapper/axrom/axrom.h"
#include "mapper/bxrom/bxrom.h"
#include "mapper/cnrom/cnrom.h"
#include "mapper/exrom/exrom.h"
#include "mapper/nrom/nrom.h"
#include "mapper/pxrom/pxrom.h"
#include "mapper/sxrom/sxrom.h"
#include "mapper/txrom/txrom.h"
#include "mapper/uxrom/uxrom.h"
#include "mapper.h"

void (*mappers[0xFF])(struct cartridge *cartridge) = {
/* 0x00 */ &nrom_load,
/* 0x01 */ &sxrom_load,
/* 0x02 */ &uxrom_load,
/* 0x03 */ &cnrom_load,
/* 0x04 */ &txrom_load,
/* 0x05 */ &exrom_load,
/* 0x06 */ NULL,
/* 0x07 */ &axrom_load,
/* 0x08 */ NULL,
/* 0x09 */ &pxrom_load,
/* 0x0A */ NULL,
/* 0x0B */ NULL,
/* 0x0C */ NULL,
/* 0x0D */ NULL,
/* 0x0E */ NULL,
/* 0x0F */ NULL,
/* 0x10 */ NULL,
/* 0x11 */ NULL,
/* 0x12 */ NULL,
/* 0x13 */ NULL,
/* 0x14 */ NULL,
/* 0x15 */ NULL,
/* 0x16 */ NULL,
/* 0x17 */ NULL,
/* 0x18 */ NULL,
/* 0x19 */ NULL,
/* 0x1A */ NULL,
/* 0x1B */ NULL,
/* 0x1C */ NULL,
/* 0x1D */ NULL,
/* 0x1E */ NULL,
/* 0x1F */ NULL,
/* 0x20 */ NULL,
/* 0x21 */ NULL,
/* 0x22 */ &bxrom_load,
};