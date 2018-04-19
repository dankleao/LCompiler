//
// Created by Daniel on 06/04/2018.
//

#ifndef LCOMPILER_SYMBOL_TABLE_H
#define LCOMPILER_SYMBOL_TABLE_H

#include "def.h"
#include "hash_table.h"

/*
 *  Tabela de símbolos
 *
 */
PUBLIC HashTable* symbolTable;

/*
 * Tipo class representa as classes de identificadores da linguagem
 */
typedef enum class{
    NULL_CLASS = -1,
    VAR_CLASS,
    CONST_CLASS
}class;

/*
 * Tipo dataType representa os tipos de dados atômicos suportados pela linguagem
 */
typedef enum data_type {
    NULL_DATA_TYPE = -1,
    CHARACTER_DATA_TYPE,
    INTEGER_DATA_TYPE
}data_type;

typedef unsigned int memory_address;

/*
 * Tipo symbol representa uma entidade básica da tabela de símbolo
 */

typedef struct symbol{

    string lexeme;       //lexema(string)
    int tok;             //número do token

    union {

        //Atributos p/ identificadores ou palavras-reservadas
        struct{
            class classId;       //classe de identificador
            data_type dataType;  //tipo de dados
            int arraySize;       //tamanho do array, se 0 então é uma variável escalar
            memory_address memAddress; //endereço de memoria
        };

        //Atributos p/ constantes( numéricas, hexdecimais, string, caracter )
        struct{
            int typeConst;
            int typeSize;
        };

    };

}Symbol;

/*
 * Compara um lexema com uma cadeia de caracteres qualquer
 * @param symbol símbolo que contém o campo lexema
 * @param str cadeia de caracteres.
 * @return TRUE caso a cadeia de caracteres é idêntica ao lexema, senão retorna FALSE
 *
 */
PRIVATE bool compareSymbol( Node* symbol , string str );

/*
 * Insere um símbolo na tabela de símbolos
 * @param symbolTable estrutura que representa a tabela de símbolos
 * @param Tok estrutura que representa o token adicionado
 * @retorn o endereço do símbolo adicionado na tabela de símbolos
 */
PUBLIC Symbol* symbolAdd(Symbol* symbol);

/*
* Aloca um Tok(Token) na memória
* @return NULL caso o token não seja alocado
*/
PUBLIC Symbol* symbolAlloc();

/*
 * Pesquisa um token na tabela de símbolos
 * @param symbolTable estrutura que representa a tabela de símbolos
 * @param lexeme string do token desejado
 * @retorn o endereço do token procurado na tabela de símbolos, caso o token não exista retorna NULL
 */
PUBLIC Symbol* symbolSearch(string lexeme);

#endif //LCOMPILER_SYMBOL_TABLE_H
