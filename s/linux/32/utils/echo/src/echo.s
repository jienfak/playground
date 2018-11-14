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

	mov $1, %eax
	mov -0x8(%ebp), %ebx

	int $0x80

	leave
	ret

.globl _start
_start:
	mov 0x8(%esp), %eax ;
	pushl %eax             ;
	/*call print*/             ;

	/* Default exit. */
	pushl $0
	movl $0, %eax           ;
	call exit              ;

	
