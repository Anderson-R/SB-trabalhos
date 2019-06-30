


SECTION text
ADD OLD_DATA
SUB OLD_DATA
MULT OLD_DATA
DIV OLD_DATA
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
jmp L2
jmpn L2
jmpp L2
jmpz L2
STOP

;loool

SECTION         data
DOIS: const 2
OLD_DATA: space
NEW_DATA: SPACE 2

  




TMP_DATA: SPACE