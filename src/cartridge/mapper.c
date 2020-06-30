#include "mapper/nrom.h"
#include "mapper.h"

struct mapper mappers[0x100] = {
/* 0x00 */ { nrom_cpu_read, nrom_cpu_write, nrom_ppu_read, nrom_ppu_write },
};