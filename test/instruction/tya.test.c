#include <stdbool.h>
#include "util.h"
#include "instruction/tya.h"
#include "tya.test.h"

void test_tya(void) {
	cpu_t *actual = cpu_random();
	actual->y = 0x48;

	cpu_t *expected = cpu_clone(actual);
	expected->accumulator = actual->y;
	expected->zero = false;
	expected->negative = false;

	tya(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_tya_zero(void) {
	cpu_t *actual = cpu_random();
	actual->y = 0x00;

	cpu_t *expected = cpu_clone(actual);
	expected->accumulator = actual->y;
	expected->zero = true;
	expected->negative = false;

	tya(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_tya_negative(void) {
	cpu_t *actual = cpu_random();
	actual->y = 0xF8;

	cpu_t *expected = cpu_clone(actual);
	expected->accumulator = actual->y;
	expected->zero = false;
	expected->negative = true;

	tya(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}