#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>
#include "ppu/screen.h"
#include "device.h"

struct controller {
	struct device device;
	struct screen *screen;

	bool write_toggle;
	uint8_t state_p1;
	uint8_t state_p2;
};

struct controller *controller_new(void);
void controller_tick(struct controller *controller);
void controller_destroy(struct controller *controller);

#endif