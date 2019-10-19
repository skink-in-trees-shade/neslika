#include <stdbool.h>
#include <assert.h>
#include "util.h"
#include "instruction/inc.h"
#include "inc.test.h"

void test_inc(void) {
	cpu_t *actual = cpu_random();
	actual->operand_address = 0xE7;
	actual->operand = 0x48;
	actual->memory[actual->operand_address] = actual->operand;

	cpu_t *expected = cpu_clone(actual);
	expected->zero = false;
	expected->negative = false;

	inc(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[actual->operand_address] == actual->operand + 1);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_inc_zero(void) {
	cpu_t *actual = cpu_random();
	actual->operand_address = 0xE7;
	actual->operand = 0xFF;
	actual->memory[actual->operand_address] = actual->operand;

	cpu_t *expected = cpu_clone(actual);
	expected->zero = true;
	expected->negative = false;

	inc(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[actual->operand_address] == 0x00);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_inc_negative(void) {
	cpu_t *actual = cpu_random();
	actual->operand_address = 0xE7;
	actual->operand = 0xF8;
	actual->memory[actual->operand_address] = actual->operand;

	cpu_t *expected = cpu_clone(actual);
	expected->zero = false;
	expected->negative = true;

	inc(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[actual->operand_address] == actual->operand + 1);

	cpu_destroy(expected);
	cpu_destroy(actual);
}