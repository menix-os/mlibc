#ifndef _MENIX_SYSCALL_H
#define _MENIX_SYSCALL_H

#include <stddef.h>

#define SYSCALL_exit 0
#define SYSCALL_sigprocmask 1
#define SYSCALL_sigsuspend 2
#define SYSCALL_sigpending 3
#define SYSCALL_sigaction 4
#define SYSCALL_sigreturn 5
#define SYSCALL_sigtimedwait 6
#define SYSCALL_mmap 7
#define SYSCALL_munmap 8
#define SYSCALL_mremap 9
#define SYSCALL_mprotect 10
#define SYSCALL_execve 11
#define SYSCALL_fork 12
#define SYSCALL_kill 13
#define SYSCALL_gettid 14
#define SYSCALL_getpid 15
#define SYSCALL_waitpid 16
#define SYSCALL_read 17
#define SYSCALL_write 18
#define SYSCALL_seek 19
#define SYSCALL_ioctl 20
#define SYSCALL_openat 21
#define SYSCALL_close 22
#define SYSCALL_stat 23
#define SYSCALL_faccessat 24
#define SYSCALL_fcntl 25
#define SYSCALL_readdir 26
#define SYSCALL_getcwd 27
#define SYSCALL_chdir 28
#define SYSCALL_fchdir 29
#define SYSCALL_mkdirat 30
#define SYSCALL_rename 31
#define SYSCALL_chmodat 32
#define SYSCALL_chownat 33
#define SYSCALL_linkat 34
#define SYSCALL_unlinkat 35
#define SYSCALL_readlinkat 36
#define SYSCALL_mount 37
#define SYSCALL_unmount 38
#define SYSCALL_setuid 39
#define SYSCALL_getuid 40
#define SYSCALL_setgid 41
#define SYSCALL_getgid 42
#define SYSCALL_umask 43
#define SYSCALL_poll 44
#define SYSCALL_isatty 45
#define SYSCALL_chroot 46
#define SYSCALL_futex_wait 47
#define SYSCALL_futex_wake 48
#define SYSCALL_socket 49
#define SYSCALL_socketpair 50
#define SYSCALL_bind 51
#define SYSCALL_connect 52
#define SYSCALL_accept 53
#define SYSCALL_listen 54
#define SYSCALL_getpeername 55
#define SYSCALL_getsockname 56
#define SYSCALL_getsockopt 57
#define SYSCALL_setsockopt 58
#define SYSCALL_recvmsg 59
#define SYSCALL_sendmsg 60
#define SYSCALL_sethostname 61
#define SYSCALL_uname 62
#define SYSCALL_archctl 63
#define SYSCALL_readtimer 64
#define SYSCALL_savetls 65

#ifndef __MLIBC_ABI_ONLY

struct syscall_result {
	size_t value;
	size_t error;
};
static_assert(sizeof(syscall_result) == 16);

#ifdef __x86_64__
extern "C" inline syscall_result syscall(
    size_t num,
    size_t a0 = 0,
    size_t a1 = 0,
    size_t a2 = 0,
    size_t a3 = 0,
    size_t a4 = 0,
    size_t a5 = 0
) {
	syscall_result r;
	asm volatile("mov %2, %%rax;"
	             "mov %3, %%rdi;"
	             "mov %4, %%rsi;"
	             "mov %5, %%rdx;"
	             "mov %6, %%r8;"
	             "mov %7, %%r10;"
	             "mov %8, %%r9;"
	             "syscall;"
	             "mov %%rax, %0;"
	             "mov %%rdx, %1;"
	             : "=g"(r.value), "=g"(r.error)
	             : "g"(num), "g"(a0), "g"(a1), "g"(a2), "g"(a3), "g"(a4), "g"(a5)
	             : "rax", "rdi", "rsi", "rdx", "r8", "r10", "r9", "rcx", "r11", "memory");
	return r;
}
#endif /* __x86_64 */

#endif /* !__MLIBC_ABI_ONLY */

#endif /* _MENIX_SYSCALL_H */
