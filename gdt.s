.text
.global gdt_flush

gdt_flush:
    movl 4(%esp), %eax
    lgdt (%eax)          

    mov $0x10, %ax
    mov %ax,  %ds
    mov %ax,  %es
    mov %ax,  %fs
    mov %ax,  %gs
    mov %ax,  %gs
    mov $0x18, %ax
    mov %ax,  %ss
    ljmp $0x08, $.flush  

.flush:
    ret               
