#include "increment_vram_x.h"

void increment_vram_x(struct ppu *ppu) {
	if ((ppu->mask & 0x08) == 0x08) {
		if ((ppu->vram_address & 0x001F) == 0x001F) {
			ppu->vram_address &= 0x7FE0;
			ppu->vram_address ^= 0x0400;
		} else {
			ppu->vram_address += 0x0001;
		}
	}
}