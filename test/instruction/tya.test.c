#include <stdbool.h>
#include "util.h"
#include "instruction/tya.h"
#include "tya.test.h"

void test_tya(void) {
	struct cpu *actual = cpu_random();
	actual->y = 0x48;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = actual->y;
	expected->zero = false;
	expected->negative = false;

	tya(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_tya_zero(void) {
	struct cpu *actual = cpu_random();
	actual->y = 0x00;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = actual->y;
	expected->zero = true;
	expected->negative = false;

	tya(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_tya_negative(void) {
	struct cpu *actual = cpu_random();
	actual->y = 0xF8;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = actual->y;
	expected->zero = false;
	expected->negative = true;

	tya(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}