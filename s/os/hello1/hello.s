section .text
use16
org 0x7C00

start:
	mov ax, cs
	mov ds, ax
	mov si, message ; si = message

	cld
	mov ah, 0x0E ; 
	mov bh, 0x00 ; page
	mov ecx, 5 ; 

	puts_loop:
		lodsb ; al = si++

		; if(al==0){break;}
		test al, al
		jz puts_loop_exit

		int 0x10 ; putchar(al)
		jmp puts_loop

	puts_loop_exit:
	jmp start

message:
	db 'Hello, World!'
finish:
	times 0x1FE-finish+start db 0
	db 0x55, 0xAA
