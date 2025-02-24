#ifndef _MENIX_SYSCALL_H
#define _MENIX_SYSCALL_H

#include <stddef.h>

#define SYSCALL_exit 0
#define SYSCALL_uname 1
#define SYSCALL_savetls 2
#define SYSCALL_archctl 3
#define SYSCALL_shutdown 4
#define SYSCALL_reboot 5
#define SYSCALL_readtimer 6
#define SYSCALL_sigprocmask 7
#define SYSCALL_sigsuspend 8
#define SYSCALL_sigpending 9
#define SYSCALL_sigaction 0
#define SYSCALL_sigtimedwait 11
#define SYSCALL_mmap 12
#define SYSCALL_munmap 13
#define SYSCALL_mprotect 14
#define SYSCALL_execve 15
#define SYSCALL_fork 16
#define SYSCALL_kill 17
#define SYSCALL_gettid 18
#define SYSCALL_getpid 19
#define SYSCALL_getppid 20
#define SYSCALL_waitid 21
#define SYSCALL_read 22
#define SYSCALL_write 23
#define SYSCALL_seek 24
#define SYSCALL_ioctl 25
#define SYSCALL_openat 26
#define SYSCALL_close 27
#define SYSCALL_stat 28
#define SYSCALL_fstat 29
#define SYSCALL_faccessat 30
#define SYSCALL_fcntl 31
#define SYSCALL_readdir 32
#define SYSCALL_getcwd 33
#define SYSCALL_chdir 34
#define SYSCALL_fchdir 35
#define SYSCALL_mkdirat 36
#define SYSCALL_rmdirat 37
#define SYSCALL_rename 38
#define SYSCALL_chmodat 39
#define SYSCALL_chownat 40
#define SYSCALL_linkat 41
#define SYSCALL_unlinkat 42
#define SYSCALL_readlinkat 43
#define SYSCALL_setuid 44
#define SYSCALL_getuid 45
#define SYSCALL_setgid 46
#define SYSCALL_getgid 47
#define SYSCALL_geteuid 48
#define SYSCALL_getegid 49
#define SYSCALL_getpgid 50
#define SYSCALL_setpgid 51
#define SYSCALL_umask 52
#define SYSCALL_poll 53
#define SYSCALL_pipe 54
#define SYSCALL_chroot 55
#define SYSCALL_mount 56
#define SYSCALL_unmount 57
#define SYSCALL_swapon 58
#define SYSCALL_swapoff 59
#define SYSCALL_futex_wait 60
#define SYSCALL_futex_wake 61
#define SYSCALL_socket 62
#define SYSCALL_socketpair 63
#define SYSCALL_bind 64
#define SYSCALL_connect 65
#define SYSCALL_accept 66
#define SYSCALL_listen 67
#define SYSCALL_getpeername 68
#define SYSCALL_getsockname 69
#define SYSCALL_getsockopt 70
#define SYSCALL_setsockopt 71
#define SYSCALL_recvmsg 72
#define SYSCALL_sendmsg 73
#define SYSCALL_sethostname 74
#define SYSCALL_sched_setaffinity 75
#define SYSCALL_sched_getaffinity 76

#ifndef __MLIBC_ABI_ONLY

struct syscall_result {
	size_t value;
	size_t error;
};
static_assert(sizeof(syscall_result) == 16);

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
#ifdef __x86_64__
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
#endif /* __x86_64 */
	return r;
}

#endif /* !__MLIBC_ABI_ONLY */

#endif /* _MENIX_SYSCALL_H */
