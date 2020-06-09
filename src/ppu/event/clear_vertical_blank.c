#include "clear_vertical_blank.h"

void clear_vertical_blank(struct ppu *ppu) {
	ppu->status |= 0x1F;
}