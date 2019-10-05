#include "abx.h"

uint8_t abx(cpu_t *cpu) {
	uint8_t high = cpu->memory[cpu->program_counter++];
	uint8_t low = cpu->memory[cpu->program_counter++];
	uint8_t address = (high << 8) + low + cpu->x;
	return cpu->memory[address];
}