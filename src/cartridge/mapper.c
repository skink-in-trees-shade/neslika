#include "mapper/nrom.h"
#include "mapper.h"

struct mapper mappers[0x100] = {
/* 0x00 */ { nrom_cpu, nrom_ppu },
};