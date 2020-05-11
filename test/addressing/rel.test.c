#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/rel.h"
#include "addressing_mode.h"
#include "rel.test.h"

void test_rel_operand(void) {
	struct cpu *cpu = cpu_random();
	cpu_poke(cpu, cpu->program_counter, 0xA2);
	uint8_t expected = 0xA2;

	rel(cpu);

	assert(cpu->operand == expected);

	cpu_destroy(cpu);
}

void test_rel_operand_address(void) {
	struct cpu *cpu = cpu_random();
	uint16_t expected = cpu->program_counter;

	rel(cpu);

	assert(cpu->operand_address == expected);

	cpu_destroy(cpu);
}

void test_rel_address_mode(void) {
	struct cpu *cpu = cpu_random();
	enum addressing_mode expected = addressing_relative;

	rel(cpu);

	assert(cpu->addressing_mode == expected);

	cpu_destroy(cpu);
}

void test_rel_program_counter(void) {
	struct cpu *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 1;

	rel(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}