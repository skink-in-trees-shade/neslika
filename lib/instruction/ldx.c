#include "ldx.h"

void ldx(cpu_t *cpu, uint8_t value) {
	cpu->x = value;
	cpu_zero(cpu, cpu->x);
	cpu_negative(cpu, cpu->x);
}