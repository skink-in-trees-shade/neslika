#include <stdlib.h>
#include <stdbool.h>
#include "clock.h"

struct clock {
	bool running;
	void *system;
	void (*tick)(void *system);
};

struct clock *clock_new(void) {
	struct clock *clock = calloc(1, sizeof(struct clock));
	return clock;
}

void clock_on_tick(struct clock *clock, void (*tick)(void *system), void *system) {
	clock->system = system;
	clock->tick = tick;
}

void clock_start(struct clock *clock) {
	clock->running = true;
	while (clock->running) {
		clock->tick(clock->system);
	}
}

void clock_stop(struct clock *clock) {
	clock->running = false;
}

void clock_destroy(struct clock *clock) {
	free(clock);
}