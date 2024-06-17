#ifndef _KERNEL_LIBK_
#define _KERNEL_LIBK_

#include <stddef.h>

size_t strlen(const char *str);
void *ft_memccpy(void *dst, const void *src, int c, size_t n);
void *ft_memmove(void *dst, const void *src, size_t len);
int ft_memcmp(const void *s1, const void *s2, size_t n);
int ft_strncmp(const char *s1, const char *s2, size_t n);
void *memcpy(void *dst, const void *src, size_t n) ;
void print_stack(void);
void print_pointer(unsigned int n);
int ft_convert_base(unsigned int n, int i, char *base);
void print_int(int number);
void println(void);
void print_str(char *str);
#endif
