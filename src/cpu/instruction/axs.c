#include "axs.h"

void axs(struct cpu *cpu) {
	uint8_t operand = cpu_peek(cpu, cpu->operand);
	uint8_t result = (cpu->accumulator & cpu->x) - operand;
	cpu->carry = (cpu->accumulator & cpu->x) >= operand;
	cpu->x = result;
	cpu_zero(cpu, cpu->x);
	cpu_negative(cpu, cpu->x);
	cpu->extra_execute_cycle = true;
}