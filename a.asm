sseg SEGMENT STACK ;inicio seg. pilha
byte 16384 DUP(?)
sseg ENDS ;fim seg. pilha
dseg SEGMENT PUBLIC ;inicio seg. dados
byte 16384 DUP(?) ;temporarios
sword ? DUP(?) ;var int em 16384
byte ? DUP(?) ;var caract em 16404
sword 10 ;const int em 20500
byte ? DUP(?) ;var caract em 20502
sword 500 ;var int em 20512
byte 99 ;var caract em 20514
dseg ENDS
cseg SEGMENT PUBLIC ;inicio do seg. código
ASSUME CS:cseg, DS:dseg
strt: ; inicio do programa
mov ax, dseg
mov ds, ax
cseg ENDS ;fim seg. código
END strt