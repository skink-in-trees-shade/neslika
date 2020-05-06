#include <stdbool.h>
#include <assert.h>
#include "util.h"
#include "instruction/dex.h"
#include "dex.test.h"

void test_dex(void) {
	struct cpu *actual = cpu_random();
	actual->x = 0x24;

	struct cpu *expected = cpu_clone(actual);
	expected->x = actual->x - 1;
	expected->zero = false;
	expected->negative = false;

	dex(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_dex_zero(void) {
	struct cpu *actual = cpu_random();
	actual->x = 0x01;

	struct cpu *expected = cpu_clone(actual);
	expected->x = actual->x - 1;
	expected->zero = true;
	expected->negative = false;

	dex(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_dex_negative(void) {
	struct cpu *actual = cpu_random();
	actual->x = 0xF8;

	struct cpu *expected = cpu_clone(actual);
	expected->x = actual->x - 1;
	expected->zero = false;
	expected->negative = true;

	dex(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}