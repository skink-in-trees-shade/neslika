#include <stdio.h>
#include "debug.h"

typedef enum {
	IMP = 1, ACC, IMM, ZPA, ZPX, ZPY, REL, ABS, ABX, ABY, IND, INX, INY
} mode_t;

typedef struct {
	char *name;
	mode_t mode;
} opcode_debug_t;

void debug_opcode(cpu_t *cpu) {
	uint8_t *ptr = &cpu->memory[cpu->program_counter];

	opcode_debug_t table[] = {
	/* 0x00 */  { "BRK", IMP },  { "ORA", INX },  { 0, 0 },        { 0, 0 },     
	/* 0x04 */	{ 0, 0 },        { "ORA", ZPA },  { "ASL", ZPA },  { 0, 0 },     
	/* 0x08 */	{ "PHP", IMP },  { "ORA", IMM },  { "ASL", ACC },  { 0, 0 },     
	/* 0x0C */	{ 0, 0 },        { "ORA", ABS },  { "ASL", ABS },  { 0, 0 },     
	/* 0x10 */	{ "BPL", REL },  { "ORA", INY },  { 0, 0 },        { 0, 0 },     
	/* 0x14 */	{ 0, 0 },        { "ORA", ZPX },  { "ASL", ZPX },  { 0, 0 },     
	/* 0x18 */	{ "CLC", IMP },  { "ORA", ABY },  { 0, 0 },        { 0, 0 },     
	/* 0x1C */	{ 0, 0 },        { "ORA", ABX },  { "ASL", ABX },  { 0, 0 },     
	/* 0x20 */	{ "JSR", ABS },  { "AND", INX },  { 0, 0 },        { 0, 0 },     
	/* 0x24 */	{ "BIT", ZPA },  { "AND", ZPA },  { "ROL", ZPA },  { 0, 0 },     
	/* 0x28 */	{ "PLP", IMP },  { "AND", IMM },  { "ROL", ACC },  { 0, 0 },     
	/* 0x2C */	{ "BIT", ABS },  { "AND", ABS },  { "ROL", ABS },  { 0, 0 },     
	/* 0x30 */	{ "BMI", REL },  { "AND", INY },  { 0, 0 },        { 0, 0 },     
	/* 0x34 */	{ 0, 0 },        { "AND", ZPX },  { "ROL", ZPX },  { 0, 0 },     
	/* 0x38 */	{ "SEC", IMP },  { "AND", ABY },  { 0, 0 },        { 0, 0 },     
	/* 0x3C */	{ 0, 0 },        { "AND", ABX },  { "ROL", ABX },  { 0, 0 },     
	/* 0x40 */	{ "RTI", IMP },  { "EOR", INX },  { 0, 0 },        { 0, 0 },     
	/* 0x44 */	{ 0, 0 },        { "EOR", ZPA },  { "LSR", ZPA },  { 0, 0 },     
	/* 0x48 */	{ "PHA", IMP },  { "EOR", IMM },  { "LSR", ACC },  { 0, 0 },     
	/* 0x4C */	{ "JMP", ABS },  { "EOR", ABS },  { "LSR", ABS },  { 0, 0 },     
	/* 0x50 */	{ "BVC", REL },  { "EOR", INY },  { 0, 0 },        { 0, 0 },     
	/* 0x54 */	{ 0, 0 },        { "EOR", ZPX },  { "LSR", ZPX },  { 0, 0 },     
	/* 0x58 */	{ "CLI", IMP },  { "EOR", ABY },  { 0, 0 },        { 0, 0 },     
	/* 0x5C */	{ 0, 0 },        { "EOR", ABX },  { "LSR", ABX },  { 0, 0 },     
	/* 0x60 */	{ "RTS", IMP },  { "ADC", INX },  { 0, 0 },        { 0, 0 },     
	/* 0x64 */	{ 0, 0 },        { "ADC", ZPA },  { "ROR", ZPA },  { 0, 0 },     
	/* 0x68 */	{ "PLA", IMP },  { "ADC", IMM },  { "ROR", ACC },  { 0, 0 },     
	/* 0x6C */	{ "JMP", IND },  { "ADC", ABS },  { "ROR", ABS },  { 0, 0 },     
	/* 0x70 */	{ "BVS", REL },  { "ADC", INY },  { 0, 0 },        { 0, 0 },     
	/* 0x74 */	{ 0, 0 },        { "ADC", ZPX },  { "ROR", ZPX },  { 0, 0 },     
	/* 0x78 */	{ "SEI", IMP },  { "ADC", ABY },  { 0, 0 },        { 0, 0 },     
	/* 0x7C */	{ 0, 0 },        { "ADC", ABX },  { "ROR", ABX },  { 0, 0 },     
	/* 0x80 */	{ 0, 0 },        { "STA", INX },  { 0, 0 },        { 0, 0 },     
	/* 0x84 */	{ "STX", ZPA },  { "STA", ZPA },  { "STX", ZPA },  { 0, 0 },     
	/* 0x88 */	{ "DEY", IMP },  { "STA", IMM },  { "TXA", IMP },  { 0, 0 },     
	/* 0x8C */	{ "STX", ABS },  { "STA", ABS },  { "STX", ABS },  { 0, 0 },     
	/* 0x90 */	{ "BCC", REL },  { "STA", INY },  { 0, 0 },        { 0, 0 },     
	/* 0x94 */	{ "STX", ZPX },  { "STA", ZPX },  { "STX", ZPY },  { 0, 0 },     
	/* 0x98 */	{ "TYA", IMP },  { "STA", ABY },  { "TXS", IMP },  { 0, 0 },     
	/* 0x9C */	{ 0, 0 },        { "STA", ABX },  { 0, 0 },        { 0, 0 },     
	/* 0xA0 */	{ "LDY", IMM },  { "LDA", INX },  { "LDX", IMM },  { 0, 0 },     
	/* 0xA4 */	{ "LDY", ZPA },  { "LDA", ZPA },  { "LDX", ZPA },  { 0, 0 },     
	/* 0xA8 */	{ "TAY", IMP },  { "LDA", IMM },  { "TAX", IMP },  { 0, 0 },     
	/* 0xAC */	{ "LDY", ABS },  { "LDA", ABS },  { "LDX", ABS },  { 0, 0 },     
	/* 0xB0 */	{ "BCS", REL },  { "LDA", INY },  { 0, 0 },        { 0, 0 },     
	/* 0xB4 */	{ "LDY", ZPX },  { "LDA", ZPX },  { "LDX", ZPY },  { 0, 0 },     
	/* 0xB8 */	{ "CLV", IMP },  { "LDA", ABY },  { "TSX", IMP },  { 0, 0 },     
	/* 0xBC */	{ "LDY", ABX },  { "LDA", ABX },  { "LDX", ABY },  { 0, 0 },     
	/* 0xC0 */	{ "CPY", IMM },  { "CMP", INX },  { 0, 0 },        { 0, 0 },     
	/* 0xC4 */	{ "CPY", ZPA },  { "CMP", ZPA },  { "DEC", ZPA },  { 0, 0 },     
	/* 0xC8 */	{ "INY", IMP },  { "CMP", IMM },  { "DEX", IMP },  { 0, 0 },     
	/* 0xCC */	{ "CPY", ABS },  { "CMP", ABS },  { "DEC", ABS },  { 0, 0 },     
	/* 0xD0 */	{ "BNE", REL },  { "CMP", INY },  { 0, 0 },        { 0, 0 },     
	/* 0xD4 */	{ 0, 0 },        { "CMP", ZPX },  { "DEC", ZPX },  { 0, 0 },     
	/* 0xD8 */	{ "CLD", IMP },  { "CMP", ABY },  { 0, 0 },        { 0, 0 },     
	/* 0xDC */	{ 0, 0 },        { "CMP", ABX },  { "DEC", ABX },  { 0, 0 },     
	/* 0xE0 */	{ "CPX", IMM },  { "SBC", INX },  { 0, 0 },        { 0, 0 },     
	/* 0xE4 */	{ "CPX", ZPA },  { "SBC", ZPA },  { "INC", ZPA },  { 0, 0 },     
	/* 0xE8 */	{ "INX", IMP },  { "SBC", IMM },  { "NOP", IMP },  { 0, 0 },     
	/* 0xEC */	{ "CPX", ABS },  { "SBC", ABS },  { "INC", ABS },  { 0, 0 },     
	/* 0xF0 */	{ "BEQ", REL },  { "SBC", INY },  { 0, 0 },        { 0, 0 },     
	/* 0xF4 */	{ 0, 0 },        { "SBC", ZPX },  { "INC", ZPX },  { 0, 0 },     
	/* 0xF8 */	{ "SED", IMP },  { "SBC", ABY },  { 0, 0 },        { 0, 0 },     
	/* 0xFC */	{ 0, 0 },        { "SBC", ABX },  { "INC", ABX },  { 0, 0 }
	};

	uint8_t code = ptr[0];
	switch (table[code].mode) {
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
			printf("%s *%+d\n", table[code].name, (int8_t)ptr[1]);
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