#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "ines.h"

#pragma pack(push, 1)
struct header {
	char signature[4];
	uint8_t prg_rom_count;
	uint8_t chr_rom_count;
	bool vertical_mirroring: 1;
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

static bool is_ines(struct header *header) {
	return strncmp(header->signature, "NES\x1A", sizeof(header->signature)) == 0 && header->version != 2;
}

bool ines_load(struct cartridge *cartridge, const char *filename) {
	FILE *file = fopen(filename, "rb");

	struct header header;
	fread(&header, sizeof(header), 1, file);

	if (is_ines(&header)) {
		cartridge->mapper = (header.mapper_high << 8) + header.mapper_low;
		cartridge->vertical_mirroring = header.vertical_mirroring;

		cartridge->prg_rom_count = header.prg_rom_count;
		cartridge->prg_rom = calloc(0x4000 * cartridge->prg_rom_count, sizeof(uint8_t));
		fread(cartridge->prg_rom, 0x4000, cartridge->prg_rom_count, file);

		bool has_chr_rom = header.chr_rom_count > 0;
		cartridge->chr_rom_count = has_chr_rom ? header.chr_rom_count : 1;
		cartridge->chr_rom = calloc(0x2000 * cartridge->chr_rom_count, sizeof(uint8_t));
		if (has_chr_rom) {
			fread(cartridge->chr_rom, 0x2000, cartridge->chr_rom_count, file);
		}

		fclose(file);
		return true;
	}

	fclose(file);
	return false;
}