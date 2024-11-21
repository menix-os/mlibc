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
		char c = '\n';
		sys_write(1, &c, 1, &written);
	}

	[[noreturn]] void sys_libc_panic() {
		//sys_libc_log("\nMLIBC PANIC\n");
		sys_exit(1);
	}

	int sys_tcb_set(void *pointer) {
		return syscall(SYSCALL_archctl, ArchCtl_SetFsBase, (size_t)pointer).error;
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
		syscall_result r = syscall(SYSCALL_mmap, 0, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
		SYSCALL_ERR_CHECK(r)
		*pointer = (void*)r.value;
		return 0;
	}

	int sys_anon_free(void *pointer, size_t size) {
		return syscall(SYSCALL_munmap, (size_t)pointer, size).error;
	}

	int sys_open(const char *pathname, int flags, mode_t mode, int *fd) {
		syscall_result r = syscall(SYSCALL_open, (size_t)pathname, flags, mode);
		SYSCALL_ERR_CHECK(r)
		*fd = (int)r.value;
		return 0;
	}

	int sys_read(int fd, void *buf, size_t count, ssize_t *bytes_read) {
		syscall_result r = syscall(SYSCALL_read, (size_t)fd, (size_t)buf, count);
		SYSCALL_ERR_CHECK(r)
		*bytes_read = (ssize_t)r.value;
		return 0;
	}

	int sys_seek(int fd, off_t offset, int whence, off_t *new_offset) {
		syscall_result r = syscall(SYSCALL_seek, fd, offset, whence);
		SYSCALL_ERR_CHECK(r)
		*new_offset = r.value;
		return 0;
	}

	int sys_close(int fd) {
		return syscall(SYSCALL_close, fd).error;
	}

	int sys_stat(fsfd_target fsfdt, int fd, const char *path, int flags, struct stat *statbuf) {
		return syscall(SYSCALL_stat, (size_t)fd, (size_t)path, (size_t)statbuf).error;
	}

	int sys_vm_map(void *hint, size_t size, int prot, int flags, int fd, off_t offset, void **window) {
		syscall_result r = syscall(SYSCALL_mmap, (size_t)hint, size, prot, flags, fd, offset);
		SYSCALL_ERR_CHECK(r)
		*window = (void*)r.value;
		return 0;
	}

	int sys_vm_unmap(void *pointer, size_t size) {
		return syscall(SYSCALL_munmap, (size_t)pointer, size).error;
	}

	int sys_vm_protect(void *pointer, size_t size, int prot) {
		return syscall(SYSCALL_mprotect, (size_t)pointer, size, prot).error;
	}

	void sys_exit(int code) {
		syscall(SYSCALL_exit, code);
		for (;;);
	}

	int sys_write(int fd, const void *buf, size_t count, ssize_t *bytes_written) {
		syscall_result r = syscall(SYSCALL_write, (size_t)fd, (size_t)buf, count);
		SYSCALL_ERR_CHECK(r)
		*bytes_written = r.value;
		return 0;
	}

	int sys_clock_get(int clock, time_t *secs, long *nanos) {
		// TODO
		return 0;
	}

	int sys_uname(struct utsname *buf) {
		syscall_result r = syscall(SYSCALL_uname, (size_t)buf);
		SYSCALL_ERR_CHECK(r)
		return 0;
	}

	int sys_fork(pid_t *child) {
		syscall_result r = syscall(SYSCALL_fork);
		SYSCALL_ERR_CHECK(r)
		*child = r.value;
		return 0;
	}

	int sys_waitpid(pid_t pid, int *status, int flags, struct rusage *ru, pid_t *ret_pid) {
		syscall_result r = syscall(SYSCALL_waitpid, (size_t)pid, (size_t)status, flags);
		SYSCALL_ERR_CHECK(r)
		*ret_pid = (int)r.value;
		return 0;
	}

	int sys_chdir(const char *path) {
		return syscall(SYSCALL_chdir, (size_t)path).error;
	}

	pid_t sys_getpid() {
		return syscall(SYSCALL_getpid).value;
	}

	pid_t sys_getppid() {
		return 0;
	}

	uid_t sys_getuid() {
		return 0;
	}

	uid_t sys_geteuid() {
		return 0;
	}

	gid_t sys_getgid() {
		return 0;
	}

	int sys_setgid(gid_t) {
		return 0;
	}

	int sys_getpgid(pid_t, pid_t *) {
		return 0;
	}

	gid_t sys_getegid() {
		return 0;
	}

	int sys_setpgid(pid_t, pid_t) {
		return 0;
	}

	int sys_ttyname(int, char *, size_t) {
		return ENOSYS;
	}

	int sys_getcwd(char *buffer, size_t size) {
		return syscall(SYSCALL_getcwd, (size_t)buffer, size).error;
	}

	int sys_execve(const char *path, char *const argv[], char *const envp[]) {
		return syscall(SYSCALL_execve, (size_t)path, (size_t)argv, (size_t)envp).error;
	}

	int sys_isatty(int fd) {
		// TODO
		if (fd >= 0 && fd < 2)
			return 0;
		return ENOTTY;
	}

} // namespace mlibc
