#ifndef _MLIBC_STDIO_H
#define _MLIBC_STDIO_H 1
 
#include <sys/cdefs.h>
 
#define EOF (-1)

_MLIBC_DECL_BEGIN
 
int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);

_MLIBC_DECL_END
 
#endif // stdio.h
