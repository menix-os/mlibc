#include <abi-bits/pid_t.h>
#include <errno.h>
#include <menix/syscall.hpp>
#include <mlibc/all-sysdeps.hpp>
#include <string.h>

namespace mlibc {

[[noreturn]] void sys_exit(int status) {
	syscall(SYSCALL_exit, status);
	__builtin_unreachable();
}

[[noreturn, gnu::weak]] void sys_thread_exit();

int sys_clock_get(int clock, time_t *secs, long *nanos) {
	struct timespec ts;
	auto r = syscall(SYSCALL_readtimer, clock, (size_t)&ts);
	if (r.error != 0)
		return r.error;
	*secs = ts.tv_sec;
	*nanos = ts.tv_nsec;
	return 0;
}

[[gnu::weak]] int sys_flock(int fd, int options);

int sys_open_dir(const char *path, int *handle) { return sys_open(path, O_DIRECTORY, 0, handle); }

[[gnu::weak]] int sys_read_entries(int handle, void *buffer, size_t max_size, size_t *bytes_read);

[[gnu::weak]] int sys_readv(int fd, const struct iovec *iovs, int iovc, ssize_t *bytes_read);

int sys_write(int fd, const void *buf, size_t count, ssize_t *bytes_written) {
	auto r = syscall(SYSCALL_write, (size_t)fd, (size_t)buf, count);
	if (r.error != 0)
		return r.error;
	*bytes_written = r.value;
	return 0;
}

[[gnu::weak]] int sys_pread(int fd, void *buf, size_t n, off_t off, ssize_t *bytes_read);
[[gnu::weak]] int sys_pwrite(int fd, const void *buf, size_t n, off_t off, ssize_t *bytes_read);

int sys_access(const char *path, int mode) { return sys_faccessat(AT_FDCWD, path, mode, 0); }

int sys_faccessat(int dirfd, const char *pathname, int mode, int flags) {
	return syscall(SYSCALL_faccessat, dirfd, (size_t)pathname, mode, flags).error;
}

[[gnu::weak]] int sys_dup(int fd, int flags, int *newfd);
[[gnu::weak]] int sys_dup2(int fd, int flags, int newfd);

int sys_isatty(int fd) {
	struct winsize ws;
	long ret = sys_ioctl(fd, TIOCGWINSZ, &ws, 0);

	if (!ret)
		return 0;

	return ENOTTY;
}

[[gnu::weak]] int sys_statvfs(const char *path, struct statvfs *out);
[[gnu::weak]] int sys_fstatvfs(int fd, struct statvfs *out);
[[gnu::weak]] int sys_readlink(const char *path, void *buffer, size_t max_size, ssize_t *length);
[[gnu::weak]] int
sys_readlinkat(int dirfd, const char *path, void *buffer, size_t max_size, ssize_t *length);
[[gnu::weak]] int sys_rmdir(const char *path);
[[gnu::weak]] int sys_ftruncate(int fd, size_t size);
[[gnu::weak]] int sys_fallocate(int fd, off_t offset, size_t size);
[[gnu::weak]] int sys_unlinkat(int fd, const char *path, int flags);

int sys_openat(int dirfd, const char *path, int flags, mode_t mode, int *fd) {
	auto r = syscall(SYSCALL_openat, dirfd, (size_t)path, flags, mode);
	if (r.error != 0)
		return r.error;
	*fd = (int)r.value;
	return 0;
}

[[gnu::weak]] int sys_socket(int family, int type, int protocol, int *fd);
[[gnu::weak]] int sys_msg_send(int fd, const struct msghdr *hdr, int flags, ssize_t *length);
[[gnu::weak]] ssize_t sys_sendto(
    int fd,
    const void *buffer,
    size_t size,
    int flags,
    const struct sockaddr *sock_addr,
    socklen_t addr_length,
    ssize_t *length
);
[[gnu::weak]] int sys_msg_recv(int fd, struct msghdr *hdr, int flags, ssize_t *length);
[[gnu::weak]] ssize_t sys_recvfrom(
    int fd,
    void *buffer,
    size_t size,
    int flags,
    struct sockaddr *sock_addr,
    socklen_t *addr_length,
    ssize_t *length
);
[[gnu::weak]] int sys_listen(int fd, int backlog);
[[gnu::weak]] gid_t sys_getgid();
[[gnu::weak]] gid_t sys_getegid();
[[gnu::weak]] uid_t sys_getuid();
[[gnu::weak]] uid_t sys_geteuid();

pid_t sys_getpid() { return syscall(SYSCALL_getpid).value; }

[[gnu::weak]] pid_t sys_gettid();
[[gnu::weak]] pid_t sys_getppid();
[[gnu::weak]] int sys_getpgid(pid_t pid, pid_t *pgid);
[[gnu::weak]] int sys_getsid(pid_t pid, pid_t *sid);
[[gnu::weak]] int sys_setpgid(pid_t pid, pid_t pgid);
[[gnu::weak]] int sys_setuid(uid_t uid);
[[gnu::weak]] int sys_seteuid(uid_t euid);
[[gnu::weak]] int sys_setgid(gid_t gid);
[[gnu::weak]] int sys_setegid(gid_t egid);
[[gnu::weak]] int sys_getgroups(size_t size, gid_t *list, int *ret);
[[gnu::weak]] void sys_yield();
[[gnu::weak]] int sys_sleep(time_t *secs, long *nanos);

int sys_fork(pid_t *child) {
	auto r = syscall(SYSCALL_fork);
	if (r.error != 0)
		return r.error;
	*child = r.value;
	return 0;
}

int sys_execve(const char *path, char *const argv[], char *const envp[]) {
	return syscall(SYSCALL_execve, (size_t)path, (size_t)argv, (size_t)envp).error;
}

[[gnu::weak]] int sys_pselect(
    int num_fds,
    fd_set *read_set,
    fd_set *write_set,
    fd_set *except_set,
    const struct timespec *timeout,
    const sigset_t *sigmask,
    int *num_events
);
[[gnu::weak]] int sys_getrusage(int scope, struct rusage *usage);
[[gnu::weak]] int sys_getrlimit(int resource, struct rlimit *limit);
[[gnu::weak]] int sys_setrlimit(int resource, const struct rlimit *limit);
[[gnu::weak]] int sys_getpriority(int which, id_t who, int *value);
[[gnu::weak]] int sys_setpriority(int which, id_t who, int prio);
[[gnu::weak]] int sys_getschedparam(void *tcb, int *policy, struct sched_param *param);
[[gnu::weak]] int sys_setschedparam(void *tcb, int policy, const struct sched_param *param);
[[gnu::weak]] int sys_getparam(pid_t pid, struct sched_param *param);
[[gnu::weak]] int sys_setparam(pid_t pid, const struct sched_param *param);
[[gnu::weak]] int sys_get_max_priority(int policy, int *out);
[[gnu::weak]] int sys_get_min_priority(int policy, int *out);

int sys_getcwd(char *buffer, size_t size) {
	return syscall(SYSCALL_getcwd, (size_t)buffer, size).error;
}

int sys_chdir(const char *path) { return syscall(SYSCALL_chdir, (size_t)path).error; }

[[gnu::weak]] int sys_fchdir(int fd);
[[gnu::weak]] int sys_chroot(const char *path);

int sys_mkdir(const char *path, mode_t mode) { return sys_mkdirat(AT_FDCWD, path, mode); }

int sys_mkdirat(int dirfd, const char *path, mode_t mode) {
	return syscall(SYSCALL_mkdirat, dirfd, (size_t)path, mode).error;
}

[[gnu::weak]] int sys_link(const char *old_path, const char *new_path);
[[gnu::weak]] int
sys_linkat(int olddirfd, const char *old_path, int newdirfd, const char *new_path, int flags);
[[gnu::weak]] int sys_symlink(const char *target_path, const char *link_path);
[[gnu::weak]] int sys_symlinkat(const char *target_path, int dirfd, const char *link_path);
[[gnu::weak]] int sys_rename(const char *path, const char *new_path);
[[gnu::weak]] int
sys_renameat(int olddirfd, const char *old_path, int newdirfd, const char *new_path);
[[gnu::weak]] int sys_fcntl(int fd, int request, va_list args, int *result);
[[gnu::weak]] int sys_ttyname(int fd, char *buf, size_t size);
[[gnu::weak]] int sys_fadvise(int fd, off_t offset, off_t length, int advice);
[[gnu::weak]] void sys_sync();
[[gnu::weak]] int sys_fsync(int fd);
[[gnu::weak]] int sys_fdatasync(int fd);
[[gnu::weak]] int sys_chmod(const char *pathname, mode_t mode);
[[gnu::weak]] int sys_fchmod(int fd, mode_t mode);
[[gnu::weak]] int sys_fchmodat(int fd, const char *pathname, mode_t mode, int flags);
[[gnu::weak]] int
sys_utimensat(int dirfd, const char *pathname, const struct timespec times[2], int flags);
[[gnu::weak]] int sys_mlock(const void *addr, size_t length);
[[gnu::weak]] int sys_munlock(const void *addr, size_t length);
[[gnu::weak]] int sys_mlockall(int flags);
[[gnu::weak]] int sys_mlock(const void *addr, size_t len);
[[gnu::weak]] int sys_munlockall(void);
[[gnu::weak]] int sys_mincore(void *addr, size_t length, unsigned char *vec);

[[gnu::weak]] int sys_vm_remap(void *pointer, size_t size, size_t new_size, void **window);

[[gnu::weak]] int sys_setsid(pid_t *sid);
[[gnu::weak]] int sys_tcgetattr(int fd, struct termios *attr);
[[gnu::weak]] int sys_tcsetattr(int, int, const struct termios *attr);
[[gnu::weak]] int sys_tcflow(int, int);
[[gnu::weak]] int sys_tcflush(int fd, int queue);
[[gnu::weak]] int sys_tcdrain(int);
[[gnu::weak]] int sys_pipe(int *fds, int flags);
[[gnu::weak]] int sys_socketpair(int domain, int type_and_flags, int proto, int *fds);
[[gnu::weak]] int sys_poll(struct pollfd *fds, nfds_t count, int timeout, int *num_events);

int sys_ioctl(int fd, unsigned long request, void *arg, int *result) {
	auto r = syscall(SYSCALL_ioctl, fd, request, (size_t)arg);
	if (r.error != 0)
		return r.error;
	*result = r.value;
	return 0;
}

[[gnu::weak]] int
sys_getsockopt(int fd, int layer, int number, void *__restrict buffer, socklen_t *__restrict size);
[[gnu::weak]] int sys_setsockopt(int fd, int layer, int number, const void *buffer, socklen_t size);
[[gnu::weak]] int sys_shutdown(int sockfd, int how);

int sys_sigprocmask(int how, const sigset_t *__restrict set, sigset_t *__restrict retrieve) {
	return syscall(SYSCALL_sigprocmask, how, (size_t)set, (size_t)retrieve).error;
}

int
sys_sigaction(int sig, const struct sigaction *__restrict act, struct sigaction *__restrict oact) {
	return syscall(SYSCALL_sigaction, sig, (size_t)act, (size_t)oact).error;
}

// NOTE: POSIX says that behavior of timeout = nullptr is unspecified. We treat this case
// as an infinite timeout, making sigtimedwait(..., nullptr) equivalent to sigwaitinfo(...)
[[gnu::weak]] int sys_sigtimedwait(
    const sigset_t *__restrict set,
    siginfo_t *__restrict info,
    const struct timespec *__restrict timeout,
    int *out_signal
);
[[gnu::weak]] int sys_kill(int, int);
[[gnu::weak]] int
sys_accept(int fd, int *newfd, struct sockaddr *addr_ptr, socklen_t *addr_length, int flags);
[[gnu::weak]] int sys_bind(int fd, const struct sockaddr *addr_ptr, socklen_t addr_length);
[[gnu::weak]] int sys_connect(int fd, const struct sockaddr *addr_ptr, socklen_t addr_length);
[[gnu::weak]] int sys_sockname(
    int fd, struct sockaddr *addr_ptr, socklen_t max_addr_length, socklen_t *actual_length
);
[[gnu::weak]] int sys_peername(
    int fd, struct sockaddr *addr_ptr, socklen_t max_addr_length, socklen_t *actual_length
);
[[gnu::weak]] int sys_gethostname(char *buffer, size_t bufsize);
[[gnu::weak]] int sys_sethostname(const char *buffer, size_t bufsize);
[[gnu::weak]] int sys_mkfifoat(int dirfd, const char *path, mode_t mode);
[[gnu::weak]] int sys_getentropy(void *buffer, size_t length);
[[gnu::weak]] int sys_mknodat(int dirfd, const char *path, int mode, int dev);
[[gnu::weak]] int sys_umask(mode_t mode, mode_t *old);

[[gnu::weak]] int sys_before_cancellable_syscall(ucontext_t *uctx);
[[gnu::weak]] int sys_tgkill(int tgid, int tid, int sig);

[[gnu::weak]] int
sys_fchownat(int dirfd, const char *pathname, uid_t owner, gid_t group, int flags);
[[gnu::weak]] int sys_sigaltstack(const stack_t *ss, stack_t *oss);

int sys_sigsuspend(const sigset_t *set) {
	syscall(SYSCALL_sigsuspend, (size_t)set);
	return EINTR;
}

[[gnu::weak]] int sys_sigpending(sigset_t *set);
[[gnu::weak]] int sys_setgroups(size_t size, const gid_t *list);
[[gnu::weak]] int sys_memfd_create(const char *name, int flags, int *fd);
[[gnu::weak]] int sys_madvise(void *addr, size_t length, int advice);
[[gnu::weak]] int sys_msync(void *addr, size_t length, int flags);

[[gnu::weak]] int sys_getitimer(int which, struct itimerval *curr_value);
[[gnu::weak]] int
sys_setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);
[[gnu::weak]] int
sys_timer_create(clockid_t clk, struct sigevent *__restrict evp, timer_t *__restrict res);
[[gnu::weak]] int sys_timer_settime(
    timer_t t, int flags, const struct itimerspec *__restrict val, struct itimerspec *__restrict old
);
[[gnu::weak]] int sys_timer_delete(timer_t t);
[[gnu::weak]] int sys_times(struct tms *tms, clock_t *out);

