#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/aby.h"
#include "addressing_mode.h"
#include "aby.test.h"

void test_aby_operand(void) {
	cpu_t *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x24;
	cpu->memory[cpu->program_counter + 1] = 0xF1;
	cpu->memory[0x24F1 + cpu->y] = 0xA2;
	uint8_t expected = 0xA2;

	aby(cpu);

	assert(cpu->operand == expected);

	cpu_destroy(cpu);
}

void test_aby_operand_address(void) {
	cpu_t *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x24;
	cpu->memory[cpu->program_counter + 1] = 0xF1;
	uint16_t expected = 0x24F1 + cpu->y;

	aby(cpu);

	assert(cpu->operand_address == expected);

	cpu_destroy(cpu);
}

void test_aby_address_mode(void) {
	cpu_t *cpu = cpu_random();
	addressing_mode_t expected = addressing_absolute_y;

	aby(cpu);

	assert(cpu->addressing_mode == expected);

	cpu_destroy(cpu);
}

void test_aby_program_counter(void) {
	cpu_t *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 2;

	aby(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}