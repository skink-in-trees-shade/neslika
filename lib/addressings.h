#ifndef ADDRESSINGS_H
#define ADDRESSINGS_H

#include <stdint.h>
#include "cpu.h"

typedef uint8_t (*addressing_t)(cpu_t *);

extern addressing_t addressings[0x100];

#endif