org16
SECTION .data

SECTION .text

exit:
	push ebp
	mov ebp, esp
        mov eax, 1      ; '_exit' syscall
        mov ebx, 0      ; zero exit code (success)
        int 0x80
	ret


global _start           ; the program entry point
;main
_start:	
	push 1;
	push 2 ;
	push 3;

	call exit
