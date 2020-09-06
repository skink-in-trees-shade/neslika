#ifndef LENGTH_H
#define LENGTH_H

#include <stdint.h>
#include <stdbool.h>

struct length {
	bool enabled;
	bool silenced;
	uint8_t counter;
};

struct length *length_new(void);
void length_reload(struct length *length, uint8_t counter);
void length_toggle(struct length *length, bool silenced);
void length_tick(struct length *length);
void length_destroy(struct length *length);

#endif