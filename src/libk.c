#include "libk.h"
#include "tty.h"

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
void *memcpy(void *dst, const void *src, size_t n) {
    unsigned char *dst_cp = (unsigned char *)dst;
    const unsigned char *src_cp = (const unsigned char *)src;

    size_t i;
    for (i = 0; i < n; ++i) {
        dst_cp[i] = src_cp[i];
    }

    return dst;
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
void println(void) { terminal_writestring("\n"); }
void print_str(char *str) { terminal_writestring(str); }


void print_stack() {
  void *stack_bottom;
  void *stack_top;
  int test = 42;
  int max_frame_seen = 10;
  int index =0;
  __asm__ volatile("mov %%ebp, %0" : "=r"(stack_bottom));
    __asm__ volatile("mov %%esp, %0" : "=r"(stack_top));
  for (void *ptr = &test; ptr <= (void *)stack_bottom; ptr++) {
    if(index > max_frame_seen){
      return ;
    }
  print_pointer((unsigned long int)ptr);
    print_str("    ");
    print_int(*(int *)ptr);
    println();
    index++;
  }
  print_str("Address of the stack bottom");
  print_pointer((unsigned int)stack_bottom);
    print_str("Address of the stack top");
  print_pointer((unsigned int)stack_top);
}

void print_int(int number) {
  int tmp = number;
  int numDigits = 0;
  while (tmp != 0) {
    tmp /= 10;
    numDigits++;
  }
  char str[numDigits];
  for (int i = numDigits - 1; i >= 0; i--) {
    str[i] = '0' + (number % 10);
    number /= 10;
  }
  str[numDigits] = '\0';
  print_str(str);
}

int get_len_hex(unsigned int n, unsigned int len) {
  int i;

  i = 0;
  if (n == 0)
    return (1);
  while (n) {
    n /= len;
    i++;
  }
  return (i);
}

int ft_convert_base(unsigned int n, int i, char *base) {
  if (n == 0)
    return (base[0 % strlen(base)]);
  while (i > 1) {
    n /= strlen(base);
    i--;
  }
  return (base[n % strlen(base)]);
}

void print_pointer(unsigned int n) {
  int i;
  unsigned int len;
  int len_hex;
  char *base = "0123456789abcdef";
  char *start_pointer = "0x";

  i = 0;
  len = strlen(base);

  len_hex = (get_len_hex(n, len));
  char fi[len_hex + 3];
  for (int i = 0; i < 2; i++) {
    fi[i] = start_pointer[i];
  }
  i = 2;
  while ((len_hex)) {

    fi[i] = ft_convert_base(n, len_hex, base);
    i++;
    len_hex--;

    fi[i] = '\0';
  }
  terminal_writestring(fi);
}
