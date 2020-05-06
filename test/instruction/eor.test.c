#include <stdbool.h>
#include "util.h"
#include "instruction/eor.h"
#include "eor.test.h"

void test_eor(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x1A;
	actual->operand = 0x48;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x52;
	expected->zero = false;
	expected->negative = false;

	eor(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_eor_zero(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0xA2;
	actual->operand = 0xA2;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x00;
	expected->zero = true;
	expected->negative = false;

	eor(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_eor_negative(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0xEA;
	actual->operand = 0x12;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0xF8;
	expected->zero = false;
	expected->negative = true;

	eor(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}