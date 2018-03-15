//
// Created by Daniel on 07/03/2018.
//

#include "syntax.h"

PRIVATE inline LexReg* getLexReg(){
    return ( currLexReg == NULL ? NULL : currLexReg );
}

PRIVATE inline int getTokID(){
    return ( currLexReg == NULL ? -1 : currLexReg->tok->id );
}

PRIVATE inline string getLexeme(){
    return ( currLexReg == NULL ? NULL : currLexReg->tok->lexeme );
}

PRIVATE inline int getTokClass(){
    return ( currLexReg == NULL ? -1 : currLexReg->tokClass );
}

PRIVATE inline void setLexReg( LexReg* lexReg ){
    currLexReg = lexReg;
}

PRIVATE void joinTok( int tokIdExpected ){

    if( getLexReg() == NULL )
        compilerror(ERR_EOF_NOT_EXPECTED,NULL);

    if( getTokID() == tokIdExpected ){
        printTok(getLexReg()->tok);
        setLexReg(nextTok());
        printf("tokId: %d\n",getTokID());
    } else{
        compilerror(ERR_TOK_NOT_EXPECTED,getLexeme());
    }
}

PRIVATE void PROGRAM(){

    setLexReg(nextTok());

    if( getLexReg() == NULL ){
        compilerror(ERR_EMPTY_FILE,NULL);
    }

    DECLARATION();

    while ( getLexReg() != NULL  ){
        CMD_BLOCK();
    }
}

PRIVATE void DECLARATION(){

    do{

        printf("Declaration\n");
        if( getTokID() == TOK_FINAL ){

            printf("Constant\n");
            joinTok(TOK_FINAL);
            joinTok(IDENTIFIER);
            joinTok(TOK_EQ);
            joinTok(CONSTANT);
            joinTok(TOK_SEMICOLON);

        } else if( getTokID() == TOK_INT || getTokID() == TOK_CHAR ){

            printf("Vars\n");
            joinTok(getTokID());
            VARS();
            joinTok(TOK_SEMICOLON);

        } else{
            return;
        }

    }while ( getTokID() == TOK_FINAL || getTokID() == TOK_INT || getTokID() == TOK_CHAR );
}

PRIVATE void VARS(){

    joinTok(IDENTIFIER);

    if( getTokID() == TOK_ASSIGN ){

        printf(" = ");
        joinTok(TOK_ASSIGN);
        joinTok(CONSTANT);

    } else if( getTokID() == TOK_L_BRACE ) {

        printf("[const]\n");
        joinTok(TOK_L_BRACE);
        EXP();
        joinTok(TOK_R_BRACE);
    }

    if( getTokID() == TOK_COMMA ){
        printf(", Vars\n");
        joinTok(TOK_COMMA);
        VARS();
    }
}

PRIVATE void CMD_BLOCK(){

    printf("CMD BLOCK\n");

    if( getTokID() == TOK_IF ){

        printf("Tok if\n");
        joinTok(TOK_IF);
        CMD_IF();

    } else if( getTokID() == TOK_FOR ){

        printf("Tok for\n");
        joinTok(TOK_FOR);
        CMD_FOR();

    } else if( getTokID() ==  TOK_READLN ){

        printf("Tok readln\n");
        joinTok(TOK_READLN);
        joinTok(TOK_L_PAREN);
        joinTok(IDENTIFIER);
        joinTok(TOK_R_PAREN);
        joinTok(TOK_SEMICOLON);

    } else if( getTokID() == TOK_WRITE || getTokID() == TOK_WRITELN ){

        printf("Write or Writeln\n");
        joinTok(getTokID());

        joinTok(TOK_L_PAREN);

        joinTok(CONSTANT);

        while( getTokID() == TOK_COMMA ){
            joinTok(TOK_COMMA);
            joinTok(CONSTANT);
        }

        joinTok(TOK_R_PAREN);
        joinTok(TOK_SEMICOLON);

        printf("end write or writeln\n");

    } else if( getTokID() == IDENTIFIER ){

        joinTok(IDENTIFIER);

         if( getTokID() == TOK_L_BRACE ){
            joinTok(TOK_L_BRACE);
            EXP();
            joinTok(TOK_R_BRACE);
        }

        joinTok(TOK_ASSIGN);

        if( getTokID() == CONSTANT ){
            joinTok(CONSTANT);
        } else if( getTokID() == IDENTIFIER ){
            joinTok(IDENTIFIER);
            joinTok(TOK_L_BRACE);
            EXP();
            joinTok(TOK_R_BRACE);
        }

        joinTok(TOK_SEMICOLON);

    } else{

        compilerror(ERR_LEXEME_NOT_FOUND,getLexeme());
    }
}

