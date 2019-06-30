section .data
snippet db 'kangaroo', 0dh, 0ah
section .text
global _start
_start: mov eax, 4
	mov ebx, 1
	mov ecx, snippet
	mov edx, 10
	int 80h
	mov ebx, snippet
	mov eax, 8
domore:	sub byte [ebx], 32
	inc ebx
	dec eax
	jnz domore
	mov eax, 4
	mov ebx, 1
	mov edx, 10
	int 80h
	mov eax, 1
	mov ebx, 0
	int 80h

