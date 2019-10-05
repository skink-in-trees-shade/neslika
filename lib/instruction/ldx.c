#include "ldx.h"

void ldx(cpu_t *cpu) {
	cpu->x = cpu->operand;
	cpu->zero = cpu->x == 0;
	cpu->negative = cpu->x & 0x80;
}