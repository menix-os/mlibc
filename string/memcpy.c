#include <string.h>
#include <stddef.h>
#include <stdint.h>

void* memcpy(void* restrict dst, const void* restrict src, size_t size) 
{
	uint8_t* dstPtr = (uint8_t*)dst;
	const uint8_t* srcPtr = (const uint8_t*)src;
	for (size_t i = 0; i < size; i++)
		dstPtr[i] = srcPtr[i];
	return dst;
}
