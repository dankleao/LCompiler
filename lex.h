//
// Created by Daniel on 28/02/2018.
//

#ifndef COMPILERL_LEX_H
#define COMPILERL_LEX_H

#include <stdio.h>
#include <stdlib.h>
#include <windef.h>
#include <string.h>
#include <ctype.h>

#include "def.h"

/* Definição dos tokens */

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
        TOK_SUM, \
        TOK_MINUS, \
        TOK_MULT, \
        TOK_DIV, \
        TOK_MOD, \
        TOK_SEMICOLON, \
        TOK_COMMA, \
        TOK_L_PAREN, \
        TOK_R_PAREN, \
        TOK_L_BRACE, \
        TOK_R_BRACE \

/* Enumeração dos tokens */
enum {
#ifdef TOKS
    TOKS,
    NUM_OF_TOKS
#endif
#undef TOKS
};

/* Vars globais */

PUBLIC string buffp;                          //aponta para o inicio da area de carga do programa fonte
PUBLIC string prog;                           //aponta para posição corrente do programa fonte
PUBLIC char buffchr[VAR_LEN_MAX+1] = {'\0'};  //armazena o lexema corrente(buffer lexema)
PUBLIC int buffindex;                         //indice do buffer lxm
PUBLIC int clin = 1;                          //contador de linhas do programa

#ifndef COMPILERL_HASH_TABLE_H
#include "hash_table.h"
#undef COMPILERL_DEF_H
#endif

/* Tabela de símbolos */
PUBLIC HashTable* symbolTable;

/* Definição das macros que manipulam a tabela de símbolos */
//#define addTok(tok) ((Tok*) ((Node*) addHashTable(symbolTable,getKey(tok->lexeme),tok))->obj);
//#define searchTok(lexeme) (Tok*) (((Node*) searchHashTable(symbolTable,lexeme,tokcmp))->obj);

/* Tok representa um token com seus atributos lexeme( lexema ) e tok_id( identificador numérico ) o qual será salvo na tabela de símbolos */

PUBLIC typedef struct tok{

    string lexeme;
    int tokId;

}Tok;

/* LexReg representa o registro léxico que será entregue ao análisador sintático. */

PUBLIC typedef struct lex_reg{

    Tok* tok;
    int pos;

}LexReg;


/*
 * Insere um token na tabela de símbolos
 * @param symbolTable estrutura que representa a tabela de símbolos
 * @param Tok estrutura que representa o token adicionado
 * @retorn o endereço do token adicionado na tabela de símbolos
 */

PRIVATE inline Tok* addTok( Tok* tok );

/*
 * Pesquisa um token na tabela de símbolos
 * @param symbolTable estrutura que representa a tabela de símbolos
 * @param lexeme string do token desejado
 * @retorn o endereço do token procurado na tabela de símbolos, caso o token não exista retorna NULL
 */

PRIVATE inline Tok* searchTok( string lexeme );

/*
 * Aloca um Tok(Token) na memória
 * @return NULL caso o token não seja alocado
 */

PRIVATE inline Tok* allocTok();

/*
 * Aloca um registro léxico na memoria.
 * @return NULL caso o registro não seja alocado.
 */

PRIVATE inline LexReg* allocLexReg();

/*
 * Avalia a extensão do arquivo de código fonte que obrigatoriamente tem que terminar com .l
 * @param file_name nome completamente qualificado do arquivo fonte
 * @return TRUE caso a extensão seja válida, senão retorna FALSE
 *
 */
PRIVATE BOOL evalFileExt(string fileName);

/*
 * Preenche o buffer que armazena os lexemas
 * @param chr caracter para adicionar no buffer
 */

PRIVATE void fillBuff(char chr);

/*
 * Delimita o fim do buffer
 */
PRIVATE inline void closeBuff();

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
PRIVATE BOOL loadProgram( string buff, string fileName );

/*
 * Configura os campos que compõe um registro léxico.
 * @param reg registro léxico alocado
 * @param tok token
 * @param tok_types tipo de token
 * @param pos posição(linha) do token no código fonte
 */
PRIVATE void setLexReg(LexReg* reg, Tok tok , int tok_types, int pos);

/*
 * Configura os campos que compõe um token
 * @param tok estrutura abstrata que representa um token
 * @param lexeme cadeia de caracteres(atributo)
 * @param tokId identificador(int) do token(atributo)
 */
PRIVATE void setTok(Tok* tok, string lexeme, int tokId );


/* Categorias dos tokens enumerados  */

enum tok_types {IDENTIFIER = NUM_OF_TOKS ,CHARACTER,HEX,STRING,NUMBER,KEYWORD};

/* Conjunto de estados do AFD
 * Q0 estado inicial
 * Q1 - Q8 estados intermediários
 * F estado final
 * DFA_ERROR estado de erro
 * */
enum state { Q0 = 0, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, Q11, Q12, Q13, Q14, Q15, Q16,Q17, F, END };

/*
 * Automato finito determinista para reconhecer os lexemas válidos da linguagem com base
 * em determinadas regras definidas.
 * @return retorna um registro léxico do token reconhecido para o análisador sintático
 */
PUBLIC LexReg* nextTok();

/*
 * Inicia a execução do analisador léxico passando como argumento de linha de
 * comando o nome do arquivo do código fonte com extensão ".l"
 * @param argc número de argumentos
 * @param argv string(s) representam os argumentos
 */
PUBLIC int main( int argc, char* argv[] );

/*
 * Compara um lexema com uma cadeia de caracteres qualquer
 * @reg tok token(lexema)
 * @str cadeia de caracteres.
 * @return TRUE caso a cadeia de caracteres é idêntica ao lexema, senão retorna FALSE
 *
 */
PRIVATE inline BOOL tokcmp( Node* tok , string str );

/*
 * Metodos auxiliares para depurar o código
 */

PRIVATE string strtoktype[] = { "IDENTIFIER","LITERAL","HEX","STRING","NUMBER","KEYWORD","DELIMITER","BOOL_OP","REL_OP","ARITH_OP" };

PUBLIC void printTok(Tok* tok);

PUBLIC void printLexReg(LexReg* lexReg);

PUBLIC void printSymTab();


#endif //COMPILERL_LEX_H
