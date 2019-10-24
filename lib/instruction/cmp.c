#include "cmp.h"

void cmp(cpu_t *cpu) {
	uint8_t result = cpu->accumulator - cpu->operand;
	cpu_carry(cpu, result);
	cpu_zero(cpu, result);
	cpu_negative(cpu, result);
}