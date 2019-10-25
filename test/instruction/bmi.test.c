#include <stdbool.h>
#include "util.h"
#include "instruction/bmi.h"
#include "bmi.test.h"

void test_bmi_negative_yes(void) {
	cpu_t *actual = cpu_random();
	actual->program_counter = 0x54;
	actual->operand = 0x24;
	actual->negative = true;

	cpu_t *expected = cpu_clone(actual);
	expected->program_counter = 0x78;

	bmi(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_bmi_negative_no(void) {
	cpu_t *actual = cpu_random();
	actual->program_counter = 0x54;
	actual->operand = 0x24;
	actual->negative = false;

	cpu_t *expected = cpu_clone(actual);

	bmi(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}