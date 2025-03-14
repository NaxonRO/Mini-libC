// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int truncate(const char *path, off_t length)
{
	/* TODO: Implement truncate(). */
	/// Am aflat cum se foloseste syscall din fisierul read_write.c
	// Am schimbat doar parametrii
	int ret = syscall(__NR_truncate, path, length);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
}
