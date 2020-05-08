#include <stdbool.h>
#include <assert.h>
#include "util.h"
#include "instruction/ror.h"
#include "addressing_mode.h"
#include "ror.test.h"

void test_ror_memory(void) {
	struct cpu *cpu = cpu_random();
	cpu->carry = true;
	cpu->operand = 0x84;
	cpu->addressing_mode = addressing_zero_page;
	uint8_t expected = 0xC2;

	ror(cpu);

	assert(cpu->operand == expected);

	cpu_destroy(cpu);
}

void test_ror_accumulator(void) {
	struct cpu *cpu = cpu_random();
	cpu->carry = true;
	cpu->accumulator = 0x84;
	cpu->addressing_mode = addressing_implicit;
	uint8_t expected = 0xC2;

	ror(cpu);

	assert(cpu->accumulator == expected);

	cpu_destroy(cpu);
}

void test_ror_carry(void) {
	struct cpu *actual = cpu_random();
	actual->carry = false;
	actual->operand = 0x85;
	actual->addressing_mode = addressing_zero_page;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = true;
	expected->zero = false;
	expected->negative = false;

	ror(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_ror_zero(void) {
	struct cpu *actual = cpu_random();
	actual->carry = false;
	actual->operand = 0x00;
	actual->addressing_mode = addressing_zero_page;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = false;
	expected->zero = true;
	expected->negative = false;

	ror(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}