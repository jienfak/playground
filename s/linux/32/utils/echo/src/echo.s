.data

.text

strlen:
	pushl %ebp
	movl %esp, %ebp

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

	/* Saving eax. */
	#mov %eax, (ebp,1,4)

	leave
	ret

.globl _start
_start:
	mov (%esp, 4, 2), %eax ;
	pushl %eax             ;
	call print             ;

	/* Default exit. */
	movl $0, %eax           ;
	call exit              ;

	
