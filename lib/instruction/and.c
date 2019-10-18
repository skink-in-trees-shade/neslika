#include "and.h"

void and(cpu_t *cpu) {
	cpu->accumulator &= cpu->operand;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}