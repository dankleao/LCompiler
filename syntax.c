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

PRIVATE void matchTok( int tokIdExpected ){

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

PRIVATE void program(){

    setLexReg(nextTok());

    if( getLexReg() == NULL ){
        compilerror(ERR_EMPTY_FILE,NULL);
    }

    declaration();

    while ( getLexReg() != NULL  ){
        block();
    }
}

PRIVATE void declaration(){

    do{

        printf("Declaration\n");
        if( getTokID() == TOK_FINAL ){

            printf("Constant\n");
            matchTok(TOK_FINAL);
            matchTok(IDENTIFIER);
            matchTok(TOK_EQ);

            if( getTokID() == TOK_PLUS || getTokID() == TOK_MINUS )
                matchTok(getTokID());

            matchTok(CONSTANT);
            matchTok(TOK_SEMICOLON);

        } else if( getTokID() == TOK_INT || getTokID() == TOK_CHAR ){

            printf("Vars\n");
            matchTok(getTokID());
            vars();
            matchTok(TOK_SEMICOLON);

        } else{
            return;
        }

    }while ( getTokID() == TOK_FINAL || getTokID() == TOK_INT || getTokID() == TOK_CHAR );
}

PRIVATE void vars(){

    matchTok(IDENTIFIER);

    if( getTokID() == TOK_ASSIGN ){

        printf(" <- ");
        matchTok(TOK_ASSIGN);
        expression();

    } else if( getTokID() == TOK_L_BRACE ) {

        printf("[const]\n");
        matchTok(TOK_L_BRACE);
        expression();
        matchTok(TOK_R_BRACE);
    }

    if( getTokID() == TOK_COMMA ){
        printf(", Vars\n");
        matchTok(TOK_COMMA);
        vars();
    }
}

PRIVATE void block(){

    printf("CMD BLOCK\n");

    if( getTokID() == TOK_IF ){

        printf("Tok if\n");
        matchTok(TOK_IF);
        cmdIf();

    } else if( getTokID() == TOK_FOR ){

        printf("Tok for\n");
        matchTok(TOK_FOR);
        cmdFor();

    } else if( getTokID() ==  TOK_READLN ){

        printf("Tok readln\n");
        matchTok(TOK_READLN);
        matchTok(TOK_L_PAREN);
        matchTok(IDENTIFIER);
        matchTok(TOK_R_PAREN);
        matchTok(TOK_SEMICOLON);

    } else if( getTokID() == TOK_WRITE || getTokID() == TOK_WRITELN ){

        printf("Write or Writeln\n");
        matchTok(getTokID());

        matchTok(TOK_L_PAREN);

        expression();

        //matchTok(CONSTANT);

        while( getTokID() == TOK_COMMA ){
            matchTok(TOK_COMMA);
            expression();
        }

        matchTok(TOK_R_PAREN);
        matchTok(TOK_SEMICOLON);

        printf("end write or writeln\n");

    } else if( getTokID() == IDENTIFIER ){

        matchTok(IDENTIFIER);

         if( getTokID() == TOK_L_BRACE ){
             matchTok(TOK_L_BRACE);
             expression();
             matchTok(TOK_R_BRACE);
        }

        matchTok(TOK_ASSIGN);

        expression();

        matchTok(TOK_SEMICOLON);

    } else{

        compilerror(ERR_LEXEME_NOT_FOUND,getLexeme());
    }
}

PRIVATE void cmdIf(){

    expression();
    matchTok(TOK_THEN);
    body();

    if( getTokID() == TOK_ELSE ){
        matchTok(TOK_ELSE);
        body();
    }
}

PRIVATE void cmdFor(){

    matchTok(IDENTIFIER);
    matchTok(TOK_ASSIGN);
    expression();
    matchTok(TOK_TO);
    expression();

    if( getTokID() == TOK_STEP ){
        matchTok(TOK_STEP);
        matchTok(CONSTANT);
    }

    matchTok(TOK_DO);

    body();

}

PRIVATE void body(){

    printf("Body\n");
    if( getTokID() == TOK_BEGIN ){

        printf("Begin\n");
        matchTok(TOK_BEGIN);
        if( getTokID() == TOK_SEMICOLON )
            matchTok(TOK_SEMICOLON);
        else{

            do{
                block();
            }while (getTokID() != TOK_END );

        }

        matchTok(TOK_END);

        printf("End\n");

    } else  {

        if( getTokID() == TOK_SEMICOLON )
            matchTok(TOK_SEMICOLON);
        else
            block();
    }
}

PRIVATE void expression(){

    term();
    if( getTokID() == TOK_EQ || getTokID() == TOK_NE || getTokID() == TOK_GE || getTokID() == TOK_GT || getTokID() == TOK_LE || getTokID() == TOK_LT ){
        matchTok(getTokID());
        term();
    }
}

PRIVATE void term(){

    if( getTokID() == TOK_PLUS || getTokID() == TOK_MINUS )
        matchTok(getTokID());

    factor();

    while ( getTokID() == TOK_PLUS || getTokID() == TOK_MINUS || getTokID() == TOK_OR ){
        matchTok(getTokID());
        factor();
    }
}

PRIVATE void factor(){

    element();
    while ( getTokID() == TOK_TIMES || getTokID() == TOK_OVER || getTokID() == TOK_MOD || getTokID() == TOK_AND ){
        matchTok(getTokID());
        element();
    }
}

PRIVATE void element(){

    if( getTokID() == TOK_L_PAREN ){

        matchTok(TOK_L_PAREN);
        expression();
        matchTok(TOK_R_PAREN);

    } else if( getTokID() == TOK_NOT  ){

        matchTok(TOK_NOT);
        element();

    } else if( getTokID() == CONSTANT){

        matchTok(CONSTANT);

    } else if( getTokID() == IDENTIFIER ){

        matchTok(IDENTIFIER);

        if( getTokID() == TOK_L_BRACE ){

            matchTok(TOK_L_BRACE);
            expression();
            matchTok(TOK_R_BRACE);
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
    program();

    return 0;
}