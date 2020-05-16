#include <stdio.h>
#include "addressing/abj.h"
#include "addressing/abo.h"
#include "addressing/abx.h"
#include "addressing/aby.h"
#include "addressing/acc.h"
#include "addressing/iix.h"
#include "addressing/iiy.h"
#include "addressing/imm.h"
#include "addressing/imp.h"
#include "addressing/ind.h"
#include "addressing/rel.h"
#include "addressing/zpa.h"
#include "addressing/zpx.h"
#include "addressing/zpy.h"
#include "instruction.h"
#include "debug.h"

static uint8_t cpu_status(struct cpu *cpu) {
	return 0
		| (cpu->carry << 0)
		| (cpu->zero << 1)
		| (cpu->interrupt_disable << 2)
		| (cpu->decimal_mode << 3)
		| (cpu->break_command << 4)
		| (1 << 5)
		| (cpu->overflow << 6)
		| (cpu->negative << 7);
}

static void debug_imp(struct cpu *cpu, struct instruction *instruction) {
	printf(
		"%04X  %02X       %s%s                             A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
		cpu->program_counter - 1,
		cpu->instruction,
		instruction->undocumented ? "*" : " ",
		instruction->name,
		cpu->accumulator,
		cpu->x,
		cpu->y,
		cpu_status(cpu),
		cpu->stack_pointer
	);
}

static void debug_acc(struct cpu *cpu, struct instruction *instruction) {
	printf(
		"%04X  %02X       %s%s A                           A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
		cpu->program_counter - 1,
		cpu->instruction,
		instruction->undocumented ? "*" : " ",
		instruction->name,
		cpu->accumulator,
		cpu->x,
		cpu->y,
		cpu_status(cpu),
		cpu->stack_pointer
	);
}

static void debug_imm(struct cpu *cpu, struct instruction *instruction) {
	printf(
		"%04X  %02X %02X    %s%s #$%02X                        A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
		cpu->program_counter - 2,
		cpu->instruction,
		cpu_peek(cpu, cpu->program_counter - 1),
		instruction->undocumented ? "*" : " ",
		instruction->name,
		cpu_peek(cpu, cpu->program_counter - 1),
		cpu->accumulator,
		cpu->x,
		cpu->y,
		cpu_status(cpu),
		cpu->stack_pointer
	);
}

static void debug_rel(struct cpu *cpu, struct instruction *instruction) {
	printf(
		"%04X  %02X %02X    %s%s $%04X                       A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
		cpu->program_counter - 2,
		cpu->instruction,
		cpu->memory[cpu->program_counter - 1],
		instruction->undocumented ? "*" : " ",
		instruction->name,
		cpu->program_counter + (int8_t)cpu->operand,
		cpu->accumulator,
		cpu->x,
		cpu->y,
		cpu_status(cpu),
		cpu->stack_pointer
	);
}

static void debug_zpa(struct cpu *cpu, struct instruction *instruction) {
	printf(
		"%04X  %02X %02X    %s%s $%02X = %02X                    A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
		cpu->program_counter - 2,
		cpu->instruction,
		cpu->operand_low,
		instruction->undocumented ? "*" : " ",
		instruction->name,
		cpu->operand_low,
		cpu_peek(cpu, cpu->operand),
		cpu->accumulator,
		cpu->x,
		cpu->y,
		cpu_status(cpu),
		cpu->stack_pointer
	);
}

static void debug_zpx(struct cpu *cpu, struct instruction *instruction) {
	printf(
		"%04X  %02X %02X    %s%s $%02X,X @ %02X = %02X             A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
		cpu->program_counter - 2,
		cpu->instruction,
		cpu_peek(cpu, cpu->program_counter - 1),
		instruction->undocumented ? "*" : " ",
		instruction->name,
		cpu_peek(cpu, cpu->program_counter - 1),
		cpu->operand,
		cpu_peek(cpu, cpu->operand),
		cpu->accumulator,
		cpu->x,
		cpu->y,
		cpu_status(cpu),
		cpu->stack_pointer
	);
}

static void debug_zpy(struct cpu *cpu, struct instruction *instruction) {
	printf(
		"%04X  %02X %02X    %s%s $%02X,Y @ %02X = %02X             A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
		cpu->program_counter - 2,
		cpu->instruction,
		cpu_peek(cpu, cpu->program_counter - 1),
		instruction->undocumented ? "*" : " ",
		instruction->name,
		cpu_peek(cpu, cpu->program_counter - 1),
		cpu->operand,
		cpu_peek(cpu, cpu->operand),
		cpu->accumulator,
		cpu->x,
		cpu->y,
		cpu_status(cpu),
		cpu->stack_pointer
	);
}

static void debug_abj(struct cpu *cpu, struct instruction *instruction) {
	printf(
		"%04X  %02X %02X %02X %s%s $%04X                       A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
		cpu->program_counter - 3,
		cpu->instruction,
		cpu->operand_low,
		cpu->operand_high,
		instruction->undocumented ? "*" : " ",
		instruction->name,
		cpu->operand,
		cpu->accumulator,
		cpu->x,
		cpu->y,
		cpu_status(cpu),
		cpu->stack_pointer
	);
}

