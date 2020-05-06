#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/zpy.h"
#include "addressing_mode.h"
#include "zpy.test.h"

void test_zpy_operand(void) {
	cpu_t *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x24;
	cpu->memory[0x24 + cpu->y] = 0xA2;
	uint8_t expected = 0xA2;

	zpy(cpu);

	assert(cpu->operand == expected);

	cpu_destroy(cpu);
}

void test_zpy_operand_address(void) {
	cpu_t *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x24;
	uint16_t expected = 0x24 + cpu->y;

	zpy(cpu);

	assert(cpu->operand_address == expected);

	cpu_destroy(cpu);
}

void test_zpy_address_mode(void) {
	cpu_t *cpu = cpu_random();
	addressing_mode_t expected = addressing_zero_page_y;

	zpy(cpu);

	assert(cpu->addressing_mode == expected);

	cpu_destroy(cpu);
}

void test_zpy_program_counter(void) {
	cpu_t *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 1;

	zpy(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}