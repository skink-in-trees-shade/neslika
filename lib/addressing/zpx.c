#include "zpx.h"

void zpx(struct cpu *cpu) {
	cpu->operand_address = cpu->memory[cpu->program_counter++] + cpu->x;
	cpu->operand = cpu->memory[cpu->operand_address];
	cpu->addressing_mode = addressing_zero_page_x;
}