// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int close(int fd)
{
	/* TODO: Implement close(). */
	/// Am aflat cum se foloseste syscall din fisierul read_write.c
	// Am schimbat doar parametrii
	int ret = syscall(__NR_close, fd);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
}
