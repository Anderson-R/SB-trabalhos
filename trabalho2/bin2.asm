;Util functions
escreverChar:
push ebp
push ebx
push ecx
push edx
mov ax, 1
mov ebp, esp
mov eax, 4
mov ebx, 1
mov ecx, [ebp+8]
mov edx, 1
int 80h
pop edx
pop ecx
pop ebx
pop ebp
ret 4
lerChar:
push ebp
push ebx
push ecx
push edx
mov ax, 0
mov ebp, esp
mov eax, 4
mov ebx, 1
mov ecx, [ebp+8]
mov edx, 1
int 80h
pop edx
pop ecx
pop ebx
pop ebp
ret 4


section .text
global _start
_start:
add eax, [OLD_DATA]
sub eax, [OLD_DATA]
imul dword [OLD_DATA]
idiv dword [OLD_DATA]
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
jmp L2
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
push DOIS
call escreverChar
push DOIS
call lerChar
mov eax, 1
mov ebx, 0
int 80h
section .data
DOIS dd 67
OLD_DATA dd 0
NEW_DATA dd 0, 0
TMP_DATA dd 0
