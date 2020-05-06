#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/iix.h"
#include "addressing_mode.h"
#include "iix.test.h"

void test_iix_operand(void) {
	struct cpu *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x84;
	cpu->memory[0x84 + cpu->x] = 0x24;
	cpu->memory[0x85 + cpu->x] = 0xF1;
	cpu->memory[0x24F1] = 0xA2;
	uint8_t expected = 0xA2;

	iix(cpu);

	assert(cpu->operand == expected);

	cpu_destroy(cpu);
}

void test_iix_operand_address(void) {
	struct cpu *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x84;
	cpu->memory[0x84 + cpu->x] = 0x24;
	cpu->memory[0x85 + cpu->x] = 0xF1;
	uint16_t expected = 0x24F1;

	iix(cpu);

	assert(cpu->operand_address == expected);

	cpu_destroy(cpu);
}

void test_iix_address_mode(void) {
	struct cpu *cpu = cpu_random();
	enum addressing_mode expected = addressing_indexed_indirect;

	iix(cpu);

	assert(cpu->addressing_mode == expected);

	cpu_destroy(cpu);
}

void test_iix_program_counter(void) {
	struct cpu *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 1;

	iix(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}