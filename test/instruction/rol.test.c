#include <stdbool.h>
#include <assert.h>
#include "util.h"
#include "instruction/rol.h"
#include "addressing_mode.h"
#include "rol.test.h"

void test_rol_memory(void) {
	struct cpu *cpu = cpu_random();
	cpu->carry = true;
	cpu->operand = 0x84;
	cpu->operand_address = 0x11B3;
	cpu->addressing_mode = addressing_zero_page;
	uint8_t expected = 0x09;

	rol(cpu);

	assert(cpu_peek(cpu, cpu->operand_address) == expected);

	cpu_destroy(cpu);
}

void test_rol_accumulator(void) {
	struct cpu *cpu = cpu_random();
	cpu->carry = true;
	cpu->accumulator = 0x84;
	cpu->addressing_mode = addressing_implicit;
	uint8_t expected = 0x09;

	rol(cpu);

	assert(cpu->accumulator == expected);

	cpu_destroy(cpu);
}

void test_rol_carry(void) {
	struct cpu *actual = cpu_random();
	actual->carry = false;
	actual->operand = 0x84;
	actual->addressing_mode = addressing_zero_page;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = true;
	expected->zero = false;
	expected->negative = false;

	rol(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_rol_zero(void) {
	struct cpu *actual = cpu_random();
	actual->carry = false;
	actual->operand = 0x00;
	actual->addressing_mode = addressing_zero_page;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = false;
	expected->zero = true;
	expected->negative = false;

	rol(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_rol_negative(void) {
	struct cpu *actual = cpu_random();
	actual->carry = false;
	actual->operand = 0x42;
	actual->addressing_mode = addressing_zero_page;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = false;
	expected->zero = false;
	expected->negative = true;

	rol(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}