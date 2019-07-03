


SECTION text
ADD OLD_DATA
SUB OLD_DATA
MULT OLD_DATA
DIV DOIS
INPUT OLD_DATA
LOAD OLD_DATA
L1:
DIV DOIS
STORE NEW_DATA + 1
mult DOIS
STORE         TMP_DATA ;this is a comment
load OLD_DATA
L2: sub                                                            TMP_DATA
STORE TMP_DATA
mult DOIS

OUTPUT TMP_DATA
COPY NEW_DATA, OLD_DATA
LOAD OLD_DATA
c_output DOIS
c_input DOIS
copy h, hello
copy e, hello+1
copy l, hello+2
copy l, hello+3
copy o, hello+4
s_output hello, 5
jmp acabou
jmpn L2
jmpp L2
jmpz L2
load OLD_DATA
store OLD_DATA
copy NEW_DATA, OLD_DATA
acabou: STOP

;loool

SECTION         data
DOIS: const 67
OLD_DATA: space
NEW_DATA: SPACE 2
h: const 72
e: const 69
l: const 76
o: const 79
hello: space 5

  




TMP_DATA: SPACE