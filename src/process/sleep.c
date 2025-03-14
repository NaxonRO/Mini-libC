// SPDX-License-Identifier: BSD-3-Clause

#include <internal/syscall.h>
#include <unistd.h>

unsigned int sleep(unsigned int seconds)
{
	// Folosim structura declarata din header-ul time.h
	struct timespec inc, fin;

	// declaram secundele si nanosecundele
	inc.tv_sec = seconds;
	inc.tv_nsec = 0;

	// Apelam nanosleep
	nanosleep(&inc, &fin);
	return 1;
}
