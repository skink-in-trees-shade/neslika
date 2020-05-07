#include "../addressing_mode.h"
#include "asl.h"

void asl(struct cpu *cpu) {
	uint16_t result;
	if (cpu->addressing_mode == addressing_implicit) {
		result = cpu->accumulator << 1;
		cpu->carry = cpu->accumulator & 0x80;
		cpu->accumulator = result;
	} else {
		result = cpu->operand << 1;
		cpu->carry = cpu->operand & 0x80;
		cpu->operand = result;
	}
	cpu_zero(cpu, result);
	cpu_negative(cpu, result);
}