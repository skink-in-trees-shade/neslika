#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

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

	uint8_t *memory;
} cpu_t;

cpu_t *cpu_new(void);
void cpu_load(cpu_t *cpu, uint8_t *rom);
void cpu_run(cpu_t *cpu);
void cpu_destroy(cpu_t *cpu);

#endif