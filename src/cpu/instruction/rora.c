#include "rora.h"

void rora(struct cpu *cpu) {
	uint8_t borrow = cpu->carry ? 0x80 : 0x00;
	cpu->carry = cpu->accumulator & 0x01;
	cpu->accumulator >>= 1;
	cpu->accumulator += borrow;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}