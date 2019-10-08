#include <stdlib.h>
#include <string.h>
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
	cpu->powered = true;
	memcpy(&cpu->memory[0x8000], rom, size);
}

void cpu_negative(cpu_t *cpu, uint8_t value) {
	cpu->negative = value & 0x80;
}

void cpu_zero(cpu_t *cpu, uint8_t value) {
	cpu->zero = value == 0;
}

void cpu_fetch(cpu_t *cpu) {
	cpu->instruction = cpu->memory[cpu->program_counter++];
	if (cpu->instruction == 0xEA) {
		cpu->powered = false;
	}
}

void cpu_decode(cpu_t *cpu) {
	if (addressing_table[cpu->instruction] != NULL) {
		cpu->operand = addressing_table[cpu->instruction](cpu);
	}
}

void cpu_execute(cpu_t *cpu) {
	if (instruction_table[cpu->instruction] != NULL) {
		uint8_t value = cpu->memory[cpu->operand];
		instruction_table[cpu->instruction](cpu, value);
	}
}

void cpu_destroy(cpu_t *cpu) {
	free(cpu->memory);
	free(cpu);
}