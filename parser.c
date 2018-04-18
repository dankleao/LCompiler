//
// Created by Daniel on 07/04/2018.
//

#include "parser.h"

PUBLIC inline void checkUniqueness(class classId){

    if( currentSymbol->tok == TOK_IDENTIFIER ){
        if( currentSymbol->classId == NULL_CLASS ){
            currentSymbol->classId = classId;
        } else{
            compilerror(ERR_IDENTIFIER_ALREADY_DECLARED,currentSymbol->lexeme);
        }
    }
}

PRIVATE inline void checkClassCompatibility(Symbol* symbol){

    if( symbol->classId == CONST_CLASS )
        compilerror(ERR_INCOMPATIBLE_CLASS_IDENTIFIER,symbol->lexeme);

}

PUBLIC inline void checkVarDeclaration(){
    if( currentSymbol->tok == TOK_IDENTIFIER ){
        if( currentSymbol->classId == NULL_CLASS ){
            compilerror(ERR_UNDECLARED_IDENTIFIER,currentSymbol->lexeme);
        }
    }
}

PUBLIC inline int withinLimitOfInteger(int signal){

    int value = atoi(currentSymbol->lexeme) * signal;

    if( value < INTEGER_MIN_VALUE || value > INTEGER_MAX_VALUE )
        compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

    return value;
}

PUBLIC inline int withinArraySizeBounds(){

    int arraySize = atoi(currentSymbol->lexeme);
    if( arraySize > ARRAY_SIZE_MAX )
        compilerror(ERR_ARRAY_SIZE_BOUND_EXCEEDED,NULL);

    return arraySize;
}

PRIVATE inline void matchTok( int tokExpected ){

    if ( currentSymbol != NULL && currentSymbol->tok == tokExpected ){
        //printSymbol(currentSymbol);
        currentSymbol = nextSymbol();
    } else{

        if( currentSymbol == NULL )
            compilerror(ERR_EOF_NOT_EXPECTED,NULL);
        else
            compilerror(ERR_TOK_NOT_EXPECTED,currentSymbol->lexeme);
    }
}

PRIVATE void program(){

    //Inicio da execução do parser
    currentSymbol = nextSymbol();//Obtém o primeiro símbolo do código fonte
    decl();
    while ( currentSymbol != NULL ){
        cmd();
    }
}

