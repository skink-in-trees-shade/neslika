#include <stdbool.h>
#include "util.h"
#include "instruction/txa.h"
#include "txa.test.h"

void test_txa(void) {
	cpu_t *actual = cpu_random();
	actual->x = 0x48;

	cpu_t *expected = cpu_clone(actual);
	expected->accumulator = actual->x;
	expected->zero = false;
	expected->negative = false;

	txa(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_txa_zero(void) {
	cpu_t *actual = cpu_random();
	actual->x = 0x00;

	cpu_t *expected = cpu_clone(actual);
	expected->accumulator = actual->x;
	expected->zero = true;
	expected->negative = false;

	txa(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_txa_negative(void) {
	cpu_t *actual = cpu_random();
	actual->x = 0xF8;

	cpu_t *expected = cpu_clone(actual);
	expected->accumulator = actual->x;
	expected->zero = false;
	expected->negative = true;

	txa(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}