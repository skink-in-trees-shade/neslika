#include "clear_oam.h"

void clear_oam(struct ppu *ppu) {
	if ((ppu->mask & 0x10) == 0x10 || (ppu->mask & 0x08) == 0x08) {
		if ((ppu->cycle & 0x01) == 0x01) {
			ppu->secondary_oam[(ppu->cycle - 1) >> 1] = 0xFF;
		}
	}
}