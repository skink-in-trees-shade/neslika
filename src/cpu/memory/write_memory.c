#include "cpu/cpu.h"
#include "write_memory.h"

void write_memory(void *device, uint16_t address, uint8_t value) {
	struct cpu *cpu = device;
	cpu->memory[address & 0x07FF] = value;
}