#include <stdbool.h>
#include "util.h"
#include "instruction/bvs.h"
#include "bvs.test.h"

void test_bvs_overflow_yes(void) {
	struct cpu *actual = cpu_random();
	actual->program_counter = 0x54;
	actual->operand = 0x24;
	actual->overflow = true;

	struct cpu *expected = cpu_clone(actual);
	expected->program_counter = 0x78;

	bvs(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_bvs_overflow_no(void) {
	struct cpu *actual = cpu_random();
	actual->program_counter = 0x54;
	actual->operand = 0x24;
	actual->overflow = false;

	struct cpu *expected = cpu_clone(actual);

	bvs(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}