#include "util.h"
#include "instruction/rts.h"
#include "rts.test.h"

void test_rts(void) {
	struct cpu *actual = cpu_random();
	actual->stack_pointer = 0x45;
	cpu_poke(actual, 0x0147, 0x8A);
	cpu_poke(actual, 0x0146, 0x20);

	struct cpu *expected = cpu_clone(actual);
	expected->program_counter = 0x8A21;
	expected->stack_pointer = 0x47;

	rts(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}