//
// Created by Daniel on 25/04/2018.
//

#include "code_generator.h"

PUBLIC void resetTempMemoryRegion(){
    memStart[TEMP_MEMORY_REGION] = 0;
}

PUBLIC void memAlloc( int* memAddress, int size, int region ){
    *memAddress = memStart[region];
    memStart[region] += size;
}

PUBLIC string newLabel(){
    static int i = 0;
    return strcat( strAlloc("R"), int2str(i++) );
}

PUBLIC void writeInstruction(string instruction,int i,...){

    va_list v;

    static string pAuxBuffer = outputBuffer;

    while ( *pAuxBuffer )
        ++pAuxBuffer;

    i += 1;
    va_start(v,i);
    vsprintf(pAuxBuffer,instruction,v);
    va_end(v);

}

PUBLIC void generateCode(string fileName){

    FILE* file = NULL;

    if( (file = fopen(fileName,"w")) == NULL )
        compilerror(ERR_COULD_NOT_CREATE_INTERMEDIATE_CODE_FILE,NULL);

    int i = 0;
    while( outputBuffer[i] ){
        fputc(outputBuffer[i],file);
        ++i;
    }

    fclose(file);
}

PUBLIC void startStackSeg(){
    writeInstruction("sseg SEGMENT STACK ;inicio seg. pilha\n",1);
    writeInstruction("\tbyte 16384 DUP(?)\n",1);
}

PUBLIC void endStackSeg(){
    writeInstruction("sseg ENDS ;fim seg. pilha\n\n",1);
}

PUBLIC void startDataSeg(){
    writeInstruction("dseg SEGMENT PUBLIC ;inicio seg. dados\n",1);
    writeInstruction("\tbyte 16384 DUP(?) ;temporarios\n",1);
}

PUBLIC void endDataSeg(){
    writeInstruction("dseg ENDS ;fim seg. dados\n\n",1);
}

PUBLIC void startCodeSeg(){
    writeInstruction("cseg SEGMENT PUBLIC ;inicio do seg. código\n",1);
    writeInstruction("\tASSUME CS:cseg, DS:dseg\n\n",1);
    writeInstruction("strt: ; inicio do programa\n",1);
    writeInstruction("\tmov ax, dseg\n",1);
    writeInstruction("\tmov ds, ax\n\n",1);
}

PUBLIC void endCodeSeg(){
    writeInstruction("\n;Fim do programa\n",1);
    writeInstruction("\tmov ah, 4Ch\n",1);
    writeInstruction("\tint 21h\n\n",1);
    writeInstruction("cseg ENDS ;fim seg. código\n",1);
    writeInstruction("END strt ;fim do programa\0",1);
}
