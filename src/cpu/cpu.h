#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>
#include "bus.h"

struct cpu {
	struct bus *bus;

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
	bool unused;
	bool overflow;
	bool negative;

	unsigned long cycle;
	bool extra_decode_cycle;
	bool extra_execute_cycle;
	uint8_t instruction;
	uint16_t operand;

	uint8_t *memory;

	bool irq_occured;
	uint8_t interrupt_disable_shifter;
	bool interrupt_disable_effective;
};

struct cpu *cpu_new(struct bus *bus);
void cpu_reset(struct cpu *cpu);
void cpu_zero(struct cpu *cpu, uint8_t value);
void cpu_negative(struct cpu *cpu, uint8_t value);
uint8_t cpu_status(struct cpu *cpu);
uint8_t cpu_read(struct cpu *cpu);
uint8_t cpu_peek(struct cpu *cpu, uint16_t address);
void cpu_poke(struct cpu *cpu, uint16_t address, uint8_t value);
void cpu_push(struct cpu *cpu, uint8_t value);
uint8_t cpu_pull(struct cpu *cpu);
void cpu_tick(struct cpu *cpu);
void cpu_nmi(struct cpu *cpu);
void cpu_irq(struct cpu *cpu);
void cpu_destroy(struct cpu *cpu);

#endif