.data

.text

strlen:
	pushl %ebp
	movl %esp, %ebp
	# Save %ECX.
	mov %ecx, -0x8(%ebp)

	mov 0x8(%ebp),  %esi

	
strlen_zero_loop:
	lodsb
	test %al, %al
	jz strlen_exit
	inc %ecx
	jmp strlen_zero_loop
strlen_exit:
	# Return counter.
	mov %ecx, %eax

	# Recover %ECX.
	mov -0x8(%ebp), %ecx
	leave
	ret


write:
	pushl %ebp
	movl %esp, %ebp


	leave
	ret	

print:
	pushl %ebp
	movl %esp, %ebp



	leave
	ret

exit:
	pushl %ebp
	movl %esp, %ebp

	mov $1, %eax
	mov 0x8(%ebp), %ebx

	int $0x80

	leave
	ret

.globl _start
_start:
	push %ebp
	mov %esp, %ebp

	mov 0x8(%ebp), %eax ;
	mov %eax, -0x8(%esp)
	call strlen
	/* Call print.*/             ;

	/* Default exit. */
	pushl $1
	movl $0, %eax           ;
	call exit              ;

	leave
	ret
	
