#include <stdbool.h>
#include "util.h"
#include "instruction/cmp.h"
#include "cmp.test.h"

void test_cmp_carry(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x48;
	actual->operand = 0x1A;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = true;
	expected->zero = false;
	expected->negative = false;

	cmp(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cmp_zero(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x48;
	actual->operand = 0x48;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = true;
	expected->zero = true;
	expected->negative = false;

	cmp(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cmp_negative(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0xEA;
	actual->operand = 0xF8;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = false;
	expected->zero = false;
	expected->negative = true;

	cmp(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}