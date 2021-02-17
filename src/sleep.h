#ifndef SLEEP_H
#define SLEEP_H

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <stdint.h>
	#include <time.h>

	#define CLOCK_REALTIME 0
	#define TIMER_ABSTIME 1

	#define BILLION                             (1E9)

	static BOOL g_first_time = 1;
	static LARGE_INTEGER g_counts_per_sec;

	int clock_gettime(int dummy, struct timespec *ct)
	{
		LARGE_INTEGER count;

		if (g_first_time)
		{
			g_first_time = 0;

			if (0 == QueryPerformanceFrequency(&g_counts_per_sec))
			{
				g_counts_per_sec.QuadPart = 0;
			}
		}

		if ((NULL == ct) || (g_counts_per_sec.QuadPart <= 0) ||
			(0 == QueryPerformanceCounter(&count)))
		{
			return -1;
		}

		ct->tv_sec = count.QuadPart / g_counts_per_sec.QuadPart;
		ct->tv_nsec = (long)(((count.QuadPart % g_counts_per_sec.QuadPart) * BILLION) / g_counts_per_sec.QuadPart);

		return 0;
	}

	#define MAX_SLEEP_IN_MS         4294967294UL

	#define POW10_2     INT64_C(100)
	#define POW10_3     INT64_C(1000)
	#define POW10_4     INT64_C(10000)
	#define POW10_6     INT64_C(1000000)
	#define POW10_7     INT64_C(10000000)
	#define POW10_9     INT64_C(1000000000)

	int nanosleep(const struct timespec *request, struct timespec *remain)
	{
		unsigned long ms, rc = 0;
		unsigned __int64 u64, want, real;

		union {
			unsigned __int64 ns100;
			FILETIME ft;
		}  _start, _end;

		if (request->tv_sec < 0 || request->tv_nsec < 0 || request->tv_nsec >= POW10_9) {
			errno = EINVAL;
			return -1;
		}

		if (remain != NULL) GetSystemTimeAsFileTime(&_start.ft);

		want = u64 = request->tv_sec * POW10_3 + request->tv_nsec / POW10_6;
		while (u64 > 0 && rc == 0) {
			if (u64 >= MAX_SLEEP_IN_MS) ms = MAX_SLEEP_IN_MS;
			else ms = (unsigned long)u64;

			u64 -= ms;
			rc = SleepEx(ms, TRUE);
		}

		if (rc != 0) { /* WAIT_IO_COMPLETION (192) */
			if (remain != NULL) {
				GetSystemTimeAsFileTime(&_end.ft);
				real = (_end.ns100 - _start.ns100) / POW10_4;

				if (real >= want) u64 = 0;
				else u64 = want - real;

				remain->tv_sec = u64 / POW10_3;
				remain->tv_nsec = (long)(u64 % POW10_3) * POW10_6;
			}

			errno = EINTR;
			return -1;
		}

		return 0;
	}

	int clock_nanosleep(int clock_id, int flags,
		const struct timespec *request,
		struct timespec *remain)
	{
		struct timespec tp;

		if (clock_id != CLOCK_REALTIME)
			return 0;

		if (flags == 0)
			return nanosleep(request, remain);

		/* TIMER_ABSTIME = 1 */
		clock_gettime(CLOCK_REALTIME, &tp);

		tp.tv_sec = request->tv_sec - tp.tv_sec;
		tp.tv_nsec = request->tv_nsec - tp.tv_nsec;
		if (tp.tv_nsec < 0) {
			tp.tv_nsec += POW10_9;
			tp.tv_sec--;

		}

		return nanosleep(&tp, remain);
	}
#else
	#define __USE_POSIX199309 1
	#define __USE_XOPEN2K 1
	#include <time.h>
#endif

#endif