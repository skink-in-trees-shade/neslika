#include "iiy.h"

void iiy(struct cpu *cpu) {
	uint16_t address = cpu_read(cpu);
	uint8_t operand_low = cpu_peek(cpu, address);
	uint8_t operand_high = cpu_peek(cpu, (address + 1) & 0xFF);
	cpu->operand = (operand_high << 8) | operand_low;

	uint16_t page = cpu->operand & 0xFF00;
	cpu->operand += cpu->y;
	if ((cpu->operand & 0xFF00) != page) {
		cpu_peek(cpu, page | (cpu->operand & 0x00FF));
		cpu->extra_decode_cycle = true;
	}
}