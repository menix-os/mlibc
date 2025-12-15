#ifndef _ABIBITS_EPOLL_H
#define _ABIBITS_EPOLL_H

#include <abi-bits/fcntl.h>
#include <abi-bits/signal.h>
#include <abi-bits/poll.h>
#include <mlibc-config.h>
#include <stdint.h>

#define EPOLL_NONBLOCK O_NONBLOCK
#define EPOLL_CLOEXEC O_CLOEXEC

#define EPOLLIN        (1U << 0)
#define EPOLLPRI       (1U << 1)
#define EPOLLOUT       (1U << 2)
#define EPOLLRDNORM    (1U << 3)
#define EPOLLRDBAND    (1U << 4)
#define EPOLLWRNORM    (1U << 5)
#define EPOLLWRBAND    (1U << 6)
#define EPOLLMSG       (1U << 7)
#define EPOLLERR       (1U << 8)
#define EPOLLHUP       (1U << 9)
#define EPOLLRDHUP     (1U << 10)
#define EPOLLEXCLUSIVE (1U << 28)
#define EPOLLWAKEUP    (1U << 29)
#define EPOLLONESHOT   (1U << 30)
#define EPOLLET        (1U << 31)

#define EPOLL_CTL_ADD 1
#define EPOLL_CTL_DEL 2
#define EPOLL_CTL_MOD 3

#ifdef __cplusplus
extern "C" {
#endif

typedef union epoll_data {
	void *ptr;
	int fd;
	uint32_t u32;
	uint64_t u64;
} epoll_data_t;

struct epoll_event {
	uint32_t events;
	epoll_data_t data;
};

#ifdef __cplusplus
}
#endif

#endif /* _ABIBITS_EPOLL_H */
