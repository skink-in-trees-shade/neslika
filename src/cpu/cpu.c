#include <stdlib.h>
#include "instruction.h"
#include "memory/read_memory.h"
#include "memory/write_memory.h"
#include "error.h"
#include "cpu.h"

struct cpu *cpu_new(struct bus *bus) {
	struct cpu *cpu = calloc(1, sizeof(struct cpu));
	cpu->memory = calloc(0x0800, sizeof(uint8_t));

	cpu->bus = bus;
	bus_register(cpu->bus, cpu, 0x0000, 0x1FFF, &read_memory, &write_memory);

	return cpu;
}

void cpu_reset(struct cpu *cpu) {
	cpu->program_counter = (cpu_peek(cpu, 0xFFFD) << 8) + cpu_peek(cpu, 0xFFFC);
	cpu->stack_pointer = 0xFD;
	cpu->accumulator = 0x00;
	cpu->x = 0x00;
	cpu->y = 0x00;
	cpu->interrupt_disable = true;
	cpu->cycle = 7;
}

void cpu_zero(struct cpu *cpu, uint8_t value) {
	cpu->zero = value == 0x00;
}

void cpu_negative(struct cpu *cpu, uint8_t value) {
	cpu->negative = value & 0x80;
}

uint8_t cpu_status(struct cpu *cpu) {
	return 0
		| (cpu->carry << 0)
		| (cpu->zero << 1)
		| (cpu->interrupt_disable << 2)
		| (cpu->decimal_mode << 3)
		| (cpu->break_command << 4)
		| (1 << 5)
		| (cpu->overflow << 6)
		| (cpu->negative << 7);
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

void cpu_tick(struct cpu *cpu) {
	cpu->instruction = cpu_read(cpu);

	if (instructions[cpu->instruction].decode == NULL) {
		error("Unknown instruction %02X.", cpu->instruction);
	}
	
	cpu->extra_decode_cycle = false;
	instructions[cpu->instruction].decode(cpu);

	cpu->extra_execute_cycle = false;
	instructions[cpu->instruction].execute(cpu);

	cpu->cycle += instructions[cpu->instruction].cycles;
	if (cpu->extra_decode_cycle && cpu->extra_execute_cycle) {
		cpu->cycle++;
	}
}

void cpu_nmi(struct cpu *cpu) {
	uint8_t high = (cpu->program_counter >> 8) & 0xFF;
	uint8_t low = cpu->program_counter & 0xFF;
	cpu_push(cpu, high);
	cpu_push(cpu, low);
	
	cpu->break_command = false;
	cpu->interrupt_disable = true;
	cpu_push(cpu, cpu_status(cpu));

	low = cpu_peek(cpu, 0xFFFA);
	high = cpu_peek(cpu, 0xFFFB);
	cpu->program_counter = (high << 8) + low;

	cpu->cycle += 8;
}

void cpu_irq(struct cpu *cpu) {
	uint8_t high = (cpu->program_counter >> 8) & 0xFF;
	uint8_t low = cpu->program_counter & 0xFF;
	cpu_push(cpu, high);
	cpu_push(cpu, low);
	
	cpu->break_command = false;
	cpu->interrupt_disable = true;
	cpu_push(cpu, cpu_status(cpu));

	low = cpu_peek(cpu, 0xFFFE);
	high = cpu_peek(cpu, 0xFFFF);
	cpu->program_counter = (high << 8) + low;

	cpu->cycle += 7;
}

void cpu_destroy(struct cpu *cpu) {
	free(cpu->memory);
	free(cpu);
}