static void debug_abo(struct cpu *cpu, struct instruction *instruction) {
	printf(
		"%04X  %02X %02X %02X %s%s $%04X = %02X                  A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
		cpu->program_counter - 3,
		cpu->instruction,
		cpu->operand_low,
		cpu->operand_high,
		instruction->undocumented ? "*" : " ",
		instruction->name,
		cpu->operand,
		cpu_peek(cpu, cpu->operand),
		cpu->accumulator,
		cpu->x,
		cpu->y,
		cpu_status(cpu),
		cpu->stack_pointer
	);
}

static void debug_abx(struct cpu *cpu, struct instruction *instruction) {
	printf(
		"%04X  %02X %02X %02X %s%s $%04X,X @ %04X = %02X         A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
		cpu->program_counter - 3,
		cpu->instruction,
		cpu_peek(cpu, cpu->program_counter - 2),
		cpu_peek(cpu, cpu->program_counter - 1),
		instruction->undocumented ? "*" : " ",
		instruction->name,
		(cpu_peek(cpu, cpu->program_counter - 1) << 8) + cpu_peek(cpu, cpu->program_counter - 2),
		cpu->operand,
		cpu_peek(cpu, cpu->operand),
		cpu->accumulator,
		cpu->x,
		cpu->y,
		cpu_status(cpu),
		cpu->stack_pointer
	);
}

static void debug_aby(struct cpu *cpu, struct instruction *instruction) {
	printf(
		"%04X  %02X %02X %02X %s%s $%04X,Y @ %04X = %02X         A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
		cpu->program_counter - 3,
		cpu->instruction,
		cpu_peek(cpu, cpu->program_counter - 2),
		cpu_peek(cpu, cpu->program_counter - 1),
		instruction->undocumented ? "*" : " ",
		instruction->name,
		(cpu_peek(cpu, cpu->program_counter - 1) << 8) + cpu_peek(cpu, cpu->program_counter - 2),
		cpu->operand,
		cpu_peek(cpu, cpu->operand),
		cpu->accumulator,
		cpu->x,
		cpu->y,
		cpu_status(cpu),
		cpu->stack_pointer
	);
}

static void debug_ind(struct cpu *cpu, struct instruction *instruction) {
	printf(
		"%04X  %02X %02X %02X %s%s ($%04X) = %04X              A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
		cpu->program_counter - 3,
		cpu->instruction,
		cpu_peek(cpu, cpu->program_counter - 2),
		cpu_peek(cpu, cpu->program_counter - 1),
		instruction->undocumented ? "*" : " ",
		instruction->name,
		(cpu_peek(cpu, cpu->program_counter - 1) << 8) + cpu_peek(cpu, cpu->program_counter - 2),
		cpu->operand,
		cpu->accumulator,
		cpu->x,
		cpu->y,
		cpu_status(cpu),
		cpu->stack_pointer
	);
}

static void debug_iix(struct cpu *cpu, struct instruction *instruction) {
	printf(
		"%04X  %02X %02X    %s%s ($%02X,X) @ %02X = %04X = %02X    A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
		cpu->program_counter - 2,
		cpu->instruction,
		cpu_peek(cpu, cpu->program_counter - 1),
		instruction->undocumented ? "*" : " ",
		instruction->name,
		cpu_peek(cpu, cpu->program_counter - 1),
		(cpu_peek(cpu, cpu->program_counter - 1) + cpu->x) & 0xFF,
		cpu->operand,
		cpu_peek(cpu, cpu->operand),
		cpu->accumulator,
		cpu->x,
		cpu->y,
		cpu_status(cpu),
		cpu->stack_pointer
	);
}

static void debug_iiy(struct cpu *cpu, struct instruction *instruction) {
	printf(
		"%04X  %02X %02X    %s%s ($%02X),Y = %04X @ %04X = %02X  A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
		cpu->program_counter - 2,
		cpu->instruction,
		cpu_peek(cpu, cpu->program_counter - 1),
		instruction->undocumented ? "*" : " ",
		instruction->name,
		cpu_peek(cpu, cpu->program_counter - 1),
		(cpu->operand - cpu->y) & 0xFFFF,
		cpu->operand,
		cpu_peek(cpu, cpu->operand),
		cpu->accumulator,
		cpu->x,
		cpu->y,
		cpu_status(cpu),
		cpu->stack_pointer
	);
}

void cpu_debug(struct cpu *cpu) {
	struct instruction instruction = instructions[cpu->instruction];
	if (instruction.decode == imp) debug_imp(cpu, &instruction);
	else if (instruction.decode == acc) debug_acc(cpu, &instruction);
	else if (instruction.decode == imm) debug_imm(cpu, &instruction);
	else if (instruction.decode == rel) debug_rel(cpu, &instruction);
	else if (instruction.decode == zpa) debug_zpa(cpu, &instruction);
	else if (instruction.decode == zpx) debug_zpx(cpu, &instruction);
	else if (instruction.decode == zpy) debug_zpy(cpu, &instruction);
	else if (instruction.decode == abj) debug_abj(cpu, &instruction);
	else if (instruction.decode == abo) debug_abo(cpu, &instruction);
	else if (instruction.decode == abx) debug_abx(cpu, &instruction);
	else if (instruction.decode == aby) debug_aby(cpu, &instruction);
	else if (instruction.decode == ind) debug_ind(cpu, &instruction);
	else if (instruction.decode == iix) debug_iix(cpu, &instruction);
	else if (instruction.decode == iiy) debug_iiy(cpu, &instruction);
}