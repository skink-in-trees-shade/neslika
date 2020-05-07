#include <stdbool.h>
#include <assert.h>
#include "util.h"
#include "instruction/lsr.h"
#include "addressing_mode.h"
#include "lsr.test.h"

void test_lsr_memory(void) {
	struct cpu *cpu = cpu_random();
	cpu->operand = 0x84;
	cpu->addressing_mode = addressing_zero_page;
	uint8_t expected = 0x42;

	lsr(cpu);

	assert(cpu->operand == expected);

	cpu_destroy(cpu);
}

void test_lsr_accumulator(void) {
	struct cpu *cpu = cpu_random();
	cpu->accumulator = 0x84;
	cpu->addressing_mode = addressing_implicit;
	uint8_t expected = 0x42;

	lsr(cpu);

	assert(cpu->accumulator == expected);

	cpu_destroy(cpu);
}

void test_lsr_carry(void) {
	struct cpu *actual = cpu_random();
	actual->operand = 0x85;
	actual->addressing_mode = addressing_zero_page;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = true;
	expected->zero = false;
	expected->negative = false;

	lsr(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_lsr_zero(void) {
	struct cpu *actual = cpu_random();
	actual->operand = 0x00;
	actual->addressing_mode = addressing_zero_page;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = false;
	expected->zero = true;
	expected->negative = false;

	lsr(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}