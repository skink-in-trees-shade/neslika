#include "iiy.h"

void iiy(cpu_t *cpu) {
	uint8_t sub = cpu->memory[cpu->program_counter++];
	uint8_t high = cpu->memory[sub];
	uint8_t low = cpu->memory[sub + 1];
	cpu->operand_address = (high << 8) + low + cpu->y;
	cpu->operand = cpu->memory[cpu->operand_address];
	cpu->addressing_mode = addressing_indirect_indexed;
}