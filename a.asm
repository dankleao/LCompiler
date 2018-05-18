sseg SEGMENT STACK ;inicio seg. pilha
	byte 16384 DUP(?)
sseg ENDS ;fim seg. pilha

dseg SEGMENT PUBLIC ;inicio seg. dados
	byte 16384 DUP(?) ;temporarios
	sword ? ;var int em 16384
	sword ? ;var int em 16386
	sword 3 ;const int em 16388
	sword 3 DUP(?) ;var vet int em 16390
	sword ? ;var int em 16396
	byte 4 DUP(?) ;var vet caract em 16398
dseg ENDS ;fim seg. dados

cseg SEGMENT PUBLIC ;inicio do seg. código
	ASSUME CS:cseg, DS:dseg

strt: ; inicio do programa
	mov ax, dseg
	mov ds, ax


dseg SEGMENT PUBLIC ; inicio seg. dados
	byte " *** Bubble Sort *** $" ;const string em 16402
dseg ENDS ;fim seg. dados

	mov si, 16402
	mov DS:[0], si
	mov dx, DS:[0]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "$" ;const string em 16424
dseg ENDS ;fim seg. dados

	mov si, 16424
	mov DS:[2], si
	mov dx, DS:[2]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h
	mov ax, 0
	mov DS:[4], ax
	mov ax, DS:[4]
	mov DS:[16384], ax
	mov si, 16388
	mov ax, DS:[si]
	mov DS:[6], ax
	mov ax, 1
	mov DS:[8], ax
	mov ax, DS:[6]
	mov bx, DS:[8]
	neg bx
	add ax, bx
	mov DS:[10], ax
R0:
	mov ax, DS:[10]
	cmp DS:[16384], ax
	jg R1
	mov ax, 1
	push ax

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "value $" ;const string em 16425
dseg ENDS ;fim seg. dados

	mov si, 16425
	mov DS:[12], si
	mov dx, DS:[12]
	mov ah, 09h
	int 21h
	mov si, 16384
	mov ax, DS:[si]
	mov DS:[14], ax
	mov ax, DS:[14]
	mov di, 16
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
	mov dx, 16
	mov ah, 09h
	int 21h

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte " : $" ;const string em 16432
dseg ENDS ;fim seg. dados

	mov si, 16432
	mov DS:[23], si
	mov dx, DS:[23]
	mov ah, 09h
	int 21h
	mov si, 16384
	mov ax, DS:[si]
	mov DS:[25], ax
	mov ax, DS:[25]
	add ax, ax
	push ax
	mov si, 16390
	mov dx, 27
	mov al, 0FFh
	mov DS:[27], al
	mov ah, 0Ah
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h
	mov di, 29
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
	add DS:[16384], ax
	jmp R0
R1:

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "$" ;const string em 16436
dseg ENDS ;fim seg. dados

	mov si, 16436
	mov DS:[36], si
	mov dx, DS:[36]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "Choose sort order: $" ;const string em 16437
dseg ENDS ;fim seg. dados

	mov si, 16437
	mov DS:[38], si
	mov dx, DS:[38]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte " asc - ascending$" ;const string em 16457
dseg ENDS ;fim seg. dados

	mov si, 16457
	mov DS:[40], si
	mov dx, DS:[40]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte " des - descending$" ;const string em 16474
dseg ENDS ;fim seg. dados

	mov si, 16474
	mov DS:[42], si
	mov dx, DS:[42]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "$" ;const string em 16492
dseg ENDS ;fim seg. dados

	mov si, 16492
	mov DS:[44], si
	mov dx, DS:[44]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "option: $" ;const string em 16493
dseg ENDS ;fim seg. dados

	mov si, 16493
	mov DS:[46], si
	mov dx, DS:[46]
	mov ah, 09h
	int 21h
	mov si, 16398

	; leitura de string
	mov dx, 48
	mov al, 0FFh
	mov DS:[48], al
	mov ah, 0Ah
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h
	mov di, 50
R8:
	mov ax, DS:[di]
	cmp ax, 0Dh
	je R9
	mov ah, 0
	mov al, DS:[di]
	mov DS:[si], ax
	add si, 1
	add di, 1
	jmp R8
R9:
	mov ah, 0
	mov al, 024h
	mov DS:[si], al

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "$" ;const string em 16502
dseg ENDS ;fim seg. dados

	mov si, 16502
	mov DS:[303], si
	mov dx, DS:[303]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte " Sorting...$" ;const string em 16503
dseg ENDS ;fim seg. dados

	mov si, 16503
	mov DS:[305], si
	mov dx, DS:[305]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "$" ;const string em 16515
