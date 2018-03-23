//
// Created by Daniel on 22/03/2018.
//

#include "lex.h"

PRIVATE bool evalFileExt(string fileName){

    int length = strlen(fileName);
    if( length < 3 )
        return FALSE;
    return ( fileName[length-1] == 'l' && fileName[length-2] == '.' ? TRUE : FALSE );
}

PRIVATE inline bool fileExists(string fileName){
    return (access( fileName, F_OK ) != -1 ? TRUE : FALSE);
}

PRIVATE inline void fillBuff(char chr){
    if( buffindex < VAR_LEN_MAX ){
        buffchr[buffindex++] = chr;
    } else{
        compilerror(ERR_VAR_LEN,NULL);
    }
}

PRIVATE inline void closeBuff(){
    buffchr[buffindex] = '\0';
}

PRIVATE inline void ignoreWs(){
    while ( isspace(*prog) && *prog ){
        if( *prog == '\n' ) ++lineCounter;
        ++prog;
    }
}

PRIVATE bool loadProgram( string buff, string fileName ){

    FILE * fp;

    //abre o arquivo bin para leitura
    if( (fp = (fopen(fileName,"rb"))) == NULL )
        return FALSE;

    char chr = (char) getc(fp);

    int i = 0;
    while( ! feof(fp) && i < PROGRAM_LEN_MAX ){
        buff[i] = chr;
        //printf("%c",buff[i]);
        ++i;
        chr = (char) getc(fp);
    }

    buff[i] = '\0';

    prog = buff;//Atribui a primeira posição do arquivo fonte

    fclose(fp);

    return TRUE;
}

