#include "tya.h"

void tya(cpu_t *cpu) {
	cpu->accumulator = cpu->y;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}