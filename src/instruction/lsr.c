#include "lsr.h"

void lsr(struct cpu *cpu) {
	uint16_t result;
	if (cpu->instruction == 0x4A) {
		result = cpu->accumulator >> 1;
		cpu->carry = cpu->accumulator & 0x01;
		cpu->accumulator = result;
	} else {
		result = cpu->operand >> 1;
		cpu->carry = cpu->operand & 0x01;
		cpu_poke(cpu, cpu->operand_address, result);
	}
	cpu_zero(cpu, result);
	cpu_negative(cpu, result);
}