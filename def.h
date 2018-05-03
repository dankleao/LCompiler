//
// Created by Daniel on 06/04/2018.
//

#ifndef LCOMPILER_DEF_H
#define LCOMPILER_DEF_H

#include <stdlib.h>
#include <string.h>

#define PUBLIC
#define PRIVATE static

//Define o tipo string
typedef char* string;

//Define o tipo bool
typedef enum boolean{
    FALSE = 0,
    TRUE
}bool;

/*
 * Converte um inteiro em sua representação string
 * @param value inteiro que será convertido
 * @return uma representação string do valor inteiro armazenado no parametro
 */

PUBLIC string int2str(int value);


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

/*
 * Compara leftStr com rightStr
 * @param leftStr string A
 * @param rightStr string B
 * @return TRUE se string A for igual string B, senão FALSE
 */
PUBLIC bool compareStrings(string leftStr, string rightStr);

/*
 * Converte um literal hexadecimal representado
 * por uma string em um valor decimal inteiro
 * @param hex literal string hexadecimal
 * @return um valor decimal(inteiro) equivalente ao valor hexadecimal(string)
 */
PUBLIC int hex2int(string hex);

/*
 * Injeta uma substring code na string source na posição pos.
 * Ex: source: "smile", code = "@!", pos: 2 => new source: "sm@!ile"
 * @param source string afetada
 * @param code string inserido na string source
 * @param pos code inserido a partir da posição definida em pos
 * @return string source acrescida da substring code
 */
PUBLIC string strInject( string source, string code, int pos );

/*
 * Retorna uma nova string formada pela substring de str.
 */
PUBLIC string substr(string str, int beginIndex, int endIndex);

#endif //LCOMPILER_DEF_H
