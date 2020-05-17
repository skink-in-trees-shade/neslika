#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "device.h"
#include "bus.h"

struct cpu {
	struct device device;
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
	bool overflow;
	bool negative;

	uint8_t instruction;
	union {
		uint16_t operand;
		struct {
			uint8_t operand_low;
			uint8_t operand_high;
		};
	};

	uint8_t *memory;
};

struct cpu *cpu_new(void);
void cpu_load(struct cpu *cpu, uint8_t *rom, size_t size);
void cpu_zero(struct cpu *cpu, uint8_t value);
void cpu_negative(struct cpu *cpu, uint8_t value);
uint8_t cpu_read(struct cpu *cpu);
uint8_t cpu_peek(struct cpu *cpu, uint16_t address);
void cpu_poke(struct cpu *cpu, uint16_t address, uint8_t value);
void cpu_push(struct cpu *cpu, uint8_t value);
uint8_t cpu_pull(struct cpu *cpu);
bool cpu_running(struct cpu *cpu);
void cpu_fetch(struct cpu *cpu);
void cpu_decode(struct cpu *cpu);
void cpu_execute(struct cpu *cpu);
void cpu_destroy(struct cpu *cpu);

#endif