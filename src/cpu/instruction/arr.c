#include "arr.h"

void arr(struct cpu *cpu) {
	uint8_t borrow = cpu->carry ? 0x80 : 0x00;
	cpu->accumulator &= cpu_peek(cpu, cpu->operand);
	cpu->accumulator >>= 1;
	cpu->accumulator += borrow;
	cpu->carry = cpu->accumulator & 0x40;
	cpu->overflow = ((cpu->accumulator >> 5) ^ (cpu->accumulator >> 6)) & 0x01;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
	cpu->extra_execute_cycle = true;
}