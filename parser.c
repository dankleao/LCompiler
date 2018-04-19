//
// Created by Daniel on 07/04/2018.
//

#include "parser.h"


PRIVATE inline void setSynthAttributes(SynthAttr* synthAttr, int size, data_type type ){
    synthAttr->size = size;
    synthAttr->type = type;
}

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

            matchTok(TOK_FINAL);

            Symbol* tmpIdentifier = currentSymbol;

            //Checa unicidade de identificador
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

                    tmpIdentifier->dataType = INTEGER_DATA_TYPE;

                    if( ! signal )
                        signal = 1;

                    int value = withinLimitOfInteger(signal);

                    //GEN CODE


                } else if( currentSymbol->typeConst == CHARACTER_CONST || currentSymbol->typeConst == HEX_CONST ){

                    if( signal ){
                        compilerror(ERR_INCOMPATIBLE_TYPES,NULL);
                    } else{

                        tmpIdentifier->dataType = CHARACTER_DATA_TYPE;

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

            if( currentSymbol->tok == TOK_INT )
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

PRIVATE void var(data_type inhDType){

    checkUniqueness(VAR_CLASS);

    Symbol* tmpIdentifier = currentSymbol;

    tmpIdentifier->dataType = inhDType;

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

            //Constante inteira
            if( currentSymbol->typeConst == NUMBER_CONST ){

                if( inhDType == INTEGER_DATA_TYPE ){

                    if( ! signal )
                        signal = 1;

                    int value = withinLimitOfInteger(signal);

                    //GEN CODE

                } else{
                    compilerror(ERR_INCOMPATIBLE_TYPES,NULL);
                }

            }//constante literal caracter ou hexadecimal
            else if( currentSymbol->typeConst == CHARACTER_CONST || currentSymbol->typeConst == HEX_CONST ){

                if( ! signal && inhDType == CHARACTER_DATA_TYPE ){
                    //GEN CODE
                } else{
                    compilerror(ERR_INCOMPATIBLE_TYPES,NULL);
                }

            }//Constante literal string, erro!
            else {
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);
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

        SynthAttr lValueChild;

        setSynthAttributes(&lValueChild,tmpIdentifier->arraySize,tmpIdentifier->dataType);

        matchTok(TOK_IDENTIFIER);

        if( currentSymbol->tok == TOK_L_BRACE ){

            //Verifica compatibilidade de classes de identificadores
            checkClassCompatibility(tmpIdentifier);

            //Verifica se identificador é do tipo arranjo
            if( tmpIdentifier->arraySize == 0 )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);


            matchTok(TOK_L_BRACE);

            SynthAttr rValueChild = { 0, INTEGER_DATA_TYPE};

            expression(&rValueChild);

            if( rValueChild.type != INTEGER_DATA_TYPE )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

            matchTok(TOK_R_BRACE);

            lValueChild.size = 0;

            //OTHER SMTC ACTIONS

        }

        if( currentSymbol->tok == TOK_ASSIGN ){

            //Verifica compatibilidade de classes de identificadores
            checkClassCompatibility(tmpIdentifier);

            matchTok(TOK_ASSIGN);

            SynthAttr rValueChild = { 0, INTEGER_DATA_TYPE };

            expression(&rValueChild);

            if( lValueChild.type != rValueChild.type || ( !(lValueChild.size && rValueChild.size ) && ( lValueChild.size || rValueChild.size )  ) )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

        }

        matchTok(TOK_SEMICOLON);

    }//Delimitador de comandos ";"
    else{
        matchTok(TOK_SEMICOLON);
    }
}

