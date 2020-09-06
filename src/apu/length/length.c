#include <stdlib.h>
#include "length.h"

static uint8_t lengths[0x20] = {
	0x0A, 0xFE, 0x14, 0x02, 0x28, 0x04, 0x50, 0x06,
	0xA0, 0x08, 0x3C, 0x0A, 0x0E, 0x0C, 0x1A, 0x0E,
	0x0C, 0x10, 0x18, 0x12, 0x30, 0x14, 0x60, 0x16,
	0xC0, 0x18, 0x48, 0x1A, 0x10, 0x1C, 0x20, 0x1E
};

struct length *length_new(void) {
	struct length *length = calloc(1, sizeof(struct length));
	length->silenced = true;
	return length;
}

void length_reload(struct length *length, uint8_t counter) {
	if (!length->silenced) {
		length->counter = lengths[counter];
	}
}

void length_toggle(struct length *length, bool silenced) {
	length->silenced = silenced;
	if (length->silenced) {
		length->counter = 0x00;
	}
}

void length_tick(struct length *length) {
	if (length->enabled && length->counter > 0x00) {
		length->counter--;
	}
}

void length_destroy(struct length *length) {
	free(length);
}