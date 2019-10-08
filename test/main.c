#include <stdint.h>
#include "cpu.h"

static void test_debug_addressing(void) {
	uint8_t rom[] = {
		0x4A,             // LSR A
		0xA9, 0xC4,       // LDA #C4
		0xA5, 0xC4,       // LDA $C4
		0xB5, 0xC4,       // LDA $C4,X
		0xB6, 0xC4,       // LDX $C4,Y
		0xD0, 0xC4,       // BNE *-60
		0xAD, 0xC4, 0x00, // LDA $C400
		0xBD, 0xC4, 0x00, // LDA $C400,X
		0xB9, 0xC4, 0x00, // LDA $C400,Y
		0x6C, 0xC4, 0x00, // JMP ($C400)
		0xA1, 0xC4,       // LDA ($C4,X)
		0xB1, 0xC4,       // LDA ($C4),Y
		0xEA              // NOP
	};

	cpu_t *cpu = cpu_new();
	cpu_load(cpu, rom, sizeof(rom));

	while (cpu->powered) {
		cpu_fetch(cpu);
		cpu_decode(cpu);
		cpu_execute(cpu);
	}

	cpu_destroy(cpu);
}

int main(void) {
	test_debug_addressing();
	return 0;
}