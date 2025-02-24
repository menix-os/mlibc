#include <abi-bits/pid_t.h>
#include <menix/syscall.hpp>
#include <mlibc/all-sysdeps.hpp>
#include <stddef.h>
#include <string.h>

namespace mlibc {

void sys_libc_log(const char *message) {
	syscall(SYSCALL_write, 1, (size_t)message, strlen(message));
	syscall(SYSCALL_write, 1, (size_t)"\n", 1);
}

[[noreturn]] void sys_libc_panic() {
	sys_libc_log("mlibc panic!");
	syscall(SYSCALL_exit, 1);
	__builtin_unreachable();
}

int sys_tcb_set(void *pointer) { return syscall(SYSCALL_savetls, (size_t)pointer).error; }

int sys_futex_tid() { return syscall(SYSCALL_gettid).value; }

int sys_futex_wait(int *pointer, int expected, const struct timespec *time) {
	return syscall(SYSCALL_futex_wait, (size_t)pointer, (size_t)expected, (size_t)time).error;
}

int sys_futex_wake(int *pointer) { return syscall(SYSCALL_futex_wake, (size_t)pointer).error; }

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
	return syscall(SYSCALL_fstat, (size_t)fd, (size_t)path, flags, (size_t)statbuf).error;
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

} // namespace mlibc
