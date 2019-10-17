#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "util.h"

static uint16_t random_uint16(void) {
	return rand() % 0x10000;
}

static uint8_t random_uint8(void) {
	return rand() % 0x100;
}

static bool random_bool(void) {
	return rand() > (RAND_MAX / 2);
}

void cpu_compare(cpu_t *left, cpu_t *right) {
	assert(left->program_counter == right->program_counter);
	assert(left->stack_pointer == right->stack_pointer);
	assert(left->accumulator == right->accumulator);
	assert(left->x == right->x);
	assert(left->y == right->y);
	assert(left->carry == right->carry);
	assert(left->zero == right->zero);
	assert(left->interrupt_disable == right->interrupt_disable);
	assert(left->decimal_mode == right->decimal_mode);
	assert(left->break_command == right->break_command);
	assert(left->overflow == right->overflow);
	assert(left->negative == right->negative);
}

cpu_t *cpu_random(void) {
	cpu_t *cpu = cpu_new();
	cpu->program_counter = random_uint16();
	cpu->stack_pointer = random_uint8();
	cpu->accumulator = random_uint8();
	cpu->x = random_uint8();
	cpu->y = random_uint8();
	cpu->carry = random_bool();
	cpu->zero = random_bool();
	cpu->interrupt_disable = random_bool();
	cpu->decimal_mode = random_bool();
	cpu->break_command = random_bool();
	cpu->overflow = random_bool();
	cpu->negative = random_bool();
	return cpu;
}

cpu_t *cpu_clone(cpu_t *cpu) {
	cpu_t *clone = cpu_new();
	clone->program_counter = cpu->program_counter;
	clone->stack_pointer = cpu->stack_pointer;
	clone->accumulator = cpu->accumulator;
	clone->x = cpu->x;
	clone->y = cpu->y;
	clone->carry = cpu->carry;
	clone->zero = cpu->zero;
	clone->interrupt_disable = cpu->interrupt_disable;
	clone->decimal_mode = cpu->decimal_mode;
	clone->break_command = cpu->break_command;
	clone->overflow = cpu->overflow;
	clone->negative = cpu->negative;
	return clone;
}