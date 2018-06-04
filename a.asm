sseg SEGMENT STACK ;inicio seg. pilha
	byte 16384 DUP(?)
sseg ENDS ;fim seg. pilha

dseg SEGMENT PUBLIC ;inicio seg. dados
	byte 16384 DUP(?) ;temporarios
	sword 0 ;const int em 16384
	sword 1 ;const int em 16386
	sword 2 ;const int em 16388
	sword 3 ;const int em 16390
	sword ? ;var int em 16392
	sword ? ;var int em 16394
	sword 3 DUP(?) ;var vet int em 16396
	sword ? ;var int em 16402
	sword ? ;var int em 16404
dseg ENDS ;fim seg. dados

cseg SEGMENT PUBLIC ;inicio do seg. código
	ASSUME CS:cseg, DS:dseg

strt: ; inicio do programa
	mov ax, dseg
	mov ds, ax


	; escrita no prompt

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "$" ;const string em 16406
dseg ENDS ;fim seg. dados

	mov si, 16406
	mov DS:[0], si
	mov dx, DS:[0]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

	; escrita no prompt

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte " *** Bubble Sort *** $" ;const string em 16407
dseg ENDS ;fim seg. dados

	mov si, 16407
	mov DS:[2], si
	mov dx, DS:[2]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

	; escrita no prompt

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "$" ;const string em 16429
dseg ENDS ;fim seg. dados

	mov si, 16429
	mov DS:[4], si
	mov dx, DS:[4]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

	; comando for
	mov ax, 0
	mov DS:[6], ax
	mov ax, DS:[6]
	mov DS:[16392], ax
	mov si, 16390
	mov ax, DS:[si]
	mov DS:[8], ax
	mov ax, 1
	mov DS:[10], ax
	mov ax, DS:[8]
	mov bx, DS:[10]
	neg bx
	add ax, bx
	mov DS:[12], ax
R0:
	mov ax, DS:[12]
	cmp DS:[16392], ax
	jg R1
	mov ax, 1
	push ax

	; escrita no prompt

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "value $" ;const string em 16430
dseg ENDS ;fim seg. dados

	mov si, 16430
	mov DS:[14], si
	mov dx, DS:[14]
	mov ah, 09h
	int 21h
	mov si, 16392
	mov ax, DS:[si]
	mov DS:[16], ax
	mov ax, DS:[16]
	mov di, 18
	mov cx, 0
	cmp ax, 0
	jge R2
	mov bl, 2Dh
	mov DS:[di], bl
	add di, 1
	neg ax
R2:
	mov bx, 10
R3:
	add cx, 1
	mov dx, 0
	idiv bx
	push dx
	cmp ax, 0
	jne R3
R4:
	pop dx
	add dx, 30h
	mov DS:[di], dl
	add di, 1
	add cx, -1
	cmp cx, 0
	jne R4
	mov dl, 024h
	mov DS:[di], dl
	mov dx, 18
	mov ah, 09h
	int 21h

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte " : $" ;const string em 16437
dseg ENDS ;fim seg. dados

	mov si, 16437
	mov DS:[25], si
	mov dx, DS:[25]
	mov ah, 09h
	int 21h
	mov si, 16392
	mov ax, DS:[si]
	mov DS:[27], ax
	mov ax, DS:[27]
	add ax, ax
	push ax
	mov si, 16396
	mov dx, 29
	mov al, 0FFh
	mov DS:[29], al
	mov ah, 0Ah
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h
	mov di, 31
	mov ax, 0
	mov cx, 10
	mov dx, 1
	mov bh, 0
	mov bl, DS:[di]
	cmp bx, 2Dh
	jne R5
	mov dx, -1
	add di, 1
	mov bl, DS:[di]
R5:
	push dx
	mov dx, 0
R6:
	cmp bx, 0Dh
	je R7
	imul cx
	add bx, -48
	add ax, bx
	add di, 1
	mov bh, 0
	mov bl, DS:[di]
	jmp R6
R7:
	pop cx
	imul cx
	pop bx
	add si, bx
	mov DS:[si], ax
	pop ax
	add DS:[16392], ax
	jmp R0
R1:

	; escrita no prompt

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "$" ;const string em 16441
dseg ENDS ;fim seg. dados

	mov si, 16441
	mov DS:[38], si
	mov dx, DS:[38]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

	; escrita no prompt

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "-- Menu -- $" ;const string em 16442
dseg ENDS ;fim seg. dados

	mov si, 16442
	mov DS:[40], si
	mov dx, DS:[40]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

	; escrita no prompt
	mov si, 16384
	mov ax, DS:[si]
	mov DS:[42], ax
	mov ax, DS:[42]
	mov di, 44
	mov cx, 0
	cmp ax, 0
	jge R8
	mov bl, 2Dh
	mov DS:[di], bl
	add di, 1
	neg ax
