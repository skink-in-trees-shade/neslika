#include <stdbool.h>
#include "util.h"
#include "instruction/txa.h"
#include "txa.test.h"

void test_txa(void) {
	struct cpu *actual = cpu_random();
	actual->x = 0x48;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = actual->x;
	expected->zero = false;
	expected->negative = false;

	txa(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_txa_zero(void) {
	struct cpu *actual = cpu_random();
	actual->x = 0x00;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = actual->x;
	expected->zero = true;
	expected->negative = false;

	txa(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_txa_negative(void) {
	struct cpu *actual = cpu_random();
	actual->x = 0xF8;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = actual->x;
	expected->zero = false;
	expected->negative = true;

	txa(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}