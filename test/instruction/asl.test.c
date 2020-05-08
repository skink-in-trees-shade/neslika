#include <stdbool.h>
#include <assert.h>
#include "util.h"
#include "instruction/asl.h"
#include "addressing_mode.h"
#include "asl.test.h"

void test_asl_memory(void) {
	struct cpu *cpu = cpu_random();
	cpu->operand = 0x84;
	cpu->operand_address = 0x11B3;
	cpu->addressing_mode = addressing_zero_page;
	uint8_t expected = 0x08;

	asl(cpu);

	assert(cpu_peek(cpu, cpu->operand_address) == expected);

	cpu_destroy(cpu);
}

void test_asl_accumulator(void) {
	struct cpu *cpu = cpu_random();
	cpu->accumulator = 0x84;
	cpu->addressing_mode = addressing_implicit;
	uint8_t expected = 0x08;

	asl(cpu);

	assert(cpu->accumulator == expected);

	cpu_destroy(cpu);
}

void test_asl_carry(void) {
	struct cpu *actual = cpu_random();
	actual->operand = 0x84;
	actual->addressing_mode = addressing_zero_page;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = true;
	expected->zero = false;
	expected->negative = false;

	asl(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_asl_zero(void) {
	struct cpu *actual = cpu_random();
	actual->operand = 0x00;
	actual->addressing_mode = addressing_zero_page;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = false;
	expected->zero = true;
	expected->negative = false;

	asl(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_asl_negative(void) {
	struct cpu *actual = cpu_random();
	actual->operand = 0x42;
	actual->addressing_mode = addressing_zero_page;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = false;
	expected->zero = false;
	expected->negative = true;

	asl(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}