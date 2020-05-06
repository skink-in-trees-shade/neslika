#include "eor.h"

void eor(struct cpu *cpu) {
	cpu->accumulator ^= cpu->operand;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}