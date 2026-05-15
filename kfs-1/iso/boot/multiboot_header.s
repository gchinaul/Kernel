section .multiboot_header

align 4
    dd 0x1BADB002
    dd 0
    dd -(0x1BADB002)

section .note.GNU-stack noalloc noexec nowrite progbits
