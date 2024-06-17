#include "gdt.h"
#include "libk.h"
#include "tty.h"

void kernel_main(void) {
  /* Initialize terminal interface */
  terminal_initialize();

  //terminal_writestring(" ");

  terminal_writestring("42\n");

  println();
  initGdt();
  print_stack();
}
