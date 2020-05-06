#include "zpa.h"

void zpa(struct cpu *cpu) {
	cpu->operand_address = cpu->memory[cpu->program_counter++];
	cpu->operand = cpu->memory[cpu->operand_address];
	cpu->addressing_mode = addressing_zero_page;
}