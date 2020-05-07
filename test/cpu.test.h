#ifndef CPU_TEST_H
#define CPU_TEST_H

#include "cpu.h"

void test_cpu_new(void);
void test_cpu_load(void);

void test_cpu_fetch(void);
void test_cpu_decode(void);
void test_cpu_execute(void);

void test_cpu_zero_yes(void);
void test_cpu_zero_no(void);

void test_cpu_negative_yes(void);
void test_cpu_negative_no(void);

void test_cpu_read(void);
void test_cpu_read_program_counter(void);
void test_cpu_peek(void);
void test_cpu_poke(void);

void test_cpu_push(void);
void test_cpu_pull(void);

void test_cpu_running_yes(void);
void test_cpu_running_no(void);

#endif