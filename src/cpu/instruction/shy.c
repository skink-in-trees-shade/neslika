#include "shy.h"

void shy(struct cpu *cpu) {
	uint8_t operand_low = cpu->operand & 0xFF;
	uint8_t operand_high = cpu->operand >> 8;
	uint8_t value = cpu->y & (operand_high + 1);
	uint16_t address = (value << 8) | operand_low;
	cpu_poke(cpu, address, value);
}