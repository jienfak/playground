.text
.global loader # Entry point to linker.

# Setting up the Multiboot header - see GRUB docs for details.
.set FLAGS,     0x0                # Multiboot 'flag' field.
.set MAGIC,     0x1BADB002         # 'magic number' lets bootloader find the header.
.set CHECKSUM,  -( MAGIC + FLAGS ) # Checksum required.

.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve initial kernel stack space.
.set STACKSIZE, 0x4000    # 16K.
.lcomm stack,   STACKSIZE # Reserve.
.comm mbd,      4         # Will be used in kmain.
.comm magic,    4         # Will be used in kmain.

loader:
	movl $(stack + STACKSIZE), %esp # Set up the stack.
	movl %eax, magic                # Multiboot magic number.
	movl %ebx, mbd                  # Mutliboot data structure.
	call main                      # Calling C code.
	cli

hang:
	hlt                            # Halt machine should kernel return.
	jmp hang
