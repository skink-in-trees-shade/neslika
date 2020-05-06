#include "plp.h"

void plp(struct cpu *cpu) {
	uint8_t status = cpu_pull(cpu);
	cpu->carry = status & 0x01;
	cpu->zero = status & 0x02;
	cpu->interrupt_disable = status & 0x04;
	cpu->decimal_mode = status & 0x08;
	cpu->overflow = status & 0x40;
	cpu->negative = status & 0x80;
}