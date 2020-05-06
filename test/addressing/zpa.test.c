#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/zpa.h"
#include "addressing_mode.h"
#include "zpa.test.h"

void test_zpa_operand(void) {
	cpu_t *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x24;
	cpu->memory[0x24] = 0xA2;
	uint8_t expected = 0xA2;

	zpa(cpu);

	assert(cpu->operand == expected);

	cpu_destroy(cpu);
}

void test_zpa_operand_address(void) {
	cpu_t *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x24;
	uint16_t expected = 0x24;

	zpa(cpu);

	assert(cpu->operand_address == expected);

	cpu_destroy(cpu);
}

void test_zpa_address_mode(void) {
	cpu_t *cpu = cpu_random();
	addressing_mode_t expected = addressing_zero_page;

	zpa(cpu);

	assert(cpu->addressing_mode == expected);

	cpu_destroy(cpu);
}

void test_zpa_program_counter(void) {
	cpu_t *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 1;

	zpa(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}