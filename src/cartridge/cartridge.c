#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "mapper.h"
#include "cartridge.h"

#pragma pack(push, 1)
struct ines_header {
	char signature[4];
	uint8_t prg_rom_count;
	uint8_t chr_rom_count;
	bool horizontal_mirroring: 1;
	bool has_prg_ram: 1;
	bool has_trainer: 1;
	bool ignore_mirroring: 1;
	uint8_t mapper_low: 4;
	bool vs_unisystem: 1;
	bool playchoice10: 1;
	uint8_t version: 2;
	uint8_t mapper_high: 4;
	uint8_t prg_ram_count;
	bool tv_ntsc: 1;
	uint8_t reserved1: 7;
	uint8_t reserved2;
	uint8_t reserved3[5];
};
#pragma pack(pop)

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
	FILE *file = fopen(filename, "rb");

	struct ines_header header;
	fread(&header, sizeof(header), 1, file);

	cartridge->mapper = (header.mapper_high << 8) + header.mapper_low;
	cartridge->prg_rom_count = header.prg_rom_count;
	fread(cartridge->prg_rom, 0x4000, cartridge->prg_rom_count, file);

	fclose(file);
}

void cartridge_destroy(struct cartridge *cartridge) {
	free(cartridge->prg_rom);
	free(cartridge);
}