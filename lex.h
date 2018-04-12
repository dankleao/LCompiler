//
// Created by Daniel on 06/04/2018.
//

#ifndef LCOMPILER_LEX_H
#define LCOMPILER_LEX_H

/* Definição dos tokens */
#include <ctype.h>
#include <io.h>
#include "def.h"
#include "error.h"
#include "config.h"
#include "symbol_table.h"

#define TOKS \
        TOK_FINAL, \
        TOK_INT, \
        TOK_CHAR, \
        TOK_FOR, \
        TOK_IF, \
        TOK_ELSE, \
        TOK_DO, \
        TOK_AND, \
        TOK_OR, \
        TOK_NOT, \
        TOK_TO, \
        TOK_BEGIN, \
        TOK_END, \
        TOK_THEN, \
        TOK_STEP, \
        TOK_READLN, \
        TOK_WRITE, \
        TOK_WRITELN, \
        TOK_ASSIGN, \
        TOK_EQ, \
        TOK_NE, \
        TOK_GT, \
        TOK_LT, \
        TOK_GE, \
        TOK_LE, \
        TOK_PLUS, \
        TOK_MINUS, \
        TOK_TIMES, \
        TOK_OVER, \
        TOK_MOD, \
        TOK_SEMICOLON, \
        TOK_COMMA, \
        TOK_L_PAREN, \
        TOK_R_PAREN, \
        TOK_L_BRACE, \
        TOK_R_BRACE

#define OTHERS \
        TOK_IDENTIFIER, \
        TOK_CONSTANT, \
        TOK_OTHER, \
        CHARACTER_CONST, \
        HEX_CONST, \
        NUMBER_CONST, \
        STRING_CONST, \

/* Enumeração dos tokens */
enum {
#ifdef TOKS
    TOKS,
    NUM_OF_TOKS,
    OTHERS
#endif
#undef OTHERS
#undef TOKS
};

/*
 *  Variáveis que auxiliam na varredura do código-fonte
 */
PRIVATE string prog;                            //aponta para posição corrente do programa fonte
PRIVATE string lexemeBegin;                     //aponta para a primeira posição de uma novo lexema
PUBLIC int lineCounter;                         //contador de linhas do programa

/* Conjunto de estados do AFD
 * Q0 estado inicial
 * Q1 - Q17 estados intermediários
 * F estado final
 * END estado auxilar para finalizar a varredura
 *
 */
PUBLIC enum state { Q0 = 0, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16, Q17, F, END };

/*
 * Automato finito determinista para reconhecer os lexemas válidos da linguagem com base
 * em determinadas regras definidas.
 * @return retorna o símbolo reconhecido para o análisador sintático
 */
PUBLIC Symbol* nextSymbol();

/*
 * Inicia a execução do analisador léxico passando como argumento de linha de
 * comando o nome do arquivo do código fonte com extensão ".l"
 * @param argc número de argumentos
 * @param argv string(s) representam os argumentos
 */
PUBLIC bool startLex( string fileName );

/*
 * Obtém o lexema corrente
 * @return lexema apontado por lexemeBegin
 */
PRIVATE string buildLexeme();

/*
 * Avalia a extensão do arquivo de código fonte que obrigatoriamente tem que terminar com .l
 * @param fileName nome completamente qualificado do arquivo fonte
 * @return TRUE caso a extensão seja válida, senão retorna FALSE
 *
 */
PRIVATE bool evalFileExt(string fileName);

/*
 * Verifica se arquivo existe
 * @param fileName nome completamente qualificado do arquivo fonte
 * @return TRUE caso o arquivo exista, senão retorna FALSE
 */

PRIVATE inline bool fileExists(string fileName);

/*
 * Ignora espaços em branco
 *
 * */
PRIVATE inline void ignoreWs();

/*
 * Carrega o programa para memória principal.
 * Tamanho padrão do buffer é de 8192 Bytes.
 * @param buff aponta para o primeiro endereço do buffer alocado para armazenar o código fonte
 * @param fileName nome da arquivo
 */
PRIVATE bool loadProgram( string buff, string fileName );

/*
 * Imprime um símbolo
 * @para symbol símbolo que será impresso
 */
PUBLIC void printSymbol(Symbol* symbol);

/*
 * Imprime a tabela de símbolos
 *
 */
PUBLIC void printSymbolTable();

#endif //LCOMPILER_LEX_H
