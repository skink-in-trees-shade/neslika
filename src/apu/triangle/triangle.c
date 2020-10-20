#include <stdlib.h>
#include "memory/triangle_status.h"
#include "memory/triangle_timer_low.h"
#include "memory/triangle_timer_high.h"
#include "triangle.h"

struct triangle *triangle_new(struct bus *bus) {
	struct triangle *triangle = calloc(1, sizeof(struct triangle));
	triangle->bus = bus;
	triangle->length = length_new();

	bus_register(triangle->bus, triangle, 0x4008, 0x4008, NULL, &triangle_status);
	bus_register(triangle->bus, triangle, 0x400A, 0x400A, NULL, &triangle_timer_low);
	bus_register(triangle->bus, triangle, 0x400B, 0x400B, NULL, &triangle_timer_high);

	return triangle;
}

void triangle_tick(struct triangle *triangle) {
	if (triangle->enabled) {
		triangle->timer--;
		if (triangle->timer == 0xFFFF) {
			triangle->timer = triangle->reload + 1;

			if (triangle->step != 0x00) {
				triangle->volume += triangle->step;
				if (triangle->volume % 0x0F == 0x00) {
					triangle->step = 0x00;
				}
			} else {
				triangle->step = triangle->volume == 0x00 ? 0x01 : -0x01;
			}
		}
	}
}

void triangle_half_frame_tick(struct triangle *triangle) {
	length_tick(triangle->length);
}

uint8_t triangle_sample(struct triangle *triangle) {
	if (!triangle->enabled || triangle->length->counter == 0x00) {
		return 0x00;
	}

	return triangle->volume;
}

void triangle_destroy(struct triangle *triangle) {
	length_destroy(triangle->length);
	free(triangle);
}