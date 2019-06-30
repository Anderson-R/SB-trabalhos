section .text
add eax, [OLD_DATA]
sub eax, [OLD_DATA]
imul [OLD_DATA]
idiv [OLD_DATA]
idiv [DOIS]
imul [DOIS]
sub eax, [TMP_DATA]
imul [DOIS]
jmp L2
cmp eax, 0
jl L2
cmp eax, 0
jg L2
cmp eax, 0
jz L2
section .data
DOIS dd 2
OLD_DATA dd 0
NEW_DATA dd 0, 0
TMP_DATA dd 0
