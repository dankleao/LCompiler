//
// Created by Daniel on 25/04/2018.
//

#ifndef LCOMPILER_CODE_GENERATOR_H
#define LCOMPILER_CODE_GENERATOR_H

#include <stdio.h>
#include <stdarg.h>
#include "def.h"
#include "error.h"
#include "config.h"
#include "symbol_table.h"

#define STANDARD_MEMORY_REGION 0
#define TEMP_MEMORY_REGION 1
#define BYTE 1
#define SWORD 2

PRIVATE int memStart [2] = { 16384, 0 };

//Buffer que armazena as sequencias de instruções traduzidas pelo compilador
PRIVATE char outputBuffer[PROGRAM_LEN_MAX+PROGRAM_LEN_MAX] = {'\0'};

/*
 * Reseta ponteiro dos temporários
 */
PUBLIC void resetTempMemRegion();

/*
 *  Reserva uma area de memory
 */
PUBLIC void memAlloc( int* memAddress, int size, int region );

/*
 * Cria um novo rotulo.
 * @return uma string que representa o rotulo. Ex: R1,R2,...,RN
 */
PUBLIC string newLabel();

/*
 * Escreve uma instrução no buffer de saída
 * @param instruction assembler 8086
 */
PUBLIC void writeInstruction(string instruction,int i,...);

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
