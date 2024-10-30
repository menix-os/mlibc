#ifndef MLIBC_MENIX_ARCHCTL
#define MLIBC_MENIX_ARCHCTL

#include <cstddef>

typedef enum : size_t
{
	ArchCtl_None = 0,

#ifdef __x86_64__
	ArchCtl_SetFsBase = 1,
#endif

} ArchCtl;


#endif
