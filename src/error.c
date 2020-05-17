#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "error.h"

void error(const char *format, ...) {
	va_list argptr;
	va_start(argptr, format);
	vfprintf(stderr, format, argptr);
	va_end(argptr);
	fprintf(stderr, "\n");
	exit(EXIT_FAILURE);
}