; 16-bit addressation, we are in real-mode.
use16

org 0x7c00

start:
	jmp 0x0000:entry
entry:
	mov ax, cs
	mov ds, ax

	; Clear the screen.
	mov ax, 0x0003
	int 0x10 

	; Open A20.
	in al, 0x92
	or al, 2
	out 0x92, al

	; Load address and side GDT into GDTR.
	lgdt [gdtr]

	; Ban the interruptings.
	cli

	; Ban unmasked interruptings.
	in al, 0x70
	or al, 0x80
	out 0x70, al

	; Change mode to protected.
	mov eax, cr0
	or al, 1
	mov cr0, eax

	; Load into CS:EIP entry point to protected mode.
o32 jmp 00001000b:pm_entry

; 32-bit addressation.
use32
pm_entry:
	; Entry point
	;

	; Load segment registers(Except SS).
	mov ax, cs
	mov ds, ax
	mov es, ax

	mov edi, 0xB8000       ; Start of video-memory.
	mov esi, msg           ; Message for outputting.
	cld

.loop
	; Outputting cycle.
	;

	lodsb                  ; Read next char.

	; Stop if meet '\0'.
	test al, al		
	jz .exit

	; Else we put current char
	; and his attribute to the video-memory.
	stosb
	mov al, 6
	stosb

	jmp .loop
.exit

	; Infinite cycle.
	jmp $

msg:
	db 'Hello, World', 0

; Global table of descriptors.
; We can't use zero-descriptor.
gdt:
	db 0x00,0x00,0x00,0x00,0x00,  0x00   ,  0x00   , 0x00
	db 0xEE,0xEE,0x00,0x00,0x00,10011010b,11001111b, 0x00
	gdt_size equ $ - gdt

; Data, loaded into register GDTR.
gdtr:
	dw gdt_size - 1
	dd gdt

finish:
	times 0x1FE-finish+start db 0
	db 0x55, 0xAA

