#ifndef RUNNER_H
#define RUNNER_H

#define runner_test(test) runner_run(#test, test)

void runner_init(void);
void runner_run(const char *name, void (*test)(void));
int runner_report(void);

#endif