// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...) {
    /// Am aflat cum se foloseste syscall din fisierul read_write.c
	// Am schimbat doar parametrii
	int ret = syscall(__NR_open, filename, flags);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
}
