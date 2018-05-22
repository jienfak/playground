SECTION .data;{
	msg     db "Hello, world!",0
	len     equ $ - msg
;}

SECTION .text
write_hello:;{

	;saving registers
	push eax
	push ebx
	push ecx
	push edx

	;arguments
        mov eax, 4      ; 'write' syscall
        mov ebx, 1      ; file descr. 1 (stdout)
        mov ecx, msg    ; pointer to the data
        mov edx, len    ; amount of data
        int 0x80

	;back registers	
	pop edx
	pop ecx
	pop ebx
	pop eax

	;exit
	ret
;}

exit:;{
        mov eax, 1      ; '_exit' syscall
        mov ebx, 0      ; zero exit code (success)
        int 0x80
	ret
;}

global _start           ; the program entry point
_start:	
	call write_hello
	call exit
