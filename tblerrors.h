//
// Created by Admin on 04/03/2018.
//

#include <stdio.h>
#include "def.h"

#ifndef COMPILERL_TBLERRORS_H
#define COMPILERL_TBLERRORS_H

PUBLIC void error( string msg, string arg ){
    if( arg == NULL )
        printf("\n%d: %s\n",clin,msg);
    else
        printf("\n%d: %s [%s]\n",clin,msg,arg);
    exit(1);
}

#define ERROR_VAR_LEN error("tamanho do identificador excede o limite [1-255].",NULL)
#define ERROR_UNRECOGNIZED_SYMBOL error("caractere invalido.",NULL)
#define ERROR_LEXEME_NOT_FOUND(lexeme) error("lexema nao identificado.",lexeme)
#define ERROR_INVALID_HEX_CONST(lexeme) error("constante hexdecimal invalida.",lexeme)
#define ERROR_EOF_NOT_EXPECTED error("fim de arquivo não esperado.",NULL);

#endif //COMPILERL_TBLERRORS_H
