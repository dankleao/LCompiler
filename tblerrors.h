//
// Created by Admin on 04/03/2018.
//

#ifndef COMPILERL_TBLERRORS_H
#define COMPILERL_TBLERRORS_H

#include "def.h"

PUBLIC void error( string msg, string arg ){
    if( arg == NULL )
        printf("\n%d: %s\n",lineCounter,msg);
    else
        printf("\n%d: %s [%s]\n",lineCounter,msg,arg);
    exit(1);
}

#define ERROR_DEF( errid, errdesc ) errid,

#define ERRORS_LIST \
        ERROR_DEF(ERROR_VAR_LEN,"tamanho do identificador excedo o limite [1-255]."); \
        ERROR_DEF(ERROR_UNRECOGNIZED_SYMBOL,"caracter não reconhecido."); \
        ERROR_DEF(ERROR_LEXEME_NOT_FOUND,"lexema não identificado.") \
        ERROR_DEF(ERROR_INVALID_HEX_CONST,"constante hexadecimal invalida.") \
        ERROR_DEF(ERROR_EOF_NOT_EXPECTED,"fim de arquivo nao esperado.");

enum {

    ERROR_LIST,
    NUM_OF_ERRROS

};

#define ERROR_VAR_LEN error("tamanho do identificador excede o limite [1-255].",NULL)
#define ERROR_UNRECOGNIZED_SYMBOL error("caractere invalido.",NULL)
#define ERROR_LEXEME_NOT_FOUND(lexeme) error("lexema nao identificado.",lexeme)
#define ERROR_INVALID_HEX_CONST(lexeme) error("constante hexdecimal invalida.",lexeme)
#define ERROR_EOF_NOT_EXPECTED error("fim de arquivo não esperado.",NULL);

#endif //COMPILERL_TBLERRORS_H
