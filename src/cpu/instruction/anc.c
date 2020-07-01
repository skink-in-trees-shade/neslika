#include "anc.h"

void anc(struct cpu *cpu) {
	cpu->accumulator &= cpu_peek(cpu, cpu->operand);
	cpu->carry = cpu->accumulator & 0x80;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
	cpu->extra_execute_cycle = true;
}