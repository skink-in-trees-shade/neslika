#include "abx.h"

void abx(struct cpu *cpu) {
	uint8_t operand_low = cpu_read(cpu);
	uint8_t operand_high = cpu_read(cpu);
	cpu->operand = (operand_high << 8) | operand_low;

	uint16_t page = cpu->operand & 0xFF00;
	cpu->operand += cpu->x;
	if (cpu->instruction == 0x3E) {
		cpu_peek(cpu, page | (cpu->operand & 0x00FF));
	}
	if ((cpu->operand & 0xFF00) != page) {
		cpu_peek(cpu, page | (cpu->operand & 0x00FF));
		cpu->extra_decode_cycle = true;
	}
}