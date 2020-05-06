#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/zpx.h"
#include "addressing_mode.h"
#include "zpx.test.h"

void test_zpx_operand(void) {
	struct cpu *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x24;
	cpu->memory[0x24 + cpu->x] = 0xA2;
	uint8_t expected = 0xA2;

	zpx(cpu);

	assert(cpu->operand == expected);

	cpu_destroy(cpu);
}

void test_zpx_operand_address(void) {
	struct cpu *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x24;
	uint16_t expected = 0x24 + cpu->x;

	zpx(cpu);

	assert(cpu->operand_address == expected);

	cpu_destroy(cpu);
}

void test_zpx_address_mode(void) {
	struct cpu *cpu = cpu_random();
	enum addressing_mode expected = addressing_zero_page_x;

	zpx(cpu);

	assert(cpu->addressing_mode == expected);

	cpu_destroy(cpu);
}

void test_zpx_program_counter(void) {
	struct cpu *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 1;

	zpx(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}