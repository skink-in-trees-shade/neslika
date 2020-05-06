#include "inx.h"

void inx(struct cpu *cpu) {
	cpu->x++;
	cpu_zero(cpu, cpu->x);
	cpu_negative(cpu, cpu->x);
}