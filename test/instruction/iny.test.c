#include <stdbool.h>
#include <assert.h>
#include "util.h"
#include "instruction/iny.h"
#include "iny.test.h"

void test_iny(void) {
	struct cpu *actual = cpu_random();
	actual->y = 0x24;

	struct cpu *expected = cpu_clone(actual);
	expected->y = actual->y + 1;
	expected->zero = false;
	expected->negative = false;

	iny(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_iny_zero(void) {
	struct cpu *actual = cpu_random();
	actual->y = 0xFF;

	struct cpu *expected = cpu_clone(actual);
	expected->y = actual->y + 1;
	expected->zero = true;
	expected->negative = false;

	iny(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_iny_negative(void) {
	struct cpu *actual = cpu_random();
	actual->y = 0xF8;

	struct cpu *expected = cpu_clone(actual);
	expected->y = actual->y + 1;
	expected->zero = false;
	expected->negative = true;

	iny(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}