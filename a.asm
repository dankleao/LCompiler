sseg SEGMENT STACK ;inicio seg. pilha
	byte 16384 DUP(?)
sseg ENDS ;fim seg. pilha

dseg SEGMENT PUBLIC ;inicio seg. dados
	byte 16384 DUP(?) ;temporarios
	sword 3 DUP(?) ;var vet int em 16384
	sword 0 ;var int em 16390
	sword ? ;var int em 16392
	byte 101 DUP(?) ;var vet caract em 16394
	byte 221 ;const caract em 16495
dseg ENDS ;fim seg. dados

cseg SEGMENT PUBLIC ;inicio do seg. código
	ASSUME CS:cseg, DS:dseg

strt: ; inicio do programa
	mov ax, dseg
	mov ds, ax


dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "My first program in L$" ;const string em 16496
dseg ENDS ;fim seg. dados

	mov ax, 16496
	mov DS:[0], ax
	mov si, 16394
	mov di, DS:[0]
R0:
	mov ah, 0
	mov al, DS:[di]
	mov DS:[si], ax
	cmp ax, 024h
	je R1
	add si, 1
	add di, 1
	jmp R0
R1:
	mov si, 16394
	mov DS:[1], si
	mov dx, DS:[1]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h
	mov ax, 0
	mov DS:[2], ax
	mov si, 16392
	mov ax, DS:[2]
	mov DS:[si], ax
	mov ax, 2
	mov DS:[4], ax
R2:
	mov ax, DS:[4]
	cmp DS:[16392], ax
	jg R3
	mov ah, 0
	mov al, 1
	push ax

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "Digite um numero: $" ;const string em 16518
dseg ENDS ;fim seg. dados

	mov ax, 16518
	mov DS:[6], ax
	mov dx, DS:[6]
	mov ah, 09h
	int 21h
	mov ax, DS:[16392]
	mov DS:[7], ax
	mov ax, DS:[16384]
	add ax, ax
	push ax
	mov si, 16384
	mov dx, 9
	mov al, 0FFh
	mov DS:[9], al
	mov ah, 0Ah
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h
	mov di, 11
	mov ax, 0
	mov cx, 10
	mov dx, 1
	mov bh, 0
	mov bl, DS:[di]
	cmp bx, 2Dh
	jne R4
	mov dx, -1
	add di, 1
	mov bl, DS:[di]
R4:
	push dx
	mov dx, 0
R5:
	cmp bx, 0Dh
	je R6
	imul cx
	add bx, -48
	add ax, bx
	add di, 1
	mov bh, 0
	mov bl, DS:[di]
	jmp R5
R6:
	pop cx
	imul cx

	; read indexed array
	pop bx
	add si, bx
	mov DS:[si], ax
	pop ax
	add DS:[16392], ax
	jmp R2
	R3:
	mov ax, 0
	mov DS:[11], ax
	mov ax, DS:[11]
	add ax, ax
	mov si, 16384
	add si, ax
	mov ax, DS:[si]
	mov DS:[13], ax
	mov ax, 1
	mov DS:[15], ax
	mov ax, DS:[15]
	add ax, ax
	mov si, 16384
	add si, ax
	mov ax, DS:[si]
	mov DS:[17], ax
	mov ax, DS:[13]
	mov bx, DS:[17]
	mov ah, 0
	mov bh, 0
	cmp ax, bx
	jg R7
R8:
	mov ax, 0
	jmp R9
R7:
	mov ax, 1
R9:
	mov DS:[19], ax
	mov ax, DS:[19]
	cmp ax, 0
	je R10
	mov ax, 0
	mov DS:[20], ax
	mov ax, DS:[20]
	add ax, ax
	mov si, 16384
	add si, ax
	mov ax, DS:[si]
	mov DS:[22], ax
	mov ax, 2
	mov DS:[24], ax
	mov ax, DS:[24]
	add ax, ax
	mov si, 16384
	add si, ax
	mov ax, DS:[si]
	mov DS:[26], ax
	mov ax, DS:[22]
	mov bx, DS:[26]
	mov ah, 0
	mov bh, 0
	cmp ax, bx
	jg R12
R13:
	mov ax, 0
	jmp R14
R12:
	mov ax, 1
R14:
	mov DS:[28], ax
	mov ax, DS:[28]
	cmp ax, 0
	je R15
	mov ax, 0
	mov DS:[29], ax
	mov ax, DS:[29]
	add ax, ax
	mov si, 16384
	add si, ax
	mov ax, DS:[si]
	mov DS:[31], ax
	mov si, 16390
	mov ax, DS:[31]
	mov DS:[si], ax
	jmp R16
R15:
	mov ax, 2
	mov DS:[33], ax
	mov ax, DS:[33]
	add ax, ax
	mov si, 16384
	add si, ax
	mov ax, DS:[si]
	mov DS:[35], ax
	mov si, 16390
	mov ax, DS:[35]
	mov DS:[si], ax
R16:
	jmp R11
R10:
	mov ax, 1
	mov DS:[37], ax
	mov ax, DS:[37]
	add ax, ax
	mov si, 16384
	add si, ax
	mov ax, DS:[si]
	mov DS:[39], ax
	mov ax, 2
	mov DS:[41], ax
	mov ax, DS:[41]
	add ax, ax
	mov si, 16384
	add si, ax
	mov ax, DS:[si]
	mov DS:[43], ax
	mov ax, DS:[39]
	mov bx, DS:[43]
	mov ah, 0
	mov bh, 0
	cmp ax, bx
	jg R17
R18:
	mov ax, 0
	jmp R19
R17:
	mov ax, 1
R19:
	mov DS:[45], ax
	mov ax, DS:[45]
	cmp ax, 0
	je R20
	mov ax, 1
	mov DS:[46], ax
	mov ax, DS:[46]
	add ax, ax
	mov si, 16384
	add si, ax
	mov ax, DS:[si]
	mov DS:[48], ax
	mov si, 16390
	mov ax, DS:[48]
	mov DS:[si], ax
	jmp R21
R20:
	mov ax, 2
	mov DS:[50], ax
	mov ax, DS:[50]
	add ax, ax
	mov si, 16384
	add si, ax
	mov ax, DS:[si]
	mov DS:[52], ax
	mov si, 16390
	mov ax, DS:[52]
	mov DS:[si], ax
R21:
R11:

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "O maior numero e $" ;const string em 16537
dseg ENDS ;fim seg. dados

	mov ax, 16537
	mov DS:[54], ax
	mov dx, DS:[54]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h
	mov ax, DS:[16390]
	mov DS:[55], ax
	mov ax, DS:[55]
	mov di, 57
	mov cx, 0
	cmp ax, 0
	jge R22
	mov bl, 2Dh
	mov DS:[di], bl
	add di, 1
	neg ax
R22:
	mov bx, 10
R23:
	add cx, 1
	mov dx, 0
	idiv bx
	push dx
	cmp ax, 0
	jne R23
R24:
	pop dx
	add dx, 30h
	mov DS:[di], dl
	add di, 1
	add cx, -1
	cmp cx, 0
	jne R24
	mov dl, 024h
	mov DS:[di], dl
	mov dx, 57
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