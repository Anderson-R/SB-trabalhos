section .data
msg db 'Hello World!', 0dh, 0ah
msgb db 'hello world!', 0dh, 0ah
old_data dd 0
data dd -1
section .bss
lido resb 1
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
l2:	
push msgb
call escreverChar
push lido
call lerChar
l3:	mov eax, 1
	mov ebx, 0
	int 80h



escreverChar:
push ebp
mov ax, 1
mov ebp, esp
mov eax, 4
mov ebx, 1
mov ecx, [ebp+8]
mov edx, 1
int 80h
pop ebp
ret 4

lerChar:
push ebp
mov ax, 1
mov ebp, esp
mov eax, 3
mov ebx, 0
mov ecx, [ebp+8]
mov edx, 1
int 80h
pop ebp
ret 4