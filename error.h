//
// Created by Daniel on 06/04/2018.
//

#ifndef LCOMPILER_ERROR_H
#define LCOMPILER_ERROR_H

#include <stdio.h>
#include "def.h"

#define ERR( errid, errdesc ) errid,

/*
 * Define um lista de erros que podem surgim em um processo de compilação
 */
#define ERR_LIST \
        ERR(ERR_FILE_NOT_FOUND,"arquivo nao encontrado.") \
        ERR(ERR_COULD_NOT_LOAD_PROGRAM,"nao foi possivel carregar o programa fonte.") \
        ERR(ERR_UNRECOGNIZED_SYMBOL,"caracter invalido.") \
        ERR(ERR_LEXEME_NOT_FOUND,"lexema nao identificado.") \
        ERR(ERR_EOF_NOT_EXPECTED,"fim de arquivo nao esperado.") \
        ERR(ERR_BAD_ARGUMENTS,"numero de argumentos invalido. Ex: lc nome_fonte.l nome_executavel.asm ") \
        ERR(ERR_TOK_NOT_EXPECTED,"token nao esperado.") \
        ERR(ERR_IDENTIFIER_ALREADY_DECLARED,"identificador ja declarado.") \
        ERR(ERR_INCOMPATIBLE_TYPES,"tipos incompativeis.") \
        ERR(ERR_ARRAY_SIZE_BOUND_EXCEEDED,"tamanho do vetor excede o maximo permitido.") \
        ERR(ERR_INCOMPATIBLE_CLASS_IDENTIFIER,"classe de identificador incom,pativel.") \
        ERR(ERR_UNDECLARED_IDENTIFIER,"identificador nao declarado.") \
        ERR(ERR_COULD_NOT_CREATE_INTERMEDIATE_CODE_FILE,"nao foi possivel criar o arquivo de codigo intermediario.") \

enum {
#ifdef ERR_LIST
    ERR_LIST
    NUM_OF_ERRORS
#endif
};

#undef ERR

#define ERR(errid,errdesc) errdesc,

//Armazena a lista de erros em uma tabela
PRIVATE string err_list[NUM_OF_ERRORS] = { ERR_LIST };

#undef ERR
#undef ERR_LIST

extern int lineCounter;//conta a posição corrente no código fonte

/*
 *  Exibe uma mensagem de erro formatada
 *  @param err_id numero do erro
 *  @param arg lexema que levou ao erro(opcional, arg = NULL).
 */
PUBLIC void compilerror(int err_id,string arg);


#endif //LCOMPILER_ERROR_H
