#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "addressing_table.h"
#include "instruction_table.h"
#include "cpu.h"

cpu_t *cpu_new(void) {
	cpu_t *cpu = calloc(1, sizeof(cpu_t));
	cpu->memory = calloc(0x10000, sizeof(uint8_t));
	return cpu;
}

void cpu_load(cpu_t *cpu, uint8_t *rom, size_t size) {
	cpu->program_counter = 0x8000;
	memcpy(&cpu->memory[0x8000], rom, size);
}

void cpu_negative(cpu_t *cpu, uint8_t value) {
	cpu->negative = value & 0x80;
}

void cpu_zero(cpu_t *cpu, uint8_t value) {
	cpu->zero = value == 0;
}

void cpu_run(cpu_t *cpu) {
	while (1) {
		debug_opcode(cpu);

		uint8_t code = cpu->memory[cpu->program_counter++];
		if (code == 0xEA) {
			break;
		}

		if (addressing_table[code] != NULL && instruction_table[code] != NULL) {
			uint16_t addr = addressing_table[code](cpu);
			uint8_t value = cpu->memory[addr];
			instruction_table[code](cpu, value);

			debug_state(cpu);
		}
	}
}

void cpu_destroy(cpu_t *cpu) {
	free(cpu->memory);
	free(cpu);
}