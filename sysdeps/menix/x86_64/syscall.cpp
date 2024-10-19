#include <stddef.h>
#include <stdint.h>
#include <menix/syscall.h>

size_t syscall(size_t num, size_t a0, size_t a1, size_t a2, size_t a3, size_t a4, size_t a5) {
	register size_t arg0 asm("rdi") = a0;
    register size_t arg1 asm("rsi") = a1;
    register size_t arg2 asm("rdx") = a2;
    register size_t arg3 asm("r8") = a3;
    register size_t arg4 asm("r10") = a4;
    register size_t arg5 asm("r9") = a5;
    register size_t selector asm("rax") = num;
	asm volatile("syscall" : "=r"(selector) : "r"(arg0), "r"(arg1), "r"(arg2), "r"(arg3), "r"(arg4), "r"(arg5));

	return selector;
}