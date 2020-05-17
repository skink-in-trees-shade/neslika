#ifndef DEVICE_H
#define DEVICE_H

#include <stdint.h>

struct device {
	uint16_t address_from;
	uint16_t address_to;
	uint8_t (*read)(struct device *device, uint16_t address);
	void (*write)(struct device *device, uint16_t address, uint8_t value);
};

#endif