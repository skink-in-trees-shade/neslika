#include "iix.h"

void iix(struct cpu *cpu) {
	uint8_t sub = cpu->memory[cpu->program_counter++];
	uint8_t high = cpu->memory[sub + cpu->x];
	uint8_t low = cpu->memory[sub + cpu->x + 1];
	cpu->operand_address = (high << 8) + low;
	cpu->operand = cpu->memory[cpu->operand_address];
	cpu->addressing_mode = addressing_indexed_indirect;
}