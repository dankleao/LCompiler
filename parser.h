//
// Created by Daniel on 07/04/2018.
//

#ifndef LCOMPILER_PARSER_H
#define LCOMPILER_PARSER_H

#include "lex.h"
#include "code_generator.h"

//Variável que armazena o símbolo corrente
PRIVATE Symbol* currentSymbol;

//Buffer que armazena uma instrução ASM
PRIVATE char instructionBuffer[128] = {"\0"};

/*
 * Verifica a unicidade dos identificadores.
 * @param classe de identificador
 */
PRIVATE inline void checkUniqueness(class classId);

/*
 * Verifica se um identificador foi declarado
 */
PRIVATE inline void checkVarDeclaration();

/*
 * Verifica a compatibilidade de classe de identificadores.
 * @param symbol símbolo identificador
 */
PRIVATE inline void checkClassCompatibility(Symbol* symbol);

/*
 * Verifica o intervalo inteiro que uma variável inteira pode armazenar
 * @return a constante inteira
 */
PRIVATE inline int withinLimitOfInteger(int signal);

/*
 * Verifica o tamanho máximo do array
 * @return o tamanho do array
 */
PRIVATE inline int withinArraySizeBounds();

/*
 * Verifica se tipos de dados são iguais, caso não seja
 * interrompe a execução e emite uma messagem de erro
 * @param dt1 tipos de dados fonte
 * @param dt2 tipos de dados alvo
 */
PRIVATE inline void checkDataTypes( data_type dt1, data_type dt2  );

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
 * DECL -> [ ( final id = [ + | - ] const | (int | char) VAR ) ; ]
 */
PRIVATE void decl();

/*
 * VAR -> id [ <- [ + | - ] const | "[" const "]" ] [ , VAR ]
 */
PRIVATE void var(data_type);

/*
 * CMD -> [ CMDIF | CMDFOR | CMDIO | id [ "[" EXP "]" ] [ <- EXP ] ; | ; ]
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
PRIVATE void expression(int*,data_type*,int*);

/*
 * TERM -> [ + | - ] FACTOR { ( + | - | or ) FACTOR }
 */
PRIVATE void term(int*,data_type*,int*);

/*
 * FACTOR -> E { ( * | / | % | and ) E }
 */
PRIVATE void factor(int*,data_type*,int*);

/*
 * E -> "(" EXP ")" | not E | const | id [ "[" EXP "]" ]
 */
PRIVATE void e(int*,data_type*,int*);


#endif //LCOMP_PARSER_H
