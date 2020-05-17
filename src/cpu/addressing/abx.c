#include "abx.h"

void abx(struct cpu *cpu) {
	cpu->operand_low = cpu_read(cpu);
	cpu->operand_high = cpu_read(cpu);

	uint16_t page = cpu->operand & 0xFF00;
	cpu->operand += cpu->x;
	if ((cpu->operand & 0xFF00) != page) {
		cpu->extra_decode_cycle = true;
	}
}