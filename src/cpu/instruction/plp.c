#include "plp.h"

void plp(struct cpu *cpu) {
	uint8_t status = cpu_pull(cpu);
	cpu->carry = (status >> 0) & 0x01;
	cpu->zero = (status >> 1) & 0x01;
	cpu->interrupt_disable = (status >> 2) & 0x01;
	cpu->decimal_mode = (status >> 3) & 0x01;
	cpu->break_command = (status >> 4) & 0x01;
	cpu->overflow = (status >> 6) & 0x01;
	cpu->negative = (status >> 7) & 0x01;
	cpu->interrupt_disable_shifter |= 0x04 | (cpu->interrupt_disable << 3);
}