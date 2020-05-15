#include "abx.h"

void abx(struct cpu *cpu) {
	uint8_t high = cpu_read(cpu);
	uint8_t low = cpu_read(cpu);
	cpu->operand_address = (high << 8) + low + cpu->x;
	cpu->operand = cpu_peek(cpu, cpu->operand_address);
}