dseg ENDS ;fim seg. dados

	mov si, 16515
	mov DS:[307], si
	mov dx, DS:[307]
	mov ah, 09h
	int 21h
	mov ah, 02h
	mov dl, 0Dh
	int 21h
	mov dl, 0Ah
	int 21h
	mov si, 16398
	mov DS:[309], si

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte "asc$" ;const string em 16516
dseg ENDS ;fim seg. dados

	mov si, 16516
	mov DS:[311], si
	mov si, DS:[309]
	mov di, DS:[311]
	mov ah, 0
	mov bh, 0
R10:
	mov al, DS:[si]
	mov bl, DS:[di]
	add si, 1
	add di, 1
	neg al
	add al, bl
	cmp ax, 0
	jne R11
	cmp bx, 024h
	jne R10
	mov al, 1
	jmp R12
R11:
	mov al, 0
R12:
	mov DS:[313], al
	mov ah, 0
	mov al, DS:[313]
	cmp ax, 0
	je R13
	mov ax, 0
	mov DS:[314], ax
	mov ax, DS:[314]
	mov DS:[16384], ax
	mov si, 16388
	mov ax, DS:[si]
	mov DS:[316], ax
	mov ax, 1
	mov DS:[318], ax
	mov ax, DS:[316]
	mov bx, DS:[318]
	neg bx
	add ax, bx
	mov DS:[320], ax
R15:
	mov ax, DS:[320]
	cmp DS:[16384], ax
	jg R16
	mov ax, 1
	push ax
	mov ax, 0
	mov DS:[322], ax
	mov ax, DS:[322]
	mov DS:[16386], ax
	mov si, 16388
	mov ax, DS:[si]
	mov DS:[324], ax
	mov ax, 1
	mov DS:[326], ax
	mov ax, DS:[324]
	mov bx, DS:[326]
	neg bx
	add ax, bx
	mov DS:[328], ax
R17:
	mov ax, DS:[328]
	cmp DS:[16386], ax
	jg R18
	mov ax, 1
	push ax
	mov si, 16384
	mov ax, DS:[si]
	mov DS:[330], ax
	mov ax, DS:[330]
	add ax, ax
	mov si, 16390
	add si, ax
	mov ax, DS:[si]
	mov DS:[332], ax
	mov si, 16386
	mov ax, DS:[si]
	mov DS:[334], ax
	mov ax, DS:[334]
	add ax, ax
	mov si, 16390
	add si, ax
	mov ax, DS:[si]
	mov DS:[336], ax
	mov ax, DS:[332]
	mov bx, DS:[336]
	mov ah, 0
	mov bh, 0
	cmp ax, bx
	jl R19
R20:
	mov al, 0
	jmp R21
R19:
	mov al, 1
R21:
	mov DS:[338], al
	mov ah, 0
	mov al, DS:[338]
	cmp ax, 0
	je R22
	mov si, 16384
	mov ax, DS:[si]
	mov DS:[339], ax
	mov ax, DS:[339]
	add ax, ax
	mov si, 16390
	add si, ax
	mov ax, DS:[si]
	mov DS:[341], ax
	mov si, 16396
	mov ax, DS:[341]
	mov DS:[si], ax
	mov si, 16384
	mov ax, DS:[si]
	mov DS:[343], ax
	mov ax, DS:[343]
	add ax, ax
	push ax
	mov si, 16386
	mov ax, DS:[si]
	mov DS:[345], ax
	mov ax, DS:[345]
	add ax, ax
	mov si, 16390
	add si, ax
	mov ax, DS:[si]
	mov DS:[347], ax
	mov si, 16390
	pop ax
	add si, ax
	mov ax, DS:[347]
	mov DS:[si], ax
	mov si, 16386
	mov ax, DS:[si]
	mov DS:[349], ax
	mov ax, DS:[349]
	add ax, ax
	push ax
	mov si, 16396
	mov ax, DS:[si]
	mov DS:[351], ax
	mov si, 16390
	pop ax
	add si, ax
	mov ax, DS:[351]
	mov DS:[si], ax
R22:
	pop ax
	add DS:[16386], ax
	jmp R17
R18:
	pop ax
	add DS:[16384], ax
	jmp R15
R16:
	jmp R14
R13:
	mov ax, 0
	mov DS:[353], ax
	mov ax, DS:[353]
	mov DS:[16384], ax
	mov si, 16388
	mov ax, DS:[si]
	mov DS:[355], ax
	mov ax, 1
	mov DS:[357], ax
	mov ax, DS:[355]
	mov bx, DS:[357]
	neg bx
	add ax, bx
	mov DS:[359], ax
