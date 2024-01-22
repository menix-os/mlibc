#ifndef _SYS_CDEFS_H
#define _SYS_CDEFS_H 1
 
#define _MLIBC 1

#ifdef __cplusplus
#define _MLIBC_DECL_BEGIN	extern "C" {
#define _MLIBC_DECL_END		}
#else
#define _MLIBC_DECL_BEGIN
#define _MLIBC_DECL_END
#endif
 
#endif // <sys/cdefs.h>
