#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>
#include "cpu.h"

typedef struct {
	uint16_t (*addressing_mode)(cpu_t *);
	void (*instruction)(cpu_t *, uint8_t);
} opcode_t;

opcode_t table[0x100];

#endif