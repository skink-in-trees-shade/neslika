#ifndef BUS_H
#define BUS_H

#include <stdint.h>

struct bus;

typedef uint8_t (read_callback)(void *device, uint16_t address);
typedef void (write_callback)(void *device, uint16_t address, uint8_t value);

struct bus *bus_new(uint32_t size);
void bus_register(struct bus *bus, void *device, uint16_t from, uint16_t to, read_callback *read, write_callback *write);
uint8_t bus_read(struct bus *bus, uint16_t address);
void bus_write(struct bus *bus, uint16_t address, uint8_t value);
void bus_destroy(struct bus *bus);

#endif