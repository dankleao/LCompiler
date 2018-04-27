sseg SEGMENT STACK ;inicio seg. pilha
byte 16384 DUP(?)
sseg ENDS ;fim seg. pilha
dseg SEGMENT PUBLIC ;inicio seg. dados
byte 16384 DUP(?) ;temporarios
dseg ENDS
cseg SEGMENT PUBLIC ;inicio do seg. código
ASSUME CS:cseg, DS:dseg
strt: ; inicio do programa
mov ax, dseg
mov ds, ax
cseg ENDS ;fim seg. código
END strt