SECTION .data
	err_msg:
		db "Not equal.",0
	err_msg_len:
		db $ - err_msg

SECTION .text
exit:
	push ebp
	mov ebp, esp

        mov eax, 1      ; '_exit' syscall
        mov ebx, 0      ; zero exit code (success)
        int 0x80

	leave
	ret

print:
	push ebp
	mov ebp, esp

	push eax
	push ebx
	push ecx
	push edx

	mov eax, 4
	mov ebx, 1
	mov ecx, err_msg
	mov edx, err_msg_len
	int 0x80

	leave
	ret

_start:	
	mov eax, DWORD [esp+4*2] ; Get first argument.
	mov ebx, DWORD [esp+4*3] ; Get second argument.

	cmp_cycle:
		mov BYTE cl, [eax]
		mov BYTE dl, [ebx]

		inc eax
		inc ebx

		test cl, cl
		jz got_zero

		cmp cl, dl             ; Exit if not ;equal.
		jne exit_not_right
	
	jmp cmp_cycle
got_zero:
	cmp cl, dl
	jne exit_not_right

	jmp right_thing


exit_not_right:
	call print_error
	call exit

right_thing:
