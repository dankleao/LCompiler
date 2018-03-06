//
// Created by Daniel on 20/02/2018.
//

#ifndef COMPILERL_DEF_H
#define COMPILERL_DEF_H

#include <malloc.h>
#include <windef.h>

#define PUBLIC
#define PRIVATE static
#define VAR_LEN_MAX 255
#define TAB_ASC2_SIZE 128
#define PROGRAM_LEN_MAX 8192
#define SYMBOL_TABLE_SIZE 40 /* Ajustável */

#define CONCAT(a,b) a##b

//Define o tipo string
typedef char* string;

/*
 * Clona uma string
 * @param str string que será clanada
 * @return nova string
 */
PUBLIC string allocString( string str );

/*
 * Verifica se um caracter pertence a cadeia de caracteres.
 * @param str cadeia de caracteres(conjunto de símbolos)
 * @param chr símbolo
 * @return TRUE se a primeira ocorrêcia da caracter aparecer na string, senão retorna FALSE.
 */
PUBLIC BOOL iscontained( char*str, char chr );

#endif //COMPILERL_DEF_H
