#include <stdbool.h>
#include "util.h"
#include "instruction/beq.h"
#include "beq.test.h"

void test_beq_zero_yes(void) {
	cpu_t *actual = cpu_random();
	actual->program_counter = 0x54;
	actual->operand = 0x24;
	actual->zero = true;

	cpu_t *expected = cpu_clone(actual);
	expected->program_counter = 0x78;

	beq(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_beq_zero_no(void) {
	cpu_t *actual = cpu_random();
	actual->program_counter = 0x54;
	actual->operand = 0x24;
	actual->zero = false;

	cpu_t *expected = cpu_clone(actual);

	beq(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}