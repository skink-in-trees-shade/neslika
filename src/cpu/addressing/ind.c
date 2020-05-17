#include "ind.h"

void ind(struct cpu *cpu) {
	uint8_t low = cpu_read(cpu);
	uint8_t high = cpu_read(cpu);
	cpu->operand_low = cpu_peek(cpu, (high << 8) + low);
	cpu->operand_high = cpu_peek(cpu, (high << 8) + ((low + 1) & 0xFF));
}