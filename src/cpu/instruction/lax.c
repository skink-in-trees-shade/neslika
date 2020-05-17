#include "lda.h"
#include "ldx.h"
#include "lax.h"

void lax(struct cpu *cpu) {
	lda(cpu);
	ldx(cpu);
}