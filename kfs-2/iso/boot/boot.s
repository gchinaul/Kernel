extern stack_top
section .text

global _start
extern kmain
bits 32

_start:
    ; mov dword [0xb8000], 0x2f4b2f4f
    cli
    mov esp, stack_top
    call kmain

.hang:
    hlt
    jmp .hang

section .bss
    resb 8000

section .note.GNU-stack noalloc noexec nowrite progbits