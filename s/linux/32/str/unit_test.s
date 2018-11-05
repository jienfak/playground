
org32

print proc
exit  proc

SECTION .data

SECTION .code

_start:
	push ebp
	mov ebp, esp

	; Getting first argument of CLI.
	push DWORD [ebp+3*4]

	call print

	; Exit.
	push 0
	call exit
