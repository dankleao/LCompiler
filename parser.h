//
// Created by Daniel on 07/04/2018.
//

#ifndef LCOMPILER_PARSER_H
#define LCOMPILER_PARSER_H

#include "lex.h"

#define NULL_TOK (-1)

//Variável que armazena o símbolo corrente
PRIVATE Symbol* currentSymbol;

/*
 * Obtém o token do símbolo corrente
 */
PRIVATE inline int getTok();

/*
 * Obtém o lexema do símbolo corrente
 */
PRIVATE inline string getLexeme();

/*
 * Verifica a unicidade dos identificadores.
 */
PRIVATE inline void checkUniqueness(class classId);

/*
 * Verifica se um identificador foi declarado
 */
PRIVATE inline void checkVarDeclaration();

/*
 * Verifica a compatibilidade de classe de identificadores.
 */
PRIVATE inline void checkClassCompatibility();

/*
 * Verifica o intervalo inteiro que uma variável inteira pode armazenar
 */
PRIVATE inline bool withinLimitOfInteger(int value);

/*
 * Casa token
 * @param tokExpected é comparado
 * com o token corrente obtido do analisador léxico
 */
PRIVATE inline void matchTok( int tokExpected );

/*
 * PROGRAM -> { DECL }* {CMD}*
 */
PRIVATE void program();

/*
 * DECL -> final id = [ + | - ] | (int | char) VAR
 */
PRIVATE void decl();

/*
 * VAR -> id [ <- [ + | - ] const | "[" const "]" ] [ , VAR ]
 */
PRIVATE void var();

/*
 * CMD -> CMDIF | CMDFOR | CMDIO | id [ "[" EXP "]" ] <- EXP; | ;
 */
PRIVATE void cmd();

/*
 * CMDIF  -> if EXP then BODY [ else BODY ]
 */
PRIVATE void cmdif();

/*
 * CMDFOR -> for id <- EXP to EXP [ step [ + | - ] const ] do BODY
 */
PRIVATE void cmdfor();

/*
 * CMDIO -> ( readln "(" id [ "[" EXP "]" ] ")" | ( write | writeln ) "(" EXP [ { , EXP }* ] ")" );
 */
PRIVATE void cmdio();

/*
 * BODY -> begin {CMD}* end | CMD
 */
PRIVATE void body();

/*
 * EXP -> TERM [ ( = | < | > | <= | >= | <> ) TERM ]
 */
PRIVATE void expression();

/*
 * TERM -> [ + | - ] FACTOR { ( + | - | or ) FACTOR }
 */
PRIVATE void term();

/*
 * FACTOR -> E { ( * | / | % | and ) E }
 */
PRIVATE void factor();

/*
 * E -> "(" EXP ")" | not E | const | id [ "[" EXP "]" ]
 */
PRIVATE void e();


#endif //LCOMP_PARSER_H
