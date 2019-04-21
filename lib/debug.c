#include <stdio.h>
#include "debug.h"

typedef enum {
	UNK, IMP, ACC, IMM, ZPA, ZPX, ZPY, REL, ABS, ABX, ABY, IND, INX, INY
} mode_t;

typedef struct {
	char *name;
	mode_t mode;
} opcode_debug_t;

void debug_opcode(cpu_t *cpu) {
	uint8_t *ptr = &cpu->memory[cpu->program_counter];

	opcode_debug_t table[] = {
	/* 0x00 */  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x04 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x08 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x0C */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x10 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x14 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x18 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x1C */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x20 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x24 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x28 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x2C */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x30 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x34 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x38 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x3C */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x40 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x44 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x48 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x4C */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x50 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x54 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x58 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x5C */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x60 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x64 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x68 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x6C */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x70 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x74 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x78 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x7C */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x80 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x84 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x88 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x8C */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x90 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x94 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x98 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0x9C */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xA0 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xA4 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xA8 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xAC */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xB0 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xB4 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xB8 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xBC */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xC0 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xC4 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xC8 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xCC */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xD0 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xD4 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xD8 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xDC */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xE0 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xE4 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xE8 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xEC */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xF0 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xF4 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xF8 */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK },
	/* 0xFC */	{ NULL, UNK },  { NULL, UNK },  { NULL, UNK },  { NULL, UNK }
	};

	uint8_t code = ptr[0];
	switch (table[code].mode) {
		case UNK:
		break;

		case IMP:
			printf("%s\n", table[code].name);
		break;

		case ACC:
			printf("%s A\n", table[code].name);
		break;

		case IMM:
			printf("%s #%02X\n", table[code].name, ptr[1]);
		break;

		case ZPA:
			printf("%s $%02X\n", table[code].name, ptr[1]);
		break;

		case ZPX:
			printf("%s $%02X,X\n", table[code].name, ptr[1]);
		break;

		case ZPY:
			printf("%s $%02X,Y\n", table[code].name, ptr[1]);
		break;

		case REL:
			printf("%s *%+02d\n", table[code].name, ptr[1]);
		break;

		case ABS:
			printf("%s $%02X%02X\n", table[code].name, ptr[1], ptr[2]);
		break;

		case ABX:
			printf("%s $%02X%02X,X\n", table[code].name, ptr[1], ptr[2]);
		break;

		case ABY:
			printf("%s $%02X%02X,Y\n", table[code].name, ptr[1], ptr[2]);
		break;

		case IND:
			printf("%s ($%02X%02X)\n", table[code].name, ptr[1], ptr[2]);
		break;

		case INX:
			printf("%s ($%02X,X)\n", table[code].name, ptr[1]);
		break;

		case INY:
			printf("%s ($%02X),Y\n", table[code].name, ptr[1]);
		break;
	}
}

void debug_state(cpu_t *cpu) {
	printf(
		"PC   SP AC X  Y  C Z I D B O N\n"
		"%04X %02X %02X %02X %02X %d %d %d %d %d %d %d\n\n",
		cpu->program_counter, cpu->stack_pointer, cpu->accumulator, cpu->x, cpu->y,
		cpu->carry, cpu->zero, cpu->interrupt_disable, cpu->decimal_mode, cpu->break_command, cpu->overflow, cpu->negative
	);
}