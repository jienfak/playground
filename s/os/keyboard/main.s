section .text
use16
org 0x7C00

start:
	push msg1
	call printStrZ

	push msg2
	call printStrZ

;void printStrZ(uint64_t pointer);
printStrZ:
	push bp
	mov bp, sp

	lea si, [bp+4]

	cld

	mov ah, 0x0E
	mov bh, 0x00

	puts_loop:
		lodsb ; al = si++

		; if(!al) break ;
		test al, al
		jz puts_loop_exit
		

		int 0x10 ; put char
		jmp puts_loop
	puts_loop_exit:

	leave
	ret

msg1:
	db "MSG1"
msg2:
	db "MSG2"

finish:
	times 0x1FE-finish+start db 0
	db 0x55, 0xAA
