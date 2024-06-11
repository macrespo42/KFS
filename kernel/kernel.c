#include <kernel/tty.h>

void kernel_main(void) {
  /* Initialize terminal interface */
  terminal_initialize();

  bobr();

  /* Initialize terminal offset */
  terminal_writestring(" ");

  terminal_writestring("42\n");

  /* Some writing to test scrolling capabilities */
  // terminal_writestring("random 1\n");
  // terminal_writestring("random 2\n");
  // terminal_writestring("random 3\n");
  // terminal_writestring("random 4\n");
  // terminal_writestring("random 5\n");
  // terminal_writestring("random 6\n");
  // terminal_writestring("random 7\n");
  // terminal_writestring("random 8\n");
  // terminal_writestring("random 9\n");
  // terminal_writestring("random 10\n");
  // terminal_writestring("random 11\n");
  // terminal_writestring("random 12\n");
  // terminal_writestring("random 13\n");
  // terminal_writestring("random 14\n");
  // terminal_writestring("random 15\n");
  // terminal_writestring("random 16\n");
  // terminal_writestring("random 17\n");
  // terminal_writestring("random 18\n");
  // terminal_writestring("random 19\n");
  // terminal_writestring("random 20\n");
  // terminal_writestring("random 21\n");
  // terminal_writestring("random 22\n");
  // terminal_writestring("random 23\n");
  // terminal_writestring("random 24\n");
  // terminal_writestring("random 25\n");
  // terminal_writestring("random 26\n");
}
