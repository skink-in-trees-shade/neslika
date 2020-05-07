#include "zpy.h"

void zpy(struct cpu *cpu) {
	cpu->operand_address = cpu_read(cpu) + cpu->y;
	cpu->operand = cpu_peek(cpu, cpu->operand_address);
	cpu->addressing_mode = addressing_zero_page_y;
}