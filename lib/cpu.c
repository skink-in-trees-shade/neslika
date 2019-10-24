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
	cpu->program_end = cpu->program_counter + size - 1;
	memcpy(&cpu->memory[cpu->program_counter], rom, size);
}

void cpu_carry(cpu_t *cpu, uint8_t value) {
	cpu->carry = (int8_t)value >= 0x00;
}

void cpu_zero(cpu_t *cpu, uint8_t value) {
	cpu->zero = value == 0x00;
}

void cpu_negative(cpu_t *cpu, uint8_t value) {
	cpu->negative = value & 0x80;
}

bool cpu_running(cpu_t *cpu) {
	return cpu->program_counter < cpu->program_end + 1;
}

void cpu_fetch(cpu_t *cpu) {
	cpu->instruction = cpu->memory[cpu->program_counter++];
}

void cpu_decode(cpu_t *cpu) {
	cpu->operand_address = addressing_table[cpu->instruction](cpu);
	cpu->operand = cpu->memory[cpu->operand_address];
}

void cpu_execute(cpu_t *cpu) {
	instruction_table[cpu->instruction](cpu);
}

void cpu_destroy(cpu_t *cpu) {
	free(cpu->memory);
	free(cpu);
}