// SPDX-License-Identifier: BSD-3-Clause

#include <internal/syscall.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

void nanosleep(struct timespec *rqtp, struct timespec *rmtp)
{
	// Am folosit syscall, cu parametrii ca la cele de open ... read_write.c
	syscall(__NR_nanosleep, rqtp, rmtp);
}
