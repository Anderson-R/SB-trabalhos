;Util functions
escreverChar:
push ebp
mov ebp, esp
push ebx
push ecx
push edx
mov eax, 4
mov ebx, 1
mov ecx, [ebp+8]
mov edx, 1
int 80h
pop edx
pop ecx
pop ebx
pop ebp
mov ax, 1
ret 4

lerChar:
push ebp
mov ebp, esp
push ebx
push ecx
push edx
mov eax, 3
mov ebx, 0
mov ecx, [ebp+8]
mov edx, 1
int 80h
pop edx
pop ecx
pop ebx
pop ebp
mov ax, 1
ret 4

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
pop edx
pop ecx
pop ebx
pop ebp
mov ax, [ebp+12]
ret 8

lerString:
push ebp
mov ebp, esp
push ebx
push ecx
push edx
mov eax, 3
mov ebx, 0
mov ecx, [ebp+8]
mov edx, [ebp+12]
int 80h
push edx
push ecx
call countTillEnter
pop edx
pop ecx
pop ebx
pop ebp
mov ax, 1
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



section .text
global _start
_start:
add eax, [OLD_DATA]
sub eax, [OLD_DATA]
imul dword [OLD_DATA]
idiv dword [DOIS]
mov eax, [OLD_DATA]
L1:
idiv dword [DOIS]
mov dword [NEW_DATA+1], eax
imul dword [DOIS]
mov dword [TMP_DATA], eax
mov eax, [OLD_DATA]
L2:
sub eax, [TMP_DATA]
mov dword [TMP_DATA], eax
imul dword [DOIS]
push eax
mov eax, [NEW_DATA]
mov dword [OLD_DATA], eax
pop eax
mov eax, [OLD_DATA]
push DOIS
call escreverChar
push DOIS
call lerChar
push eax
mov eax, [H]
mov dword [HELLO], eax
pop eax
push eax
mov eax, [E]
mov dword [HELLO+1], eax
pop eax
push eax
mov eax, [L]
mov dword [HELLO+2], eax
pop eax
push eax
mov eax, [L]
mov dword [HELLO+3], eax
pop eax
push eax
mov eax, [O]
mov dword [HELLO+4], eax
pop eax
push 5
push HELLO
call escreverString
jmp ACABOU
cmp eax, 0
jl L2
cmp eax, 0
jg L2
cmp eax, 0
jz L2
mov eax, [OLD_DATA]
mov dword [OLD_DATA], eax
push eax
mov eax, [NEW_DATA]
mov dword [OLD_DATA], eax
pop eax
ACABOU:
mov eax, 1
mov ebx, 0
int 80h
section .data
DOIS dd 67
OLD_DATA dd 0
NEW_DATA dd 0, 0
H dd 72
E dd 69
L dd 76
O dd 79
HELLO dd 0, 0, 0, 0, 0
TMP_DATA dd 0
