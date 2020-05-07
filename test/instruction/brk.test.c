#include <stdbool.h>
#include <assert.h>
#include "util.h"
#include "instruction/brk.h"
#include "brk.test.h"

void test_brk(void) {
	struct cpu *actual = cpu_random();
	cpu_poke(actual, 0xFFFE, 0x31);
	cpu_poke(actual, 0xFFFF, 0xA2);

	struct cpu *expected = cpu_clone(actual);
	expected->program_counter = 0x31A2;
	expected->break_command = true;
	expected->stack_pointer = actual->stack_pointer - 3;

	brk(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_brk_status(void) {
	struct cpu *actual = cpu_random();
	actual->carry = true;
	actual->zero = false;
	actual->interrupt_disable = true;
	actual->decimal_mode = false;
	actual->overflow = true;
	actual->negative = false;

	uint8_t expected = 0x75;

	brk(actual);

	uint8_t status = cpu_pull(actual);
	assert(status == expected);

	cpu_destroy(actual);
}

void test_brk_program_counter(void) {
	struct cpu *actual = cpu_random();
	actual->program_counter = 0x254A;

	uint16_t expected = 0x254A;

	brk(actual);

	(void)cpu_pull(actual);
	uint8_t low = cpu_pull(actual);
	uint8_t high = cpu_pull(actual);
	uint16_t program_counter = (high << 8) + low;
	assert(program_counter == expected);

	cpu_destroy(actual);
}