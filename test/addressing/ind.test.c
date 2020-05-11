#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/ind.h"
#include "addressing_mode.h"
#include "ind.test.h"

void test_ind_operand(void) {
	struct cpu *cpu = cpu_random();
	cpu_poke(cpu, cpu->program_counter, 0x84);
	cpu_poke(cpu, 0x84, 0x24);
	cpu_poke(cpu, 0x85, 0xF1);
	cpu_poke(cpu, 0x24F1, 0xA2);
	uint8_t expected = 0xA2;

	ind(cpu);

	assert(cpu->operand == expected);

	cpu_destroy(cpu);
}

void test_ind_operand_address(void) {
	struct cpu *cpu = cpu_random();
	cpu_poke(cpu, cpu->program_counter, 0x84);
	cpu_poke(cpu, 0x84, 0x24);
	cpu_poke(cpu, 0x85, 0xF1);
	uint16_t expected = 0x24F1;

	ind(cpu);

	assert(cpu->operand_address == expected);

	cpu_destroy(cpu);
}

void test_ind_address_mode(void) {
	struct cpu *cpu = cpu_random();
	enum addressing_mode expected = addressing_indirect;

	ind(cpu);

	assert(cpu->addressing_mode == expected);

	cpu_destroy(cpu);
}

void test_ind_program_counter(void) {
	struct cpu *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 1;

	ind(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}