SECTION .data

SECTION .text

exit:
        mov eax, 1      ; '_exit' syscall
        mov ebx, 0      ; zero exit code (success)
        int 0x80
	ret


global _start           ; the program entry point
;main
_start:	
	push BYTE 1 ;
	push WORD 2 ;
	push DWORD 3 ;

	call exit
