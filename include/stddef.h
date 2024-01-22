#ifndef _MLIBC_STDDEF_H
#define _MLIBC_STDDEF_H

#define NULL ((void*)0)
#define offsetof(type, member) ((size_t)(&((type*)0)->member))

// ptrdiff_t
#if (_MLIBC_BITS == 64)
typedef signed long long    ptrdiff_t;
#else
typedef signed long         ptrdiff_t;
#endif

// wchar_t
typedef unsigned int wchar_t;

// size_t
#if (_MLIBC_BITS == 64)
typedef unsigned long long  size_t;
#else
typedef unsigned long       size_t;
#endif

#endif // stddef.h
