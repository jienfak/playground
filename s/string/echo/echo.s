section .data
	string: db "Hello, World!\n",0
section .text

strln:;{
		;save ebx
		push ebx

		mov ebx, 0 ;counter of chars
	strln_char_isntzero:;{

		cmp byte [eax] , 0 ;{
			je strln_char_iszero ; break if *eax is zero
		;}else{
			inc eax ; ++eax
			inc ebx ; ++ebx
			jmp strln_char_isntzero ; continue cycle
		;}
	;}	

	strln_char_iszero: ; got zero char
		mov eax, ebx

		;exit 
		pop ebx
		ret

;}

write:;{
	push edx
	push eax
	push ebx
	push ecx

	pop edx
	pop ecx
	pop ebx
	mov eax, 4

	int 0x80

	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	pop edx
	ret	
;}

print:;{
	push ebx
	push ecx

	push eax
	call strln
	
	mov ecx, eax
	pop ebx
	mov eax, 1
	call write
	
	xor eax, eax ; eax = 0

	pop ecx
	pop ebx

	ret
;}

exit:;{

	push ebx;

	mov ebx, eax;
	mov eax, 1;
	int 0x80;
	
	xor eax, eax

	pop ebx

	ret;
;}

global _start
_start:;{
	mov eax, dword [esp+4*2]
	call print
	;default exit
	mov eax, 0 ;
	call exit;

;}
	
