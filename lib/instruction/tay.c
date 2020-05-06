#include "tay.h"

void tay(struct cpu *cpu) {
	cpu->y = cpu->accumulator;
	cpu_zero(cpu, cpu->y);
	cpu_negative(cpu, cpu->y);
}