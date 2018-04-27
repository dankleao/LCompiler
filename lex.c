//
// Created by Daniel on 06/04/2018.
//

#include "lex.h"
#include "symbol_table.h"

PRIVATE inline void ignoreWs(){
    while ( isspace(*prog) && *prog ){
        if( *prog == '\n' ) ++lineCounter;
        ++prog;
    }
}

PRIVATE string buildLexeme(){

    int length = 0;
    string lexeme = lexemeBegin;
    while( lexeme != prog ){
        ++length;
        ++lexeme;
    }

    lexeme = (string) malloc( sizeof(char) * (length + 1) );

    int i = 0;
    for( i = 0; i < length; ++i )
        lexeme[i] = lexemeBegin[i];
    lexeme[i] = '\0';

    return lexeme;

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

    fclose(fp);

    return TRUE;
}

PUBLIC Symbol* nextSymbol(){

    Symbol* symbol = NULL;
    int symbolType = TOK_IDENTIFIER;
    string currentLexeme = NULL;

    //Verifica se arquivo chegou ao fim
    if( *prog == '\0' )
        return NULL;

    int state = Q0;//inicia o automato sempre para o estado inicial na chamada da função

    while ( state != END ){

        switch ( state ){

            case Q0:

                ignoreWs();//Ignora espaços em branco

                lexemeBegin = prog;//inicio de um novo padrão de token

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
                }//Fim de arquivo
                else if( *prog == '\0' ){
                    return NULL;
                }//Reconhece um op.aritmético, delimitadores e op.igualdade
                else if( strChr("+-*%[](),;=",*prog) ){
                    ++prog;
                    state = F;
                }//Símbolos permitidos pela linguagem, mas não são tokens
                else if( strchr(":.@^!?",*prog++) ){
                    compilerror(ERR_LEXEME_NOT_FOUND,buildLexeme());
                }//Estado de erro do automato
                else{
                    compilerror(ERR_UNRECOGNIZED_SYMBOL,NULL);
                }
                break;//Fim Q0
            case Q1:
                while ( *(++prog) == '_' );
                if( isalnum(*prog) ) {
                    state = Q2;
                } else{
                    compilerror(ERR_LEXEME_NOT_FOUND,buildLexeme());
                }
                break;//Fim Q1
            case Q2:
               while ( isalnum(*(++prog)) || *prog == '_' );
               state = F;
               break;//Fim Q2
            case Q3:
                if( *(++prog) >= 'A' && *prog <= 'F' ){
                    state = Q4;
                } else if( isdigit(*prog) ){
                    state = Q5;
                } else{
                    symbolType = NUMBER_CONST;
                    state = F;
                }
                break;//Fim Q3
            case Q4:
                if( (*(++prog) >= 'A' && *prog <= 'F') || isdigit(*prog) ){
                    state = Q6;
                }else{
                    compilerror(ERR_LEXEME_NOT_FOUND,buildLexeme());
                }
                break;//Fim Q4
            case Q5:
                if( *(++prog) >= 'A' && *prog <= 'F' ){
                    state = Q6;
                } else if( isdigit(*prog) ){
                    state = Q7;
                } else{
                    symbolType = NUMBER_CONST;
                    state = F;
                }
                break;//Fim Q5
            case Q6:
                if( *(++prog) == 'h' ){
                    symbolType = HEX_CONST;
                    ++prog;
                    state = F;
                } else{
                    compilerror(ERR_LEXEME_NOT_FOUND,buildLexeme());
                }
                break;//Fim Q6
            case Q7:
                if( isdigit(*(++prog)) ){
                    state = Q8;
                } else if( *prog == 'h' ){
                    symbolType = HEX_CONST;
                    ++prog;
                    state = F;
                } else{
                    symbolType = NUMBER_CONST;
                    state = F;
                }
                break;//Fim Q7
            case Q8:
                while ( isdigit(*(++prog)) );
                symbolType = NUMBER_CONST;
                state = F;
                break;//Fim Q8
            case Q9:
                while ( isalnum(*(++prog)) || strChr("()[]|\\%&@;,.!?*/-+_-<>=:{}\'^ ",*prog) );
                if( *prog == '\"'){
                    state = Q10;
                } else if( *prog == '$' ){
                    compilerror(ERR_UNRECOGNIZED_SYMBOL,NULL);
                } else if ( isspace(*prog) ){
                    compilerror(ERR_UNRECOGNIZED_SYMBOL,NULL);
                } else{
                    compilerror(ERR_UNRECOGNIZED_SYMBOL,NULL);
                }
                break;//Fim Q9
            case Q10:
                if( *(++prog) == '\"' ){
                    compilerror(ERR_UNRECOGNIZED_SYMBOL,NULL);
                } else{
                    symbolType = STRING_CONST;
                    state = F;
                }
                break;//Fim Q10
            case Q11:
                if( isalnum(*(++prog)) || strChr("()[]|\\%&@;,.!?*/-+_-<>=:{}\'^\"$ ",*prog) ){
                    state = Q12;
                }
                else{
                    compilerror(ERR_UNRECOGNIZED_SYMBOL,NULL);
                }
                break;//Fim Q11
            case Q12:
                if( *(++prog) == '\'' ){
                    symbolType = CHARACTER_CONST;
                    ++prog;
                    state = F;
                }
                else{
                    compilerror(ERR_LEXEME_NOT_FOUND,buildLexeme());
                }
                break;//Fim Q12
            case Q13:
                if( *(++prog) == '*' ){
                    state = Q14;
                } else{
                    state = F;
                }
                break;//Fim Q13
            case Q14:;
                while( *(++prog) != '*' );
                state = Q15;
                break;//Fim Q14
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
                break;//Fim Q15
            case Q16:
                if( *(++prog) == '>' || *prog == '-' || *prog == '=' )
                    ++prog;
                state = F;
                break;//Fim Q16
            case Q17:
                if( *(++prog) == '=' )
                    ++prog;
                state = F;
                break;//Fim Q17
            default:

                //Estado F(Final do automato)

                currentLexeme = buildLexeme();

                if( symbolType == TOK_IDENTIFIER ){

                    if( (symbol = symbolSearch(currentLexeme)) == NULL ){

                        symbol = symbolAlloc();
                        symbol->lexeme = currentLexeme;
                        symbol->tok = TOK_IDENTIFIER;
                        symbol->classId = NULL_CLASS;
                        symbol->dataType = NULL_DATA_TYPE;
                        symbol->arraySize = 0;
                        symbol->memAddress = 0;
                        symbolAdd(symbol);

                    }

                } else{

                    symbol = symbolAlloc();
                    symbol->lexeme = currentLexeme;
                    symbol->tok = TOK_CONSTANT;
                    symbol->type = symbolType;
                    symbol->size = strlen(currentLexeme);

                }

                //printSymbol(symbol);

                state = END;
                break;
        }
    }

    return symbol;
}

