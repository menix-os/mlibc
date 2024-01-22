#include <stdio.h>

extern void terminal_write(const char*, size_t);

int putchar(int ic) 
{
#if defined(__is_libk)
	char c = (char) ic;
	terminal_write(&c, sizeof(c));
#else
	char c = (char) ic;
	terminal_write(&c, sizeof(c));
#endif
	return ic;
}
