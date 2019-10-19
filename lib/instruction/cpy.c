#include "cpy.h"

void cpy(cpu_t *cpu) {
	uint8_t result = cpu->y - cpu->operand;
	cpu->carry = (int8_t)result >= 0x00;
	cpu_zero(cpu, result);
	cpu_negative(cpu, result);
}