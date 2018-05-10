sseg SEGMENT STACK ;inicio seg. pilha
	byte 16384 DUP(?)
sseg ENDS ;fim seg. pilha

dseg SEGMENT PUBLIC ;inicio seg. dados
	byte 16384 DUP(?) ;temporarios
dseg ENDS ;fim seg. dados

cseg SEGMENT PUBLIC ;inicio do seg. código
	ASSUME CS:cseg, DS:dseg

strt: ; inicio do programa
	mov ax, dseg
	mov ds, ax


dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "Hello World!$" ;const string em 16384
dseg ENDS ;fim seg. dados

	mov ax, 16384
	mov DS:[0], ax
	mov dx, DS:[0]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

;Fim do programa
	mov ah, 4Ch
	int 21h

cseg ENDS ;fim seg. código
END strt ;fim do programa