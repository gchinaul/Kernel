section .text
bits 32

global irq1_stub
extern keyboard_handler

irq1_stub:
    pusha

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call keyboard_handler
    popa

    mov al, 0x20
    out 0x20, al

    iret

section .note.GNU-stack noalloc noexec nowrite progbits