R8:
	mov bx, 10
R9:
	add cx, 1
	mov dx, 0
	idiv bx
	push dx
	cmp ax, 0
	jne R9
R10:
	pop dx
	add dx, 30h
	mov DS:[di], dl
	add di, 1
	add cx, -1
	cmp cx, 0
	jne R10
	mov dl, 024h
	mov DS:[di], dl
	mov dx, 44
	mov ah, 09h
	int 21h

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte " - exit$" ;const string em 16454
dseg ENDS ;fim seg. dados

	mov si, 16454
	mov DS:[51], si
	mov dx, DS:[51]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

	; escrita no prompt
	mov si, 16386
	mov ax, DS:[si]
	mov DS:[53], ax
	mov ax, DS:[53]
	mov di, 55
	mov cx, 0
	cmp ax, 0
	jge R11
	mov bl, 2Dh
	mov DS:[di], bl
	add di, 1
	neg ax
R11:
	mov bx, 10
R12:
	add cx, 1
	mov dx, 0
	idiv bx
	push dx
	cmp ax, 0
	jne R12
R13:
	pop dx
	add dx, 30h
	mov DS:[di], dl
	add di, 1
	add cx, -1
	cmp cx, 0
	jne R13
	mov dl, 024h
	mov DS:[di], dl
	mov dx, 55
	mov ah, 09h
	int 21h

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte " - ascending$" ;const string em 16462
dseg ENDS ;fim seg. dados

	mov si, 16462
	mov DS:[62], si
	mov dx, DS:[62]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

	; escrita no prompt
	mov si, 16388
	mov ax, DS:[si]
	mov DS:[64], ax
	mov ax, DS:[64]
	mov di, 66
	mov cx, 0
	cmp ax, 0
	jge R14
	mov bl, 2Dh
	mov DS:[di], bl
	add di, 1
	neg ax
R14:
	mov bx, 10
R15:
	add cx, 1
	mov dx, 0
	idiv bx
	push dx
	cmp ax, 0
	jne R15
R16:
	pop dx
	add dx, 30h
	mov DS:[di], dl
	add di, 1
	add cx, -1
	cmp cx, 0
	jne R16
	mov dl, 024h
	mov DS:[di], dl
	mov dx, 66
	mov ah, 09h
	int 21h

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte " - descending$" ;const string em 16475
dseg ENDS ;fim seg. dados

	mov si, 16475
	mov DS:[73], si
	mov dx, DS:[73]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

	; escrita no prompt

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "$" ;const string em 16489
dseg ENDS ;fim seg. dados

	mov si, 16489
	mov DS:[75], si
	mov dx, DS:[75]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

	; escrita no prompt

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "order by: $" ;const string em 16490
dseg ENDS ;fim seg. dados

	mov si, 16490
	mov DS:[77], si
	mov dx, DS:[77]
	mov ah, 09h
	int 21h
	mov si, 16404
	mov dx, 79
	mov al, 0FFh
	mov DS:[79], al
	mov ah, 0Ah
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h
	mov di, 81
	mov ax, 0
	mov cx, 10
	mov dx, 1
	mov bh, 0
	mov bl, DS:[di]
	cmp bx, 2Dh
	jne R17
	mov dx, -1
	add di, 1
	mov bl, DS:[di]
R17:
	push dx
	mov dx, 0
R18:
	cmp bx, 0Dh
	je R19
	imul cx
	add bx, -48
	add ax, bx
	add di, 1
	mov bh, 0
	mov bl, DS:[di]
	jmp R18
R19:
	pop cx
	imul cx
	mov DS:[si], ax

	; comando if
	mov si, 16404
	mov ax, DS:[si]
	mov DS:[88], ax
	mov si, 16384
	mov ax, DS:[si]
	mov DS:[90], ax
	mov ax, DS:[88]
	mov bx, DS:[90]
	cmp ax, bx
	jg R20
R21:
	mov al, 0
	jmp R22
R20:
	mov al, 1
R22:
	mov DS:[92], al
	mov si, 16404
	mov ax, DS:[si]
	mov DS:[93], ax
	mov si, 16388
	mov ax, DS:[si]
	mov DS:[95], ax
	mov ax, DS:[93]
	mov bx, DS:[95]
	cmp ax, bx
	jle R23
R24:
	mov al, 0
	jmp R25
R23:
	mov al, 1
