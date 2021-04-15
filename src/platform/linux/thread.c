#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stdlib.h>
#include "platform/thread.h"

struct thread {
	uint8_t fps;
	struct timespec time;
};

struct thread *thread_new(uint8_t fps) {
	struct thread *thread = calloc(1, sizeof(struct thread));
	thread->fps = fps;
	clock_gettime(CLOCK_MONOTONIC, &thread->time);
	return thread;
}

void thread_sleep(struct thread *thread) {
	struct timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);

	int64_t delta_ns = (thread->time.tv_sec - time.tv_sec) * 1000000000 + (thread->time.tv_nsec - time.tv_nsec) + (1000000000 / thread->fps);
	if (delta_ns > 0) {
		struct timespec delta;
		delta.tv_sec = delta_ns / 1000000000;
		delta.tv_nsec = delta_ns % 1000000000;
		nanosleep(&delta, NULL);
	}

	clock_gettime(CLOCK_MONOTONIC, &thread->time);
}

void thread_destroy(struct thread *thread) {
	free(thread);
}