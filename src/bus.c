#include <stdlib.h>
#include "bus.h"

struct bus {
	struct device **devices;
	size_t next_device_index;
};

struct bus *bus_new(void) {
	struct bus *bus = calloc(1, sizeof(struct bus));
	bus->devices = calloc(10, sizeof(struct device *));
	return bus;
}

void bus_attach(struct bus *bus, struct device *device) {
	bus->devices[bus->next_device_index++] = device;
}

uint8_t bus_read(struct bus *bus, uint16_t address) {
	for (size_t i = 0; i < bus->next_device_index; i++) {
		struct device *device = bus->devices[i];
		if (device->address_from <= address && device->address_to >= address) {
			return device->read(device, address);
		}
	}
	return 0x00;
}

void bus_write(struct bus *bus, uint16_t address, uint8_t value) {
	for (size_t i = 0; i < bus->next_device_index; i++) {
		struct device *device = bus->devices[i];
		if (device->address_from <= address && device->address_to >= address) {
			device->write(device, address, value);
		}
	}
}

void bus_destroy(struct bus *bus) {
	free(bus->devices);
	free(bus);
}