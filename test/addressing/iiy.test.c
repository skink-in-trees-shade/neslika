#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/iiy.h"
#include "addressing_mode.h"
#include "iiy.test.h"

void test_iiy_operand(void) {
	cpu_t *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x84;
	cpu->memory[0x84] = 0x24;
	cpu->memory[0x85] = 0xF1;
	cpu->memory[0x24F1 + cpu->y] = 0xA2;
	uint8_t expected = 0xA2;

	iiy(cpu);

	assert(cpu->operand == expected);

	cpu_destroy(cpu);
}

void test_iiy_operand_address(void) {
	cpu_t *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x84;
	cpu->memory[0x84] = 0x24;
	cpu->memory[0x85] = 0xF1;
	uint16_t expected = 0x24F1 + cpu->y;

	iiy(cpu);

	assert(cpu->operand_address == expected);

	cpu_destroy(cpu);
}

void test_iiy_address_mode(void) {
	cpu_t *cpu = cpu_random();
	addressing_mode_t expected = addressing_indirect_indexed;

	iiy(cpu);

	assert(cpu->addressing_mode == expected);

	cpu_destroy(cpu);
}

void test_iiy_program_counter(void) {
	cpu_t *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 1;

	iiy(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}