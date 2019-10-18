#include "ora.h"

void ora(cpu_t *cpu) {
	cpu->accumulator |= cpu->operand;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}