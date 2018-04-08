//
// Created by Daniel on 06/04/2018.
//

#ifndef LCOMPILER_DEF_H
#define LCOMPILER_DEF_H

#include <stdlib.h>
#include <string.h>

#define PUBLIC
#define PRIVATE static
#define CONCAT(a,b) a##b

//Define o tipo string
typedef char* string;

//Define o tipo bool
typedef enum boolean{
    FALSE = 0,
    TRUE
}bool;

/*
 * Clona uma string
 * @param str string que será clonada
 * @return nova string
 */
PUBLIC string strAlloc( string str );

/*
 * Verifica se um caracter pertence a cadeia de caracteres.
 * @param str cadeia de caracteres(conjunto de símbolos)
 * @param chr símbolo
 * @return TRUE se a primeira ocorrêcia da caracter aparecer na string, senão retorna FALSE.
 */
PUBLIC bool strChr( string str, char chr );

#endif //LCOMPILER_DEF_H
