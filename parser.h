//
// Created by Daniel on 22/03/2018.
//

#ifndef LCOMPILER_PARSER_H
#define LCOMPILER_PARSER_H

#include "lex.h"


#define NULL_TOK (-1)

PRIVATE Symbol* currentSymbol;

PRIVATE inline string getLexeme();
PRIVATE inline int getTok();

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
PRIVATE void e();

#endif //LCOMPILER_PARSER_H
