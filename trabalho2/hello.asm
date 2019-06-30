section .data
msg db 'Hello World!', 0dh, 0ah
old_data dd 0
section .text
global _start
_start: mov eax, 4
	mov ebx, 1
	mov ecx, msg
	mov edx, 14
	int 80h
	mov eax, 1
	mov ebx, 0
	int 80h

