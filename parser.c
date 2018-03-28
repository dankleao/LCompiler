//
// Created by Daniel on 22/03/2018.
//

#include "parser.h"

PRIVATE inline int getTok(){
    return ( currentSymbol == NULL ? NULL_TOK : currentSymbol->tok );
}

PRIVATE inline string getLexeme(){
    return ( currentSymbol == NULL ? "" : currentSymbol->lexeme );
}

PRIVATE inline void matchTok( int tokExpected ){

    if( getTok() == tokExpected ){
        //printSymbol(GET_SYMBOL);
        currentSymbol = nextSymbol();
        //printf("tokId: %d\n",getTok());
    } else{

        if( getTok() == NULL_TOK )
            compilerror(ERR_EOF_NOT_EXPECTED,NULL);
        else
            compilerror(ERR_TOK_NOT_EXPECTED,getLexeme());

    }
}

PRIVATE void program(){
    currentSymbol = nextSymbol();
    declaration();
    while (currentSymbol != NULL ){
        cmdBlock();
    }
}

PRIVATE void declaration(){

    do{
        //printf("Declaration\n");
        if( getTok() == TOK_FINAL ){

            //printf("Constant\n");
            matchTok(TOK_FINAL);
            matchTok(IDENTIFIER);
            matchTok(TOK_EQ);

            if( getTok() == TOK_PLUS || getTok() == TOK_MINUS )
                matchTok(getTok());

            matchTok(CONSTANT);

        } else if( getTok() == TOK_INT || getTok() == TOK_CHAR ){

            //printf("Vars\n");
            matchTok(getTok());
            vars();

        } else{
            return;
        }

        matchTok(TOK_SEMICOLON);

    }while ( getTok() == TOK_FINAL || getTok() == TOK_INT || getTok() == TOK_CHAR );
}

PRIVATE void vars(){

    matchTok(IDENTIFIER);

    if( getTok() == TOK_ASSIGN ){

        //printf(" <- ");
        matchTok(TOK_ASSIGN);
        if( getTok() == TOK_PLUS || getTok() == TOK_MINUS )
            matchTok(getTok());

        matchTok(CONSTANT);

    } else if( getTok() == TOK_L_BRACE ) {

        //printf("[const]\n");
        matchTok(TOK_L_BRACE);
        matchTok(CONSTANT);
        matchTok(TOK_R_BRACE);
    }

    if( getTok() == TOK_COMMA ){
        //printf(", Vars\n");
        matchTok(TOK_COMMA);
        vars();
    }
}

PRIVATE void cmdBlock(){
    //printf("CMD BLOCK\n");

    if( getTok() == TOK_IF ){

        //printf("Tok if\n");
        matchTok(TOK_IF);
        cmdIf();

    } else if( getTok() == TOK_FOR ){

        //printf("Tok for\n");
        matchTok(TOK_FOR);
        cmdFor();

    } else if( getTok() ==  TOK_READLN ){

        //printf("Tok readln\n");
        matchTok(TOK_READLN);
        matchTok(TOK_L_PAREN);
        matchTok(IDENTIFIER);
        matchTok(TOK_R_PAREN);
        matchTok(TOK_SEMICOLON);

    } else if( getTok() == TOK_WRITE || getTok() == TOK_WRITELN ){

        //printf("Write or Writeln\n");
        matchTok(getTok());

        matchTok(TOK_L_PAREN);

        expression();

        while( getTok() == TOK_COMMA ){
            matchTok(TOK_COMMA);
            expression();
        }

        matchTok(TOK_R_PAREN);
        matchTok(TOK_SEMICOLON);

        //printf("end write or writeln\n");

    } else if( getTok() == IDENTIFIER ){

        matchTok(IDENTIFIER);

        if( getTok() == TOK_L_BRACE ){
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

    if( getTok() == TOK_ELSE ){
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

    if( getTok() == TOK_STEP ){
        matchTok(TOK_STEP);

        if( getTok() == TOK_PLUS || getTok() == TOK_MINUS )
            matchTok(getTok());

        matchTok(CONSTANT);
    }

    matchTok(TOK_DO);
    cmdBody();

}

PRIVATE void cmdBody(){

    //printf("Body\n");
    if( getTok() == TOK_BEGIN ){

        //printf("Begin\n");
        matchTok(TOK_BEGIN);

        do{
            cmdBlock();
        }while (getTok() != TOK_END );

        matchTok(TOK_END);
        //printf("End\n");

    } else{
        cmdBlock();
    }
}

PRIVATE void expression(){
    term();
    if( getTok() == TOK_EQ || getTok() == TOK_NE || getTok() == TOK_GE || getTok() == TOK_GT || getTok() == TOK_LE || getTok() == TOK_LT ){
        matchTok(getTok());
        term();
    }
}

PRIVATE void term(){

    if( getTok() == TOK_PLUS || getTok() == TOK_MINUS )
        matchTok(getTok());

    factor();

    while ( getTok() == TOK_PLUS || getTok() == TOK_MINUS ||getTok() == TOK_OR ){
        matchTok(getTok());
        factor();
    }
}

PRIVATE void factor(){
    e();
    while ( getTok() == TOK_TIMES || getTok() == TOK_OVER || getTok() == TOK_MOD || getTok() == TOK_AND ){
        matchTok(getTok());
        e();
    }
}

PRIVATE void e(){

    if( getTok() == TOK_L_PAREN ){

        matchTok(TOK_L_PAREN);
        expression();
        matchTok(TOK_R_PAREN);

    } else if( getTok() == TOK_NOT  ){

        matchTok(TOK_NOT);
        e();

    } else if( getTok() == CONSTANT){

        matchTok(CONSTANT);

    } else{

        matchTok(IDENTIFIER);

        if( getTok() == TOK_L_BRACE ){

            matchTok(TOK_L_BRACE);
            expression();
            matchTok(TOK_R_BRACE);
        }
    }
}

int main( int argc, char* argv[] ){

    if( argc < 2 || argc > 3 )
        compilerror(ERR_BAD_ARGUMENTS,NULL);

    //inicializa o analisador lex
    startLex(argv[1]);

    //inicializa o analisador sintatico
    program();

    //printSymbolTable();

    return 0;
}