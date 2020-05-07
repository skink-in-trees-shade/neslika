#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/imm.h"
#include "addressing_mode.h"
#include "imm.test.h"

void test_imm_operand(void) {
	struct cpu *cpu = cpu_random();
	cpu_poke(cpu, cpu->program_counter, 0xA2);
	uint8_t expected = 0xA2;

	imm(cpu);

	assert(cpu->operand == expected);

	cpu_destroy(cpu);
}

void test_imm_operand_address(void) {
	struct cpu *cpu = cpu_random();
	uint16_t expected = cpu->program_counter;

	imm(cpu);

	assert(cpu->operand_address == expected);

	cpu_destroy(cpu);
}

void test_imm_address_mode(void) {
	struct cpu *cpu = cpu_random();
	enum addressing_mode expected = addressing_immediate;

	imm(cpu);

	assert(cpu->addressing_mode == expected);

	cpu_destroy(cpu);
}

void test_imm_program_counter(void) {
	struct cpu *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 1;

	imm(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}