//
// Created by Daniel on 07/03/2018.
//

#ifndef COMPILERL_SYNTAX_H
#define COMPILERL_SYNTAX_H

#include "lex.h"

PRIVATE LexReg* currLexReg;

PRIVATE inline LexReg* getLexReg();

PRIVATE inline int getTokID();

PRIVATE inline string getLexeme();

PRIVATE inline int getTokClass();

PRIVATE inline void setLexReg( LexReg* lexReg );

/*
 * Casa token
 */
PRIVATE void matchTok( int tokIdExpected );

/*
 * Program -> {declaration}* {block}*
 */
PRIVATE void program();

/*
 *  declaration -> ( final id = [+-] const | ( int | char ) vars );
 */
PRIVATE void declaration();

/*
 *  vars -> id [ <- exp | "[" exp "]" ) ] [ , vars ]
 */
PRIVATE void vars();

/*
 * block -> cmdIf | cmdFor | read(id); | write( exp [ {, exp} ] ); | writeln( exp [ {, exp} ] ); | id [ "[" exp "]" ] <- exp )
 */
PRIVATE void block();

/*
 * cmdIf -> if exp then body [ else body ]
 */
PRIVATE void cmdIf();

/*
 * cmdFor ->  for id <- exp to exp [ step const ] do body
 */
PRIVATE void cmdFor();

/*
 *  body -> ( begin( {block}* | ; ) end ) | ( block | ; )
 */
PRIVATE void body();

/*
 * expression -> term[ ( < | > | <= | >= | <> ) term ]
 */
PRIVATE void expression();

/*
 * term -> [+-] factor { (+ | - | or ) factor }
 */
PRIVATE void term();

/*
 * factor -> element { ( * | / | % | and ) element }
 */
PRIVATE void factor();

/*
 * element -> "(" expression ")" | not f | const | id [ "[" expression "]" ]
 */
PRIVATE void element();

#endif //COMPILERL_SYNTAX_H
