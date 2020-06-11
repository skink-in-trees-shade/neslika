#include "zpx.h"

void zpx(struct cpu *cpu) {
	uint8_t operand_low = cpu_read(cpu);
	cpu->operand = (operand_low + cpu->x) & 0x00FF;
}