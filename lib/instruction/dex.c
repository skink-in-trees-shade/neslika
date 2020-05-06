#include "dex.h"

void dex(struct cpu *cpu) {
	cpu->x--;
	cpu_zero(cpu, cpu->x);
	cpu_negative(cpu, cpu->x);
}