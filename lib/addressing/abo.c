#include "abo.h"

void abo(cpu_t *cpu) {
	uint8_t high = cpu->memory[cpu->program_counter++];
	uint8_t low = cpu->memory[cpu->program_counter++];
	cpu->operand_address = (high << 8) + low;
	cpu->operand = cpu->memory[cpu->operand_address];
	cpu->addressing_mode = addressing_absolute;
}