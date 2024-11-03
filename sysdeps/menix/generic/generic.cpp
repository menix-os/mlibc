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
		ssize_t written;
		sys_write(1, message, strlen(message), &written);
		sys_write(1, "\n", 1, &written);
	}

	[[noreturn]] void sys_libc_panic() {
		sys_libc_log("\nMLIBC PANIC\n");
		sys_exit(1);
	}

	int sys_tcb_set(void *pointer) {
		mlibc::infoLogger() << "Hello" << frg::endlog;
		return syscall(SYSCALL_archctl, ArchCtl_SetFsBase, (size_t)pointer);
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
		*pointer = (void*)syscall(SYSCALL_mmap, 0, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
		return 0;
	}

	int sys_anon_free(void *pointer, size_t size) {
		// TODO
		return 0;
	}

	int sys_open(const char *pathname, int flags, mode_t mode, int *fd) {
		size_t result = syscall(SYSCALL_open, (size_t)pathname, flags, mode);

		if (result < 0)
			return result;

		*fd = (int)result;

		return 0;
	}

	int sys_read(int fd, void *buf, size_t count, ssize_t *bytes_read) {
		size_t result = syscall(SYSCALL_read, (size_t)fd, (size_t)buf, count);
		if (result < 0)
			return result;

		*bytes_read = result;
		return 0;
	}

	int sys_seek(int fd, off_t offset, int whence, off_t *new_offset) {
		ssize_t result = syscall(SYSCALL_seek, fd, offset, whence);

		if (result < 0)
			return -result;

		*new_offset = result;
		return 0;
	}

	int sys_close(int fd) {
		return syscall(SYSCALL_close, fd);
	}

	int sys_stat(fsfd_target fsfdt, int fd, const char *path, int flags,
			struct stat *statbuf) {
		// TODO
		return syscall(SYSCALL_stat, (size_t)path, (size_t)statbuf);
	}

	int sys_vm_map(void *hint, size_t size, int prot, int flags, int fd, off_t offset, void **window) {
		(void)window;
		void* result = (void*)syscall(SYSCALL_mmap, (size_t)hint, size, prot, flags, fd, offset);
		if (result == MAP_FAILED)
			return ENOMEM;
		*window = result;
		return 0;
	}

	int sys_vm_unmap(void *pointer, size_t size) {
		return syscall(SYSCALL_munmap, (size_t)pointer, size);
	}

	int sys_vm_protect(void *pointer, size_t size, int prot) {
		return syscall(SYSCALL_mprotect, (size_t)pointer, size, prot);
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
