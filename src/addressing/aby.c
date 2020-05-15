#include "aby.h"

void aby(struct cpu *cpu) {
	uint8_t high = cpu_read(cpu);
	uint8_t low = cpu_read(cpu);
	cpu->operand_address = (high << 8) + low + cpu->y;
	cpu->operand = cpu_peek(cpu, cpu->operand_address);
}