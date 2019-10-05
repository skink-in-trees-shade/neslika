#include "iny.h"

uint8_t iny(cpu_t *cpu) {
	uint8_t sub = cpu->memory[cpu->program_counter++];
	uint8_t high = cpu->memory[sub];
	uint8_t low = cpu->memory[sub + 1];
	uint8_t address = (high << 8) + low + cpu->y;
	return cpu->memory[address];
}