#include "rts.h"

void rts(struct cpu *cpu) {
	uint8_t low = cpu_pull(cpu);
	uint8_t high = cpu_pull(cpu);
	uint16_t return_address = (low | (high << 8)) + 1;
	cpu->program_counter = return_address;
}