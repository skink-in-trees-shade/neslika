#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "ines.h"

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

void ines_load(struct cpu *cpu, const char *filename) {
	FILE *file = fopen(filename, "rb");

	struct ines_header header;
	fread(&header, sizeof(header), 1, file);

	size_t prg_rom_size = header.prg_rom_count * 0x4000;
	uint8_t *prg_rom = malloc(prg_rom_size);
	fread(prg_rom, prg_rom_size, 1, file);

	cpu_load(cpu, prg_rom, prg_rom_size);

	free(prg_rom);

	fclose(file);
}