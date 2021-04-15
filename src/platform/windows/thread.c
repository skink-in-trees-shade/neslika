#include <windows.h>
#include <stdlib.h>
#include "platform/thread.h"

struct thread {
	uint8_t fps;
	LARGE_INTEGER frequency;
	LARGE_INTEGER time;
};

struct thread *thread_new(uint8_t fps) {
	struct thread *thread = calloc(1, sizeof(struct thread));
	thread->fps = fps;
	timeBeginPeriod(1);
	QueryPerformanceFrequency(&thread->frequency);
	QueryPerformanceCounter(&thread->time);
	return thread;
}

void thread_sleep(struct thread *thread) {
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	LONGLONG delta_ms = (thread->time.QuadPart - time.QuadPart) * 1000 / thread->frequency.QuadPart + 1000 / thread->fps;
	if (delta_ms > 0) {
		Sleep(delta_ms);
	}

	QueryPerformanceCounter(&thread->time);
}

void thread_destroy(struct thread *thread) {
	timeEndPeriod(1);
	free(thread);
}