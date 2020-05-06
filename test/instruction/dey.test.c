#include <stdbool.h>
#include <assert.h>
#include "util.h"
#include "instruction/dey.h"
#include "dey.test.h"

void test_dey(void) {
	struct cpu *actual = cpu_random();
	actual->y = 0x24;

	struct cpu *expected = cpu_clone(actual);
	expected->y = actual->y - 1;
	expected->zero = false;
	expected->negative = false;

	dey(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_dey_zero(void) {
	struct cpu *actual = cpu_random();
	actual->y = 0x01;

	struct cpu *expected = cpu_clone(actual);
	expected->y = actual->y - 1;
	expected->zero = true;
	expected->negative = false;

	dey(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_dey_negative(void) {
	struct cpu *actual = cpu_random();
	actual->y = 0xF8;

	struct cpu *expected = cpu_clone(actual);
	expected->y = actual->y - 1;
	expected->zero = false;
	expected->negative = true;

	dey(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}