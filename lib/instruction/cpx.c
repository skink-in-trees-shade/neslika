#include "cpx.h"

void cpx(struct cpu *cpu) {
	uint8_t result = cpu->x - cpu->operand;
	cpu_carry(cpu, result);
	cpu_zero(cpu, result);
	cpu_negative(cpu, result);
}