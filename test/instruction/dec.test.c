#include <stdbool.h>
#include <assert.h>
#include "util.h"
#include "instruction/dec.h"
#include "dec.test.h"

void test_dec(void) {
	cpu_t *actual = cpu_random();
	actual->operand_address = 0xE7;
	actual->operand = 0x48;
	actual->memory[actual->operand_address] = actual->operand;

	cpu_t *expected = cpu_clone(actual);
	expected->zero = false;
	expected->negative = false;

	dec(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[actual->operand_address] == actual->operand - 1);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_dec_zero(void) {
	cpu_t *actual = cpu_random();
	actual->operand_address = 0xE7;
	actual->operand = 0x01;
	actual->memory[actual->operand_address] = actual->operand;

	cpu_t *expected = cpu_clone(actual);
	expected->zero = true;
	expected->negative = false;

	dec(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[actual->operand_address] == 0x00);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_dec_negative(void) {
	cpu_t *actual = cpu_random();
	actual->operand_address = 0xE7;
	actual->operand = 0xF8;
	actual->memory[actual->operand_address] = actual->operand;

	cpu_t *expected = cpu_clone(actual);
	expected->zero = false;
	expected->negative = true;

	dec(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[actual->operand_address] == actual->operand - 1);

	cpu_destroy(expected);
	cpu_destroy(actual);
}