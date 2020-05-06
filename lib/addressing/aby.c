#include "aby.h"

void aby(struct cpu *cpu) {
	uint8_t high = cpu->memory[cpu->program_counter++];
	uint8_t low = cpu->memory[cpu->program_counter++];
	cpu->operand_address = (high << 8) + low + cpu->y;
	cpu->operand = cpu->memory[cpu->operand_address];
	cpu->addressing_mode = addressing_absolute_y;
}