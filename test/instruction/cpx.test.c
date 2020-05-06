#include <stdbool.h>
#include "util.h"
#include "instruction/cpx.h"
#include "cpx.test.h"

void test_cpx_carry(void) {
	struct cpu *actual = cpu_random();
	actual->x = 0x48;
	actual->operand = 0x1A;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = true;
	expected->zero = false;
	expected->negative = false;

	cpx(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cpx_zero(void) {
	struct cpu *actual = cpu_random();
	actual->x = 0x48;
	actual->operand = 0x48;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = true;
	expected->zero = true;
	expected->negative = false;

	cpx(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cpx_negative(void) {
	struct cpu *actual = cpu_random();
	actual->x = 0xEA;
	actual->operand = 0xF8;

	struct cpu *expected = cpu_clone(actual);
	expected->carry = false;
	expected->zero = false;
	expected->negative = true;

	cpx(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}