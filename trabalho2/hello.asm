section .data
msg db 'Hello World!', 0dh, 0ah
msgb db 'hello world!', 0dh, 0ah
old_data dd 0
data dd -1
section .text
global _start
_start:	
	push eax
	mov eax, [old_data] 
	mov dword [data], eax
	pop eax 
	mov eax, [data]
	cmp eax, 0
	jz l2
l1:	mov eax, 4
	mov ebx, 1
	mov ecx, msg
	mov edx, 14
	int 80h
	jmp l3
l2:	mov eax, 4
	mov ebx, 1
	mov ecx, msgb
	mov edx, 14
	int 80h
l3:	mov eax, 1
	mov ebx, 0
	int 80h