R25:
	mov DS:[97], al
	mov ax, DS:[92]
	mov bx, DS:[97]
	imul bx
	mov DS:[98], ax
	mov ah, 0
	mov al, DS:[98]
	cmp ax, 0
	je R26

	; escrita no prompt

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "$" ;const string em 16501
dseg ENDS ;fim seg. dados

	mov si, 16501
	mov DS:[100], si
	mov dx, DS:[100]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

	; escrita no prompt

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte " Sorting...$" ;const string em 16502
dseg ENDS ;fim seg. dados

	mov si, 16502
	mov DS:[102], si
	mov dx, DS:[102]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

	; escrita no prompt

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "$" ;const string em 16514
dseg ENDS ;fim seg. dados

	mov si, 16514
	mov DS:[104], si
	mov dx, DS:[104]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

	; comando if
	mov si, 16404
	mov ax, DS:[si]
	mov DS:[106], ax
	mov si, 16386
	mov ax, DS:[si]
	mov DS:[108], ax
	mov ax, DS:[106]
	mov bx, DS:[108]
	cmp ax, bx
	je R28
R29:
	mov al, 0
	jmp R30
R28:
	mov al, 1
R30:
	mov DS:[110], al
	mov ah, 0
	mov al, DS:[110]
	cmp ax, 0
	je R31

	; comando for
	mov ax, 0
	mov DS:[111], ax
	mov ax, DS:[111]
	mov DS:[16392], ax
	mov si, 16390
	mov ax, DS:[si]
	mov DS:[113], ax
	mov ax, 1
	mov DS:[115], ax
	mov ax, DS:[113]
	mov bx, DS:[115]
	neg bx
	add ax, bx
	mov DS:[117], ax
R33:
	mov ax, DS:[117]
	cmp DS:[16392], ax
	jg R34
	mov ax, 1
	push ax

	; comando for
	mov ax, 0
	mov DS:[119], ax
	mov ax, DS:[119]
	mov DS:[16394], ax
	mov si, 16390
	mov ax, DS:[si]
	mov DS:[121], ax
	mov ax, 1
	mov DS:[123], ax
	mov ax, DS:[121]
	mov bx, DS:[123]
	neg bx
	add ax, bx
	mov DS:[125], ax
R35:
	mov ax, DS:[125]
	cmp DS:[16394], ax
	jg R36
	mov ax, 1
	push ax

	; comando if
	mov si, 16392
	mov ax, DS:[si]
	mov DS:[127], ax
	mov ax, DS:[127]
	add ax, ax
	mov si, 16396
	add si, ax
	mov ax, DS:[si]
	mov DS:[129], ax
	mov si, 16394
	mov ax, DS:[si]
	mov DS:[131], ax
	mov ax, DS:[131]
	add ax, ax
	mov si, 16396
	add si, ax
	mov ax, DS:[si]
	mov DS:[133], ax
	mov ax, DS:[129]
	mov bx, DS:[133]
	cmp ax, bx
	jl R37
R38:
	mov al, 0
	jmp R39
R37:
	mov al, 1
R39:
	mov DS:[135], al
	mov ah, 0
	mov al, DS:[135]
	cmp ax, 0
	je R40
	mov si, 16392
	mov ax, DS:[si]
	mov DS:[136], ax
	mov ax, DS:[136]
	add ax, ax
	mov si, 16396
	add si, ax
	mov ax, DS:[si]
	mov DS:[138], ax
	mov si, 16402
	mov ax, DS:[138]
	mov DS:[si], ax
	mov si, 16392
	mov ax, DS:[si]
	mov DS:[140], ax
	mov ax, DS:[140]
	add ax, ax
	push ax
	mov si, 16394
	mov ax, DS:[si]
	mov DS:[142], ax
	mov ax, DS:[142]
	add ax, ax
	mov si, 16396
	add si, ax
	mov ax, DS:[si]
	mov DS:[144], ax
	mov si, 16396
	pop ax
	add si, ax
	mov ax, DS:[144]
	mov DS:[si], ax
	mov si, 16394
	mov ax, DS:[si]
	mov DS:[146], ax
	mov ax, DS:[146]
	add ax, ax
	push ax
	mov si, 16402
	mov ax, DS:[si]
	mov DS:[148], ax
	mov si, 16396
	pop ax
	add si, ax
	mov ax, DS:[148]
	mov DS:[si], ax
R40:
	pop ax
	add DS:[16394], ax
	jmp R35
R36:
	pop ax
	add DS:[16392], ax
	jmp R33
R34:
	jmp R32
R31:

	; comando for
	mov ax, 0
	mov DS:[150], ax
	mov ax, DS:[150]
	mov DS:[16392], ax
	mov si, 16390
	mov ax, DS:[si]
	mov DS:[152], ax
	mov ax, 1
	mov DS:[154], ax
	mov ax, DS:[152]
	mov bx, DS:[154]
	neg bx
	add ax, bx
	mov DS:[156], ax
