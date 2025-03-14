// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <errno.h>

int fstat(int fd, struct stat *st)
{
	/* TODO: Implement fstat(). */
	/// Am aflat cum se foloseste syscall din fisierul read_write.c
	// Am schimbat doar parametrii
	int ret = syscall(__NR_fstat, fd, st);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
}
