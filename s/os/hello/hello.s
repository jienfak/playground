section .text
use16
org 0x7C00

;writeNBytesToScreen(char *str, uint16_t n); /* writes n bytes to the screen */
writeNBytesToScreen:
	mov si, esp+0x04 ; Load a 'str'
	mov ah, [esp+0x05] ; Load a n

	lodsb;

	test al, al ;

ret

;writeStrToScreen(char *str); /* writes a zero end string to screen */
writeStrToScreen:

ret

start:

	mov ax, cs
	mov ds, ax
	mov si, message

endless_loop:

	puts_loop:

		lodsb
		test al, al

		jz puts_loop_exit

		int 0x10
		jmp puts_loop

	puts_loop_exit:
loop endless_loop


cld

	mov ah, 0x0E
	mov bh, 0x00
	mov ecx, 5
endless_loop:

	puts_loop:

		lodsb
		test al, al

		jz puts_loop_exit

		int 0x10
		jmp puts_loop

	puts_loop_exit:
	loop endless_loop

	jmp $

message:
	db 'Hello',0

finish:
	times 0x1FE-finish+start db 0
	db 0x55, 0xAA
