#ifndef CPU_TEST_H
#define CPU_TEST_H

#include "cpu.h"

void test_cpu_new(void);
void test_cpu_load(void);

void test_cpu_fetch(void);
void test_cpu_decode(void);
void test_cpu_execute(void);

void test_cpu_carry_yes(void);
void test_cpu_carry_no(void);

void test_cpu_zero_yes(void);
void test_cpu_zero_no(void);

void test_cpu_negative_yes(void);
void test_cpu_negative_no(void);

void test_cpu_push(void);
void test_cpu_pull(void);

void test_cpu_running_yes(void);
void test_cpu_running_no(void);

#endif