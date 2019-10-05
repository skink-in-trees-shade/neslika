#include "lda.h"

void lda(cpu_t *cpu) {
	cpu->accumulator = cpu->operand;
	cpu->zero = cpu->accumulator == 0;
	cpu->negative = cpu->accumulator & 0x80;
}