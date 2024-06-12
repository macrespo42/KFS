#include "libk.h"

size_t strlen(const char *str) {
  size_t len = 0;
  while (str[len])
    len++;
  return len;
}

void *ft_memccpy(void *dst, const void *src, int c, size_t n) {
  size_t i;
  unsigned char *dst_cp;
  unsigned char *src_cp;

  dst_cp = (unsigned char *)dst;
  src_cp = (unsigned char *)src;
  i = 0;
  while (i < n) {
    dst_cp[i] = src_cp[i];
    if (src_cp[i] == (unsigned char)c)
      return (dst + i + 1);
    i++;
  }
  return (NULL);
}

void *ft_memmove(void *dst, const void *src, size_t len) {
  size_t i;
  unsigned char *dst_cp;
  unsigned char *src_cp;
  unsigned char temp[len];

  i = 0;
  if (!dst && !src)
    return (NULL);
  dst_cp = (unsigned char *)dst;
  src_cp = (unsigned char *)src;
  while (i < len) {
    temp[i] = src_cp[i];
    i++;
  }
  i = 0;
  while (i < len) {
    dst_cp[i] = temp[i];
    i++;
  }
  return (dst);
}

int ft_memcmp(const void *s1, const void *s2, size_t n) {
  size_t i;
  unsigned char *s1_cp;
  unsigned char *s2_cp;

  s1_cp = (unsigned char *)s1;
  s2_cp = (unsigned char *)s2;
  i = 0;
  while (i < n) {
    if (s1_cp[i] != s2_cp[i])
      return (s1_cp[i] - s2_cp[i]);
    i++;
  }
  return (0);
}

int ft_strncmp(const char *s1, const char *s2, size_t n) {
  size_t i;

  i = 0;
  if (n == 0)
    return (0);
  while (s1[i] == s2[i]) {
    if ((s1[i] == '\0' && s2[i] == '\0') || i == (n - 1))
      return (0);
    i++;
  }
  return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
