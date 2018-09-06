org32
; void exit(int code);
exit:
	push ebp
	mov ebp, esp

	push eax

	mov eax, 1
	; Get code.
	mov ebx, [ebp+2*4]

	; Exit.
	int 0x80

	pop eax

	leave
	ret
