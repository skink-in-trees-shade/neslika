#include "iiy.h"

void iiy(struct cpu *cpu) {
	uint8_t sub = cpu_read(cpu);
	uint8_t high = cpu_peek(cpu, sub);
	uint8_t low = cpu_peek(cpu, sub + 1);
	cpu->operand_address = (high << 8) + low + cpu->y;
	cpu->operand = cpu_peek(cpu, cpu->operand_address);
	cpu->addressing_mode = addressing_indirect_indexed;
}