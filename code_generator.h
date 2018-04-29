//
// Created by Daniel on 25/04/2018.
//

#ifndef LCOMPILER_CODE_GENERATOR_H
#define LCOMPILER_CODE_GENERATOR_H

#include <stdio.h>
#include "def.h"
#include "error.h"
#include "config.h"
#include "symbol_table.h"


//Endereço da posição inicial de memória do programa
PRIVATE int memStartPos = 16384;

//Buffer que armazena as sequencias de instruções traduzidas pelo compilador
PRIVATE struct{

    int index;
    char buffer[PROGRAM_LEN_MAX+PROGRAM_LEN_MAX];

}outputBuffer = {0,"\0"};

/*
 *  Reserva uma area de memory
 */
PUBLIC void memAlloc( Symbol* identifier, int size );

/*
 * Cria um novo rotulo.
 * @return uma string que representa o rotulo. Ex: R1,R2,...,RN
 */
PUBLIC string newLabel();

/*
 * Escreve uma instrução no buffer de saída
 * @param instruction assembler 8086
 */
PUBLIC void writeInstruction(string instruction);

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