R42:
	mov ax, DS:[156]
	cmp DS:[16392], ax
	jg R43
	mov ax, 1
	push ax

	; comando for
	mov ax, 0
	mov DS:[158], ax
	mov ax, DS:[158]
	mov DS:[16394], ax
	mov si, 16390
	mov ax, DS:[si]
	mov DS:[160], ax
	mov ax, 1
	mov DS:[162], ax
	mov ax, DS:[160]
	mov bx, DS:[162]
	neg bx
	add ax, bx
	mov DS:[164], ax
R44:
	mov ax, DS:[164]
	cmp DS:[16394], ax
	jg R45
	mov ax, 1
	push ax

	; comando if
	mov si, 16392
	mov ax, DS:[si]
	mov DS:[166], ax
	mov ax, DS:[166]
	add ax, ax
	mov si, 16396
	add si, ax
	mov ax, DS:[si]
	mov DS:[168], ax
	mov si, 16394
	mov ax, DS:[si]
	mov DS:[170], ax
	mov ax, DS:[170]
	add ax, ax
	mov si, 16396
	add si, ax
	mov ax, DS:[si]
	mov DS:[172], ax
	mov ax, DS:[168]
	mov bx, DS:[172]
	cmp ax, bx
	jg R46
R47:
	mov al, 0
	jmp R48
R46:
	mov al, 1
R48:
	mov DS:[174], al
	mov ah, 0
	mov al, DS:[174]
	cmp ax, 0
	je R49
	mov si, 16392
	mov ax, DS:[si]
	mov DS:[175], ax
	mov ax, DS:[175]
	add ax, ax
	mov si, 16396
	add si, ax
	mov ax, DS:[si]
	mov DS:[177], ax
	mov si, 16402
	mov ax, DS:[177]
	mov DS:[si], ax
	mov si, 16392
	mov ax, DS:[si]
	mov DS:[179], ax
	mov ax, DS:[179]
	add ax, ax
	push ax
	mov si, 16394
	mov ax, DS:[si]
	mov DS:[181], ax
	mov ax, DS:[181]
	add ax, ax
	mov si, 16396
	add si, ax
	mov ax, DS:[si]
	mov DS:[183], ax
	mov si, 16396
	pop ax
	add si, ax
	mov ax, DS:[183]
	mov DS:[si], ax
	mov si, 16394
	mov ax, DS:[si]
	mov DS:[185], ax
	mov ax, DS:[185]
	add ax, ax
	push ax
	mov si, 16402
	mov ax, DS:[si]
	mov DS:[187], ax
	mov si, 16396
	pop ax
	add si, ax
	mov ax, DS:[187]
	mov DS:[si], ax
R49:
	pop ax
	add DS:[16394], ax
	jmp R44
R45:
	pop ax
	add DS:[16392], ax
	jmp R42
R43:
R32:

	; comando for
	mov ax, 0
	mov DS:[189], ax
	mov ax, DS:[189]
	mov DS:[16392], ax
	mov si, 16390
	mov ax, DS:[si]
	mov DS:[191], ax
	mov ax, 1
	mov DS:[193], ax
	mov ax, DS:[191]
	mov bx, DS:[193]
	neg bx
	add ax, bx
	mov DS:[195], ax
R51:
	mov ax, DS:[195]
	cmp DS:[16392], ax
	jg R52
	mov ax, 1
	push ax

	; escrita no prompt
	mov si, 16392
	mov ax, DS:[si]
	mov DS:[197], ax
	mov ax, DS:[197]
	add ax, ax
	mov si, 16396
	add si, ax
	mov ax, DS:[si]
	mov DS:[199], ax
	mov ax, DS:[199]
	mov di, 201
	mov cx, 0
	cmp ax, 0
	jge R53
	mov bl, 2Dh
	mov DS:[di], bl
	add di, 1
	neg ax
R53:
	mov bx, 10
R54:
	add cx, 1
	mov dx, 0
	idiv bx
	push dx
	cmp ax, 0
	jne R54
R55:
	pop dx
	add dx, 30h
	mov DS:[di], dl
	add di, 1
	add cx, -1
	cmp cx, 0
	jne R55
	mov dl, 024h
	mov DS:[di], dl
	mov dx, 201
	mov ah, 09h
	int 21h

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte " $" ;const string em 16515
dseg ENDS ;fim seg. dados

	mov si, 16515
	mov DS:[208], si
	mov dx, DS:[208]
	mov ah, 09h
	int 21h
	pop ax
	add DS:[16392], ax
	jmp R51
R52:
R26:

;Fim do programa
	mov ah, 4Ch
	int 21h

cseg ENDS ;fim seg. código
END strt ;fim do programa