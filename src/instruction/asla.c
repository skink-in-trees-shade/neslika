#include "asla.h"

void asla(struct cpu *cpu) {
	cpu->carry = cpu->accumulator & 0x80;
	cpu->accumulator <<= 1;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}