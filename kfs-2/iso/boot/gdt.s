;registre GDTR

global gdt_flush

gdt_flush:
	mov eax, [esp+4]
	lgdt [eax]

;Bits 15–3 : index 2 dans la GDT (segment de données)
;Bit 2 : 0 = GDT (pas LDT)
;Bits 1–0 : 0 = Ring 0

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ax, 0x18
	mov ss, ax

; Far jump pour recharger Code Segment
	
	jmp 0x08:.flush

.flush:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
