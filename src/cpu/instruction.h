#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdbool.h>
#include "cpu.h"

struct instruction {
	const char *name;
	bool undocumented;
	void (*decode)(struct cpu *);
	void (*execute)(struct cpu *);
	unsigned int cycles;
};

extern struct instruction instructions[0x100];

#endif