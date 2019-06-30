section .text
add eax, [OLD_DATA]
sub eax, [OLD_DATA]
imul [OLD_DATA]
idiv [OLD_DATA]
mov eax, [OLD_DATA]
idiv [DOIS]
mov dword [NEW_DATA+1], eax
imul [DOIS]
mov dword [TMP_DATA], eax
mov eax, [OLD_DATA]
sub eax, [TMP_DATA]
mov dword [TMP_DATA], eax
imul [DOIS]
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
call escreverCharpush DOIS
call lerCharmov eax, 1
mov ebx, 0
int 80h
section .data
DOIS dd 67
OLD_DATA dd 0
NEW_DATA dd 0, 0
TMP_DATA dd 0
