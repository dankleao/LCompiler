//
// Created by Daniel on 20/02/2018.
//

#ifndef COMPILERL_DEF_H
#define COMPILERL_DEF_H

<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <windef.h>
#include <string.h>
#include <ctype.h>

/*
 * Define o escopo das funções definidas no projeto
 */

#define PUBLIC
#define PRIVATE static

/*
 * Define valores de parâmetros para funcionalidades do compilador
 *
 */

#define VAR_LEN_MAX 255
#define TAB_ASC2_SIZE 128
#define PROGRAM_LEN_MAX 8192
#define SYMBOL_TABLE_SIZE 40
=======
#include <malloc.h>
#include <windef.h>

#define PUBLIC
#define PRIVATE static
#define VAR_LEN_MAX 255
#define TAB_ASC2_SIZE 128
#define PROGRAM_LEN_MAX 8192
#define SYMBOL_TABLE_SIZE 40 /* Ajustável */
>>>>>>> master

#define CONCAT(a,b) a##b

//Define o tipo string
typedef char* string;

/*
 * Clona uma string
 * @param str string que será clanada
 * @return nova string
 */
<<<<<<< HEAD
PUBLIC string strAlloc( string str );
=======
PUBLIC string allocString( string str );
>>>>>>> master

/*
 * Verifica se um caracter pertence a cadeia de caracteres.
 * @param str cadeia de caracteres(conjunto de símbolos)
 * @param chr símbolo
 * @return TRUE se a primeira ocorrêcia da caracter aparecer na string, senão retorna FALSE.
 */
<<<<<<< HEAD
PUBLIC BOOL strChr( char*str, char chr );
=======
PUBLIC BOOL iscontained( char*str, char chr );
>>>>>>> master

#endif //COMPILERL_DEF_H
