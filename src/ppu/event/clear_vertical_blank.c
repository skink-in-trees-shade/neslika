#include "clear_vertical_blank.h"

void clear_vertical_blank(struct ppu *ppu) {
	if (ppu->cycle == 1) {
		ppu->status &= 0x9F;
	} else if (ppu->cycle == 2) {
		ppu->status &= 0x7F;
	}
}