R24:
	mov ax, DS:[359]
	cmp DS:[16384], ax
	jg R25
	mov ax, 1
	push ax
	mov ax, 0
	mov DS:[361], ax
	mov ax, DS:[361]
	mov DS:[16386], ax
	mov si, 16388
	mov ax, DS:[si]
	mov DS:[363], ax
	mov ax, 1
	mov DS:[365], ax
	mov ax, DS:[363]
	mov bx, DS:[365]
	neg bx
	add ax, bx
	mov DS:[367], ax
R26:
	mov ax, DS:[367]
	cmp DS:[16386], ax
	jg R27
	mov ax, 1
	push ax
	mov si, 16384
	mov ax, DS:[si]
	mov DS:[369], ax
	mov ax, DS:[369]
	add ax, ax
	mov si, 16390
	add si, ax
	mov ax, DS:[si]
	mov DS:[371], ax
	mov si, 16386
	mov ax, DS:[si]
	mov DS:[373], ax
	mov ax, DS:[373]
	add ax, ax
	mov si, 16390
	add si, ax
	mov ax, DS:[si]
	mov DS:[375], ax
	mov ax, DS:[371]
	mov bx, DS:[375]
	mov ah, 0
	mov bh, 0
	cmp ax, bx
	jg R28
R29:
	mov al, 0
	jmp R30
R28:
	mov al, 1
R30:
	mov DS:[377], al
	mov ah, 0
	mov al, DS:[377]
	cmp ax, 0
	je R31
	mov si, 16384
	mov ax, DS:[si]
	mov DS:[378], ax
	mov ax, DS:[378]
	add ax, ax
	mov si, 16390
	add si, ax
	mov ax, DS:[si]
	mov DS:[380], ax
	mov si, 16396
	mov ax, DS:[380]
	mov DS:[si], ax
	mov si, 16384
	mov ax, DS:[si]
	mov DS:[382], ax
	mov ax, DS:[382]
	add ax, ax
	push ax
	mov si, 16386
	mov ax, DS:[si]
	mov DS:[384], ax
	mov ax, DS:[384]
	add ax, ax
	mov si, 16390
	add si, ax
	mov ax, DS:[si]
	mov DS:[386], ax
	mov si, 16390
	pop ax
	add si, ax
	mov ax, DS:[386]
	mov DS:[si], ax
	mov si, 16386
	mov ax, DS:[si]
	mov DS:[388], ax
	mov ax, DS:[388]
	add ax, ax
	push ax
	mov si, 16396
	mov ax, DS:[si]
	mov DS:[390], ax
	mov si, 16390
	pop ax
	add si, ax
	mov ax, DS:[390]
	mov DS:[si], ax
R31:
	pop ax
	add DS:[16386], ax
	jmp R26
R27:
	pop ax
	add DS:[16384], ax
	jmp R24
R25:
R14:
	mov ax, 0
	mov DS:[392], ax
	mov ax, DS:[392]
	mov DS:[16384], ax
	mov si, 16388
	mov ax, DS:[si]
	mov DS:[394], ax
	mov ax, 1
	mov DS:[396], ax
	mov ax, DS:[394]
	mov bx, DS:[396]
	neg bx
	add ax, bx
	mov DS:[398], ax
R33:
	mov ax, DS:[398]
	cmp DS:[16384], ax
	jg R34
	mov ax, 1
	push ax
	mov si, 16384
	mov ax, DS:[si]
	mov DS:[400], ax
	mov ax, DS:[400]
	add ax, ax
	mov si, 16390
	add si, ax
	mov ax, DS:[si]
	mov DS:[402], ax
	mov ax, DS:[402]
	mov di, 404
	mov cx, 0
	cmp ax, 0
	jge R35
	mov bl, 2Dh
	mov DS:[di], bl
	add di, 1
	neg ax
R35:
	mov bx, 10
R36:
	add cx, 1
	mov dx, 0
	idiv bx
	push dx
	cmp ax, 0
	jne R36
R37:
	pop dx
	add dx, 30h
	mov DS:[di], dl
	add di, 1
	add cx, -1
	cmp cx, 0
	jne R37
	mov dl, 024h
	mov DS:[di], dl
	mov dx, 404
	mov ah, 09h
	int 21h

dseg SEGMENT PUBLIC ; inicio seg. dados
	byte " $" ;const string em 16520
dseg ENDS ;fim seg. dados

	mov si, 16520
	mov DS:[411], si
	mov dx, DS:[411]
	mov ah, 09h
	int 21h
	pop ax
	add DS:[16384], ax
	jmp R33
R34:

;Fim do programa
	mov ah, 4Ch
	int 21h

cseg ENDS ;fim seg. código
END strt ;fim do programa