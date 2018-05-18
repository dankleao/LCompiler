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

    if ( currentSymbol != &NullSymbol && currentSymbol->tok == tokExpected ){
        //printSymbol(currentSymbol);
        currentSymbol = nextSymbol();
    } else{

        if( currentSymbol == &NullSymbol )
            compilerror(ERR_EOF_NOT_EXPECTED,NULL);
        else
            compilerror(ERR_TOK_NOT_EXPECTED,currentSymbol->lexeme);
    }
}

PRIVATE void program(){

    //Inicio da execução do parser
    currentSymbol = nextSymbol();//Obtém o primeiro símbolo do código fonte

    //Seg de pilha
    startStackSeg();//inicio
    endStackSeg();//fim

    //Seg de dados
    startDataSeg();//inicio
    decl();
    endDataSeg();//fim

    //Seg de código
    startCodeSeg();//inicio
    while ( currentSymbol != &NullSymbol )
        cmd();
    endCodeSeg();//fim

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

                //Constante inteira
                if( currentSymbol->type == NUMBER_CONST ){

                    tmpIdentifier->dataType = INTEGER_DATA_TYPE;

                    if( ! signal )
                        signal = 1;

                    int value = withinLimitOfInteger(signal);

                    //GERAÇÃO CÓDIGO

                    //Reserva memoria p/ id tipo inteiro
                    memAlloc(&tmpIdentifier->address, SWORD, STANDARD_MEMORY_REGION);

                    //Escreve instrução asm
                    writeInstruction("\tsword %d ;const int em %d\n", 2, value, tmpIdentifier->address);

                }//Constante hexa ou char
                else if( currentSymbol->type == CHARACTER_CONST || currentSymbol->type == HEX_CONST ){

                    if( signal ){
                        compilerror(ERR_INCOMPATIBLE_TYPES,NULL);
                    } else{

                        tmpIdentifier->dataType = CHARACTER_DATA_TYPE;

                        //GERAÇÃO CÓDIGO

                        //Reserva memoria p/ id tipo caracter ou hexa
                        memAlloc(&tmpIdentifier->address, BYTE, STANDARD_MEMORY_REGION);

                        //Format instrução
                        if( currentSymbol->type == CHARACTER_CONST )
                            writeInstruction("\tbyte %d ;const caract em %d\n", 2, currentSymbol->lexeme[1], tmpIdentifier->address);
                        else
                            writeInstruction("\tbyte %d ;const caract em %d\n", 2, hex2int(substr(currentSymbol->lexeme,1,3)), tmpIdentifier->address);
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
            if( currentSymbol->type == NUMBER_CONST ){

                if( inhDType == INTEGER_DATA_TYPE ){

                    if( ! signal )
                        signal = 1;

                    int value = withinLimitOfInteger(signal);

                    //GERAÇÃO DE CÓDIGO

                    //Reserva de memoria p/ id var inteira
                    memAlloc(&tmpIdentifier->address, SWORD, STANDARD_MEMORY_REGION);

                    //Escreve instrução asm
                    writeInstruction("\tsword %d ;var int em %d\n", 2, value, tmpIdentifier->address);


                } else{
                    compilerror(ERR_INCOMPATIBLE_TYPES,NULL);
                }

            }//constante literal caracter ou hexadecimal
            else if( currentSymbol->type == CHARACTER_CONST || currentSymbol->type == HEX_CONST ){

                if( ! signal && inhDType == CHARACTER_DATA_TYPE ){

                    //GERAÇÃO DE CÓDIGO

                    //Reserva memoria p/ id
                    memAlloc(&tmpIdentifier->address, BYTE, STANDARD_MEMORY_REGION);

                    //Format instrução
                    if( currentSymbol->type == CHARACTER_CONST )
                        writeInstruction("\tbyte %d ;const caract em %d\n", 2, currentSymbol->lexeme[1], tmpIdentifier->address);
                    else
                        writeInstruction("\tbyte %d ;const caract em %d\n", 2, hex2int(substr(currentSymbol->lexeme,1,3)), tmpIdentifier->address);

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

            if( currentSymbol->type == NUMBER_CONST ){

                tmpIdentifier->arraySize = withinArraySizeBounds();

                //GERAÇÃO DE CÓDIGO

                if( tmpIdentifier->dataType == INTEGER_DATA_TYPE ){

                    //Reserva memoria p/ id
                    memAlloc(&tmpIdentifier->address, (tmpIdentifier->arraySize + tmpIdentifier->arraySize ), STANDARD_MEMORY_REGION );

                    //Escreve instrução asm
                    writeInstruction("\tsword %d DUP(?) ;var vet int em %d\n", 2, tmpIdentifier->arraySize, tmpIdentifier->address);

                } else{

                    //Reserva memoria p/ id char
                    memAlloc(&tmpIdentifier->address, tmpIdentifier->arraySize, STANDARD_MEMORY_REGION);

                    //Escreve instrução asm
                    writeInstruction("\tbyte %d DUP(?) ;var vet caract em %d\n", 2, tmpIdentifier->arraySize, tmpIdentifier->address);

                }

            } else{
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);
            }
        }

        matchTok(TOK_CONSTANT);
        matchTok(TOK_R_BRACE);
    }
    else{

        //GERAÇÃO DE CÓDIGO

        if( tmpIdentifier->dataType == INTEGER_DATA_TYPE ){

            //Reserva memoria p/ id
            memAlloc(&tmpIdentifier->address, SWORD, STANDARD_MEMORY_REGION);

            //Escreve instrução asm
            writeInstruction("\tsword ? ;var int em %d\n", 1, tmpIdentifier->address);

        } else{

            //Reserva memoria p/ id
            memAlloc(&tmpIdentifier->address, BYTE, STANDARD_MEMORY_REGION);

            //Escreve instrução asm
            writeInstruction("\tbyte ? ;var caract em %d\n", 1, tmpIdentifier->address);
        }
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
        Symbol* tempIdentifier = currentSymbol;

        checkVarDeclaration();

        //Atributos sintetizados
        int s = tempIdentifier->arraySize;
        data_type t = tempIdentifier->dataType;
        int address = tempIdentifier->address;

        matchTok(TOK_IDENTIFIER);

        bool isIndexedArray = FALSE;

        if( currentSymbol->tok == TOK_L_BRACE ){

            //Verifica compatibilidade de classes de identificadores
            checkClassCompatibility(tempIdentifier);

            //Verifica se identificador é do tipo arranjo
            if( tempIdentifier->arraySize == 0 )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

            matchTok(TOK_L_BRACE);

            //Atributos sintetizados
            int s1 = 0;
            data_type t1 = INTEGER_DATA_TYPE;
            int address1 = 0;

            expression(&s1,&t1,&address1);

            if( t1 != INTEGER_DATA_TYPE )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

            matchTok(TOK_R_BRACE);

            s = 0;

            isIndexedArray = TRUE;

            //Geração de código
            writeInstruction("\tmov ax, DS:[%d]\n", 1, address1);

            if( t == INTEGER_DATA_TYPE )
                writeInstruction("\tadd ax, ax\n", 0);

            writeInstruction("\tpush ax\n", 0);

        }

        matchTok(TOK_ASSIGN);

        //Atributos sintetizados
        int s1 = 0;
        data_type t1 = INTEGER_DATA_TYPE;
        int address1 = 0;

        expression(&s1,&t1,&address1);

        if( t != t1 || ( !( s && s1 ) && ( s || s1 )  ) )
            compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

        //Geração de código
        writeInstruction("\tmov si, %d\n", 1, address);

        //Se ponteiro
        if( s != 0 ){

            //Se ponteiro de inteiro, erro!
            if( t == INTEGER_DATA_TYPE)
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

            //Se ponteiro de caracter
            string labelR0 = newLabel();
            string finalLabel = newLabel();

            writeInstruction("\tmov di, DS:[%d]\n", 1, address1);
            writeInstruction("\tmov ah, 0\n", 0);
            writeInstruction("%s:\n", 1, labelR0);
            writeInstruction("\tmov al, DS:[di]\n", 0);
            writeInstruction("\tmov DS:[si], al\n", 0);
            writeInstruction("\tcmp ax, 024h\n", 0);
            writeInstruction("\tje %s\n", 1, finalLabel);
            writeInstruction("\tadd si, 1\n",0);
            writeInstruction("\tadd di, 1\n",0);
            writeInstruction("\tjmp %s\n", 1, labelR0);
            writeInstruction("%s:\n", 1, finalLabel);

        }//Se escalar
        else{

            if( isIndexedArray ){
                writeInstruction("\tpop ax\n", 0);
                writeInstruction("\tadd si, ax\n", 0);
            }

            if( t == INTEGER_DATA_TYPE ){
                writeInstruction("\tmov ax, DS:[%d]\n", 1, address1 );
                writeInstruction("\tmov DS:[si], ax\n", 0);
            } else{
                writeInstruction("\tmov ah, 0\n", 0);
                writeInstruction("\tmov al, DS:[%d]\n", 1, address1 );
                writeInstruction("\tmov DS:[si], al\n", 0);
            }
        }

        matchTok(TOK_SEMICOLON);

    }//Delimitador de comandos ";"
    else{
        matchTok(TOK_SEMICOLON);
    }
}

PRIVATE void cmdif(){

    matchTok(TOK_IF);

    //Atributos sintetizados
    int s = 0;
    data_type t = INTEGER_DATA_TYPE;
    int address = 0;

    expression(&s,&t,&address);

    if( t != INTEGER_DATA_TYPE )
        compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

    string labelFalse = newLabel();
    string labelFinal = newLabel();

    writeInstruction("\tmov ah, 0\n", 0);
    writeInstruction("\tmov al, DS:[%d]\n" , 1, address);
    writeInstruction("\tcmp ax, 0\n", 0);
    writeInstruction("\tje %s\n", 1, labelFalse);

    matchTok(TOK_THEN);
    body();

    //Comando else opcional
    if( currentSymbol->tok == TOK_ELSE ){
        matchTok(TOK_ELSE);

        writeInstruction("\tjmp %s\n", 1, labelFinal);
        writeInstruction("%s:\n", 1, labelFalse);

        body();

        writeInstruction("%s:\n", 1, labelFinal);

    } else{
        writeInstruction("%s:\n", 1, labelFalse);
    }
}

PRIVATE void cmdfor(){

    matchTok(TOK_FOR);

    checkVarDeclaration();

    Symbol* tempIdentifier = currentSymbol;

    //Verifica compatibilidade de classes de identificadores
    if( currentSymbol->tok == TOK_IDENTIFIER ){
        checkClassCompatibility(currentSymbol);

        //Se o tipo do identificador for diferente de inteiro, erro!
        if( currentSymbol->dataType != INTEGER_DATA_TYPE || currentSymbol->arraySize != 0 )
            compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

    }

    matchTok(TOK_IDENTIFIER);
    matchTok(TOK_ASSIGN);

    //Atributos sintetizados
    int s = 0;
    data_type t = INTEGER_DATA_TYPE;
    int address = 0;

    expression(&s,&t,&address);

    if( t != INTEGER_DATA_TYPE || s != 0 )
        compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

    writeInstruction("\tmov ax, DS:[%d]\n", 1, address);
    writeInstruction("\tmov DS:[%d], ax\n", 1, tempIdentifier->address);

    matchTok(TOK_TO);

    s = 0;
    t = INTEGER_DATA_TYPE;
    address = 0;

    expression(&s,&t,&address);

    if( t != INTEGER_DATA_TYPE || s != 0 )
        compilerror(ERR_INCOMPATIBLE_TYPES,NULL);


    string labelStart = newLabel();
    string labelFinal = newLabel();

    writeInstruction("%s:\n", 1, labelStart);
    writeInstruction("\tmov ax, DS:[%d]\n", 1, address);
    writeInstruction("\tcmp DS:[%d], ax\n", 1, tempIdentifier->address);
    writeInstruction("\tjg %s\n", 1, labelFinal);
    writeInstruction("\tmov ax, 1\n",0);

    //Instrução step opcional
    if( currentSymbol->tok == TOK_STEP ){

        matchTok(TOK_STEP);

        int signal = 1;
        switch (currentSymbol->tok){
            case TOK_MINUS:
                signal = -1;
            case TOK_PLUS:
                matchTok(currentSymbol->tok);
            default:
                break;
        }

        //Senão for constante numérica, erro!
        if( currentSymbol->tok == TOK_CONSTANT && currentSymbol->type != NUMBER_CONST )
            compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

        int constValue = atoi(currentSymbol->lexeme) * signal;

        writeInstruction("\tmov bx, %d\n", 1, constValue);
        writeInstruction("\timul bx\n", 0);

        matchTok(TOK_CONSTANT);
    }

    writeInstruction("\tpush ax\n", 0);

    matchTok(TOK_DO);
    body();

    writeInstruction("\tpop ax\n", 0);
    writeInstruction("\tadd DS:[%d], ax\n", 1, tempIdentifier->address);
    writeInstruction("\tjmp %s\n", 1, labelStart);
    writeInstruction("%s:\n", 1, labelFinal);
}

PRIVATE void cmdio(){

    //Atributos sintetizados
    int s = 0;
    data_type t = INTEGER_DATA_TYPE;
    int address = 0;

    if( currentSymbol->tok == TOK_READLN ){

        matchTok(TOK_READLN);
        matchTok(TOK_L_PAREN);

        checkVarDeclaration();

        //Verifica compatibilidade de classes de identificadores
        if( currentSymbol->tok == TOK_IDENTIFIER )
            checkClassCompatibility(currentSymbol);

        Symbol* tempIdentifier = currentSymbol;

        s = tempIdentifier->arraySize;
        t = tempIdentifier->dataType;
        address = tempIdentifier->address;

        matchTok(TOK_IDENTIFIER);

        bool isIndexedArray = FALSE;

        if( currentSymbol->tok == TOK_L_BRACE ){

            //Se identificador não for do tipo arranjo,ERRO!
            if( tempIdentifier->arraySize == 0 )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

            //Atributos sintetizados
            int s1 = 0;
            data_type t1 = INTEGER_DATA_TYPE;
            int address1 = 0;

            matchTok(TOK_L_BRACE);
            expression(&s1,&t1,&address1);
            matchTok(TOK_R_BRACE);

            //Se índice do arranjo não for uma valor inteiro,ERRO!
            if( t1 != INTEGER_DATA_TYPE )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

            s = 0;//Marca arranjo

            isIndexedArray = TRUE;

            //Geração de código

            //Calcula o valor do indice do arranjo
            writeInstruction("\tmov ax, DS:[%d]\n", 1, address1);

            if( t == INTEGER_DATA_TYPE )
                writeInstruction("\tadd ax, ax\n", 0);

            writeInstruction("\tpush ax\n", 0);

        }

        //Geração de código
        writeInstruction("\tmov si, %d\n", 1, address);

        int tempIN = 0;//temporario p/ buffer de entrada

        //Se ponteiro
        if( s ){

            if( t == INTEGER_DATA_TYPE )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

            writeInstruction("\n\t; leitura de string\n", 0);

            //Define tamanho do buffer de entrada
            memAlloc(&tempIN, INPUT_STRING_SIZE, TEMP_MEMORY_REGION);

            //Leitura do DOS
            writeInstruction("\tmov dx, %d\n", 1, tempIN);
            writeInstruction("\tmov al, 0FFh\n", 0);
            writeInstruction("\tmov DS:[%d], al\n", 1, tempIN);
            writeInstruction("\tmov ah, 0Ah\n", 0);
            writeInstruction("\tint 21h\n", 0);

            //Quebra de linha
            writeInstruction("\tmov ah, 02h\n", 0);
            writeInstruction("\tmov dl, 0Dh\n", 0);
            writeInstruction("\tint 21h\n", 0);
            writeInstruction("\tmov dl, 0Ah\n", 0);
            writeInstruction("\tint 21h\n", 0);

            string labelR0 = newLabel();
            string labelFinal = newLabel();

            //Atribui string à variável
            writeInstruction("\tmov di, %d\n", 1, tempIN + 2 );
            writeInstruction("%s:\n", 1, labelR0);
            writeInstruction("\tmov ax, DS:[di]\n", 0);
            writeInstruction("\tcmp ax, 0Dh\n", 1);
            writeInstruction("\tje %s\n", 1, labelFinal);
            writeInstruction("\tmov ah, 0\n", 0);
            writeInstruction("\tmov al, DS:[di]\n", 0);
            writeInstruction("\tmov DS:[si], ax\n", 0);
            writeInstruction("\tadd si, 1\n",0);
            writeInstruction("\tadd di, 1\n",0);
            writeInstruction("\tjmp %s\n", 1, labelR0);
            writeInstruction("%s:\n", 1, labelFinal);
            writeInstruction("\tmov ah, 0\n", 0);
            writeInstruction("\tmov al, 024h\n", 0);

            //adiciona fim de string
            writeInstruction("\tmov DS:[si], al\n", 0);

        }//Senão escalar
        else{

            if( t == INTEGER_DATA_TYPE ){

                string labelR0 = newLabel();
                string  labelR1 = newLabel();
                string  labelR2 = newLabel();

                memAlloc(&tempIN, INPUT_INTEGER_SIZE, TEMP_MEMORY_REGION);

                //Leitura do DOS
                writeInstruction("\tmov dx, %d\n", 1, tempIN);
                writeInstruction("\tmov al, 0FFh\n", 0);
                writeInstruction("\tmov DS:[%d], al\n", 1, tempIN);
                writeInstruction("\tmov ah, 0Ah\n", 0);
                writeInstruction("\tint 21h\n", 0);

                //Quebra de linha
                writeInstruction("\tmov ah, 02h\n", 0);
                writeInstruction("\tmov dl, 0Dh\n", 0);
                writeInstruction("\tint 21h\n", 0);
                writeInstruction("\tmov dl, 0Ah\n", 0);
                writeInstruction("\tint 21h\n", 0);

                //Conversão de string p/ inteiro
                writeInstruction("\tmov di, %d\n", 1, tempIN + 2);
                writeInstruction("\tmov ax, 0\n", 0);
                writeInstruction("\tmov cx, 10\n", 0);
                writeInstruction("\tmov dx, 1\n", 0);
                writeInstruction("\tmov bh, 0\n", 0);
                writeInstruction("\tmov bl, DS:[di]\n", 0);
                writeInstruction("\tcmp bx, 2Dh\n", 0);
                writeInstruction("\tjne %s\n", 1, labelR0);
                writeInstruction("\tmov dx, -1\n", 0);
                writeInstruction("\tadd di, 1\n", 0);
                writeInstruction("\tmov bl, DS:[di]\n", 0);
                writeInstruction("%s:\n", 1, labelR0);
                writeInstruction("\tpush dx\n", 0);
                writeInstruction("\tmov dx, 0\n", 0);
                writeInstruction("%s:\n", 1, labelR1);
                writeInstruction("\tcmp bx, 0Dh\n", 0);
                writeInstruction("\tje %s\n", 1, labelR2);
                writeInstruction("\timul cx\n", 0);
                writeInstruction("\tadd bx, -48\n", 0);
                writeInstruction("\tadd ax, bx\n", 0);
                writeInstruction("\tadd di, 1\n", 0);
                writeInstruction("\tmov bh, 0\n", 0);
                writeInstruction("\tmov bl, DS:[di]\n", 0);
                writeInstruction("\tjmp %s\n", 1, labelR1);
                writeInstruction("%s:\n", 1, labelR2);
                writeInstruction("\tpop cx\n", 0);
                writeInstruction("\timul cx\n", 0);

                if( isIndexedArray ){
                    writeInstruction("\tpop bx\n", 0);
                    writeInstruction("\tadd si, bx\n", 0);
                }

                //Atribui inteiro à variável
                writeInstruction("\tmov DS:[si], ax\n", 0);

            } else{

                memAlloc(&tempIN, INPUT_CHAR_SIZE, TEMP_MEMORY_REGION);

                //Leitura do DOS
                writeInstruction("\tmov dx, %d\n", 1, tempIN);
                writeInstruction("\tmov al, 0FFh\n", 0);
                writeInstruction("\tmov DS:[%d], al\n", 1, tempIN);
                writeInstruction("\tmov ah, 0Ah\n", 0);
                writeInstruction("\tint 21h\n", 0);

                //Quebra de linha
                writeInstruction("\tmov ah, 02h\n", 0);
                writeInstruction("\tmov dl, 0Dh\n", 0);
                writeInstruction("\tint 21h\n", 0);
                writeInstruction("\tmov dl, 0Ah\n", 0);
                writeInstruction("\tint 21h\n", 0);

                if( isIndexedArray ){
                    writeInstruction("\tpop bx\n", 0);
                    writeInstruction("\tadd si, bx\n", 0);
                }

                //Atribui caracter à variável
                writeInstruction("\tmov di, %d\n", 1, tempIN + 2 );
                writeInstruction("\tmov ah, 0\n", 0);
                writeInstruction("\tmov al, DS:[di]\n", 0);
                writeInstruction("\tmov DS:[si], al\n", 0);

            }
        }

        matchTok(TOK_R_PAREN);

    } else if( currentSymbol->tok == TOK_WRITE || currentSymbol->tok == TOK_WRITELN ){

        int cmd = currentSymbol->tok;

        matchTok(currentSymbol->tok);
        matchTok(TOK_L_PAREN);

        //Lista de argumentos opcional
        do {

            s = 0;
            t = INTEGER_DATA_TYPE;
            address = 0;

            expression(&s, &t, &address);

            if( s != 0 ){

                writeInstruction("\tmov dx, DS:[%d]\n", 1, address);

            }else{

                int tempOUT;//temporario p/ buffer de saída

                if( t == INTEGER_DATA_TYPE ){

                    string labelR0 = newLabel();
                    string  labelR1 = newLabel();
                    string labelR2 = newLabel();

                    memAlloc(&tempOUT, OUTPUT_INTEGER_SIZE, TEMP_MEMORY_REGION);

                    writeInstruction("\tmov ax, DS:[%d]\n",1, address);
                    writeInstruction("\tmov di, %d\n",1, tempOUT);
                    writeInstruction("\tmov cx, 0\n",0);
                    writeInstruction("\tcmp ax, 0\n",0);
                    writeInstruction("\tjge %s\n",1,labelR0);
                    writeInstruction("\tmov bl, 2Dh\n",0);
                    writeInstruction("\tmov DS:[di], bl\n",0);
                    writeInstruction("\tadd di, 1\n",0);
                    writeInstruction("\tneg ax\n",0);
                    writeInstruction("%s:\n",1,labelR0);
                    writeInstruction("\tmov bx, 10\n",0);
                    writeInstruction("%s:\n",1,labelR1);
                    writeInstruction("\tadd cx, 1\n",0);
                    writeInstruction("\tmov dx, 0\n",0);
                    writeInstruction("\tidiv bx\n",0);
                    writeInstruction("\tpush dx\n",0);
                    writeInstruction("\tcmp ax, 0\n",0);
                    writeInstruction("\tjne %s\n",1,labelR1);
                    writeInstruction("%s:\n",1,labelR2);
                    writeInstruction("\tpop dx\n",0);
                    writeInstruction("\tadd dx, 30h\n",0);
                    writeInstruction("\tmov DS:[di], dl\n",0);
                    writeInstruction("\tadd di, 1\n",0);
                    writeInstruction("\tadd cx, -1\n",0);
                    writeInstruction("\tcmp cx, 0\n",0);
                    writeInstruction("\tjne %s\n",1,labelR2);
                    writeInstruction("\tmov dl, 024h\n",0);
                    writeInstruction("\tmov DS:[di], dl\n",0);
                    writeInstruction("\tmov dx, %d\n",1, tempOUT);

                } else{

                    memAlloc(&tempOUT, OUTPUT_CHAR_SIZE, TEMP_MEMORY_REGION);
                    writeInstruction("\tmov ah, 024h\n", 0);
                    writeInstruction("\tmov al, DS:[%d]\n", 1, address);
                    writeInstruction("\tmov DS:[%d], ax \n", 1, tempOUT );
                    writeInstruction("\tmov dx, %d\n", 1, tempOUT);

                }
            }

            writeInstruction("\tmov ah, 09h\n",0);
            writeInstruction("\tint 21h\n",0);

        }while ( currentSymbol->tok == TOK_COMMA ? matchTok(TOK_COMMA),TRUE : FALSE );

        if( cmd == TOK_WRITELN ){
            writeInstruction("\tmov ah, 02h\n",0);
            writeInstruction("\tmov dl, 0Dh\n",0);
            writeInstruction("\tint 21h\n",0);
            writeInstruction("\tmov dl, 0Ah\n",0);
            writeInstruction("\tint 21h\n",0);
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

PRIVATE void expression(int* s , data_type* t, int* address){

    //Atributos sintetizados
    int s1 = 0; data_type t1 = INTEGER_DATA_TYPE; int address1 = 0;
    int s2 = 0; data_type t2 = INTEGER_DATA_TYPE; int address2 = 0;

    int operator;

    term(&s1,&t1,&address1);

    *s = s1;
    *t = t1;
    *address = address1;

    while ( currentSymbol->tok == TOK_EQ || currentSymbol->tok == TOK_NE ||
            currentSymbol->tok == TOK_GE || currentSymbol->tok == TOK_GT ||
            currentSymbol->tok == TOK_LE || currentSymbol->tok == TOK_LT ){

        //salva o operador binário
        operator = currentSymbol->tok;

        matchTok(currentSymbol->tok);

        term(&s2,&t2,&address2);

        if( (!( s1 && s2 ) && ( s1 || s2 ) ) || // term.size xor term1.size or
            (!( t1 && t2 ) && ( t1 || t2 ) ) || // term.tipo xor term1.tipo or
            ( s1 && t1 ) || // term.size == 1 (ARRAY) and term.tipo == INTEGER or
            ( ( !t1 && s1 ) && ( operator != TOK_EQ && operator != TOK_NE ) ) ) //caracter and array and op != EQ and op != NE
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

        string labelR0 = newLabel();
        string labelR1 = newLabel();
        string finalLabel = newLabel();

        //Ponteiro
        if( *s != 0 ){

            //Reg A
            writeInstruction("\tmov si, DS:[%d]\n", 1, *address);
            //Reg B
            writeInstruction("\tmov di, DS:[%d]\n", 1, address2 );

            writeInstruction("\tmov ah, 0\n", 0);
            writeInstruction("\tmov bh, 0\n",0);
            writeInstruction("%s:\n",1,labelR0);
            writeInstruction("\tmov al, DS:[si]\n",0);
            writeInstruction("\tmov bl, DS:[di]\n",0);
            writeInstruction("\tadd si, 1\n",0);
            writeInstruction("\tadd di, 1\n",0);
            writeInstruction("\tneg al\n", 0);
            writeInstruction("\tadd al, bl\n",0);
            writeInstruction("\tcmp ax, 0\n",0);
            writeInstruction("\tjne %s\n",1, labelR1 );
            writeInstruction("\tcmp bx, 024h\n",0);
            writeInstruction("\tjne %s\n",1, labelR0);
            writeInstruction("\tmov al, %d\n", 1, (operator == TOK_EQ ? 1 : 0) );
            writeInstruction("\tjmp %s\n", 1, finalLabel);
            writeInstruction("%s:\n", 1, labelR1);
            writeInstruction("\tmov al, %d\n", 1, (operator == TOK_EQ ? 0 : 1));

        }//Escalar
        else {

            //Reg A
            writeInstruction("\tmov ax, DS:[%d]\n", 1, *address);
            //Reg B
            writeInstruction("\tmov bx, DS:[%d]\n", 1, address2);

            //Converte reg A e reg B em inteiros
            writeInstruction("\tmov ah, 0\n", 0);
            writeInstruction("\tmov bh, 0\n", 0);

            //Compara reg A e reg B
            writeInstruction("\tcmp ax, bx\n", 0);

            if (operator == TOK_EQ) {
                writeInstruction("\tje %s\n", 1, labelR0);
            } else if (operator == TOK_NE) {
                writeInstruction("\tjne %s\n", 1, labelR0);
            } else if (operator == TOK_LT) {
                writeInstruction("\tjl %s\n", 1, labelR0);
            } else if (operator == TOK_GT) {
                writeInstruction("\tjg %s\n", 1, labelR0);
            } else if (operator == TOK_GE) {
                writeInstruction("\tjge %s\n", 1, labelR0);
            } else if (operator == TOK_LE) {
                writeInstruction("\tjle %s\n", 1, labelR0);
            }

            writeInstruction("%s:\n",1,labelR1);
            writeInstruction("\tmov al, 0\n",0);
            writeInstruction("\tjmp %s\n", 1, finalLabel);
            writeInstruction("%s:\n", 1, labelR0);
            writeInstruction("\tmov al, 1\n", 0);

        }

        writeInstruction("%s:\n", 1, finalLabel);
        memAlloc(address, BYTE, TEMP_MEMORY_REGION);
        writeInstruction("\tmov DS:[%d], al\n",1, *address);


        //Operadores relacionais geram tipos lógicos(implicitos) = INTEIROS
        *s = 0;
        *t = INTEGER_DATA_TYPE;

    }
}

PRIVATE void term(int* s, data_type* t, int* address ){

    //Atributos sintetizados
    int s1 = 0; data_type t1 = INTEGER_DATA_TYPE; int address1 = 0;
    int s2 = 0; data_type t2 = INTEGER_DATA_TYPE; int address2 = 0;
    int operator;

    bool signal = FALSE;
    switch (currentSymbol->tok){
        case TOK_MINUS:
            signal = TRUE;
        case TOK_PLUS:
            matchTok(currentSymbol->tok);
        default:
            break;
    }

    factor(&s1,&t1,&address1);

    if( signal ){

        writeInstruction("\tmov ax, DS:[%d]\n", 1, address1);
        writeInstruction("\tneg ax\n",0);
        memAlloc(&address1, SWORD, TEMP_MEMORY_REGION);
        writeInstruction("\tmov DS:[%d], ax\n", 1, address1);
    }

    *s = s1;
    *t = t1;
    *address = address1;

    while ( currentSymbol->tok == TOK_PLUS || currentSymbol->tok == TOK_MINUS ||currentSymbol->tok == TOK_OR ){

        operator = currentSymbol->tok;

        matchTok(currentSymbol->tok);

        factor(&s2,&t2,&address2);

        //Se tipo for diferente de inteiro escalar, erro!
        if( ( !t1 || s1 ) || ( !t2 || s2 ) )
            compilerror(ERR_INCOMPATIBLE_TYPES,"term");

        //Reg A
        writeInstruction("\tmov ax, DS:[%d]\n", 1, *address);

        //Reg B
        writeInstruction("\tmov bx, DS:[%d]\n", 1, address2);

        memAlloc(address, SWORD, TEMP_MEMORY_REGION);

        switch (operator){

            case TOK_PLUS:
            case TOK_OR:
                writeInstruction("\tadd ax, bx\n", 0);
                break;
            case TOK_MINUS:
                writeInstruction("\tneg bx\n", 0);
                writeInstruction("\tadd ax, bx\n", 0);
                break;
            default:
                break;
        }

        writeInstruction("\tmov DS:[%d], ax\n", 1, *address);


    }
}

PRIVATE void factor(int* s, data_type* t, int* address ){

    //Atributos sintetizados
    int s1 = 0; data_type t1 = INTEGER_DATA_TYPE; int address1 = 0;
    int s2 = 0; data_type t2 = INTEGER_DATA_TYPE; int address2 = 0;
    int operator;

    e(&s1,&t1,&address1);

    *s = s1;
    *t = t1;
    *address = address1;

    while ( currentSymbol->tok == TOK_TIMES || currentSymbol->tok == TOK_OVER || currentSymbol->tok == TOK_MOD || currentSymbol->tok == TOK_AND ){

        operator = currentSymbol->tok;

        matchTok(currentSymbol->tok);

        e(&s2,&t2,&address2);

        //Se tipo for diferente de inteiro escalar, erro!
        if( ( !t1 || s1 ) || ( !t2 || s2 ) )
            compilerror(ERR_INCOMPATIBLE_TYPES,"factor");

        //Reg A
        writeInstruction("\tmov ax, DS:[%d]\n", 1, *address);

        //Reg B
        writeInstruction("\tmov bx, DS:[%d]\n", 1, address2);

        memAlloc(address, SWORD, TEMP_MEMORY_REGION);

        switch (operator){

            case TOK_TIMES:
            case TOK_AND:
                writeInstruction("\timul bx\n", 0);
                writeInstruction("\tmov DS:[%d], ax\n", 1, *address);
                break;
            case TOK_OVER:
                writeInstruction("\tmov dx, 0\n", 0);
                writeInstruction("\tidiv bx\n", 0);
                writeInstruction("\tmov DS:[%d], ax\n", 1, *address);
                break;
            case TOK_MOD:
                writeInstruction("\tmov dx, 0\n", 0);
                writeInstruction("\tidiv bx\n", 0);
                writeInstruction("\tmov DS:[%d], dx\n", 1, *address);
                break;
            default:
                break;
        }
    }
}

PRIVATE void e(int* s, data_type* t, int* address){

    //Atributos sintetizados
    int s1 = 0; data_type t1 = INTEGER_DATA_TYPE; int address1 = 0;

    if( currentSymbol->tok == TOK_L_PAREN ){

        matchTok(TOK_L_PAREN);

        expression(&s1,&t1,&address1);

        *s = s1;
        *t = t1;
        *address = address1;

        matchTok(TOK_R_PAREN);

    } else if( currentSymbol->tok == TOK_NOT  ){

        matchTok(TOK_NOT);

        e(&s1,&t1,&address1);

        if( t1 != INTEGER_DATA_TYPE )
            compilerror(ERR_INCOMPATIBLE_TYPES," Op.Not ");

        *s = s1;
        *t = t1;

        memAlloc(address, BYTE, TEMP_MEMORY_REGION);
        writeInstruction("\tmov ah, 0\n", 0);
        writeInstruction("\tmov al, DS:[%d]\n", 1, address1);
        writeInstruction("\tneg al\n", 0);
        writeInstruction("\tadd al, 1\n", 0);
        writeInstruction("\tmov DS:[%d], al\n", 1, *address);


    } else if( currentSymbol->tok == TOK_CONSTANT ){

        if( currentSymbol->type == NUMBER_CONST ){
            *t = INTEGER_DATA_TYPE;

            //Geração de código
            int constValue = atoi(currentSymbol->lexeme);

            writeInstruction("\tmov ax, %d\n", 1, constValue);
            memAlloc(address, SWORD, TEMP_MEMORY_REGION);
            writeInstruction("\tmov DS:[%d], ax\n", 1, *address);

        } else if( currentSymbol->type == CHARACTER_CONST || currentSymbol->type == HEX_CONST ){
            *t = CHARACTER_DATA_TYPE;

            //Geração de código
            writeInstruction("\tmov ah, 0\n", 0);

            //Converte o valor inteiro de um caracter em seu respectivo valor hexadecimal
            if( currentSymbol->type == CHARACTER_CONST )
                writeInstruction("\tmov al, %s\n", 1, int2str(currentSymbol->lexeme[1]) );
            else
                writeInstruction("\tmov al, %s\n", 1, currentSymbol->lexeme );

            memAlloc(address, BYTE, TEMP_MEMORY_REGION);
            writeInstruction("\tmov DS:[%d], al\n", 1, *address);

        } else{

            //Adiciona o caracter fim de string '$'
            string newStr = strInject( currentSymbol->lexeme, "$", currentSymbol->size - 1 );

            //Libera lexema sem '$'
            free(currentSymbol->lexeme);

            //referencia o novo lexema
            currentSymbol->lexeme = newStr;

            *t = CHARACTER_DATA_TYPE;

            //Aceita string vazia. Subtrai -2 para retirar as aspas da contagem
            *s = currentSymbol->size = strlen(currentSymbol->lexeme) - 2;

            //Reserva memória na area de dados p/ um literal string
            memAlloc( address, *s, STANDARD_MEMORY_REGION );

            //Declara literal string na area de dados
            writeInstruction("\ndseg SEGMENT PUBLIC ; inicio seg. dados\n", 0);
            writeInstruction("\tbyte %s ;const string em %d\n", 2, currentSymbol->lexeme, *address);
            writeInstruction("dseg ENDS ;fim seg. dados\n\n", 0);

            writeInstruction("\tmov si, %d\n", 1, *address );
            memAlloc( address, SWORD, TEMP_MEMORY_REGION );
            writeInstruction("\tmov DS:[%d], si\n", 1, *address);
        }

        matchTok(TOK_CONSTANT);

    } else{

        //Armazena o identificador para uso posterior
        Symbol * tempIdentifier = currentSymbol;

        //Se identificador não foi declarado, erro!
        checkVarDeclaration();

        *s = tempIdentifier->arraySize;
        *t = tempIdentifier->dataType;
        *address = tempIdentifier->address;

        matchTok(TOK_IDENTIFIER);

        bool isIndexedArray = FALSE;

        if( currentSymbol->tok == TOK_L_BRACE ){

            //Se identificador for da classe constante, erro!
            checkClassCompatibility(tempIdentifier);

            //Se identificador for escalar, ERRO!
            if( tempIdentifier->arraySize == 0 )
                compilerror(ERR_INCOMPATIBLE_TYPES," Var.scalar ");

            matchTok(TOK_L_BRACE);
            expression(&s1,&t1,&address1);
            matchTok(TOK_R_BRACE);

            //Se exp for diferente do tipo inteiro
            if( t1 != INTEGER_DATA_TYPE )
                compilerror(ERR_INCOMPATIBLE_TYPES," No.int.type ");

            *s = 0;

            isIndexedArray = TRUE;

            //Geração de código

            //Calcula o valor do indice do arranjo
            writeInstruction("\tmov ax, DS:[%d]\n", 1, address1);

            if( *t == INTEGER_DATA_TYPE )
                writeInstruction("\tadd ax, ax\n", 0);
        }

        //Geração de código
        writeInstruction("\tmov si, %d\n", 1, *address);

        //Se ponteiro
        if( *s ){

            if( *t == INTEGER_DATA_TYPE )
                compilerror(ERR_INCOMPATIBLE_TYPES,NULL);

            memAlloc(address, SWORD, TEMP_MEMORY_REGION);
            writeInstruction("\tmov DS:[%d], si\n", 1, *address);


        }//Senão escalar
        else{

            if( isIndexedArray )
                writeInstruction("\tadd si, ax\n", 0);

            if( *t == INTEGER_DATA_TYPE ){

                writeInstruction("\tmov ax, DS:[si]\n", 0);
                memAlloc(address, SWORD, TEMP_MEMORY_REGION);
                writeInstruction("\tmov DS:[%d], ax\n", 1, *address);

            } else{

                writeInstruction("\tmov ah, 0\n", 0);
                writeInstruction("\tmov al, DS:[si]\n", 0);
                memAlloc(address, BYTE, TEMP_MEMORY_REGION);
                writeInstruction("\tmov DS:[%d], al\n", 1, *address);

            }
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

    //Se usuário não fornecer o nome do arquivo intermediário, ex: nome_arquivo.asm,
    //criar um arquivo: a.asm como padrão
    if( argc == 2 ) {
        generateCode("a.asm");//salva as instruções no arquivo a.asm
    }
    //Senão, verificar o nome completamente qualificado do arquivo intermediário
    else{

        if( ! evalFileExt(argv[2],".asm") )
            compilerror(ERR_COULD_NOT_CREATE_INTERMEDIATE_CODE_FILE,NULL);

        generateCode(argv[2]);//salva as instruções no arquivo fornecido pelo usuario
    }

    return 0;
}