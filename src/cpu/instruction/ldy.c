#include "ldy.h"

void ldy(struct cpu *cpu) {
	cpu->y = cpu_peek(cpu, cpu->operand);
	cpu_zero(cpu, cpu->y);
	cpu_negative(cpu, cpu->y);
	cpu->extra_execute_cycle = true;
}