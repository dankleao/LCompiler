//
// Created by Daniel on 06/04/2018.
//

#ifndef LCOMPILER_CONFIG_H
#define LCOMPILER_CONFIG_H

/*
 * Valores constantes para manipulação do analisador léxico, parser e tradutor
 */

//Lex values
#define VAR_LEN_MAX 32
#define ARRAY_SIZE_MAX 4096
#define TAB_ASC2_SIZE 128
#define PROGRAM_LEN_MAX 8192
#define SYMBOL_TABLE_SIZE 40

//Sintax values
#define INTEGER_MIN_VALUE (-32768)
#define INTEGER_MAX_VALUE 32767

//Gen values
#define OUTPUT_BUFFER_MAX INTEGER_MAX_VALUE
#define OUTPUT_INTEGER_SIZE 7 // sinal + 5 digitos + $
#define OUTPUT_CHAR_SIZE 2 //caracter + $
#define INPUT_STRING_SIZE 255
#define INPUT_INTEGER_SIZE 9
#define INPUT_CHAR_SIZE 4


#endif //LCOMPILER_CONFIG_H
