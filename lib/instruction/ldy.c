#include "ldy.h"

void ldy(cpu_t *cpu, uint8_t value) {
	cpu->y = value;
	cpu_zero(cpu, cpu->y);
	cpu_negative(cpu, cpu->y);
}