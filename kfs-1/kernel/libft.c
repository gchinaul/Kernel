 #include "ksh.h"
 #include "vga.h"
 

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void    *kmemset(void *dst, int c, size_t n)
{
    uint8_t     *p;

    p = (uint8_t *)dst;
    while (n--)
        *p++ = (uint8_t)c;
    return (dst);
}
