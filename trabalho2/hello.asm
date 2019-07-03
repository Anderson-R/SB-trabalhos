section .data
msg db 'Hello World!', 0dh, 0ah
msgb db 'hello world!', 0dh, 0ah
ok db 'ok', 0dh, 0ah
number db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
inteiro dd 0
old_data dd 0
data dd -1
section .bss
lido resb 10
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
push dword 14
push msgb
call escreverString
cmp eax, 14
jne t1
push dword 4
push ok
call escreverString

t1:
push lido
call lerChar
cmp eax, 5
jne t2
push dword 4
push ok
call escreverString

t2:
sub esp, 4
call lerInt
push ebx
mov ebx, [esp+4]
mov [inteiro], ebx
pop ebx
add esp, 4

cmp eax, 4
jne l3
push dword 4
push ok
call escreverString
cmp dword [inteiro], 1234
jne l3
push dword 4
push ok
call escreverString

l3:	mov eax, 1
	mov ebx, 0
	int 80h



escreverString:
push ebp
mov ebp, esp
push ebx
push ecx
push edx
mov eax, 4
mov ebx, 1
mov ecx, [ebp+8]
mov edx, [ebp+12]
int 80h
mov eax, [ebp+12]
pop edx
pop ecx
pop ebx
pop ebp
ret 8

lerChar:
push ebp
mov ax, 1
mov ebp, esp
mov eax, 3
mov ebx, 0
mov ecx, [ebp+8]
mov edx, 10
int 80h
push edx
push ecx
call countTillEnter
pop ebp
ret 4

lerInt:
push ebp
mov ebp, esp
push ebx
push ecx
push edx
mov eax, 3
mov ebx, 0
mov ecx, number
mov edx, 11
int 80h
push edx
push ecx
call countTillEnter
push dword 0
push eax
push ecx
call stoi
pop edx
mov dword [ebp+8], edx
pop edx
pop ecx
pop ebx
pop ebp
ret

stoi:
push ebp
mov ebp, esp
pusha
mov eax, 0
mov ecx, 0
mov edx, 0
mov ebx, [ebp+8]
cmp byte [ebx], 0x2D
convert: cmp byte [ebx+ecx], 0x0A
je stoi_fim
imul dword eax, 10
sub byte [ebx+ecx], 0x30
mov byte dl, [ebx+ecx]
add eax, edx
inc ecx
cmp ecx, [ebp+12]
jne convert
stoi_fim:
mov [ebp+16], eax
popa
pop ebp
ret 8

countTillEnter: push ebp
mov ebp, esp
push ebx
mov ebx, [ebp+8]
mov eax, -1
compare: cmp eax, [ebp+12]
je end
inc eax
cmp byte [ebx+eax], 0x0A
jne compare
end: pop ebx
pop ebp
ret 8