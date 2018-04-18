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

PRIVATE inline void checkUniqueness(class classId){
    if( getTok() == TOK_IDENTIFIER ){
        if( currentSymbol->classId == NULL_CLASS ){
            currentSymbol->classId = classId;
        } else{
            compilerror(ERR_IDENTIFIER_ALREADY_DECLARED,getLexeme());
        }
    }
}

PRIVATE inline void checkVarDeclaration(){
    if( getTok() == TOK_IDENTIFIER ){
        if( currentSymbol->classId == NULL_CLASS ){
            compilerror(ERR_UNDECLARED_IDENTIFIER,getLexeme());
        }
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

            data_type * syntDType;

            matchTok(TOK_FINAL);

            syntDType = &currentSymbol->dataType;

            checkUniqueness(CONST_CLASS);

            matchTok(TOK_IDENTIFIER);
            matchTok(TOK_EQ);

            int signal = 0;

            if( getTok() == TOK_PLUS || getTok() == TOK_MINUS ){

                signal = ( getTok() == TOK_PLUS ? 1 : -1 );

                matchTok(getTok());
            }

            if( getTok() == TOK_CONSTANT ){

                if( currentSymbol->typeConst == NUMBER_CONST ){

                    *syntDType = INTEGER_DATA_TYPE;

                    int value;

                    if( ! signal )
                        signal = 1;

                    value = atoi(currentSymbol->lexeme) * signal;

                    if( value < INTEGER_MIN_VALUE || value > INTEGER_MAX_VALUE )
                        compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

                    //GEN CODE


                } else if( currentSymbol->typeConst == CHARACTER_CONST || currentSymbol->typeConst == HEX_CONST ){
                    if( signal ){
                        compilerror(ERR_INCOMPATIBLE_TYPES,NULL);
                    } else{
                        *syntDType = CHARACTER_DATA_TYPE;

                        //GEN CODE
                    }
                } else{
                    compilerror(ERR_INCOMPATIBLE_TYPES,NULL);
                }
            }

            matchTok(TOK_CONSTANT);

        }//Declaração das variáveis
        else if( getTok() == TOK_INT || getTok() == TOK_CHAR ){

            data_type inhDType;

            if( getTok()== TOK_INT )
                inhDType = INTEGER_DATA_TYPE;
            else
                inhDType = CHARACTER_DATA_TYPE;

            matchTok(getTok());

            var(inhDType);

        } else{
            return;
        }

        matchTok(TOK_SEMICOLON);

    }while ( getTok() == TOK_FINAL || getTok() == TOK_INT || getTok() == TOK_CHAR );
}

PRIVATE void var(data_type inhDType ){

    checkUniqueness(VAR_CLASS);

    Symbol* identifierPtr = currentSymbol;

    matchTok(TOK_IDENTIFIER);

    //Definição de variáveis escalares
    if( getTok() == TOK_ASSIGN ){

        matchTok(TOK_ASSIGN);

        int signal = 0;

        if( getTok() == TOK_PLUS || getTok() == TOK_MINUS ){

            signal = ( getTok() == TOK_PLUS ? 1 : -1 );

            matchTok(getTok());
        }

        if( getTok() == TOK_CONSTANT ){

            switch (currentSymbol->typeConst){

                case NUMBER_CONST:

                    if( inhDType == INTEGER_DATA_TYPE ){

                        int value;

                        if( ! signal )
                            signal = 1;

                        value = atoi(currentSymbol->lexeme) * signal;

                        if( value < INTEGER_MIN_VALUE || value > INTEGER_MAX_VALUE )
                            compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

                        //GEN CODE
                    } else{
                        compilerror(ERR_INCOMPATIBLE_TYPES,NULL);
                    }
                    break;
                case CHARACTER_CONST:
                case HEX_CONST:
                    if( ! signal && inhDType == CHARACTER_DATA_TYPE ){
                        //GEN CODE
                    } else{
                        compilerror(ERR_INCOMPATIBLE_TYPES,NULL);
                    }
                    break;
                default:
                    compilerror(ERR_INCOMPATIBLE_TYPES,NULL);
                    break;

            }
        }

        matchTok(TOK_CONSTANT);

    }//Definição de vetores unidimensionais
    else if( getTok() == TOK_L_BRACE ) {

        matchTok(TOK_L_BRACE);

        if( getTok() == TOK_CONSTANT ){

            if( currentSymbol->typeConst == NUMBER_CONST ){

                int arraySize = atoi(currentSymbol->lexeme);

                if( arraySize > ARRAY_SIZE_MAX )
                    compilerror(ERR_ARRAY_SIZE_BOUND_EXCEEDED,NULL);

                identifierPtr->arraySize = arraySize;

                //GEN CODE

            } else{
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);
            }
        }

        matchTok(TOK_CONSTANT);
        matchTok(TOK_R_BRACE);
    }

    //Lista de declarações de variáveis
    if( getTok() == TOK_COMMA ){

        matchTok(TOK_COMMA);
        var(inhDType);
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

        Symbol* identifierPtr = currentSymbol;

        checkVarDeclaration();

        matchTok(TOK_IDENTIFIER);

        if( getTok() == TOK_L_BRACE ){

            matchTok(TOK_L_BRACE);
            expression();
            matchTok(TOK_R_BRACE);

            //Verifica compatibilidade de classes de identificadores
            if(identifierPtr->classId == CONST_CLASS )
                compilerror(ERR_INCOMPATIBLE_CLASS_IDENTIFIER,identifierPtr->lexeme);

            //Verifica se identificador é do tipo arranjo
            if( identifierPtr->arraySize == 0 )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

        }

        if( getTok() == TOK_ASSIGN ){

            matchTok(TOK_ASSIGN);

            //Verifica compatibilidade de classes de identificadores
            if( identifierPtr->classId == CONST_CLASS )
                compilerror(ERR_INCOMPATIBLE_CLASS_IDENTIFIER,identifierPtr->lexeme);

            expression();

        }

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

    checkVarDeclaration();

    //Verifica compatibilidade de classes de identificadores
    if( getTok() == TOK_IDENTIFIER ){
        if( currentSymbol->classId == CONST_CLASS )
            compilerror(ERR_INCOMPATIBLE_CLASS_IDENTIFIER,getLexeme());
    }

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

        checkVarDeclaration();

        //Verifica compatibilidade de classes de identificadores
        if( getTok() == TOK_IDENTIFIER ){
            if( currentSymbol->classId == CONST_CLASS )
                compilerror(ERR_INCOMPATIBLE_CLASS_IDENTIFIER,getLexeme());
        }

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

        Symbol * identifierPtr = currentSymbol;

        checkVarDeclaration();

        matchTok(TOK_IDENTIFIER);

        if( getTok() == TOK_L_BRACE ){

            matchTok(TOK_L_BRACE);
            expression();
            matchTok(TOK_R_BRACE);

            //Verifica compatibilidade de classes de identificadores
            if(identifierPtr->classId == CONST_CLASS )
                compilerror(ERR_INCOMPATIBLE_CLASS_IDENTIFIER,identifierPtr->lexeme);

            //Verifica se identificador é do tipo arranjo
            if( identifierPtr->arraySize == 0 )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

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