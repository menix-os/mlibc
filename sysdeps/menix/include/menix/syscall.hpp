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
#define SYSCALL_yield 7
#define SYSCALL_mmap 8
#define SYSCALL_munmap 9
#define SYSCALL_mprotect 10
#define SYSCALL_sigprocmask 11
#define SYSCALL_sigsuspend 12
#define SYSCALL_sigpending 13
#define SYSCALL_sigaction 14
#define SYSCALL_sigtimedwait 15
#define SYSCALL_execve 16
#define SYSCALL_fork 17
#define SYSCALL_kill 18
#define SYSCALL_gettid 19
#define SYSCALL_getpid 20
#define SYSCALL_getppid 21
#define SYSCALL_waitid 22
#define SYSCALL_read 23
#define SYSCALL_write 24
#define SYSCALL_seek 25
#define SYSCALL_ioctl 26
#define SYSCALL_openat 27
#define SYSCALL_close 28
#define SYSCALL_stat 29
#define SYSCALL_fstat 30
#define SYSCALL_faccessat 31
#define SYSCALL_fcntl 32
#define SYSCALL_readdir 33
#define SYSCALL_getcwd 34
#define SYSCALL_chdir 35
#define SYSCALL_fchdir 36
#define SYSCALL_mkdirat 37
#define SYSCALL_rmdirat 38
#define SYSCALL_rename 39
#define SYSCALL_chmodat 40
#define SYSCALL_chownat 41
#define SYSCALL_linkat 42
#define SYSCALL_unlinkat 43
#define SYSCALL_readlinkat 44
#define SYSCALL_dup 45
#define SYSCALL_sync 46
#define SYSCALL_fsync 47
#define SYSCALL_getsid 48
#define SYSCALL_setuid 49
#define SYSCALL_getuid 50
#define SYSCALL_setgid 51
#define SYSCALL_getgid 52
#define SYSCALL_geteuid 53
#define SYSCALL_getegid 54
#define SYSCALL_getpgid 55
#define SYSCALL_setpgid 56
#define SYSCALL_getgroups 57
#define SYSCALL_umask 58
#define SYSCALL_poll 59
#define SYSCALL_pipe 60
#define SYSCALL_chroot 61
#define SYSCALL_mount 62
#define SYSCALL_unmount 63
#define SYSCALL_swapon 64
#define SYSCALL_swapoff 65
#define SYSCALL_futex_wait 66
#define SYSCALL_futex_wake 67
#define SYSCALL_socket 68
#define SYSCALL_socketpair 69
#define SYSCALL_bind 70
#define SYSCALL_connect 71
#define SYSCALL_accept 72
#define SYSCALL_listen 73
#define SYSCALL_getpeername 74
#define SYSCALL_getsockname 75
#define SYSCALL_getsockopt 76
#define SYSCALL_setsockopt 77
#define SYSCALL_recvmsg 78
#define SYSCALL_sendmsg 79
#define SYSCALL_gethostname 80
#define SYSCALL_sethostname 81
#define SYSCALL_sched_setaffinity 82
#define SYSCALL_sched_getaffinity 83

struct syscall_result {
	size_t value;
	size_t error;
};
static_assert(sizeof(syscall_result) == 16);

#ifndef __MLIBC_ABI_ONLY

extern "C" inline syscall_result menix_syscall(
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
	register size_t r3 asm("r10") = a3;
	register size_t r4 asm("r8") = a4;
	register size_t r5 asm("r9") = a5;

	asm volatile("syscall"
	             : "=a"(r.value), "=d"(r.error)
	             : "a"(num), "D"(a0), "S"(a1), "d"(a2), "r"(r3), "r"(r4), "r"(r5)
	             : "memory", "rcx", "r11");
#endif /* __x86_64 */
	return r;
}

#endif /* !__MLIBC_ABI_ONLY */

#endif /* _MENIX_SYSCALL_H */
