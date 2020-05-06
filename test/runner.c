#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <time.h>
#include "runner.h"

static jmp_buf env;
static char error[BUFSIZ];
static int failed;

static void handle_sigabrt(int signum) {
	(void)signum;
	longjmp(env, 1);
}

static void handle_sigsegv(int signum) {
	(void)signum;
	strcpy(error, "Segmentation fault\n");
	longjmp(env, 1);
}

static const char *null_device(void) {
	const char *candidates[] = { "/dev/null", "NUL" };
	for (size_t i = 0; i < sizeof(candidates) / sizeof(*candidates); i++) {
		FILE *f = fopen(candidates[i], "r");
		if (f) {
			fclose(f);
			return candidates[i];
		}
	}
	return NULL;
}

void runner_init(void) {
	srand(time(NULL));
	freopen(null_device(), "a", stderr);
	setbuf(stderr, error);
}

void runner_run(const char *name, void (*test)(void)) {
	signal(SIGABRT, handle_sigabrt);
	signal(SIGSEGV, handle_sigsegv);

	if (!setjmp(env)) {
		test();
		printf("\033[1;32m+ %s\033[0m\n", name);
	} else {
		printf("\033[1;31m- %s\n    %s\033[0m", name, error);
		failed++;
	}

	memset(error, 0, BUFSIZ);
}

int runner_report(void) {
	if (failed) {
		printf("\033[1;31m  FAILED\033[0m\n");
	} else {
		printf("\033[1;32m  PASSED\033[0m\n");
	}
	return failed;
}