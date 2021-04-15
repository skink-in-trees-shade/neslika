#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>

struct thread;

struct thread *thread_new(uint8_t fps);
void thread_sleep(struct thread *thread);
void thread_destroy(struct thread *thread);

#endif