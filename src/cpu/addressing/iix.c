#include "iix.h"

void iix(struct cpu *cpu) {
	uint16_t address = cpu_read(cpu) + cpu->x;
	cpu->operand_low = cpu_peek(cpu, address & 0xFF);
	cpu->operand_high = cpu_peek(cpu, (address + 1) & 0xFF);
}