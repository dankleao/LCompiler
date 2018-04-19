//
// Created by Daniel on 07/04/2018.
//

#ifndef LCOMPILER_PARSER_H
#define LCOMPILER_PARSER_H

#include "lex.h"

#define NULL_TOK (-1)

typedef struct synthesizedAttributes {

    int size;
    data_type type;

}SynthAttr;

//Variável que armazena o símbolo corrente
PRIVATE Symbol* currentSymbol;

/*
 * Configura campos dos atributos sintetizados.
 * @param synthAttr referencia do atributo sintetizado.
 * @param size tamanho do arranjo. Se 0, então variável do tipo escalar senão variável do tipo arranjo.
 * @param type tipo de dados.( INTEGER - inteiro, CHAR - caracter ).
 */
PRIVATE inline void setSynthAttributes(SynthAttr* synthAttr, int size, data_type type );

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
PRIVATE void expression(SynthAttr*);

/*
 * TERM -> [ + | - ] FACTOR { ( + | - | or ) FACTOR }
 */
PRIVATE void term(SynthAttr*);

/*
 * FACTOR -> E { ( * | / | % | and ) E }
 */
PRIVATE void factor(SynthAttr*);

/*
 * E -> "(" EXP ")" | not E | const | id [ "[" EXP "]" ]
 */
PRIVATE void e(SynthAttr*);


#endif //LCOMP_PARSER_H
