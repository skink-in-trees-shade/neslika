#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "mapper.h"
#include "format/ines.h"
#include "cartridge.h"

static uint8_t _cartridge_read(struct device *device, uint16_t address) {
	struct cartridge *cartridge = (struct cartridge *)device;
	address = mappers[cartridge->mapper].map(cartridge, address);
	return cartridge->prg_rom[address];
}

static void _cartridge_write(struct device *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = (struct cartridge *)device;
	address = mappers[cartridge->mapper].map(cartridge, address);
	cartridge->prg_rom[address] = value;
}

struct cartridge *cartridge_new(void) {
	struct cartridge *cartridge = calloc(1, sizeof(struct cartridge));
	cartridge->prg_rom = calloc(0x4000, sizeof(uint8_t));
	cartridge->device.address_from = 0x8000;
	cartridge->device.address_to = 0xFFFF;
	cartridge->device.read = &_cartridge_read;
	cartridge->device.write = &_cartridge_write;
	return cartridge;
}

void cartridge_load(struct cartridge *cartridge, const char *filename) {
	ines_load(cartridge, filename);
}

void cartridge_destroy(struct cartridge *cartridge) {
	free(cartridge->prg_rom);
	free(cartridge);
}