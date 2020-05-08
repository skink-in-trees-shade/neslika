#include "../addressing_mode.h"
#include "ror.h"

void ror(struct cpu *cpu) {
	uint16_t result;
	if (cpu->addressing_mode == addressing_implicit) {
		result = (cpu->accumulator >> 1) + (cpu->carry ? 0x80 : 0x00);
		cpu->carry = cpu->accumulator & 0x01;
		cpu->accumulator = result;
	} else {
		result = (cpu->operand >> 1) + (cpu->carry ? 0x80 : 0x00);
		cpu->carry = cpu->operand & 0x01;
		cpu->operand = result;
	}
	cpu_zero(cpu, result);
	cpu_negative(cpu, result);
}