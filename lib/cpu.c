#include <stdlib.h>
#include "cpu.h"

cpu_t *cpu_new(void) {
	cpu_t *cpu = calloc(1, sizeof(cpu_t));
	cpu->memory = calloc(0x10000, sizeof(uint8_t));
	return cpu;
}

void cpu_run(cpu_t *cpu) {
	while (1) {
		uint8_t code = cpu->memory[cpu->program_counter++];
		if (code == 0) {
			break;
		}
	}
}

void cpu_destroy(cpu_t *cpu) {
	free(cpu->memory);
	free(cpu);
}