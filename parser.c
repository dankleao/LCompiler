//
// Created by Daniel on 07/04/2018.
//

#include "parser.h"

PRIVATE inline int getTok(){
    return (currentSymbol == NULL ? NULL_TOK : currentSymbol->tok);
}

PRIVATE inline string getLexeme(){
    return (currentSymbol == NULL ? "" : currentSymbol->lexeme );
}

PRIVATE inline void matchTok( int tokExpected ){

    if( getTok() == tokExpected ){
        //printSymbol(currentSymbol);
        currentSymbol = nextSymbol();
    } else{
        if( getTok() == NULL_TOK )
            compilerror(ERR_EOF_NOT_EXPECTED,NULL);
        else
            compilerror(ERR_TOK_NOT_EXPECTED,getLexeme());
    }
}

PRIVATE void program(){

    //Inicio da execução do parser
    currentSymbol = nextSymbol();//Obtém o primeiro símbolo do código fonte
    decl();
    while (currentSymbol != NULL ){
        cmd();
    }
}

PRIVATE void decl(){

    //Declarações

    do{

        //Declaração de constantes
        if( getTok() == TOK_FINAL ){

            //printf("Constant\n");
            matchTok(TOK_FINAL);
            matchTok(TOK_IDENTIFIER);
            matchTok(TOK_EQ);

            if( getTok() == TOK_PLUS || getTok() == TOK_MINUS )
                matchTok(getTok());

            matchTok(TOK_CONSTANT);

        }//Declaração das variáveis
        else if( getTok() == TOK_INT || getTok() == TOK_CHAR ){

            matchTok(getTok());
            var();

        } else{
            return;
        }

        matchTok(TOK_SEMICOLON);

    }while ( getTok() == TOK_FINAL || getTok() == TOK_INT || getTok() == TOK_CHAR );
}

PRIVATE void var(){

    matchTok(TOK_IDENTIFIER);

    //Definição de variáveis escalares
    if( getTok() == TOK_ASSIGN ){

        matchTok(TOK_ASSIGN);

        if( getTok() == TOK_PLUS || getTok() == TOK_MINUS )
            matchTok(getTok());

        matchTok(TOK_CONSTANT);

    }//Definição de vetores unidimensionais
    else if( getTok() == TOK_L_BRACE ) {

        matchTok(TOK_L_BRACE);
        matchTok(TOK_CONSTANT);
        matchTok(TOK_R_BRACE);
    }

    //Lista de declarações de variáveis
    if( getTok() == TOK_COMMA ){

        matchTok(TOK_COMMA);
        var();
    }
}

PRIVATE void cmd(){

    //Comando if
    if( getTok() == TOK_IF ){
        cmdif();
    }//Comando for
    else if( getTok() == TOK_FOR ){
        cmdfor();
    }//Comando readln, write ou writeln
    else if( getTok() ==  TOK_READLN || getTok() == TOK_WRITE || getTok() == TOK_WRITELN ){
        cmdio();
    }// Atribuições
    else if( getTok() == TOK_IDENTIFIER ){

        matchTok(TOK_IDENTIFIER);

        if( getTok() == TOK_L_BRACE ){
            matchTok(TOK_L_BRACE);
            expression();
            matchTok(TOK_R_BRACE);
        }

        matchTok(TOK_ASSIGN);
        expression();
        matchTok(TOK_SEMICOLON);

    }//Delimitador de comandos ";"
    else{
        matchTok(TOK_SEMICOLON);
    }
}

PRIVATE void cmdif(){

    matchTok(TOK_IF);
    expression();
    matchTok(TOK_THEN);
    body();

    //Comando else opcional
    if( getTok() == TOK_ELSE ){
        matchTok(TOK_ELSE);
        body();
    }
}

PRIVATE void cmdfor(){

    matchTok(TOK_FOR);
    matchTok(TOK_IDENTIFIER);
    matchTok(TOK_ASSIGN);
    expression();
    matchTok(TOK_TO);
    expression();

    //Instrução step opcional
    if( getTok() == TOK_STEP ){
        matchTok(TOK_STEP);

        if( getTok() == TOK_PLUS || getTok() == TOK_MINUS )
            matchTok(getTok());

        matchTok(TOK_CONSTANT);
    }

    matchTok(TOK_DO);
    body();

}

PRIVATE void cmdio(){

    if( getTok() == TOK_READLN ){

        matchTok(TOK_READLN);
        matchTok(TOK_L_PAREN);
        matchTok(TOK_IDENTIFIER);

        if( getTok() == TOK_L_BRACE ){
            matchTok(TOK_L_BRACE);
            expression();
            matchTok(TOK_R_BRACE);
        }

        matchTok(TOK_R_PAREN);

    } else if( getTok() == TOK_WRITE || getTok() == TOK_WRITELN ){

        matchTok(getTok());
        matchTok(TOK_L_PAREN);
        expression();

        //Lista de argumentos opcional
        while( getTok() == TOK_COMMA ){
            matchTok(TOK_COMMA);
            expression();
        }

        matchTok(TOK_R_PAREN);

    }

    matchTok(TOK_SEMICOLON);

}

PRIVATE void body(){

    if( getTok() == TOK_BEGIN ){

        matchTok(TOK_BEGIN);

        do{
            cmd();
        }while (getTok() != TOK_END );

        matchTok(TOK_END);

    } else{
        cmd();
    }
}

PRIVATE void expression(){

    term();
    while ( getTok() == TOK_EQ || getTok() == TOK_NE || getTok() == TOK_GE || getTok() == TOK_GT || getTok() == TOK_LE || getTok() == TOK_LT ){
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

    } else if( getTok() == TOK_CONSTANT){

        matchTok(TOK_CONSTANT);

    } else{

        matchTok(TOK_IDENTIFIER);

        if( getTok() == TOK_L_BRACE ){

            matchTok(TOK_L_BRACE);
            expression();
            matchTok(TOK_R_BRACE);
        }
    }
}

PUBLIC int main( int argc, char* argv[] ){

    //Verifica o número de argumentos para compilar
    if( argc < 2 || argc > 3 )
        compilerror(ERR_BAD_ARGUMENTS,NULL);

    //inicializa o analisador lex
    startLex(argv[1]);

    //inicializa o analisador sintatico
    program();

    //printSymbolTable();

    return 0;
}