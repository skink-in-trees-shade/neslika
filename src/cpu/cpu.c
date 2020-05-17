#include <stdlib.h>
#include <string.h>
#include "instruction.h"
#include "debug.h"
#include "cpu/cpu.h"

static uint8_t _cpu_read(struct device *device, uint16_t address) {
	struct cpu *cpu = (struct cpu *)device;
	return cpu->memory[address];
}

static void _cpu_write(struct device *device, uint16_t address, uint8_t value) {
	struct cpu *cpu = (struct cpu *)device;
	cpu->memory[address] = value;
}

struct cpu *cpu_new(void) {
	struct cpu *cpu = calloc(1, sizeof(struct cpu));
	cpu->memory = calloc(0x10000, sizeof(uint8_t));
	cpu->device.address_from = 0x0000;
	cpu->device.address_to = 0xFFFF;
	cpu->device.read = &_cpu_read;
	cpu->device.write = &_cpu_write;
	return cpu;
}

void cpu_load(struct cpu *cpu, uint8_t *rom, size_t size) {
	cpu->stack_pointer = 0xFD;
	cpu->interrupt_disable = true;
	memcpy(&cpu->memory[0x8000], rom, size);
	if (size == 0x4000) {
		memcpy(&cpu->memory[0xC000], rom, size);
	}
	cpu->program_counter = (cpu_peek(cpu, 0xFFFD) << 8) + cpu_peek(cpu, 0xFFFC);
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

void cpu_fetch(struct cpu *cpu) {
	cpu->instruction = cpu_read(cpu);
}

void cpu_decode(struct cpu *cpu) {
	instructions[cpu->instruction].decode(cpu);
	cpu_debug(cpu);
}

void cpu_execute(struct cpu *cpu) {
	instructions[cpu->instruction].execute(cpu);
}

void cpu_destroy(struct cpu *cpu) {
	free(cpu->memory);
	free(cpu);
}