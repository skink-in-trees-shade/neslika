#include <stdbool.h>
#include "util.h"
#include "instruction/bit.h"
#include "bit.test.h"

void test_bit_zero(void) {
	cpu_t *actual = cpu_random();
	actual->accumulator = 0xD9;
	actual->operand = 0x26;

	cpu_t *expected = cpu_clone(actual);
	expected->zero = true;
	expected->overflow = false;
	expected->negative = false;

	bit(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_bit_overflow(void) {
	cpu_t *actual = cpu_random();
	actual->accumulator = 0xD9;
	actual->operand = 0x66;

	cpu_t *expected = cpu_clone(actual);
	expected->zero = false;
	expected->overflow = true;
	expected->negative = false;

	bit(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_bit_negative(void) {
	cpu_t *actual = cpu_random();
	actual->accumulator = 0xD9;
	actual->operand = 0xA6;

	cpu_t *expected = cpu_clone(actual);
	expected->zero = false;
	expected->overflow = false;
	expected->negative = true;

	bit(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}