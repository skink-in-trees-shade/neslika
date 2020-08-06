#include "apu/triangle/triangle.h"
#include "triangle_timer_low.h"

void triangle_timer_low(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct triangle *triangle = device;
	triangle->reload = (triangle->reload & 0xFF00) | value;
}