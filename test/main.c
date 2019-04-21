#include <stdint.h>
#include "cpu.h"

static void test_rom_load(void) {
	uint8_t rom[] = {
		0xA9, 0xC4,       // LDA #C4
		0xA5, 0xC4,       // LDA $C4
		0xB5, 0xC4,       // LDA $C4,X
		0xAD, 0xC4, 0x00, // LDA $C400
		0xBD, 0xC4, 0x00, // LDA $C400,X
		0xB9, 0xC4, 0x00, // LDA $C400,Y
		0xA1, 0xC4,       // LDA ($C4,X)
		0xB1, 0xC4,       // LDA ($C4),Y
		0xEA              // NOP
	};

	cpu_t *cpu = cpu_new();
	cpu_load(cpu, rom);
	cpu_run(cpu);
	cpu_destroy(cpu);
}

int main(void) {
	test_rom_load();
	return 0;
}