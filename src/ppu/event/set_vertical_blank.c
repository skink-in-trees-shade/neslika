#include "set_vertical_blank.h"

void set_vertical_blank(struct ppu *ppu) {
	ppu->status |= 0x80;
	if ((ppu->control & 0x80) == 0x80) {
		ppu->nmi_occured = true;
	}
	ppu->frame_completed = true;
}