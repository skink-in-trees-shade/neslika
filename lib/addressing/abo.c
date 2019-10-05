#include "abo.h"

uint8_t abo(cpu_t *cpu) {
	uint8_t high = cpu->memory[cpu->program_counter++];
	uint8_t low = cpu->memory[cpu->program_counter++];
	uint8_t address = (high << 8) + low;
	return cpu->memory[address];
}