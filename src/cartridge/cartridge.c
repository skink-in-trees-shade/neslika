#include <stdlib.h>
#include "mapper.h"
#include "format/ines.h"
#include "error.h"
#include "cartridge.h"

static uint8_t _cartridge_cpu_read(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	return mappers[cartridge->mapper].cpu_read(cartridge, address);
}

static void _cartridge_cpu_write(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	mappers[cartridge->mapper].cpu_write(cartridge, address, value);
}

static uint8_t _cartridge_ppu_read(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	return mappers[cartridge->mapper].ppu_read(cartridge, address);
}

static void _cartridge_ppu_write(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	mappers[cartridge->mapper].ppu_write(cartridge, address, value);
}

struct cartridge *cartridge_new(struct bus *cpu_bus, struct bus *ppu_bus) {
	struct cartridge *cartridge = calloc(1, sizeof(struct cartridge));

	cartridge->cpu_bus = cpu_bus;
	cartridge->ppu_bus = ppu_bus;

	bus_register(cartridge->cpu_bus, cartridge, 0x8000, 0xFFFF, &_cartridge_cpu_read, &_cartridge_cpu_write);
	bus_register(cartridge->ppu_bus, cartridge, 0x0000, 0x1FFF, &_cartridge_ppu_read, &_cartridge_ppu_write);

	return cartridge;
}

void cartridge_load(struct cartridge *cartridge, const char *filename) {
	if (!ines_load(cartridge, filename)) {
		error("Unknown cartridge format.");
	}

	if (mappers[cartridge->mapper].cpu_read == NULL) {
		error("Unknown mapper %02X.", cartridge->mapper);
	}
}

void cartridge_tick(struct cartridge *cartridge) {
	(void)cartridge;
}

void cartridge_destroy(struct cartridge *cartridge) {
	free(cartridge->chr_rom);
	free(cartridge->prg_rom);
	free(cartridge);
}