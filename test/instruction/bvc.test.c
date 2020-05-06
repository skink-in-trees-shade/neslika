#include <stdbool.h>
#include "util.h"
#include "instruction/bvc.h"
#include "bvc.test.h"

void test_bvc_overflow_yes(void) {
	struct cpu *actual = cpu_random();
	actual->program_counter = 0x54;
	actual->operand = 0x24;
	actual->overflow = true;

	struct cpu *expected = cpu_clone(actual);

	bvc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_bvc_overflow_no(void) {
	struct cpu *actual = cpu_random();
	actual->program_counter = 0x54;
	actual->operand = 0x24;
	actual->overflow = false;

	struct cpu *expected = cpu_clone(actual);
	expected->program_counter = 0x78;

	bvc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}