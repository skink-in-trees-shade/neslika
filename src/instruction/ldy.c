#include "ldy.h"

void ldy(struct cpu *cpu) {
	cpu->y = cpu->operand;
	cpu_zero(cpu, cpu->y);
	cpu_negative(cpu, cpu->y);
}