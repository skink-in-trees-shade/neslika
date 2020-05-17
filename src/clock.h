#ifndef CLOCK_H
#define CLOCK_H

struct clock;

struct clock *clock_new(void);
void clock_on_tick(struct clock *clock, void (*tick)(void *system), void *system);
void clock_start(struct clock *clock);
void clock_stop(struct clock *clock);
void clock_destroy(struct clock *clock);

#endif