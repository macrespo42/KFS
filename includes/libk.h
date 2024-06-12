#ifndef _KERNEL_LIBK_
#define _KERNEL_LIBK_

#include <stddef.h>

size_t strlen(const char *str);
void *ft_memccpy(void *dst, const void *src, int c, size_t n);
void *ft_memmove(void *dst, const void *src, size_t len);
int ft_memcmp(const void *s1, const void *s2, size_t n);
int ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
