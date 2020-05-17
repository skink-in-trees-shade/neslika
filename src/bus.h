#ifndef BUS_H
#define BUS_H

#include <stdint.h>
#include "device.h"

struct bus;

struct bus *bus_new(void);
void bus_attach(struct bus *bus, struct device *device);
uint8_t bus_read(struct bus *bus, uint16_t address);
void bus_write(struct bus *bus, uint16_t address, uint8_t value);
void bus_destroy(struct bus *bus);

#endif