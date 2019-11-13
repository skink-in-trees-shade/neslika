#include "jsr.h"

void jsr(cpu_t *cpu) {
	uint16_t return_address = cpu->program_counter - 1;
	uint8_t high = (return_address >> 8) & 0xFF;
	uint8_t low = return_address & 0xFF;
	cpu_push(cpu, high);
	cpu_push(cpu, low);
	cpu->program_counter = cpu->operand;
}