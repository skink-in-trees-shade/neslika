#include "cmp.h"

void cmp(cpu_t *cpu) {
	uint8_t result = cpu->accumulator - cpu->operand;
	cpu->carry = (int8_t)result >= 0x00;
	cpu_zero(cpu, result);
	cpu_negative(cpu, result);
}