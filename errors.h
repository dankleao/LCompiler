//
// Created by Daniel on 13/03/2018.
//

#ifndef COMPILERL_LEXCPT_H
#define COMPILERL_LEXCPT_H

#include "def.h"

#define ERR( errid, errdesc ) errid,

#define ERR_LIST \
        ERR(ERR_VAR_LEN,"tamanho do identificador excede o limite permitido.") \
        ERR(ERR_UNRECOGNIZED_SYMBOL,"caracter não reconhecido.") \
        ERR(ERR_LEXEME_NOT_FOUND,"lexema nao identificado.") \
        ERR(ERR_TOK_NOT_EXPECTED,"token nao esperado.") \
        ERR(ERR_INVALID_HEX_CONST,"constante hexadecimal invalida.") \
        ERR(ERR_EOF_NOT_EXPECTED,"fim de arquivo nao esperado.") \
        ERR(ERR_EMPTY_FILE,"arquivo vazio.") \
        ERR(ERR_INVALID_DECL,"declaração invalida.") \
        ERR(ERR_INVALID_CMD,"comando invalido.") \
        ERR(ERR_FILE_NOT_FOUND,"arquivo nao encontrado.") \
        ERR(ERR_COULD_NOT_LOAD_PROGRAM,"nao foi possivel carregar o programa fonte.") \
        ERR(ERR_INVALID_EXPRESSION,"expressao invalida.") \
        ERR(ERR_INVALID_CHARACTER,"literal caracter nao terminado.") \
        ERR(ERR_UNTERMINETED_STRING_LITERAL,"literal string nao terminado.")

enum {
#ifdef ERR_LIST
    ERR_LIST
    NUM_OF_ERRORS
#endif
};

#undef ERR

#define ERR(errid,errdesc) errdesc,

PRIVATE string err_list[NUM_OF_ERRORS] = { ERR_LIST };

#undef ERR
#undef ERR_LIST

extern int lineCounter;

PUBLIC void compilerror(int err_id,string arg);

#endif //COMPILERL_LEXCPT_H
