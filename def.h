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

/*
 * Verifica se arquivo existe
 * @param fileName nome completamente qualificado do arquivo fonte
 * @return TRUE caso o arquivo exista, senão retorna FALSE
 */

PUBLIC bool fileExists(string fileName);

/*
 * Avalia a extensão do arquivo de código fonte que obrigatoriamente tem que terminar com .l
 * @param fileName nome completamente qualificado do arquivo fonte
 * @param ext extensão permitida do arquivo
 * @return TRUE caso a extensão seja válida, senão retorna FALSE
 *
 */
PUBLIC bool evalFileExt(string fileName,string ext);


#endif //LCOMPILER_DEF_H
