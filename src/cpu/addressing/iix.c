#include "iix.h"

void iix(struct cpu *cpu) {
	uint16_t address = cpu_read(cpu) + cpu->x;
	uint8_t operand_low = cpu_peek(cpu, address & 0xFF);
	uint8_t operand_high = cpu_peek(cpu, (address + 1) & 0xFF);
	cpu->operand = (operand_high << 8) | operand_low;
}