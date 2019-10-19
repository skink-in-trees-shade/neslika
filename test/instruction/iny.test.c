#include <stdbool.h>
#include <assert.h>
#include "util.h"
#include "instruction/iny.h"
#include "iny.test.h"

void test_iny(void) {
	cpu_t *actual = cpu_random();
	actual->y = 0x24;

	cpu_t *expected = cpu_clone(actual);
	expected->y = actual->y + 1;
	expected->zero = false;
	expected->negative = false;

	iny(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_iny_zero(void) {
	cpu_t *actual = cpu_random();
	actual->y = 0xFF;

	cpu_t *expected = cpu_clone(actual);
	expected->y = actual->y + 1;
	expected->zero = true;
	expected->negative = false;

	iny(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_iny_negative(void) {
	cpu_t *actual = cpu_random();
	actual->y = 0xF8;

	cpu_t *expected = cpu_clone(actual);
	expected->y = actual->y + 1;
	expected->zero = false;
	expected->negative = true;

	iny(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}