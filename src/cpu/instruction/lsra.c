#include "lsra.h"

void lsra(struct cpu *cpu) {
	cpu->carry = cpu->accumulator & 0x01;
	cpu->accumulator >>= 1;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}