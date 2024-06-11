#include "vga.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

/* move next to our own libc */
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