PUBLIC Symbol* nextSymbol(){
    //auxilia a criação do registro lexico
    Symbol* symbol = NULL;
    int symbolType = IDENTIFIER;

    buffindex = 0;//zera contador do buffer do lexema

    //Verifica se arquivo chegou ao fim
    if( *prog == '\0' )
        return NULL;

    int state = Q0;//inicia o automato sempre para o estado inicial na chamada da função

    while( state != END ){

        switch ( state ){

            case Q0:

                ignoreWs();//Ignora espaços em branco

                //Reconhece palavra-reservada ou identificador -  teste ok!
                if( *prog == '_' ){
                    state = Q1;
                } else if( isalpha(*prog) ){
                    state = Q2;
                }//Reconhece constantes hexdecimais
                else if( *prog == '0' ){
                    state = Q3;
                }//Reconhece constantes numéricas
                else if( *prog >= '1' && *prog <= '9' ){
                    state = Q8;
                }//Reconhece uma String
                else if( *prog == '\"' ){
                    state = Q9;
                }//Reconhece um literal
                else if( *prog == '\'' ){
                    state = Q11;
                }//Reconhece comentário ou op.divisão
                else if( *prog == '/' ){
                    state = Q13;
                }//Reconhece ops.rel { <, <=, >, >= } ; op.bin { <> } ; op.atribuição { <- }
                else if( *prog == '<' ){
                    state = Q16;
                } else if( *prog == '>' ){
                    state = Q17;
                }//Reconhece um op.aritmético, delimitadores e op.igualdade
                else if( strChr("+-*%[](),;=",*prog) ){
                    fillBuff(*prog);
                    ++prog;
                    state = F;
                }//Fim de arquivo
                else if(*prog == '\0'){
                    return NULL;
                }//Estado de erro do automato
                else{
                    fillBuff(*prog);
                    closeBuff();
                    compilerror(ERR_UNRECOGNIZED_SYMBOL,NULL);
                }
                break;
            case Q1:
                do{
                    fillBuff(*prog);
                }while ( *(++prog) == '_' );
                if( isalnum(*prog) ) {
                    state = Q2;
                }
                else{
                    closeBuff();
                    compilerror(ERR_LEXEME_NOT_FOUND,buffchr);
                }
                break;
            case Q2:
                do{
                    fillBuff(*prog);
                }while ( isalnum(*(++prog)) || *prog == '_' );
                state = F;
                break;
            case Q3:
                fillBuff(*prog);
                if( *(++prog) >= 'A' && *prog <= 'F' ){
                    state = Q4;
                }
                else if( isdigit(*prog) ){
                    state = Q5;
                }
                else{
                    symbolType = NUMBER;
                    state = F;
                }
                break;
            case Q4:
                fillBuff(*prog);
                if( (*(++prog) >= 'A' && *prog <= 'F') || isdigit(*prog) ){
                    state = Q6;
                }else{
                    while ( ! isspace(*prog) ) fillBuff(*prog++);
                    closeBuff();
                    compilerror(ERR_INVALID_HEX_CONST,buffchr);
                }
                break;
            case Q5:
                fillBuff(*prog);
                if( *(++prog) >= 'A' && *prog <= 'F' ){
                    state = Q6;
                }
                else if( isdigit(*prog) ){
                    state = Q7;
                }
                else{
                    symbolType = NUMBER;
                    state = F;
                }
                break;
            case Q6:
                fillBuff(*prog);
                if( *(++prog) == 'h' ){
                    fillBuff(*prog);
                    symbolType = HEX;
                    ++prog;
                    state = F;
                } else{
                    fillBuff(*prog++);
                    while ( ! isspace(*prog) ) fillBuff(*prog++);
                    closeBuff();
                    compilerror(ERR_INVALID_HEX_CONST,buffchr);
                }
                break;
            case Q7:
                fillBuff(*prog);
                if( isdigit(*(++prog)) ){
                    state = Q8;
                } else if( *prog == 'h' ){
                    fillBuff(*prog);
                    symbolType = HEX;
                    ++prog;
                    state = F;
                } else{
                    symbolType = NUMBER;
                    state = F;
                }
                break;
            case Q8:
                do{
                    fillBuff(*prog);
                }while ( isdigit(*(++prog)) );
                symbolType = NUMBER;
                state = F;
                break;
            case Q9:
                while ( isalnum(*(++prog)) || strChr("()[]|\\%&@;,!?*/-+_-<>=:{}'^ ",*prog) ){
                    fillBuff(*prog );
                }
                if( *prog == '\"'){
                    state = Q10;
                }
                else if( *prog == '$' || *prog == '\n'  ){
                    compilerror(ERR_UNRECOGNIZED_SYMBOL,NULL);
                }
                else{
                    compilerror(ERR_UNRECOGNIZED_SYMBOL,NULL);
                }
                break;
            case Q10:
                if( *(++prog) == '\"' ){
                    compilerror(ERR_UNRECOGNIZED_SYMBOL,NULL);
                } else{
                    symbolType = STRING;
                    state = F;
                }
                break;
            case Q11:
                if( isalnum(*(++prog)) || strChr("()[]|\\%&@;,!?*/-+_-<>=:{}\'^\"\n$ ",*prog) ){
                    fillBuff(*prog);
                    state = Q12;
                }
                else{
                    compilerror(ERR_UNRECOGNIZED_SYMBOL,NULL);
                }
                break;
            case Q12:
                if( *(++prog) == '\'' ){
                    symbolType = CHR;
                    ++prog;
                    state = F;
                }
                else{
                    compilerror(ERR_UNTERMINETED_CHARACTER_LITERAL,NULL);
                }
                break;
            case Q13:
                if( *(++prog) == '*' ){
                    state = Q14;
                } else{
                    fillBuff(*(prog-1));
                    state = F;
                }
                break;
            case Q14:;
                while( *(++prog) != '*' );
                state = Q15;
                break;
            case Q15:
                while ( *(++prog) == '*' );
                if( *prog == '/' ){
                    ++prog;
                    state = Q0;
                }//detecta erro lexíco de comentário sem fechamento
                else if( *prog == '\0' ){
                    compilerror(ERR_EOF_NOT_EXPECTED,NULL);
                }
                else {
                    state = Q14;
                }
                break;
            case Q16:
                fillBuff(*prog);
                if( *(++prog) == '>' ){
                    fillBuff(*prog);
                }
                else if( *prog == '-' ){
                    symbolType = KEYWORD;
                    fillBuff(*prog);
                }
                else if( *prog == '=' ){
                    fillBuff(*prog);
                }
                ++prog;
                state = F;
                break;
            case Q17:
                if( *(++prog) == '=')
                    fillBuff(*prog++);
                state = F;
                break;
                //Estado Final
            default:
                //Delimita o fim do lexema
                closeBuff();

                //Verifica se o lexema reconhecido é esta presente na tabela de símbolos
                if( (symbol = symbolSearch(buffchr)) == NULL ){

                    symbol = symbolAlloc();
                    symbol->lexeme = strAlloc(buffchr);

                    if( symbolType == IDENTIFIER ){
                        symbol->tok = IDENTIFIER;
                        symbol->class = EMPTY_CLASS;
                        symbol->dataType = EMPTY_DATA_TYPE;
                        symbol->lenght = 0;
                        symbol->addr = 0;
                        symbolAdd(symbol);
                    } else {
                        symbol->tok = CONSTANT;
                        symbol->typeConst = symbolType;
                    }
                } else{

                    if( symbol->tok >= TOK_FINAL && symbol->tok < NUM_OF_TOKS )
                        symbol->typeConst = KEYWORD;

                }

                state = END;//fim da varredura, lexema pertence a linguagem!
                break;
        }
    }

    return symbol;
}

