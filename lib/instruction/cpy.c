#include "cpy.h"

void cpy(cpu_t *cpu) {
	uint8_t result = cpu->y - cpu->operand;
	cpu_carry(cpu, result);
	cpu_zero(cpu, result);
	cpu_negative(cpu, result);
}