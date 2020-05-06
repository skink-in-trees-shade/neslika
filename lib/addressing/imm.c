#include "imm.h"

void imm(cpu_t *cpu) {
	cpu->operand_address = cpu->program_counter++;
	cpu->operand = cpu->memory[cpu->operand_address];
	cpu->addressing_mode = addressing_immediate;
}