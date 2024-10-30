#include <menix/syscall.h>
#include <stddef.h>
#include <stdint.h>

size_t syscall(size_t num, size_t a0, size_t a1, size_t a2, size_t a3, size_t a4, size_t a5) {
	size_t result = 0;
	asm volatile(
		"mov %1, %%rax;"
		"mov %2, %%rdi;"
		"mov %3, %%rsi;"
		"mov %4, %%rdx;"
		"mov %5, %%r8;"
		"mov %6, %%r10;"
		"mov %7, %%r9;"
		"syscall;"
		"mov %%rax, %0"
		: "=m"(result)
		: "g"(num), "g"(a0), "g"(a1), "g"(a2), "g"(a3), "g"(a4), "g"(a5)
		: "rax", "rdi", "rsi", "rdx", "r8", "r10", "r9", "rcx", "r11", "memory"
	);
	return result;
}