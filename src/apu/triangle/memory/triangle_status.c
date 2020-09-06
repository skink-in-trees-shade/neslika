#include "apu/triangle/triangle.h"
#include "triangle_status.h"

void triangle_status(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct triangle *triangle = device;
	triangle->length->enabled = (value & 0x80) == 0x00;
}