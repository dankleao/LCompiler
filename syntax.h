//
// Created by Daniel on 07/03/2018.
//

#ifndef COMPILERL_SYNTAX_H
#define COMPILERL_SYNTAX_H

#include "lex.h"

// Registro lexico corrente obtido da tabela de símbolos
PRIVATE LexReg* currLexReg;

/*
 * Funções que manipulam o registro léxico corrente obtido.
 */

/*
 * Obtém o endereço do registro léxico
 * @return endereço do registro léxico caso exista, senão retorna NULL
 */
PRIVATE inline LexReg* getLexReg();

/*
 * Obtém o id do token
 * @return o valor do id do token caso exista, senão retorna -1
 */
PRIVATE inline int getTokID();


/*
 * Obtém o lexema
 * @return uma string que representa o lexema caso exista, senão retorna NULL
 */
PRIVATE inline string getLexeme();

PRIVATE inline int getTokClass();

PRIVATE inline void setLexReg( LexReg* lexReg );

/*
 * Casa token
 */
PRIVATE void matchTok( int tokIdExpected );

/*
 * Funções que representam as produções da gramática da linguagem L
 * A função program é o ponto de partida da gramática
 */

/*
 * Program -> {declaration}* {block}*
 */
PRIVATE void program();

/*
 *  declaration -> ( final id = [ + | - ] const | ( int | char ) vars );
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
 * cmdFor ->  for id <- exp to exp [ step [ + | - ]const ] do body
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
