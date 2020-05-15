#include "pla.h"

void pla(struct cpu *cpu) {
	cpu->accumulator = cpu_pull(cpu);
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}