PRIVATE void cmdif(){

    matchTok(TOK_IF);

    SynthAttr lValueChild = { 0, INTEGER_DATA_TYPE };

    expression(&lValueChild);

    if( lValueChild.type != INTEGER_DATA_TYPE )
        compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

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

    SynthAttr lValueChild = { 0, INTEGER_DATA_TYPE };

    expression(&lValueChild);

    if( lValueChild.type != INTEGER_DATA_TYPE )
        compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

    matchTok(TOK_TO);

    setSynthAttributes(&lValueChild,0,INTEGER_DATA_TYPE);

    expression(&lValueChild);

    if( lValueChild.type != INTEGER_DATA_TYPE )
        compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

    //Instrução step opcional
    if( currentSymbol->tok == TOK_STEP ){

        matchTok(TOK_STEP);

        if( currentSymbol->tok == TOK_PLUS || currentSymbol->tok == TOK_MINUS )
            matchTok(currentSymbol->tok);

        //Senão for constante numérica, erro!
        if( currentSymbol->tok == TOK_CONSTANT && currentSymbol->typeConst != NUMBER_CONST )
            compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

        matchTok(TOK_CONSTANT);
    }

    matchTok(TOK_DO);
    body();

}

PRIVATE void cmdio(){

    SynthAttr lValueChild = { 0, INTEGER_DATA_TYPE };

    if( currentSymbol->tok == TOK_READLN ){

        matchTok(TOK_READLN);
        matchTok(TOK_L_PAREN);

        checkVarDeclaration();

        //Verifica compatibilidade de classes de identificadores
        if( currentSymbol->tok == TOK_IDENTIFIER )
            checkClassCompatibility(currentSymbol);

        Symbol* tmpIdentifier = currentSymbol;

        matchTok(TOK_IDENTIFIER);

        if( currentSymbol->tok == TOK_L_BRACE ){
            matchTok(TOK_L_BRACE);

            expression(&lValueChild);

            //Se identificador não for do tipo arranjo ou índice do arranjo não for uma constante numérica
            if( tmpIdentifier->arraySize == 0 || lValueChild.type != INTEGER_DATA_TYPE )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

            lValueChild.size = 1;//Marca arranjo

            matchTok(TOK_R_BRACE);

        }

        //Se identificador for um arranjo de inteiros sem colchetes, erro!
        if( tmpIdentifier->dataType == INTEGER_DATA_TYPE && tmpIdentifier->arraySize != 0 && lValueChild.size == 0 )
            compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

        matchTok(TOK_R_PAREN);

    } else if( currentSymbol->tok == TOK_WRITE || currentSymbol->tok == TOK_WRITELN ){

        matchTok(currentSymbol->tok);
        matchTok(TOK_L_PAREN);

        expression(&lValueChild);

        if( lValueChild.type == INTEGER_DATA_TYPE && lValueChild.size != 0 )
            compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

        //Lista de argumentos opcional
        while( currentSymbol->tok == TOK_COMMA ){
            matchTok(TOK_COMMA);

            SynthAttr rValueChild = { 0, INTEGER_DATA_TYPE };

            expression(&rValueChild);

            if( rValueChild.type == INTEGER_DATA_TYPE && rValueChild.size != 0 )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

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

PRIVATE void expression(SynthAttr* lValueRoot){

    SynthAttr lValueChild = { 0, INTEGER_DATA_TYPE};
    SynthAttr rValueChild = { 0, INTEGER_DATA_TYPE};
    int operator;

    term(&lValueChild);

    setSynthAttributes(lValueRoot,lValueChild.size,lValueChild.type);

    while ( currentSymbol->tok == TOK_EQ || currentSymbol->tok == TOK_NE ||
            currentSymbol->tok == TOK_GE || currentSymbol->tok == TOK_GT ||
            currentSymbol->tok == TOK_LE || currentSymbol->tok == TOK_LT ){

        //salva o operador binário
        operator = currentSymbol->tok;

        matchTok(currentSymbol->tok);

        term(&rValueChild);

        //Se rValue.tipo == CHAR
        if( rValueChild.type == CHARACTER_DATA_TYPE ){

            //Se rValue.size == 0 ( ESCALAR )
            if( rValueChild.size == 0 ){

                if( lValueChild.type != CHARACTER_DATA_TYPE || lValueChild.size != 0 )
                    compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

                //GEN CODE

            }//Senão, rValue != 0 ( ARRANJO )
            else{

                if ( ( lValueChild.type != CHARACTER_DATA_TYPE || lValueChild.size != 1 ) && operator != TOK_EQ || operator != TOK_NE )
                    compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

                //GEN CODE
            }

        }//Senão, rValue == INTEGER
        else{

            //Se rValue.size == 0 ( ESCALAR )
            if( rValueChild.size == 0 ){

                if( lValueChild.type != INTEGER_DATA_TYPE || lValueChild.size != 0 )
                    compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

                //GEN CODE

            }//Senão, rValue != 0 ( ARRANJO )
            else{
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);
            }

        }

    }
}

PRIVATE void term(SynthAttr* lValueRoot){

    SynthAttr lValueChild = { 0, INTEGER_DATA_TYPE};
    SynthAttr rValueChild = { 0, INTEGER_DATA_TYPE};

    if( currentSymbol->tok == TOK_PLUS || currentSymbol->tok == TOK_MINUS )
        matchTok(currentSymbol->tok);

    factor(&lValueChild);

    setSynthAttributes(lValueRoot,lValueChild.size,lValueChild.type);

    while ( currentSymbol->tok == TOK_PLUS || currentSymbol->tok == TOK_MINUS ||currentSymbol->tok == TOK_OR ){

        matchTok(currentSymbol->tok);

        factor(&rValueChild);

        if( ( !lValueChild.type || lValueChild.size) || ( !rValueChild.type || rValueChild.size ) )
            compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

    }
}

PRIVATE void factor(SynthAttr* lValueRoot){

    SynthAttr lValueChild = { 0, INTEGER_DATA_TYPE};
    SynthAttr rValueChild = { 0, INTEGER_DATA_TYPE};

    e(&lValueChild);

    setSynthAttributes(lValueRoot,lValueChild.size,lValueChild.type);

    while ( currentSymbol->tok == TOK_TIMES || currentSymbol->tok == TOK_OVER || currentSymbol->tok == TOK_MOD || currentSymbol->tok == TOK_AND ){

        matchTok(currentSymbol->tok);

        e(&rValueChild);

        if( ( !lValueChild.type || lValueChild.size) || ( !rValueChild.type || rValueChild.size ) )
            compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

    }
}

PRIVATE void e(SynthAttr* lValueRoot){

    SynthAttr lValueChild = { 0, INTEGER_DATA_TYPE };

    if( currentSymbol->tok == TOK_L_PAREN ){

        matchTok(TOK_L_PAREN);

        expression(&lValueChild);

        setSynthAttributes(lValueRoot,lValueChild.size,lValueChild.type);

        matchTok(TOK_R_PAREN);

    } else if( currentSymbol->tok == TOK_NOT  ){

        matchTok(TOK_NOT);

        e(&lValueChild);

        if( lValueChild.type != INTEGER_DATA_TYPE )
            compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

        setSynthAttributes(lValueRoot,lValueChild.size,lValueChild.type);


    } else if( currentSymbol->tok == TOK_CONSTANT ){

        if( currentSymbol->typeConst == NUMBER_CONST ){
            lValueRoot->type = INTEGER_DATA_TYPE;
        } else if( currentSymbol->typeConst == CHARACTER_CONST || currentSymbol->typeConst == HEX_CONST ){
            lValueRoot->type = CHARACTER_DATA_TYPE;
        } else{
            lValueRoot->type = CHARACTER_DATA_TYPE;
            lValueRoot->size = strlen( currentSymbol->lexeme );//Aceita string vazia.
        }

        matchTok(TOK_CONSTANT);

    } else{

        //Armazena o identificador para uso posterior
        Symbol * tmpIdentifier = currentSymbol;

        checkVarDeclaration();

        setSynthAttributes(lValueRoot,tmpIdentifier->arraySize,tmpIdentifier->dataType);

        matchTok(TOK_IDENTIFIER);

        if( currentSymbol->tok == TOK_L_BRACE ){

            //Verifica compatibilidade de classes de identificadores
            checkClassCompatibility(tmpIdentifier);

            //Se identificador é do tipo array
            if( tmpIdentifier->arraySize == 0 )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

            matchTok(TOK_L_BRACE);
            expression(&lValueChild);
            matchTok(TOK_R_BRACE);

            if( lValueChild.type != INTEGER_DATA_TYPE )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

            lValueRoot->size = 0;

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