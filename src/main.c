#include <stdint.h>
#include "cpu.h"
#include "debug.h"

int main(void) {
	struct cpu *cpu = cpu_new();

	uint8_t rom[] = {
		0xA2, 0x00,		// LDX #$00
		0xA0, 0x00,		// LDY #$00
		0x8A,			// TXA 
		0x99, 0x00, 0x02,	// STA $0200,Y
		0x48,			// PHA 
		0xE8,			// INX 
		0xC8,			// INY 
		0xC0, 0x10,		// CPY #$10
		0xD0, 0xF5,		// BNE $0604
		0x68,			// PLA 
		0x99, 0x00, 0x02,	// STA $0200,Y
		0xC8,			// INY 
		0xC0, 0x20,		// CPY #$20
		0xD0, 0xF7,		// BNE $060f
		0x00			// BRK
	};

	cpu_load(cpu, rom, sizeof(rom));

	do {
		cpu_fetch(cpu);
		cpu_decode(cpu);
		cpu_debug(cpu);
		cpu_execute(cpu);
	} while (cpu->instruction != 0x00);

	cpu_destroy(cpu);
	return 0;
}