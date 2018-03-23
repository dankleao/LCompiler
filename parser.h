//
// Created by Daniel on 22/03/2018.
//

#ifndef LCOMPILER_PARSER_H
#define LCOMPILER_PARSER_H

#include "lex.h"

PRIVATE Symbol* currentSymbol;

#define NULL_TOK (-1)
#define SET_SYMBOL currentSymbol = nextSymbol()
#define GET_SYMBOL currentSymbol
#define GET_TOK (GET_SYMBOL == NULL ? NULL_TOK : GET_SYMBOL->tok )
#define GET_LEXEME GET_SYMBOL->lexeme
#define GET_CLASS GET_SYMBOL->class
#define GET_DATA_TYPE GET_SYMBOL->dataType
#define GET_MEM_ADDR GET_SYMBOL->addr


PRIVATE inline void matchTok( int tokExpected );

PRIVATE void program();
PRIVATE void declaration();
PRIVATE void vars();
PRIVATE void cmdBlock();
PRIVATE void cmdIf();
PRIVATE void cmdFor();
PRIVATE void cmdBody();
PRIVATE void expression();
PRIVATE void term();
PRIVATE void factor();
PRIVATE void element();

#endif //LCOMPILER_PARSER_H
