#include "txa.h"

void txa(cpu_t *cpu) {
	cpu->accumulator = cpu->x;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}