PRIVATE void decl(){

    //Declarações

    do{

        //Declaração de constantes
        if( currentSymbol->tok == TOK_FINAL ){

            data_type * syntDType;

            matchTok(TOK_FINAL);

            syntDType = &currentSymbol->dataType;

            checkUniqueness(CONST_CLASS);

            matchTok(TOK_IDENTIFIER);
            matchTok(TOK_EQ);

            int signal = 0;

            if( currentSymbol->tok == TOK_PLUS || currentSymbol->tok == TOK_MINUS ){

                signal = ( currentSymbol->tok == TOK_PLUS ? 1 : -1 );

                matchTok(currentSymbol->tok);
            }

            if( currentSymbol->tok == TOK_CONSTANT ){

                if( currentSymbol->typeConst == NUMBER_CONST ){

                    *syntDType = INTEGER_DATA_TYPE;

                    if( ! signal )
                        signal = 1;

                    int value = withinLimitOfInteger(signal);

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
        else if( currentSymbol->tok == TOK_INT || currentSymbol->tok == TOK_CHAR ){

            data_type inhDType;

            if( currentSymbol->tok== TOK_INT )
                inhDType = INTEGER_DATA_TYPE;
            else
                inhDType = CHARACTER_DATA_TYPE;

            matchTok(currentSymbol->tok);

            var(inhDType);

        } else{
            return;
        }

        matchTok(TOK_SEMICOLON);

    }while ( currentSymbol->tok == TOK_FINAL || currentSymbol->tok == TOK_INT || currentSymbol->tok == TOK_CHAR );
}

PRIVATE void var(data_type inhDType ){

    checkUniqueness(VAR_CLASS);

    Symbol* tmpIdentifier = currentSymbol;

    matchTok(TOK_IDENTIFIER);

    //Definição de variáveis escalares
    if( currentSymbol->tok == TOK_ASSIGN ){

        matchTok(TOK_ASSIGN);

        int signal = 0;

        if( currentSymbol->tok == TOK_PLUS || currentSymbol->tok == TOK_MINUS ){

            signal = ( currentSymbol->tok == TOK_PLUS ? 1 : -1 );

            matchTok(currentSymbol->tok);
        }

        if( currentSymbol->tok == TOK_CONSTANT ){

            switch (currentSymbol->typeConst){

                case NUMBER_CONST:

                    if( inhDType == INTEGER_DATA_TYPE ){

                        if( ! signal )
                            signal = 1;

                        int value = withinLimitOfInteger(signal);

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
    else if( currentSymbol->tok == TOK_L_BRACE ) {

        matchTok(TOK_L_BRACE);

        if( currentSymbol->tok == TOK_CONSTANT ){

            if( currentSymbol->typeConst == NUMBER_CONST ){

                tmpIdentifier->arraySize = withinArraySizeBounds();

                //GEN CODE

            } else{
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);
            }
        }

        matchTok(TOK_CONSTANT);
        matchTok(TOK_R_BRACE);
    }

    //Lista de declarações de variáveis
    if( currentSymbol->tok == TOK_COMMA ){

        matchTok(TOK_COMMA);
        var(inhDType);
    }
}

PRIVATE void cmd(){

    //Comando if
    if( currentSymbol->tok == TOK_IF ){
        cmdif();
    }//Comando for
    else if( currentSymbol->tok == TOK_FOR ){
        cmdfor();
    }//Comando readln, write ou writeln
    else if( currentSymbol->tok ==  TOK_READLN || currentSymbol->tok == TOK_WRITE || currentSymbol->tok == TOK_WRITELN ){
        cmdio();
    }// Atribuições
    else if( currentSymbol->tok == TOK_IDENTIFIER ){

        //Armazena o identificador para uso posterior
        Symbol* tmpIdentifier = currentSymbol;

        checkVarDeclaration();

        matchTok(TOK_IDENTIFIER);

        if( currentSymbol->tok == TOK_L_BRACE ){

            matchTok(TOK_L_BRACE);
            expression();
            matchTok(TOK_R_BRACE);

            //Verifica compatibilidade de classes de identificadores
            checkClassCompatibility(tmpIdentifier);

            //Verifica se identificador é do tipo arranjo
            if( tmpIdentifier->arraySize == 0 )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

            //OTHER SMTC ACTIONS

        }

        if( currentSymbol->tok == TOK_ASSIGN ){

            matchTok(TOK_ASSIGN);

            //Verifica compatibilidade de classes de identificadores
            checkClassCompatibility(tmpIdentifier);

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
    if( currentSymbol->tok == TOK_ELSE ){
        matchTok(TOK_ELSE);
        body();
    }
}

PRIVATE void cmdfor(){

    matchTok(TOK_FOR);

    checkVarDeclaration();

    //Verifica compatibilidade de classes de identificadores
    if( currentSymbol->tok == TOK_IDENTIFIER )
        checkClassCompatibility(currentSymbol);

    matchTok(TOK_IDENTIFIER);
    matchTok(TOK_ASSIGN);
    expression();
    matchTok(TOK_TO);
    expression();

    //Instrução step opcional
    if( currentSymbol->tok == TOK_STEP ){
        matchTok(TOK_STEP);

        if( currentSymbol->tok == TOK_PLUS || currentSymbol->tok == TOK_MINUS )
            matchTok(currentSymbol->tok);

        matchTok(TOK_CONSTANT);
    }

    matchTok(TOK_DO);
    body();

}

PRIVATE void cmdio(){

    if( currentSymbol->tok == TOK_READLN ){

        matchTok(TOK_READLN);
        matchTok(TOK_L_PAREN);

        checkVarDeclaration();

        //Verifica compatibilidade de classes de identificadores
        if( currentSymbol->tok == TOK_IDENTIFIER )
            checkClassCompatibility(currentSymbol);


        matchTok(TOK_IDENTIFIER);

        if( currentSymbol->tok == TOK_L_BRACE ){
            matchTok(TOK_L_BRACE);
            expression();
            matchTok(TOK_R_BRACE);
        }

        matchTok(TOK_R_PAREN);

    } else if( currentSymbol->tok == TOK_WRITE || currentSymbol->tok == TOK_WRITELN ){

        matchTok(currentSymbol->tok);
        matchTok(TOK_L_PAREN);
        expression();

        //Lista de argumentos opcional
        while( currentSymbol->tok == TOK_COMMA ){
            matchTok(TOK_COMMA);
            expression();
        }

        matchTok(TOK_R_PAREN);

    }

    matchTok(TOK_SEMICOLON);

}

PRIVATE void body(){

    if( currentSymbol->tok == TOK_BEGIN ){

        matchTok(TOK_BEGIN);

        do{
            cmd();
        }while (currentSymbol->tok != TOK_END );

        matchTok(TOK_END);

    } else{
        cmd();
    }
}

PRIVATE void expression(){

    term();
    while ( currentSymbol->tok == TOK_EQ || currentSymbol->tok == TOK_NE ||
            currentSymbol->tok == TOK_GE || currentSymbol->tok == TOK_GT ||
            currentSymbol->tok == TOK_LE || currentSymbol->tok == TOK_LT ){

        matchTok(currentSymbol->tok);
        term();
    }
}

PRIVATE void term(){

    if( currentSymbol->tok == TOK_PLUS || currentSymbol->tok == TOK_MINUS )
        matchTok(currentSymbol->tok);

    factor();

    while ( currentSymbol->tok == TOK_PLUS || currentSymbol->tok == TOK_MINUS ||currentSymbol->tok == TOK_OR ){
        matchTok(currentSymbol->tok);
        factor();
    }
}

PRIVATE void factor(){
    e();
    while ( currentSymbol->tok == TOK_TIMES || currentSymbol->tok == TOK_OVER || currentSymbol->tok == TOK_MOD || currentSymbol->tok == TOK_AND ){
        matchTok(currentSymbol->tok);
        e();
    }
}

PRIVATE void e(){

    if( currentSymbol->tok == TOK_L_PAREN ){

        matchTok(TOK_L_PAREN);
        expression();
        matchTok(TOK_R_PAREN);

    } else if( currentSymbol->tok == TOK_NOT  ){

        matchTok(TOK_NOT);
        e();

    } else if( currentSymbol->tok == TOK_CONSTANT){

        matchTok(TOK_CONSTANT);

    } else{

        //Armazena o identificador para uso posterior
        Symbol * tmpIdentifier = currentSymbol;

        checkVarDeclaration();

        matchTok(TOK_IDENTIFIER);

        if( currentSymbol->tok == TOK_L_BRACE ){

            matchTok(TOK_L_BRACE);
            expression();
            matchTok(TOK_R_BRACE);

            //Verifica compatibilidade de classes de identificadores
            checkClassCompatibility(tmpIdentifier);

            //Verifica se identificador é do tipo arranjo
            if( tmpIdentifier->arraySize == 0 )
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