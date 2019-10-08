#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
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

	bool powered;
	uint8_t instruction;
	uint8_t operand;

	uint8_t *memory;
} cpu_t;

cpu_t *cpu_new(void);
void cpu_load(cpu_t *cpu, uint8_t *rom, size_t size);
void cpu_negative(cpu_t *cpu, uint8_t value);
void cpu_zero(cpu_t *cpu, uint8_t value);
void cpu_fetch(cpu_t *cpu);
void cpu_decode(cpu_t *cpu);
void cpu_execute(cpu_t *cpu);
void cpu_destroy(cpu_t *cpu);

#endif