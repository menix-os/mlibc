#include <bits/ensure.h>
#include <mlibc/all-sysdeps.hpp>
#include <mlibc/debug.hpp>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <sys/select.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#include <menix/syscall.h>
#include <menix/archctl.h>
#include <menix/powerctl.h>

namespace mlibc {
	void sys_libc_log(const char *message) {
		syscall(SYSCALL_write, 1, (size_t)message);
	}

	[[noreturn]] void sys_libc_panic() {
		// TODO
	}

	int sys_tcb_set(void *pointer) {
		// TODO
		return 0;
	}

	int sys_futex_tid() {
		// TODO
		return 0;
	}

	int sys_futex_wait(int *pointer, int expected, const struct timespec *time) {
		// TODO
		return 0;
	}

	int sys_futex_wake(int *pointer) {
		// TODO
		return 0;
	}

	int sys_anon_allocate(size_t size, void **pointer) {
		// TODO
		return 0;
	}

	int sys_anon_free(void *pointer, size_t size) {
		// TODO
		return 0;
	}

	int sys_open(const char *pathname, int flags, mode_t mode, int *fd) {
		// TODO
		return 0;
	}

	int sys_read(int fd, void *buf, size_t count, ssize_t *bytes_read) {
		// TODO
		return 0;
	}

	int sys_seek(int fd, off_t offset, int whence, off_t *new_offset) {
		// TODO
		return 0;
	}

	int sys_close(int fd) {
		// TODO
		return 0;
	}

	int sys_stat(fsfd_target fsfdt, int fd, const char *path, int flags,
			struct stat *statbuf) {
		// TODO
		return 0;
	}

	int sys_vm_map(void *hint, size_t size, int prot, int flags, int fd, off_t offset, void **window) {
		// TODO
		return 0;
	}

	int sys_vm_unmap(void *pointer, size_t size) {
		// TODO
		return 0;
	}

	int sys_vm_protect(void *pointer, size_t size, int prot) {
		// TODO
		return 0;
	}

	void sys_exit(int code) {
		syscall(SYSCALL_exit, code);
		for (;;);
	}

	int sys_write(int fd, const void *buf, size_t count, ssize_t *bytes_written) {
		size_t result = syscall(SYSCALL_write, (size_t)fd, (size_t)buf, count);
		if (result < 0)
			return result;

		*bytes_written = result;
		return 0;
	}

	int sys_clock_get(int clock, time_t *secs, long *nanos) {
		// TODO
		return 0;
	}
} // namespace mlibc
