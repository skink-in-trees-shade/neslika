#include <stdbool.h>
#include "util.h"
#include "instruction/and.h"
#include "and.test.h"

void test_and(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x1A;
	actual->operand = 0x48;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x08;
	expected->zero = false;
	expected->negative = false;

	and(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_and_zero(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x24;
	actual->operand = 0xDB;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x00;
	expected->zero = true;
	expected->negative = false;

	and(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_and_negative(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0xEA;
	actual->operand = 0xFD;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0xE8;
	expected->zero = false;
	expected->negative = true;

	and(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}