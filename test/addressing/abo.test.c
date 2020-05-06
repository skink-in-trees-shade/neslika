#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/abo.h"
#include "addressing_mode.h"
#include "abo.test.h"

void test_abo_operand(void) {
	cpu_t *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x24;
	cpu->memory[cpu->program_counter + 1] = 0xF1;
	cpu->memory[0x24F1] = 0xA2;
	uint8_t expected = 0xA2;

	abo(cpu);

	assert(cpu->operand == expected);

	cpu_destroy(cpu);
}

void test_abo_operand_address(void) {
	cpu_t *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x24;
	cpu->memory[cpu->program_counter + 1] = 0xF1;
	uint16_t expected = 0x24F1;

	abo(cpu);

	assert(cpu->operand_address == expected);

	cpu_destroy(cpu);
}

void test_abo_address_mode(void) {
	cpu_t *cpu = cpu_random();
	addressing_mode_t expected = addressing_absolute;

	abo(cpu);

	assert(cpu->addressing_mode == expected);

	cpu_destroy(cpu);
}

void test_abo_program_counter(void) {
	cpu_t *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 2;

	abo(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}