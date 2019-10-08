#include "imm.h"

uint16_t imm(cpu_t *cpu) {
	return cpu->program_counter++;
}