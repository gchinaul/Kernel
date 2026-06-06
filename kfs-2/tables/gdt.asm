; Set GDT selectors to be used by CPU.

; bits 15-3: = Index
; bit 2: 0 = GDT (not LDT)
; bit 1-0: CPU Privilege level = 0 (Ring 0) 

GDT_KERNEL_CODE_SELECTOR equ 0x08	; 0000 0000 0000 1000
GDT_KERNEL_DATA_SELECTOR equ 0x10	; 0000 0000 0001 0000
GDT_KERNEL_STACK_SELECTOR equ 0x18	; 0000 0000 0001 1000

global gdt_flush

gdt_flush:
	
	; Load the GDT address into GDT register

	mov eax, [esp+4]
	lgdt [eax]

	; Reload data segment registers

	mov ax, GDT_KERNEL_DATA_SELECTOR
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ax, GDT_KERNEL_STACK_SELECTOR
	mov ss, ax

	; Reload cs register with a far jump (EIP = adrr of .flush, cs -> GDT[1])

	jmp GDT_KERNEL_CODE_SELECTOR:.flush

.flush:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
