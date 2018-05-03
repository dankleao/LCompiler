sseg SEGMENT STACK ;inicio seg. pilha
	byte 16384 DUP(?)
sseg ENDS ;fim seg. pilha

dseg SEGMENT PUBLIC ;inicio seg. dados
	byte 16384 DUP(?) ;temporarios
	sword 10 DUP(?) ;var vet int em 16384
	byte 4096 DUP(?) ;var vet caract em 16404
	sword 10 ;const int em 20500
	byte 10 DUP(?) ;var vet caract em 20502
	sword 500 ;var int em 20512
	byte 99 ;const caract em 20514
dseg ENDS ;fim seg. dados

cseg SEGMENT PUBLIC ;inicio do seg. código
	ASSUME CS:cseg, DS:dseg

strt: ; inicio do programa
	mov ax, dseg
	mov ds, ax

	;TEMP CONST INT em 0
	mov ax, 0
	mov DS:[0], ax

	;TEMP CONST INT em 0
	mov ax, 9
	mov DS:[0], ax

	;TEMP CONST INT em 0
	mov ax, 1
	mov DS:[0], ax

	;TEMP CONST INT em 0
	mov ax, 0
	mov DS:[0], ax

	mov ax, DS:[0]
	add ax, ax
	add ax, 16384
	mov bx, ax
	mov ax, DS:[bx]
	mov DS:[1], ax

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "Digite seu nome: $" ;const string em 20515
dseg ENDS ;fim seg. dados

	;TEMP CONST INT em 0
	mov ax, 1
	mov DS:[0], ax

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "Ola' $" ;const string em 20533
dseg ENDS ;fim seg. dados

cseg ENDS ;fim seg. código
END strt ;fim do programa