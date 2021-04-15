#include <mach/mach.h>
#include <mach/mach_time.h>
#include <stdlib.h>
#include "platform/thread.h"

struct thread {
	uint8_t fps;
	mach_timebase_info_data_t timebase;
	uint64_t time;
};

struct thread *thread_new(uint8_t fps) {
	struct thread *thread = calloc(1, sizeof(struct thread));
	thread->fps = fps;
	thread->time = mach_absolute_time();
	mach_timebase_info(&thread->timebase);
	return thread;
}

void thread_sleep(struct thread *thread) {
	uint64_t delta = 1000000000 / thread->fps * thread->timebase.denom / thread->timebase.numer;
	mach_wait_until(thread->time + delta);
	thread->time = mach_absolute_time();
}

void thread_destroy(struct thread *thread) {
	free(thread);
}