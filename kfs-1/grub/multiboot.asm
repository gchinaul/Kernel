MBALIGN  equ  1 << 0
MEMINFO  equ  1 << 1
MBFLAGS  equ  MBALIGN | MEMINFO

section .multiboot

align 4
    dd 0x1BADB002   ; standard magic
    dd MBFLAGS
    dd -(0x1BADB002 + MBFLAGS)  ; should be 0

section .bss
align 16
stack_bottom:
resb 16384			; 16 KiB reserved for stack
stack_top:

section .text
global _start:function (_start.end - _start)
_start:

	mov esp, stack_top

	extern kmain
	call kmain

	cli

.hang:
	hlt
	jmp .hang

.end:

section .note.GNU-stack noalloc noexec nowrite progbits