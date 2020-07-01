#include "alr.h"

void alr(struct cpu *cpu) {
	uint8_t operand = cpu_peek(cpu, cpu->operand);
	cpu->accumulator &= operand;
	cpu->carry = cpu->accumulator & 0x01;
	cpu->accumulator >>= 1;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
	cpu->extra_execute_cycle = true;
}