PUBLIC bool startLex( string fileName ){

    //Representação string dos tokens da linguagem
    string tokstr [] = {"final","int","char","for","if","else","do","and","or","not","to",
                        "begin","end","then","step","readln","write","writeln","<-","=","<>",">","<",">=","<=",
                        "+","-","*","/","%",";",",","(",")","[","]"};

    //Verifica a extensão do código-fonte
    if( !evalFileExt(fileName) || !fileExists(fileName) ){
        compilerror(ERR_FILE_NOT_FOUND,NULL);
    }

    //Reserva espaço para carregar o programa
    if( ( buffp = (char*) malloc(sizeof(char)*PROGRAM_LEN_MAX ) ) == NULL ){
        compilerror(ERR_COULD_NOT_LOAD_PROGRAM,NULL);
    }

    //carrega o programa para memória principal
    if( ! loadProgram(buffp,fileName) ){
        exit(1);
    }

    //cria a tabela de símbolos
    symbolTable = hashTableCreate(SYMBOL_TABLE_SIZE);

    //Carrega as palavras reservadas na tabela de símbolos.
    Symbol* symbol;
    int tok_id;
    for( tok_id = 0; tok_id < NUM_OF_TOKS; ++tok_id ){
        symbol = symbolAlloc();
        symbol->lexeme = tokstr[tok_id];
        symbol->tok = tok_id;
        symbolAdd(symbol);
    }

    //inicializa o contador de linhas
    lineCounter = 1;

    return TRUE;

}

PUBLIC void printSymbol(Symbol* symbol){

    string cType[] = { "IDENTIFIER","CONSTANT","CHR","HEX","NUMBER","STRING","KEYWORD"};

    if( symbol != NULL ) {
        if ( symbol->tok == IDENTIFIER ) {
            printf("\n\tTok( "
                           "\n\t\t addr: %p"
                           "\n\t\t lexeme: \"%s\" ; size: %d"
                           "\n\t\t tok: %d"
                           "\n\t\t class: %d"
                           "\n\t\t data type: %d"
                           "\n\t\t addr: %d\n\t);",
                   symbol,
                   symbol->lexeme,
                   strlen(symbol->lexeme),
                   symbol->tok,
                   symbol->class,
                   symbol->dataType,
                   symbol->addr);

        } else {
            printf("\n\tTok( "
                           "\n\t\t addr: %p"
                           "\n\t\t lexeme: \"%s\" ; size: %d"
                           "\n\t\t tok: %d"
                           "\n\t\t constType: %s\n\t);",
                   symbol,
                   symbol->lexeme,
                   strlen(symbol->lexeme),
                   symbol->tok,
                   cType[symbol->typeConst-IDENTIFIER]);
        }
    }else{
        printf("\n\tTok( null );\n");
    }
}

PUBLIC void printSymbolTable(){
    printf("\n\n****** SHOW SYMBOL TABLE *******\n");

    printf("Number elements: %d\n",symbolTable->count);
    printf("hash: %p\n", symbolTable );
    printf("node**: %p\n", symbolTable->node );

    int i;
    struct node* sNode = NULL;
    for( i = 0; i < symbolTable->size; ++i ) {

        sNode = symbolTable->node[i];

        if( sNode != NULL ){

            printf("node*: %p { lexeme: %s }", sNode->obj, ((Symbol*) sNode->obj)->lexeme );

            while ( sNode->prox != NULL ){
                printf(" -> node*: %p { lexeme: %s }", sNode->prox->obj, ((Symbol*) sNode->prox->obj)->lexeme );
                sNode = sNode->prox;
            }
            printf("\n");
        } else{
            printf("node*: %p { lexeme: %s }\n", sNode, "" );
        }
    }
}