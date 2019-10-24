#include <stdbool.h>
#include "util.h"
#include "instruction/cpx.h"
#include "cpx.test.h"

void test_cpx_carry(void) {
	cpu_t *actual = cpu_random();
	actual->x = 0x48;
	actual->operand = 0x1A;

	cpu_t *expected = cpu_clone(actual);
	expected->carry = true;
	expected->zero = false;
	expected->negative = false;

	cpx(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cpx_zero(void) {
	cpu_t *actual = cpu_random();
	actual->x = 0x48;
	actual->operand = 0x48;

	cpu_t *expected = cpu_clone(actual);
	expected->carry = true;
	expected->zero = true;
	expected->negative = false;

	cpx(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cpx_negative(void) {
	cpu_t *actual = cpu_random();
	actual->x = 0xEA;
	actual->operand = 0xF8;

	cpu_t *expected = cpu_clone(actual);
	expected->carry = false;
	expected->zero = false;
	expected->negative = true;

	cpx(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}