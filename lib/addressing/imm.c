#include "imm.h"

uint8_t imm(cpu_t *cpu) {
	uint8_t address = cpu->program_counter++;
	return cpu->memory[address];
}