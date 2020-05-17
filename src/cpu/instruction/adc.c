#include "adc.h"

void adc(struct cpu *cpu) {
	uint8_t operand = cpu_peek(cpu, cpu->operand);
	uint16_t result = cpu->accumulator + operand + (cpu->carry ? 0x01 : 0x00);
	cpu->carry = result > 0xFF;
	cpu->overflow = (cpu->accumulator ^ result) & (operand ^ result) & 0x80;
	cpu->accumulator = result & 0xFF;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}