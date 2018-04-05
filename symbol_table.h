//
// Created by Daniel on 22/03/2018.
//

#ifndef LCOMPILER_SYMBOL_TABLE_H
#define LCOMPILER_SYMBOL_TABLE_H

#include "def.h"
#include "hash_table.h"

PUBLIC HashTable* symbolTable;

typedef enum class{
    NULL_CLASS = -1,
    VAR_CLASS,
    CONST_CLASS
}class;

typedef enum data_type {
    NULL_DATA_TYPE = -1,
    BOOLEAN_DATA_TYPE,
    CHARACTER_DATA_TYPE,
    INTEGER_DATA_TYPE
}dataType;

typedef unsigned int memoryAddress;

typedef struct symbol{
    string lexeme;
    int tok;
    union{
        struct{
            class classId;
            dataType dataType;
            int arraySize;
            memoryAddress addr;
        };
        int typeConst;
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
