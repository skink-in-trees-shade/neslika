#include "aby.h"

uint8_t aby(cpu_t *cpu) {
	uint8_t high = cpu->memory[cpu->program_counter++];
	uint8_t low = cpu->memory[cpu->program_counter++];
	uint8_t address = (high << 8) + low + cpu->y;
	return cpu->memory[address];
}