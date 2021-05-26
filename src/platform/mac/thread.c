#include <mach/mach.h>
#include <mach/mach_time.h>
#include <stdlib.h>
#include "platform/thread.h"

struct thread {
	uint8_t fps;
	mach_timebase_info_data_t timebase;
	uint64_t time;
	int64_t delta;
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
	uint64_t deadline = thread->time + delta;
	mach_wait_until(deadline - thread->delta);
	thread->time = mach_absolute_time();
	thread->delta = thread->time - deadline - thread->delta;
	if (thread->delta < 0) {
		thread->delta = 0;
	}
}

void thread_destroy(struct thread *thread) {
	free(thread);
}