section .data

section .text
global _start
_start:;{
	mov eax, 2;
	bsr ebx, eax
	
	mov eax, 1
	xor ebx, ebx
	int 0x80
;}
