#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdbool.h>
#include "bus.h"

struct triangle {
	struct bus *bus;

	bool enabled;
	uint16_t timer;
	uint16_t reload;
	int8_t step;
	uint8_t volume;
};

struct triangle *triangle_new(struct bus *bus);
void triangle_tick(struct triangle *triangle);
double triangle_sample(struct triangle *triangle);
void triangle_destroy(struct triangle *triangle);

#endif