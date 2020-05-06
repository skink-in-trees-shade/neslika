#include <stdbool.h>
#include <assert.h>
#include "util.h"
#include "instruction/inx.h"
#include "inx.test.h"

void test_inx(void) {
	struct cpu *actual = cpu_random();
	actual->x = 0x24;

	struct cpu *expected = cpu_clone(actual);
	expected->x = actual->x + 1;
	expected->zero = false;
	expected->negative = false;

	inx(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_inx_zero(void) {
	struct cpu *actual = cpu_random();
	actual->x = 0xFF;

	struct cpu *expected = cpu_clone(actual);
	expected->x = actual->x + 1;
	expected->zero = true;
	expected->negative = false;

	inx(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_inx_negative(void) {
	struct cpu *actual = cpu_random();
	actual->x = 0xF8;

	struct cpu *expected = cpu_clone(actual);
	expected->x = actual->x + 1;
	expected->zero = false;
	expected->negative = true;

	inx(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}