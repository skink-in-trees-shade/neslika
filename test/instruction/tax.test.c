#include <stdbool.h>
#include "util.h"
#include "instruction/tax.h"
#include "tax.test.h"

void test_tax(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x48;

	struct cpu *expected = cpu_clone(actual);
	expected->x = actual->accumulator;
	expected->zero = false;
	expected->negative = false;

	tax(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_tax_zero(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x00;

	struct cpu *expected = cpu_clone(actual);
	expected->x = actual->accumulator;
	expected->zero = true;
	expected->negative = false;

	tax(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_tax_negative(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0xF8;

	struct cpu *expected = cpu_clone(actual);
	expected->x = actual->accumulator;
	expected->zero = false;
	expected->negative = true;

	tax(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}