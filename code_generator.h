//
// Created by Daniel on 25/04/2018.
//

#ifndef LCOMPILER_CODE_GENERATOR_H
#define LCOMPILER_CODE_GENERATOR_H

#include <stdio.h>
#include "def.h"
#include "error.h"
#include "config.h"

//Buffer que armazena as sequencias de instruções traduzidas pelo compilador
PRIVATE struct{

    int index;
    char buffer[PROGRAM_LEN_MAX+PROGRAM_LEN_MAX];

}outputBuffer = {0,"\0"};

/*
 * Escreve uma instrução no buffer de saída
 * @param instruction assembler 8086
 */
PRIVATE inline void writeInstruction(string instruction);

PUBLIC void asmInstruction( int mnemonics, string value, int flag , string comment);

/*
 * Esvazia o buffer de saída em um arquivo .asm
 * @param fileName nome do arquivo de código intermediário com as instruções assembler
 */
PUBLIC void generateCode(string fileName);

/*
 * Instruções de segmento de pilha
 */
PUBLIC void startStackSeg();
PUBLIC void endStackSeg();

/*
 * Instruções de segmento de dados
 */
PUBLIC void startDataSeg();
PUBLIC void endDataSeg();

/*
 * Instruções de segmento de Código
 */
PUBLIC void startCodeSeg();
PUBLIC void endCodeSeg();


#endif //LCOMPILER_CODE_GENERATOR_H
