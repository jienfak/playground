.data

.text

strlen:
	# Returns length of C-string.
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

	# Saving registers.
	pushl %ebx
	pushl %ecx
	pushl %edx

	# Num of write-call.
	mov $4, %eax
	# Descriptor.
	mov 0x8(%ebp), %ebx
	# Pointer.
	mov 0xc(%ebp), %ecx
	# Number of bytes.
	mov 0x10(%ebp), %edx

	# Syscall to write.
	int $0x80

	# Recovering registers.
	popl %edx
	popl %ecx
	popl %ebx

	# Returing value.

	# Interrupting returned value to %EAX itself.

	# Exiting.
	leave
	ret	

print:
	# Prints standard C-string to output.
	pushl %ebp
	movl %esp, %ebp

	# Getting pointer.
	movl 0x8(%ebp), %eax
	pushl %eax

	call strlen

	# For the 'write' function.

	# Length of string.
	pushl %eax
	

	# Pushing pointer. 
	movl 0x8(%ebp), %eax
	pushl %eax

	# Desc...
	pushl $1

	call write


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

	# Call print.
	mov 0xc(%ebp), %eax ;
	push %eax
	call print

	/* Default exit. */
	pushl $1
	movl $0, %eax           ;
	call exit              ;

	leave
	ret
	
