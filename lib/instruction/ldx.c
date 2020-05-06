#include "ldx.h"

void ldx(struct cpu *cpu) {
	cpu->x = cpu->operand;
	cpu_zero(cpu, cpu->x);
	cpu_negative(cpu, cpu->x);
}