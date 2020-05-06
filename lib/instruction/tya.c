#include "tya.h"

void tya(struct cpu *cpu) {
	cpu->accumulator = cpu->y;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}