#include "bit.h"

void bit(cpu_t *cpu) {
	cpu_zero(cpu, cpu->accumulator & cpu->operand);
	cpu_negative(cpu, cpu->operand);
	cpu->overflow = cpu->operand & 0x40;
}