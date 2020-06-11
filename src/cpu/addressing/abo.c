#include "abo.h"

void abo(struct cpu *cpu) {
	uint8_t operand_low = cpu_read(cpu);
	uint8_t operand_high = cpu_read(cpu);
	cpu->operand = (operand_high << 8) | operand_low;
}