int sys_uname(struct utsname *buf) { return syscall(SYSCALL_uname, (size_t)buf).error; }

[[gnu::weak]] int sys_pause();

[[gnu::weak]] int sys_setresuid(uid_t ruid, uid_t euid, uid_t suid);
[[gnu::weak]] int sys_setresgid(gid_t rgid, gid_t egid, gid_t sgid);
[[gnu::weak]] int sys_getresuid(uid_t *ruid, uid_t *euid, uid_t *suid);
[[gnu::weak]] int sys_getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid);
[[gnu::weak]] int sys_setreuid(uid_t ruid, uid_t euid);
[[gnu::weak]] int sys_setregid(gid_t rgid, gid_t egid);

[[gnu::weak]] int sys_poll(struct pollfd *fds, nfds_t count, int timeout, int *num_events);

[[gnu::weak]] int sys_if_indextoname(unsigned int index, char *name);
[[gnu::weak]] int sys_if_nametoindex(const char *name, unsigned int *ret);

[[gnu::weak]] int sys_ptsname(int fd, char *buffer, size_t length);
[[gnu::weak]] int sys_unlockpt(int fd);

[[gnu::weak]] int sys_thread_setname(void *tcb, const char *name);
[[gnu::weak]] int sys_thread_getname(void *tcb, char *name, size_t size);

[[gnu::weak]] int sys_sysconf(int num, long *ret);

[[gnu::weak]] int sys_semget(key_t key, int n, int fl, int *id);
[[gnu::weak]] int sys_semctl(int semid, int semnum, int cmd, void *semun, int *ret);

[[gnu::weak]] int sys_getaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);
[[gnu::weak]] int sys_getthreadaffinity(pid_t tid, size_t cpusetsize, cpu_set_t *mask);

[[gnu::weak]] int sys_setaffinity(pid_t pid, size_t cpusetsize, const cpu_set_t *mask);
[[gnu::weak]] int sys_setthreadaffinity(pid_t tid, size_t cpusetsize, const cpu_set_t *mask);

[[gnu::weak]] int sys_waitid(idtype_t idtype, id_t id, siginfo_t *info, int options);

[[gnu::weak]] int sys_name_to_handle_at(
    int dirfd, const char *pathname, struct file_handle *handle, int *mount_id, int flags
);
[[gnu::weak]] int sys_splice(
    int in_fd,
    off_t *in_off,
    int out_fd,
    off_t *out_off,
    size_t size,
    unsigned int flags,
    ssize_t *out
);

} // namespace mlibc
