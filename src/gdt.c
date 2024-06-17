#include "gdt.h"
#include "libk.h"

struct gdt_entry_struct gdt_entries[7] ;
struct gdt_ptr_struct gdt_ptr ;
extern void gdt_flush(void *addr_t);

void initGdt(void) {
  gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * 7) - 1;
  gdt_ptr.base = (void *)GDT_ADDRESS;

  setGdtGate(0, 0, 0, 0, 0);
  setGdtGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // kernel code
  setGdtGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // kernel data
  //setGdtGate(2, 0, 0xFFFFFFFF, 0x9A, 0xCF); // kernel data doesnt work because it got the same right acces of code
  setGdtGate(3, 0, 0xFFFFFFFF, 0x96, 0xCF); // kernel stack
  setGdtGate(4, 0, 0xFFFFFFFF, 0xFA, 0xCF); // user code
  setGdtGate(5, 0, 0xFFFFFFFF, 0xF2, 0xCF); // user data
  setGdtGate(6, 0, 0xFFFFFFFF, 0xF6, 0xCF); // user stack
  memcpy(gdt_ptr.base , &gdt_entries, sizeof(gdt_entries));
  gdt_flush(&gdt_ptr);
  print_str("Print the pointer");
  print_pointer((unsigned int)gdt_ptr.base);
  println();
}


//  ; SS get the right code of the stack segment
 //  dw 0xFFFF                     ; Limit (low)
 //  dw 0                        ; Base (low)
 //  db 0                        ; Base (middle)
 //  db 10010010b                  ; Access
 //  db 11001111b                  ; Granularity
 //  db 0                        ; Base (hi)


void setGdtGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access,
                uint8_t gran) {
  gdt_entries[num].base_low = (base & 0xFFFF);
  gdt_entries[num].base_middle = (base >> 16) & 0xFF;
  gdt_entries[num].base_high = (base >> 24) & 0xFF;
  gdt_entries[num].limit = (limit & 0xFFFF);
  gdt_entries[num].flags = (limit >> 16) & 0x0F;
  gdt_entries[num].flags |= (gran & 0xF0);
  gdt_entries[num].access = access;
}
