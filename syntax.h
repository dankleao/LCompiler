//
// Created by Daniel on 07/03/2018.
//

#ifndef COMPILERL_SYNTAX_H
#define COMPILERL_SYNTAX_H

#include "lex.h"

extern int lineCounter;

PRIVATE LexReg* currLexReg;

PRIVATE inline LexReg* getLexReg();

PRIVATE inline int getTokID();

PRIVATE inline string getLexeme();

PRIVATE inline int getTokClass();

PRIVATE inline void setLexReg( LexReg* lexReg );

PRIVATE void joinTok( int tokIdExpected );
/*
 * Program -> {declaration}* {cmdBlock}*
 */
PRIVATE void PROGRAM();

/*
 *  declaration -> ( final id = const | ( int | char ) var )
 */
PRIVATE void DECLARATION();

/*
 *  V -> id [ <- ( const | "[" EXP "]" ) ] [ , V ]
 */
PRIVATE void VARS();

PRIVATE void CMD_BLOCK();
PRIVATE void CMD_IF();
PRIVATE void CMD_FOR();
PRIVATE void BLOCK_BODY();
PRIVATE void EXP();
PRIVATE void EXPS();
PRIVATE void T();
PRIVATE void F();

#endif //COMPILERL_SYNTAX_H
