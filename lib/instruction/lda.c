#include "lda.h"

void lda(cpu_t *cpu, uint8_t value) {
	cpu->accumulator = value;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}