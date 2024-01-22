cmake_minimum_required(VERSION 3.25)
add_library(libc_string STATIC
	memcmp.c
	memcpy.c
	memmove.c
	memset.c
	printf.c
	putchar.c
	puts.c
	strlen.c
)
