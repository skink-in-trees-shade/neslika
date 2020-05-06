#include <stdbool.h>
#include "util.h"
#include "instruction/ldy.h"
#include "ldy.test.h"

void test_ldy(void) {
	struct cpu *actual = cpu_random();
	actual->operand = 0x48;

	struct cpu *expected = cpu_clone(actual);
	expected->y = actual->operand;
	expected->zero = false;
	expected->negative = false;

	ldy(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_ldy_zero(void) {
	struct cpu *actual = cpu_random();
	actual->operand = 0x00;

	struct cpu *expected = cpu_clone(actual);
	expected->y = actual->operand;
	expected->zero = true;
	expected->negative = false;

	ldy(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_ldy_negative(void) {
	struct cpu *actual = cpu_random();
	actual->operand = 0xF8;

	struct cpu *expected = cpu_clone(actual);
	expected->y = actual->operand;
	expected->zero = false;
	expected->negative = true;

	ldy(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}