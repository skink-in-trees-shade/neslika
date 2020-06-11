#include "zpy.h"

void zpy(struct cpu *cpu) {
	uint8_t operand_low = cpu_read(cpu);
	cpu->operand = (operand_low + cpu->y) & 0x00FF;
}