#include <stdbool.h>
#include "util.h"
#include "instruction/sbc.h"
#include "sbc.test.h"

void test_sbc_no_carry_no_overflow(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x51;
	actual->operand = 0xF0;
	actual->carry = false;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x60;
	expected->carry = false;
	expected->overflow = false;
	expected->zero = false;
	expected->negative = false;

	sbc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_sbc_carry_overflow(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0xD1;
	actual->operand = 0x70;
	actual->carry = false;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x60;
	expected->carry = true;
	expected->overflow = true;
	expected->zero = false;
	expected->negative = false;

	sbc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_sbc_carry_no_overflow(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x63;
	actual->operand = 0x1A;
	actual->carry = false;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x48;
	expected->carry = true;
	expected->overflow = false;
	expected->zero = false;
	expected->negative = false;

	sbc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_sbc_no_carry_overflow(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x51;
	actual->operand = 0xB0;
	actual->carry = false;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0xA0;
	expected->carry = false;
	expected->overflow = true;
	expected->zero = false;
	expected->negative = true;

	sbc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_sbc_carry(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x50;
	actual->operand = 0xF0;
	actual->carry = true;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x60;
	expected->carry = false;
	expected->overflow = false;
	expected->zero = false;
	expected->negative = false;

	sbc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_sbc_zero(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x01;
	actual->operand = 0x00;
	actual->carry = false;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x00;
	expected->carry = true;
	expected->overflow = false;
	expected->zero = true;
	expected->negative = false;

	sbc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_sbc_negative(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0xEA;
	actual->operand = 0x01;
	actual->carry = false;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0xE8;
	expected->carry = true;
	expected->overflow = false;
	expected->zero = false;
	expected->negative = true;

	sbc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}