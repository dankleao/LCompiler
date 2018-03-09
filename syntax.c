//
// Created by Daniel on 07/03/2018.
//

#include "syntax.h"

PRIVATE BOOL joinTok( LexReg* lexReg ){
    return FALSE;
}

int main( int argc, char* argv[] ){

    //inicializa o analisador lex
    startLex(argv[1]);

    LexReg* lexReg;

    do{

        lexReg = nextTok();
        printLexReg(lexReg);

    }while ( lexReg != NULL );

    return 0;
}