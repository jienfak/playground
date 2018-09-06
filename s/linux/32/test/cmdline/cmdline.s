global _start
section .text
_start:


	;opening file
	mov eax, 5
	mov ebx, filename_cmdline
	xor ecx, ecx
	xor edx, edx
	int 0x80
	
	;copying got descriptor to like an argument
	mov ebx, eax

	; reading from cmdline
	mov eax, 3
	mov ecx, buffer_cmdline
	mov edx, 0x100
	int 0x80

	; writing this to stdout
	mov eax, 4
	xor ebx, ebx
	inc ebx
	int 0x80
	
	;exit
	mov eax, 1
	xor ebx, ebx

section .data
filename_cmdline: db "/proc/self/cmdline",0
buffer_cmdline: db 0x100
