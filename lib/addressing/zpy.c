#include "zpy.h"

void zpy(cpu_t *cpu) {
	cpu->operand_address = cpu->memory[cpu->program_counter++] + cpu->y;
	cpu->operand = cpu->memory[cpu->operand_address];
	cpu->addressing_mode = addressing_zero_page_y;
}