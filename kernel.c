#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error                                                                         \
    "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

/* Hardware text mode color constants. */
enum vga_color {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
  return (uint16_t)uc | (uint16_t)color << 8;
}

size_t strlen(const char *str) {
  size_t len = 0;
  while (str[len])
    len++;
  return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;
int banner;

void outb(uint16_t port, uint8_t data) {
  asm("out %%al, %%dx" : : "a"(data), "d"(port));
}

void terminal_set_cursor(int x, int y) {
  uint16_t pos = y * VGA_WIDTH + x + 1;
  outb(0x3D4, 0x0F);
  outb(0x3D5, (uint8_t)(pos & 0xFF));
  outb(0x3D4, 0x0E);
  outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void terminal_initialize(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  banner = 0;
  terminal_buffer = (uint16_t *)0xB8000;
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_setcolor(uint8_t color) { terminal_color = color; }

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
}

void scroll() {
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      const size_t next_index = (y + 1) * VGA_WIDTH + x;
      char c = terminal_buffer[next_index];
      if ((y + 1) == VGA_HEIGHT) {
        c = '\0';
      }
      terminal_buffer[index] = vga_entry(c, terminal_color);
    }
  }
  terminal_row = VGA_HEIGHT - 1;
}

void terminal_putchar(char c) {
  if (c == '\n') {
    ++terminal_row;
    terminal_column = 0;
  } else {
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    terminal_column++;
  }

  if (terminal_column >= VGA_WIDTH) {
    terminal_column = 0;
    terminal_row++;
  }
  if (terminal_row >= VGA_HEIGHT) {
    scroll();
  }
}

void clear(void) {
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry('\0', terminal_color);
    }
  }
  terminal_row = 0;
  terminal_column = 0;
}

void terminal_write(const char *data, size_t size) {
  for (size_t i = 0; i < size; i++)
    terminal_putchar(data[i]);
}

void terminal_writestring(const char *data) {
  terminal_write(data, strlen(data));
  terminal_set_cursor(terminal_column - 1, terminal_row);
}

void bobr(void) {
  banner = 1;
  terminal_color = vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
  terminal_writestring("       (\\.---./)        \n");
  terminal_color = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
  terminal_writestring("        /.-.-.\\\n");
  terminal_color = vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_BLACK);
  terminal_writestring("       /| 0_0 |\\\n");
  terminal_color = vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
  terminal_writestring("      |_`-(v)-'_|\n");
  terminal_color = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
  terminal_writestring("      \\`-._._.-'/      .-.\n");
  terminal_color = vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_BLACK);
  terminal_writestring("-~-(((.`-\\_|_/-'.)))-~' <_\n");
  terminal_color = vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
  terminal_writestring("       `.     .'\n");
  terminal_color = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
  terminal_writestring("         `._.'\n");
  terminal_color = vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_BLACK);
  terminal_writestring("-----~--~---~~~----~-`.-;~\n");
  terminal_color = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
  banner = 0;
}

void println(void){
    terminal_writestring("\n");
    terminal_color = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
}
void print_str(char * str){
      terminal_writestring(str);
    terminal_color = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
}
void  print_int(int number) {
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

int			get_len_hex(unsigned long long n, unsigned int len)
{
	unsigned long long i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= len;
		i++;
	}
	return (i);
}

int			ft_convert_base(unsigned long long n, unsigned long long i, char *base)
{
	if (n == 0)
		return (base[0 % strlen(base)]);
	while (i > 1)
	{
		n /= strlen(base);
		i--;
	}
	return (base[n % strlen(base)]);
}

void print_pointer(unsigned long long n){
	int					i;
	unsigned int		len;
	unsigned long long	len_hex;
 char *base = "0123456789abcdef";
  char *start_pointer = "0x";

	i = 0;
	len = strlen(base);

	len_hex = (get_len_hex(n, len));
	char				fi[len_hex + 3];
  for (int i = 0; i < 2 ; i++){
    fi[i] = start_pointer[i];
  }
  i = 2;
	while ((len_hex)){

		fi[i] = ft_convert_base(n, len_hex, base);
    i++;
    len_hex--;

	  fi[i] = '\0';
  }
    terminal_writestring(fi);
  terminal_color = vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
}

void print_stack() {
    void *stack_bottom;
    int test = 42;
    __asm__ volatile (
        "mov %%ebp, %0"  
        : "=r" (stack_bottom)
    );
        for (void *ptr = &test; ptr <= (void*)stack_bottom; ptr++) {
            print_pointer(ptr);
            print_int(*(int *)ptr);
            println();
    }
}





void kernel_main(void) {
  /* Initialize terminal interface */
  terminal_initialize();
  initGdt();
print_stack();


  /* Initialize terminal offset */

}
