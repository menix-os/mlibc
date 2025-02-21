#include <bits/ensure.h>
#include <dirent.h>
#include <errno.h>
#include <mlibc/all-sysdeps.hpp>
#include <mlibc/debug.hpp>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <unistd.h>

#include <menix/syscall.h>

namespace mlibc {

void sys_libc_log(const char *message) {
	ssize_t written;
	sys_write(1, message, strlen(message), &written);
	const char newline = '\n';
	sys_write(1, &newline, 1, &written);
}

[[noreturn]] void sys_libc_panic() {
	sys_libc_log("mlibc panic!");
	sys_exit(0xC);
}

void sys_exit(int code) {
	syscall(SYSCALL_exit, code);
	__builtin_unreachable();
}

int sys_tcb_set(void *pointer) { return syscall(SYSCALL_savetls, (size_t)pointer).error; }

int sys_futex_tid() { return syscall(SYSCALL_gettid).error; }

int sys_futex_wait(int *pointer, int expected, const struct timespec *time) {
	return syscall(SYSCALL_futex_wait, (size_t)pointer, (size_t)expected, (size_t)time).error;
}

int sys_futex_wake(int *pointer) { return syscall(SYSCALL_futex_wake, (size_t)pointer).error; }

int sys_sigsuspend(const sigset_t *set) {
	syscall(SYSCALL_sigsuspend, (size_t)set);
	return EINTR;
}

int sys_sigaction(int, const struct sigaction *__restrict, struct sigaction *__restrict) {
	return 0;
}

int sys_anon_allocate(size_t size, void **pointer) {
	auto r =
	    syscall(SYSCALL_mmap, 0, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
	if (r.error != 0)
		return r.error;
	*pointer = (void *)r.value;
	return 0;
}

int sys_anon_free(void *pointer, size_t size) {
	return syscall(SYSCALL_munmap, (size_t)pointer, size).error;
}

int sys_openat(int dirfd, const char *path, int flags, mode_t mode, int *fd) {
	auto r = syscall(SYSCALL_openat, dirfd, (size_t)path, flags, mode);
	if (r.error != 0)
		return r.error;
	*fd = (int)r.value;
	return 0;
}

int sys_open(const char *pathname, int flags, mode_t mode, int *fd) {
	return sys_openat(AT_FDCWD, pathname, flags, mode, fd);
}

int sys_read(int fd, void *buf, size_t count, ssize_t *bytes_read) {
	auto r = syscall(SYSCALL_read, (size_t)fd, (size_t)buf, count);
	if (r.error != 0)
		return r.error;
	*bytes_read = (ssize_t)r.value;
	return 0;
}

int sys_seek(int fd, off_t offset, int whence, off_t *new_offset) {
	auto r = syscall(SYSCALL_seek, fd, offset, whence);
	if (r.error != 0)
		return r.error;
	*new_offset = r.value;
	return 0;
}

int sys_close(int fd) { return syscall(SYSCALL_close, fd).error; }

int sys_stat(fsfd_target fsfdt, int fd, const char *path, int flags, struct stat *statbuf) {
	(void)fsfdt;
	return syscall(SYSCALL_stat, (size_t)fd, (size_t)path, flags, (size_t)statbuf).error;
}

int sys_vm_map(void *hint, size_t size, int prot, int flags, int fd, off_t offset, void **window) {
	auto r = syscall(SYSCALL_mmap, (size_t)hint, size, prot, flags, fd, offset);
	if (r.error != 0)
		return r.error;
	*window = (void *)r.value;
	return 0;
}

int sys_vm_unmap(void *pointer, size_t size) {
	return syscall(SYSCALL_munmap, (size_t)pointer, size).error;
}

int sys_vm_protect(void *pointer, size_t size, int prot) {
	return syscall(SYSCALL_mprotect, (size_t)pointer, size, prot).error;
}

int sys_write(int fd, const void *buf, size_t count, ssize_t *bytes_written) {
	auto r = syscall(SYSCALL_write, (size_t)fd, (size_t)buf, count);
	if (r.error != 0)
		return r.error;
	*bytes_written = r.value;
	return 0;
}

int sys_clock_get(int clock, time_t *secs, long *nanos) {
	struct timespec ts;
	auto r = syscall(SYSCALL_readtimer, clock, (size_t)&ts);
	if (r.error != 0)
		return r.error;
	*secs = ts.tv_sec;
	*nanos = ts.tv_nsec;
	return 0;
}

int sys_uname(struct utsname *buf) { return syscall(SYSCALL_uname, (size_t)buf).error; }

int sys_fork(pid_t *child) {
	auto r = syscall(SYSCALL_fork);
	if (r.error != 0)
		return r.error;
	*child = r.value;
	return 0;
}

int sys_waitpid(pid_t pid, int *status, int flags, struct rusage *ru, pid_t *ret_pid) {
	(void)ru;
	auto r = syscall(SYSCALL_waitpid, (size_t)pid, (size_t)status, flags);
	if (r.error != 0)
		return r.error;
	*ret_pid = (int)r.value;
	return 0;
}

int sys_chdir(const char *path) { return syscall(SYSCALL_chdir, (size_t)path).error; }

pid_t sys_getpid() { return syscall(SYSCALL_getpid).value; }

pid_t sys_getppid() { return 0; }

uid_t sys_getuid() { return syscall(SYSCALL_getuid).value; }

uid_t sys_geteuid() { return 0; }

gid_t sys_getgid() { return 0; }

int sys_setgid(gid_t) { return 0; }

int sys_getpgid(pid_t, pid_t *) { return 0; }

gid_t sys_getegid() { return 0; }

int sys_setpgid(pid_t, pid_t) { return 0; }

int sys_ttyname(int, char *, size_t) { return ENOSYS; }

int sys_getcwd(char *buffer, size_t size) {
	return syscall(SYSCALL_getcwd, (size_t)buffer, size).error;
}

int sys_execve(const char *path, char *const argv[], char *const envp[]) {
	return syscall(SYSCALL_execve, (size_t)path, (size_t)argv, (size_t)envp).error;
}

int sys_isatty(int fd) { return syscall(SYSCALL_isatty, fd).value; }

int sys_sigprocmask(int how, const sigset_t *__restrict set, sigset_t *__restrict retrieve) {
	return syscall(SYSCALL_sigprocmask, how, (size_t)set, (size_t)retrieve).error;
}

} // namespace mlibc
