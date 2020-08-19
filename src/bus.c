#include <stdlib.h>
#include "bus.h"

struct handler {
	void *read_device;
	read_callback *read;
	void *write_device;
	write_callback *write;
};

struct bus {
	struct handler *handlers;
};

struct bus *bus_new(uint32_t size) {
	struct bus *bus = calloc(1, sizeof(struct bus));
	bus->handlers = calloc(size, sizeof(struct handler));
	return bus;
}

void bus_register(struct bus *bus, void *device, uint16_t from, uint16_t to, read_callback *read, write_callback *write) {
	for (uint32_t i = from; i <= to; i++) {
		struct handler *handler = &bus->handlers[i];
		if (!handler->read && read) {
			handler->read = read;
			handler->read_device = device;
		}
		if (!handler->write && write) {
			handler->write = write;
			handler->write_device = device;
		}
	}
}

uint8_t bus_read(struct bus *bus, uint16_t address) {
	struct handler *handler = &bus->handlers[address];
	if (handler->read) {
		return handler->read(handler->read_device, address);
	}
	return 0x00;
}

void bus_write(struct bus *bus, uint16_t address, uint8_t value) {
	struct handler *handler = &bus->handlers[address];
	if (handler->write) {
		handler->write(handler->write_device, address, value);
	}
}

void bus_destroy(struct bus *bus) {
	free(bus->handlers);
	free(bus);
}