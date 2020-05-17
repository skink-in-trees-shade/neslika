#include "txa.h"

void txa(struct cpu *cpu) {
	cpu->accumulator = cpu->x;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}