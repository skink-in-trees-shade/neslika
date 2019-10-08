#include "ldy.h"

void ldy(cpu_t *cpu) {
	cpu->y = cpu->operand;
	cpu_zero(cpu, cpu->y);
	cpu_negative(cpu, cpu->y);
}