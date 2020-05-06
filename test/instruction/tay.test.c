#include <stdbool.h>
#include "util.h"
#include "instruction/tay.h"
#include "tay.test.h"

void test_tay(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x48;

	struct cpu *expected = cpu_clone(actual);
	expected->y = actual->accumulator;
	expected->zero = false;
	expected->negative = false;

	tay(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_tay_zero(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x00;

	struct cpu *expected = cpu_clone(actual);
	expected->y = actual->accumulator;
	expected->zero = true;
	expected->negative = false;

	tay(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_tay_negative(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0xF8;

	struct cpu *expected = cpu_clone(actual);
	expected->y = actual->accumulator;
	expected->zero = false;
	expected->negative = true;

	tay(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}