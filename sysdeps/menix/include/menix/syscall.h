#ifndef _MENIX_SYSCALL_H
#define _MENIX_SYSCALL_H

#include <stddef.h>
#include <stdint.h>

#define SYSCALL_exit 0
#define SYSCALL_open 1
#define SYSCALL_close 2
#define SYSCALL_stat 3
#define SYSCALL_access 4
#define SYSCALL_read 5
#define SYSCALL_write 6
#define SYSCALL_seek 7
#define SYSCALL_ioctl 8
#define SYSCALL_chdir 9
#define SYSCALL_chmod 10
#define SYSCALL_chown 11
#define SYSCALL_mount 12
#define SYSCALL_unmount 13
#define SYSCALL_link 14
#define SYSCALL_unlink 15
#define SYSCALL_symlink 16
#define SYSCALL_readlink 17
#define SYSCALL_rmdir 18
#define SYSCALL_setuid 19
#define SYSCALL_getuid 20
#define SYSCALL_setgid 21
#define SYSCALL_getgid 22
#define SYSCALL_sync 23
#define SYSCALL_mmap 24
#define SYSCALL_munmap 25
#define SYSCALL_mremap 26
#define SYSCALL_mprotect 27
#define SYSCALL_execve 28
#define SYSCALL_fork 29
#define SYSCALL_kill 30
#define SYSCALL_getpid 31
#define SYSCALL_getparentpid 32
#define SYSCALL_recvmsg 33
#define SYSCALL_sendmsg 34
#define SYSCALL_accept 35
#define SYSCALL_getpeername 36
#define SYSCALL_getsockname 37
#define SYSCALL_uname 38
#define SYSCALL_powerctl 39
#define SYSCALL_archctl 40

#ifndef __MLIBC_ABI_ONLY

size_t syscall(size_t num, size_t a0 = 0, size_t a1 = 0, size_t a2 = 0, size_t a3 = 0, size_t a4 = 0, size_t a5 = 0);

#endif /* !__MLIBC_ABI_ONLY */

#endif /* _MENIX_SYSCALL_H */
