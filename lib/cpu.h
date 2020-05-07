#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "addressing_mode.h"

struct cpu {
	uint16_t program_counter;
	uint8_t stack_pointer;
	uint8_t accumulator;
	uint8_t x;
	uint8_t y;

	bool carry;
	bool zero;
	bool interrupt_disable;
	bool decimal_mode;
	bool break_command;
	bool overflow;
	bool negative;

	uint16_t program_end;
	uint8_t instruction;
	uint8_t operand;
	uint16_t operand_address;
	enum addressing_mode addressing_mode;

	uint8_t *memory;
};

struct cpu *cpu_new(void);
void cpu_load(struct cpu *cpu, uint8_t *rom, size_t size);
void cpu_zero(struct cpu *cpu, uint8_t value);
void cpu_negative(struct cpu *cpu, uint8_t value);
void cpu_push(struct cpu *cpu, uint8_t value);
uint8_t cpu_pull(struct cpu *cpu);
bool cpu_running(struct cpu *cpu);
void cpu_fetch(struct cpu *cpu);
void cpu_decode(struct cpu *cpu);
void cpu_execute(struct cpu *cpu);
void cpu_destroy(struct cpu *cpu);

#endif