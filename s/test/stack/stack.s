org64
SECTION .data

SECTION .text

func:
	push rbp
	mov rbp, rsp
	push 4
	push 5
	push 6
	leave
	ret

exit:
	push rbp
	mov rbp, rsp
        mov rax, 1      ; '_exit' syscall
        mov rbx, 0      ; zero exit code (success)
        int 0x80
	leave
	ret


global _start           ; the program entry point
;main
_start:	
	push 1;
	push 2 ;
	push 3;
	
	call func

	call exit
