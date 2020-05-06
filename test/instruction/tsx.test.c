#include <stdbool.h>
#include "util.h"
#include "instruction/tsx.h"
#include "tsx.test.h"

void test_tsx(void) {
	struct cpu *actual = cpu_random();
	actual->stack_pointer = 0x48;

	struct cpu *expected = cpu_clone(actual);
	expected->x = actual->stack_pointer;
	expected->zero = false;
	expected->negative = false;

	tsx(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_tsx_zero(void) {
	struct cpu *actual = cpu_random();
	actual->stack_pointer = 0x00;

	struct cpu *expected = cpu_clone(actual);
	expected->x = actual->stack_pointer;
	expected->zero = true;
	expected->negative = false;

	tsx(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_tsx_negative(void) {
	struct cpu *actual = cpu_random();
	actual->stack_pointer = 0xF8;

	struct cpu *expected = cpu_clone(actual);
	expected->x = actual->stack_pointer;
	expected->zero = false;
	expected->negative = true;

	tsx(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}