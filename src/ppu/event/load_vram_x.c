#include "load_vram_x.h"

void load_vram_x(struct ppu *ppu) {
	if ((ppu->mask & 0x08) == 0x08) {
		ppu->vram_address = (ppu->vram_address & 0x7BE0) | (ppu->temp_vram_address & 0x041F);
	}
}