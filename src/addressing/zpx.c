#include "zpx.h"

void zpx(struct cpu *cpu) {
	cpu->operand_address = cpu_read(cpu) + cpu->x;
	cpu->operand = cpu_peek(cpu, cpu->operand_address);
}