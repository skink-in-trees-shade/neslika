#include "ldy.h"

void ldy(cpu_t *cpu) {
	cpu->y = cpu->operand;
	cpu->zero = cpu->y == 0;
	cpu->negative = cpu->y & 0x80;
}