PUBLIC bool startLex( string fileName ){

    //Representação string dos tokens da linguagem
    string tokName [] = {"final","int","char","for","if","else",
                        "do","and","or","not","to", "begin",
                        "end","then","step","readln","write","writeln",
                        "<-","=","<>",">","<",">=",
                        "<=","+","-","*","/","%",
                        ";",",","(",")","[","]"};

    //Verifica a extensão do código-fonte
    if( !fileExists(fileName) ){
        compilerror(ERR_FILE_NOT_FOUND,NULL);
    }

    //Reserva espaço para carregar o programa
    if( ( prog = (char*) malloc(sizeof(char)*PROGRAM_LEN_MAX ) ) == NULL ){
        compilerror(ERR_COULD_NOT_LOAD_PROGRAM,NULL);
    }

    //carrega o programa para memória principal
    if( ! loadProgram(prog,fileName) ){
        exit(1);
    }

    //cria a tabela de símbolos
    symbolTable = hashTableCreate(SYMBOL_TABLE_SIZE);

    //Carrega as palavras reservadas na tabela de símbolos.
    Symbol* symbol;
    int i;
    for( i = 0; i < NUM_OF_TOKS; ++i ){
        symbol = symbolAlloc();
        symbol->lexeme = strAlloc( tokName[i] );
        symbol->tok = i;
        symbolAdd(symbol);
    }

    //inicializa o contador de linhas
    lineCounter = 1;

    return TRUE;

}

PUBLIC void printSymbol(Symbol* symbol){

    if( symbol != NULL ) {

        if ( symbol->tok == TOK_CONSTANT ) {

            static string typeNames[] = { "CHARACTER","HEX","NUMBER","STRING"};

            printf("\n\tTok( "
                   "\n\t\t addr: %p"
                   "\n\t\t lexeme: \"%s\" ; size: %d"
                   "\n\t\t tok: %d"
                   "\n\t\t constType: %s"
                   "\n\t\t constSize %d\n\t);",
                   symbol,
                   symbol->lexeme,
                   strlen(symbol->lexeme),
                   symbol->tok,
                   typeNames[ symbol->type - CHARACTER_CONST],
                   symbol->size);
        } else {
            if( symbol->tok == TOK_IDENTIFIER ){
                printf("\n\tTok( "
                       "\n\t\t addr: %p"
                       "\n\t\t lexeme: \"%s\" ; size: %d"
                       "\n\t\t tok: %d"
                       "\n\t\t class: %s"
                       "\n\t\t data type: %s"
                       "\n\t\t arraySize: %s"
                       "\n\t\t addr: %d\n\t);",
                       symbol,
                       symbol->lexeme,
                       strlen(symbol->lexeme),
                       symbol->tok,
                       ( symbol->classId == CONST_CLASS ? "CONST_CLASS" : "VAR_CLASS"  ),
                       ( symbol->dataType == CHARACTER_DATA_TYPE ? "CHAR" : "INTEGER"  ),
                       ( symbol->arraySize == 0 ? "SINGLE" : "ARRAY" ),
                       symbol->memAddress);
            }
            else{
                printf("\n\tTok( "
                       "\n\t\t addr: %p"
                       "\n\t\t lexeme: \"%s\" ; size: %d"
                       "\n\t\t tok: %d\n\t);",
                       symbol,
                       symbol->lexeme,
                       strlen(symbol->lexeme),
                       symbol->tok);
            }
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
