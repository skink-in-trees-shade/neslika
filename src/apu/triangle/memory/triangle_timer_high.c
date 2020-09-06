#include "apu/triangle/triangle.h"
#include "triangle_timer_high.h"

void triangle_timer_high(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct triangle *triangle = device;
	triangle->reload = ((uint16_t)(value & 0x07) << 8) | (triangle->reload & 0x00FF);
	triangle->timer = triangle->reload;
	triangle->step = -0x01;
	triangle->volume = 0x0F;
	length_reload(triangle->length, (value & 0xF8) >> 3);
}