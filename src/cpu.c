#include <stdlib.h>
#include <string.h>
#include "addressing_table.h"
#include "instruction_table.h"
#include "cpu.h"

struct cpu *cpu_new(void) {
	struct cpu *cpu = calloc(1, sizeof(struct cpu));
	cpu->memory = calloc(0x10000, sizeof(uint8_t));
	return cpu;
}

void cpu_load(struct cpu *cpu, uint8_t *rom, size_t size) {
	cpu->stack_pointer = 0xFD;
	cpu->program_counter = 0xC000; 
	cpu->interrupt_disable = true;
	cpu->program_end = cpu->program_counter + size - 1;
	memcpy(&cpu->memory[0x4000], rom, size);
	memcpy(&cpu->memory[0x8000], rom, size);
	memcpy(&cpu->memory[0xC000], rom, size);
}

void cpu_zero(struct cpu *cpu, uint8_t value) {
	cpu->zero = value == 0x00;
}

void cpu_negative(struct cpu *cpu, uint8_t value) {
	cpu->negative = value & 0x80;
}

uint8_t cpu_read(struct cpu *cpu) {
	return cpu_peek(cpu, cpu->program_counter++);
}

uint8_t cpu_peek(struct cpu *cpu, uint16_t address) {
	return cpu->memory[address];
}

void cpu_poke(struct cpu *cpu, uint16_t address, uint8_t value) {
	cpu->memory[address] = value;
}

void cpu_push(struct cpu *cpu, uint8_t value) {
	cpu_poke(cpu, 0x0100 + cpu->stack_pointer--, value);
}

uint8_t cpu_pull(struct cpu *cpu) {
	return cpu_peek(cpu, 0x0100 + ++cpu->stack_pointer);
}

bool cpu_running(struct cpu *cpu) {
	return cpu->program_counter < cpu->program_end + 1;
}

void cpu_fetch(struct cpu *cpu) {
	cpu->instruction = cpu_read(cpu);
}

void cpu_decode(struct cpu *cpu) {
	addressing_table[cpu->instruction](cpu);
}

void cpu_execute(struct cpu *cpu) {
	instruction_table[cpu->instruction](cpu);
}

void cpu_destroy(struct cpu *cpu) {
	free(cpu->memory);
	free(cpu);
}