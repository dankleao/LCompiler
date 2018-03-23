//
// Created by Daniel on 22/03/2018.
//

#include "parser.h"

PRIVATE inline void matchTok( int tokExpected ){

    if( GET_TOK == tokExpected ){
        //printSymbol(GET_SYMBOL);
        SET_SYMBOL;
        //printf("tokId: %d\n",GET_TOK);
    } else{

        if( GET_TOK == NULL_TOK )
            compilerror(ERR_EOF_NOT_EXPECTED,NULL);
        else
            compilerror(ERR_TOK_NOT_EXPECTED,GET_LEXEME);

    }
}

PRIVATE void program(){
    SET_SYMBOL;
    declaration();
    while (GET_SYMBOL != NULL ){
        cmdBlock();
    }
}

PRIVATE void declaration(){

    do{
        //printf("Declaration\n");
        if( GET_TOK == TOK_FINAL ){

            //printf("Constant\n");
            matchTok(TOK_FINAL);
            matchTok(IDENTIFIER);
            matchTok(TOK_EQ);

            if( GET_TOK == TOK_PLUS || GET_TOK == TOK_MINUS )
                matchTok(GET_TOK);

            matchTok(CONSTANT);

        } else if( GET_TOK == TOK_INT || GET_TOK == TOK_CHAR ){

            //printf("Vars\n");
            matchTok(GET_TOK);
            vars();

        } else{
            return;
        }

        matchTok(TOK_SEMICOLON);

    }while ( GET_TOK == TOK_FINAL || GET_TOK == TOK_INT || GET_TOK == TOK_CHAR );
}

PRIVATE void vars(){

    matchTok(IDENTIFIER);

    if( GET_TOK == TOK_ASSIGN ){

        //printf(" <- ");
        matchTok(TOK_ASSIGN);
        expression();

    } else if( GET_TOK == TOK_L_BRACE ) {

        //printf("[const]\n");
        matchTok(TOK_L_BRACE);
        expression();
        matchTok(TOK_R_BRACE);
    }

    if( GET_TOK == TOK_COMMA ){
        //printf(", Vars\n");
        matchTok(TOK_COMMA);
        vars();
    }
}

PRIVATE void cmdBlock(){
    //printf("CMD BLOCK\n");

    if( GET_TOK == TOK_IF ){

        //printf("Tok if\n");
        matchTok(TOK_IF);
        cmdIf();

    } else if( GET_TOK == TOK_FOR ){

        //printf("Tok for\n");
        matchTok(TOK_FOR);
        cmdFor();

    } else if( GET_TOK ==  TOK_READLN ){

        //printf("Tok readln\n");
        matchTok(TOK_READLN);
        matchTok(TOK_L_PAREN);
        matchTok(IDENTIFIER);
        matchTok(TOK_R_PAREN);
        matchTok(TOK_SEMICOLON);

    } else if( GET_TOK == TOK_WRITE || GET_TOK == TOK_WRITELN ){

        //printf("Write or Writeln\n");
        matchTok(GET_TOK);

        matchTok(TOK_L_PAREN);

        expression();

        while( GET_TOK == TOK_COMMA ){
            matchTok(TOK_COMMA);
            expression();
        }

        matchTok(TOK_R_PAREN);
        matchTok(TOK_SEMICOLON);

        //printf("end write or writeln\n");

    } else if( GET_TOK == IDENTIFIER ){

        matchTok(IDENTIFIER);

        if( GET_TOK == TOK_L_BRACE ){
            matchTok(TOK_L_BRACE);
            expression();
            matchTok(TOK_R_BRACE);
        }

        matchTok(TOK_ASSIGN);
        expression();
        matchTok(TOK_SEMICOLON);

    } else{
        matchTok(TOK_SEMICOLON);
    }
}

PRIVATE void cmdIf(){

    expression();
    matchTok(TOK_THEN);
    cmdBody();

    if( GET_TOK == TOK_ELSE ){
        matchTok(TOK_ELSE);
        cmdBody();
    }
}

PRIVATE void cmdFor(){

    matchTok(IDENTIFIER);
    matchTok(TOK_ASSIGN);
    expression();
    matchTok(TOK_TO);
    expression();

    if( GET_TOK == TOK_STEP ){
        matchTok(TOK_STEP);

        if( GET_TOK == TOK_PLUS || GET_TOK == TOK_MINUS )
            matchTok(GET_TOK);

        matchTok(CONSTANT);
    }

    matchTok(TOK_DO);
    cmdBody();

}

PRIVATE void cmdBody(){

    //printf("Body\n");
    if( GET_TOK == TOK_BEGIN ){

        //printf("Begin\n");
        matchTok(TOK_BEGIN);
        if( GET_TOK == TOK_SEMICOLON ){
            matchTok(TOK_SEMICOLON);
        }
        else{

            do{
                cmdBlock();
            }while (GET_TOK != TOK_END );
        }

        matchTok(TOK_END);
        //printf("End\n");

    } else{
        cmdBlock();
    }
}

PRIVATE void expression(){
    term();
    if( GET_TOK == TOK_EQ || GET_TOK == TOK_NE || GET_TOK == TOK_GE || GET_TOK == TOK_GT || GET_TOK == TOK_LE || GET_TOK == TOK_LT ){
        matchTok(GET_TOK);
        term();
    }
}

PRIVATE void term(){

    if( GET_TOK == TOK_PLUS || GET_TOK == TOK_MINUS )
        matchTok(GET_TOK);

    factor();

    while ( GET_TOK == TOK_PLUS || GET_TOK == TOK_MINUS ||GET_TOK == TOK_OR ){
        matchTok(GET_TOK);
        factor();
    }
}

PRIVATE void factor(){
    element();
    while ( GET_TOK == TOK_TIMES || GET_TOK == TOK_OVER || GET_TOK == TOK_MOD || GET_TOK == TOK_AND ){
        matchTok(GET_TOK);
        element();
    }
}

PRIVATE void element(){

    if( GET_TOK == TOK_L_PAREN ){

        matchTok(TOK_L_PAREN);
        expression();
        matchTok(TOK_R_PAREN);

    } else if( GET_TOK == TOK_NOT  ){

        matchTok(TOK_NOT);
        element();

    } else if( GET_TOK == CONSTANT){

        matchTok(CONSTANT);

    } else if( GET_TOK == IDENTIFIER ){

        matchTok(IDENTIFIER);

        if( GET_TOK == TOK_L_BRACE ){

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
    //printf("Program\n");
    program();

    return 0;
}