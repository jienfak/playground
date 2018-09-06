org32

; void printStrZ(char *str);
printStrZ:
	; Function to print 'zero-end' string.
	push ebp
	mov ebp, esp
	push eax
	push ebx
	push ecx
	push edx

	; Standart output descriptor.
	mov ebx, 1


	; Getting length of string.
	push DWORD [ebp+2*4] ; Pointer to string.
	call strlen ; Function to get length.

		; Setting length for 'int 0x80'.
		mov edx, eax
		

	; Write syscall.
	mov eax, 4

	int 0x80

	; Delete  pointer from stack to get registers
	; safely.
	pop edx

	pop edx
	pop ecx
	pop ebx
	pop eax
	leave
	ret

; uint32_t strlen(char *str);
strlen:
	; Function to check length of string.

	push ebp
	mov ebp, esp

	; Registers saving.
	push esi

	cld ; Direction flag setting.
	mov esi, [ebp+2*4] ; String pointer getting.

strlen_GettingCharLoop:
		; Load byte and check it to zero.
		lodsb
		test al, al
	jz strlen_Exit
	jmp strlen_GettingCharLoop

strlen_Exit:
	
	sub esi, [ebp+2*4]

	mov eax, esi

	; Restoring of ESI.
	pop esi
	leave
	ret
