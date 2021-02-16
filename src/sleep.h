#ifndef SLEEP_H
#define SLEEP_H

#include <time.h>

#define CLOCK_REALTIME 1
#define TIMER_ABSTIME 1

int clock_gettime(int dummy, struct timespec *ct);
int clock_nanosleep(int clock_id, int flags, const struct timespec *request, struct timespec *remain);

#endif