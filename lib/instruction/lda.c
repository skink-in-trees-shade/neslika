#include "lda.h"

void lda(struct cpu *cpu) {
	cpu->accumulator = cpu->operand;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}