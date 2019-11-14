#include "pla.h"

void pla(cpu_t *cpu) {
	cpu->accumulator = cpu_pull(cpu);
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}