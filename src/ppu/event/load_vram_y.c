#include "load_vram_y.h"

void load_vram_y(struct ppu *ppu) {
	if ((ppu->mask & 0x08) == 0x08) {
		ppu->vram_address = (ppu->vram_address & 0x041F) | (ppu->temp_vram_address & 0x7BE0);
	}
}