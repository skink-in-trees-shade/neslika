#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>
#include "ppu/screen.h"
#include "bus.h"

struct controller {
	struct bus *bus;
	struct screen *screen;

	bool write_toggle;
	uint8_t player_one;
	uint8_t player_two;
};

struct controller *controller_new(struct bus *bus);
void controller_tick(struct controller *controller);
void controller_destroy(struct controller *controller);

#endif