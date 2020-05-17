#include <stdlib.h>
#include "instruction.h"
#include "debug.h"
#include "error.h"
#include "cpu.h"

static uint8_t _cpu_read(struct device *device, uint16_t address) {
	struct cpu *cpu = (struct cpu *)device;
	return cpu->memory[address & 0x07FF];
}

static void _cpu_write(struct device *device, uint16_t address, uint8_t value) {
	struct cpu *cpu = (struct cpu *)device;
	cpu->memory[address & 0x07FF] = value;
}

struct cpu *cpu_new(void) {
	struct cpu *cpu = calloc(1, sizeof(struct cpu));
	cpu->memory = calloc(0x0800, sizeof(uint8_t));
	cpu->device.address_from = 0x0000;
	cpu->device.address_to = 0x1FFF;
	cpu->device.read = &_cpu_read;
	cpu->device.write = &_cpu_write;
	return cpu;
}

void cpu_reset(struct cpu *cpu) {
	cpu->program_counter = (cpu_peek(cpu, 0xFFFD) << 8) + cpu_peek(cpu, 0xFFFC);
	cpu->stack_pointer = 0xFD;
	cpu->accumulator = 0x00;
	cpu->x = 0x00;
	cpu->y = 0x00;
	cpu->status = 0x24;
	cpu->cycle = 7;
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
	return bus_read(cpu->bus, address);
}

void cpu_poke(struct cpu *cpu, uint16_t address, uint8_t value) {
	bus_write(cpu->bus, address, value);
}

void cpu_push(struct cpu *cpu, uint8_t value) {
	cpu_poke(cpu, 0x0100 + cpu->stack_pointer--, value);
}

uint8_t cpu_pull(struct cpu *cpu) {
	return cpu_peek(cpu, 0x0100 + ++cpu->stack_pointer);
}

bool cpu_running(struct cpu *cpu) {
	return cpu->instruction != 0x00;
}

void cpu_tick(struct cpu *cpu) {
	cpu->instruction = cpu_read(cpu);
	if (instructions[cpu->instruction].decode == NULL) {
		error("Unknown instruction %02X.", cpu->instruction);
	}
	
	cpu->extra_decode_cycle = false;
	instructions[cpu->instruction].decode(cpu);

	cpu_debug(cpu);

	cpu->extra_execute_cycle = false;
	instructions[cpu->instruction].execute(cpu);

	cpu->cycle += instructions[cpu->instruction].cycles;
	if (cpu->extra_decode_cycle && cpu->extra_execute_cycle) {
		cpu->cycle++;
	}
}

void cpu_destroy(struct cpu *cpu) {
	free(cpu->memory);
	free(cpu);
}