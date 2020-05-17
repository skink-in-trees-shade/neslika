#include "dey.h"

void dey(struct cpu *cpu) {
	cpu->y--;
	cpu_zero(cpu, cpu->y);
	cpu_negative(cpu, cpu->y);
}