PRIVATE void CMD_IF(){

    EXP();
    joinTok(TOK_THEN);
    BLOCK_BODY();

    if( getTokID() == TOK_ELSE ){
        joinTok(TOK_ELSE);
        BLOCK_BODY();
    }

}

PRIVATE void CMD_FOR(){

    joinTok(IDENTIFIER);
    joinTok(TOK_ASSIGN);
    EXP();
    joinTok(TOK_TO);
    EXP();

    if( getTokID() == TOK_STEP ){
        joinTok(TOK_STEP);
        joinTok(CONSTANT);
    }

    joinTok(TOK_DO);

    BLOCK_BODY();

}

PRIVATE void BLOCK_BODY(){

    printf("Block Body\n");
    if( getTokID() == TOK_BEGIN ){

        printf("Begin\n");
        joinTok(TOK_BEGIN);
        if( getTokID() == TOK_SEMICOLON )
            joinTok(TOK_SEMICOLON);
        else{

            do{
                CMD_BLOCK();
            }while (getTokID() != TOK_END );

        }

        joinTok(TOK_END);

        printf("End\n");

    } else  {

        if( getTokID() == TOK_SEMICOLON )
            joinTok(TOK_SEMICOLON);
        else
            CMD_BLOCK();
    }
}

PRIVATE void EXP(){

    EXPS();
    if( getTokID() == TOK_EQ || getTokID() == TOK_NE || getTokID() == TOK_GE || getTokID() == TOK_GT || getTokID() == TOK_LE || getTokID() == TOK_LT ){
        joinTok(getTokID());
        EXPS();
    }
}

PRIVATE void EXPS(){

    if( getTokID() == TOK_PLUS || getTokID() == TOK_MINUS )
        joinTok(getTokID());

    T();

    while ( getTokID() == TOK_PLUS || getTokID() == TOK_MINUS || getTokID() == TOK_OR ){
        joinTok(getTokID());
        T();
    }
}

PRIVATE void T(){

    F();
    while ( getTokID() == TOK_TIMES || getTokID() == TOK_OVER || getTokID() == TOK_MOD || getTokID() == TOK_AND ){
        joinTok(getTokID());
        F();
    }
}

PRIVATE void F(){

    if( getTokID() == TOK_L_PAREN ){

        joinTok(TOK_L_PAREN);
        EXP();
        joinTok(TOK_R_PAREN);

    } else if( getTokID() == TOK_NOT  ){

        joinTok(TOK_NOT);
        F();

    } else if( getTokID() == CONSTANT){

        joinTok(CONSTANT);

    } else if( getTokID() == IDENTIFIER ){

        joinTok(IDENTIFIER);

        if( getTokID() == TOK_L_BRACE ){

            joinTok(TOK_L_BRACE);
            EXP();
            joinTok(TOK_R_BRACE);
        }
    } else{
        //Invalid expression
        compilerror(ERR_INVALID_EXPRESSION,NULL);
    }
}

int main( int argc, char* argv[] ){


    //inicializa o analisador lex
    startLex(argv[1]);

    //inicializa o analisador sintatico
    printf("Program\n");
    PROGRAM();

    return 0;
}