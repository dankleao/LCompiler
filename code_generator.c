//
// Created by Daniel on 25/04/2018.
//

#include "code_generator.h"

PRIVATE inline void writeInstruction(string instruction){

    int instructionLength = strlen(instruction);

    int i = 0;
    while ( i < instructionLength ){
        outputBuffer.buffer[outputBuffer.index] = instruction[i];
        ++outputBuffer.index;
        ++i;
    }
}

PUBLIC void generateCode(string fileName){

    FILE* file = NULL;

    if( (file = fopen(fileName,"w")) == NULL )
        compilerror(ERR_COULD_NOT_CREATE_INTERMEDIATE_CODE_FILE,NULL);

    int i = 0;
    while( outputBuffer.buffer[i] ){
        fputc(outputBuffer.buffer[i],file);
        ++i;
    }

    fclose(file);

    //printf("code successfully generated!\n");
}

PUBLIC void startStackSeg(){
    writeInstruction("sseg SEGMENT STACK ;inicio seg. pilha\n");
    writeInstruction("byte 16384 DUP(?)\n");
}

PUBLIC void endStackSeg(){
    writeInstruction("sseg ENDS ;fim seg. pilha\n");
}

PUBLIC void startDataSeg(){
    writeInstruction("dseg SEGMENT PUBLIC ;inicio seg. dados\n");
    writeInstruction("byte 16384 DUP(?) ;temporarios\n");
}

PUBLIC void endDataSeg(){
    writeInstruction("dseg ENDS\n");
}

PUBLIC void startCodeSeg(){
    writeInstruction("cseg SEGMENT PUBLIC ;inicio do seg. código\n");
    writeInstruction("ASSUME CS:cseg, DS:dseg\n");
    writeInstruction("strt: ; inicio do programa\n");
    writeInstruction("mov ax, dseg\n");
    writeInstruction("mov ds, ax\n");
}

PUBLIC void endCodeSeg(){
    writeInstruction("cseg ENDS ;fim seg. código\n");
    writeInstruction("END strt\0");
}
