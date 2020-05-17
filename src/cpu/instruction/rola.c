#include "rola.h"

void rola(struct cpu *cpu) {
	uint8_t carry = cpu->carry ? 0x01 : 0x00;
	cpu->carry = cpu->accumulator & 0x80;
	cpu->accumulator <<= 1;
	cpu->accumulator += carry;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}