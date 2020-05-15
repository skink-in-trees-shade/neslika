#include "and.h"
#include "rol.h"
#include "rla.h"

void rla(struct cpu *cpu) {
	rol(cpu);
	and(cpu);
}