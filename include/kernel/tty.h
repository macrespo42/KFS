#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void scroll();
void terminal_putchar(char c);
void clear(void);
void terminal_write(const char *data, size_t size);
void terminal_writestring(const char *data);
void bobr(void);
// tmp next go to IO dir
void outb(uint16_t port, uint8_t data);
void terminal_set_cursor(int x, int y);

#endif
