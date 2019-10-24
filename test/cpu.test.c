#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "util.h"
#include "cpu.test.h"

void test_cpu_new(void) {
	cpu_t *cpu = cpu_new();

	assert(cpu);
	assert(cpu->memory);

	cpu_destroy(cpu);
}

void test_cpu_load(void) {
	uint8_t rom[] = { 0xA9, 0xC4, 0xEA };
	cpu_t *actual = cpu_random();
	cpu_t *expected = cpu_clone(actual);
	expected->program_counter = 0x8000;
	expected->program_end = 0x8002;

	cpu_load(actual, rom, sizeof(rom));

	cpu_compare(expected, actual);
	assert(actual->memory[0x8000] == rom[0]);
	assert(actual->memory[0x8001] == rom[1]);
	assert(actual->memory[0x8002] == rom[2]);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cpu_fetch(void) {
	uint8_t rom[] = { 0xEA };
	cpu_t *actual = cpu_new();
	cpu_load(actual, rom, sizeof(rom));

	cpu_t *expected = cpu_clone(actual);
	expected->instruction = rom[0];
	expected->program_counter = actual->program_counter + 1;

	cpu_fetch(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cpu_decode(void) {
	uint8_t rom[] = { 0xA4, 0x24 };
	cpu_t *actual = cpu_new();
	cpu_load(actual, rom, sizeof(rom));
	actual->memory[rom[1]] = 0x1E;
	cpu_fetch(actual);

	cpu_t *expected = cpu_clone(actual);
	expected->operand = actual->memory[rom[1]];
	expected->operand_address = rom[1];
	expected->program_counter = actual->program_counter + 1;

	cpu_decode(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cpu_execute(void) {
	uint8_t rom[] = { 0x00 };
	cpu_t *actual = cpu_new();
	cpu_load(actual, rom, sizeof(rom));
	cpu_fetch(actual);
	cpu_decode(actual);

	cpu_t *expected = cpu_clone(actual);
	expected->break_command = true;

	cpu_execute(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cpu_negative_yes(void) {
	cpu_t *actual = cpu_random();
	cpu_t *expected = cpu_clone(actual);
	expected->negative = true;

	cpu_negative(actual, 0xF8);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cpu_carry_yes(void) {
	cpu_t *actual = cpu_random();
	cpu_t *expected = cpu_clone(actual);
	expected->carry = true;

	cpu_carry(actual, 0x24);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cpu_carry_no(void) {
	cpu_t *actual = cpu_random();
	cpu_t *expected = cpu_clone(actual);
	expected->carry = false;

	cpu_carry(actual, 0x82);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cpu_zero_yes(void) {
	cpu_t *actual = cpu_random();
	cpu_t *expected = cpu_clone(actual);
	expected->zero = true;

	cpu_zero(actual, 0x00);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cpu_zero_no(void) {
	cpu_t *actual = cpu_random();
	cpu_t *expected = cpu_clone(actual);
	expected->zero = false;

	cpu_zero(actual, 0xA4);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cpu_negative_no(void) {
	cpu_t *actual = cpu_random();
	cpu_t *expected = cpu_clone(actual);
	expected->negative = false;

	cpu_negative(actual, 0x48);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_cpu_running_yes(void) {
	uint8_t rom[] = { 0xA9, 0xC4, 0xEA };
	cpu_t *cpu = cpu_new();
	cpu_load(cpu, rom, sizeof(rom));

	bool result = cpu_running(cpu);

	assert(result);
}

void test_cpu_running_no(void) {
	uint8_t rom[] = { 0xEA };
	cpu_t *cpu = cpu_new();
	cpu_load(cpu, rom, sizeof(rom));
	cpu_fetch(cpu);

	bool result = cpu_running(cpu);

	assert(!result);
}