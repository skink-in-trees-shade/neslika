#include "iix.h"

void iix(struct cpu *cpu) {
	uint8_t sub = cpu_read(cpu);
	uint8_t high = cpu_peek(cpu, sub + cpu->x);
	uint8_t low = cpu_peek(cpu, sub + cpu->x + 1);
	cpu->operand_address = (high << 8) + low;
	cpu->operand = cpu_peek(cpu, cpu->operand_address);
	cpu->addressing_mode = addressing_indexed_indirect;
}