#include "cpu/cpu.h"
#include "read_memory.h"

uint8_t read_memory(void *device, uint16_t address) {
	struct cpu *cpu = device;
	return cpu->memory[address & 0x07FF];
}