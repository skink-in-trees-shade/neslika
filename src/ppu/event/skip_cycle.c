#include "skip_cycle.h"

void skip_cycle(struct ppu *ppu) {
	if (((ppu->mask & 0x08) == 0x08 || (ppu->mask & 0x10) == 0x10) && ppu->odd_frame) {
		ppu->cycle++;
	}
}