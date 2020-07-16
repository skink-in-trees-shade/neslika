#include <stdlib.h>
#include "bus.h"

struct handler {
	void *device;
	uint16_t from;
	uint16_t to;
	read_callback *read;
	write_callback *write;
};

struct bus {
	struct handler *handlers;
	size_t next_handler_index;
};

struct bus *bus_new(void) {
	struct bus *bus = calloc(1, sizeof(struct bus));
	bus->handlers = calloc(10, sizeof(struct handler));
	return bus;
}

void bus_register(struct bus *bus, void *device, uint16_t from, uint16_t to, read_callback *read, write_callback *write) {
	struct handler *handler = &bus->handlers[bus->next_handler_index++];
	handler->device = device;
	handler->from = from;
	handler->to = to;
	handler->read = read;
	handler->write = write;
}

uint8_t bus_read(struct bus *bus, uint16_t address) {
	for (size_t i = 0; i < bus->next_handler_index; i++) {
		struct handler *handler = &bus->handlers[i];
		if (handler->from <= address && handler->to >= address && handler->read) {
			return handler->read(handler->device, address);
		}
	}
	return 0x00;
}

void bus_write(struct bus *bus, uint16_t address, uint8_t value) {
	for (size_t i = 0; i < bus->next_handler_index; i++) {
		struct handler *handler = &bus->handlers[i];
		if (handler->from <= address && handler->to >= address && handler->write) {
			handler->write(handler->device, address, value);
			return;
		}
	}
}

void bus_destroy(struct bus *bus) {
	free(bus->handlers);
	free(bus);
}