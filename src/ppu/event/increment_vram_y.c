#include "increment_vram_y.h"

void increment_vram_y(struct ppu *ppu) {
	if ((ppu->mask & 0x08) == 0x08) {
		if ((ppu->vram_address & 0x7000) == 0x7000) {
			ppu->vram_address &= 0x0FFF;
			if ((ppu->vram_address & 0x03E0) == 0x03A0) {
				ppu->vram_address &= 0x7C1F;
				ppu->vram_address ^= 0x0800;
			} else if ((ppu->vram_address & 0x03E0) == 0x03E0) {
				ppu->vram_address &= 0x7C1F;
			} else {
				ppu->vram_address += 0x0020;
			}
		} else {
			ppu->vram_address += 0x1000;
		}
	}
}