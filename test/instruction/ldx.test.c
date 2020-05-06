#include <stdbool.h>
#include "util.h"
#include "instruction/ldx.h"
#include "ldx.test.h"

void test_ldx(void) {
	struct cpu *actual = cpu_random();
	actual->operand = 0x48;

	struct cpu *expected = cpu_clone(actual);
	expected->x = actual->operand;
	expected->zero = false;
	expected->negative = false;

	ldx(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_ldx_zero(void) {
	struct cpu *actual = cpu_random();
	actual->operand = 0x00;

	struct cpu *expected = cpu_clone(actual);
	expected->x = actual->operand;
	expected->zero = true;
	expected->negative = false;

	ldx(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_ldx_negative(void) {
	struct cpu *actual = cpu_random();
	actual->operand = 0xF8;

	struct cpu *expected = cpu_clone(actual);
	expected->x = actual->operand;
	expected->zero = false;
	expected->negative = true;

	ldx(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}