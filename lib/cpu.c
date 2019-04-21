#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "table.h"
#include "cpu.h"

cpu_t *cpu_new(void) {
	cpu_t *cpu = calloc(1, sizeof(cpu_t));
	cpu->memory = calloc(0x10000, sizeof(uint8_t));
	return cpu;
}

void cpu_load(cpu_t *cpu, uint8_t *rom) {
	cpu->program_counter = 0x8000;
	memcpy(&cpu->memory[0x8000], rom, sizeof(uint8_t) * 0x4000);
}

void cpu_run(cpu_t *cpu) {
	while (1) {
		debug_opcode(cpu);

		uint8_t code = cpu->memory[cpu->program_counter++];
		opcode_t opcode = table[code];
		if (opcode.addressing_mode == NULL || opcode.instruction == NULL) {
			break;
		}

		uint16_t addr = opcode.addressing_mode(cpu);
		uint8_t value = cpu->memory[addr];
		opcode.instruction(cpu, value);

		debug_state(cpu);
	}
}

void cpu_destroy(cpu_t *cpu) {
	free(cpu->memory);
	free(cpu);
}