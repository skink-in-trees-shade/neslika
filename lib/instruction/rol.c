#include "../addressing_mode.h"
#include "rol.h"

void rol(struct cpu *cpu) {
	uint16_t result;
	if (cpu->addressing_mode == addressing_implicit) {
		result = (cpu->accumulator << 1) + (cpu->carry ? 0x01 : 0x00);
		cpu->carry = cpu->accumulator & 0x80;
		cpu->accumulator = result;
	} else {
		result = (cpu->operand << 1) + (cpu->carry ? 0x01 : 0x00);
		cpu->carry = cpu->operand & 0x80;
		cpu_poke(cpu, cpu->operand_address, result);
	}
	cpu_zero(cpu, result);
	cpu_negative(cpu, result);
}