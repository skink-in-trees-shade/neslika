#include "iiy.h"

void iiy(struct cpu *cpu) {
	uint16_t address = cpu_read(cpu);
	cpu->operand_low = cpu_peek(cpu, address);
	cpu->operand_high = cpu_peek(cpu, (address + 1) & 0xFF);
	cpu->operand += cpu->y;
}