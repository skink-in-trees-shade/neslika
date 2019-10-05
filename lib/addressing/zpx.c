#include "zpx.h"

uint8_t zpx(cpu_t *cpu) {
	uint8_t address = cpu->memory[cpu->program_counter++] + cpu->x;
	return cpu->memory[address];
}