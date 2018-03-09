//
// Created by Daniel on 28/02/2018.
//


#include <unistd.h>

#define LEX_IMP //Habilita a visualização dos metodos privados

#include "lex.h"
#include "tblerrors.h"

/*
 * Métodos privados
 */

PRIVATE inline Tok* tokAdd( Tok* tok ){
    return (Tok*) hashTableAdd(symbolTable,getKey(tok->lexeme),tok)->obj;
}

PRIVATE inline Tok* tokSearch( string lexeme ){
    Node* node;
    if( (node = hashTableSearch(symbolTable,lexeme,compareTok) ) != NULL )
        return (Tok*) node->obj;
    else
        return NULL;
}

PRIVATE inline Tok* tokAlloc(){
    return (Tok*) malloc(sizeof(Tok));
}

PRIVATE inline LexReg* lexRegAlloc(){
    return (LexReg*) malloc(sizeof(LexReg));
}

PRIVATE BOOL evalFileExt(string fileName){

    int length = strlen(fileName);
    if( length < 3 )
        return FALSE;

    return ( fileName[length-1] == 'l' && fileName[length-2] == '.' ? TRUE : FALSE );
}

PRIVATE BOOL fileExists(string fileName){
    return (access( fileName, F_OK ) != -1 ? TRUE : FALSE);
}

PRIVATE void fillBuff(char chr){
    if( buffindex < VAR_LEN_MAX ){
        buffchr[buffindex++] = chr;
    } else{
        ERROR_VAR_LEN;
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

PRIVATE void setTok(Tok* tok, string lexeme, int tokId ){
    tok->lexeme = strAlloc(lexeme);
    tok->tokId = tokId;
}

PRIVATE inline BOOL compareTok( Node* tok , string str ){
    return ( ! strcmp( strAlloc( ((Tok*)tok->obj)->lexeme ) ,str) ? TRUE : FALSE );
}

PRIVATE BOOL loadProgram( string buff, string fileName ){

    FILE * fp;

    //abre o arquivo bin para leitura
    if( (fp = (fopen(fileName,"rb"))) == NULL )
        return FALSE;

    char chr = (char) getc(fp);

    int i = 0;
    while( ! feof(fp) && i < PROGRAM_LEN_MAX ){
        buff[i] = chr;
        printf("%c",buff[i]);
        ++i;
        chr = (char) getc(fp);
    }

    buff[i] = '\0';

    prog = buff;//Atribui a primeira posição do arquivo fonte

    fclose(fp);

    return TRUE;
}

/*
 * Métodos públicos
 */

PUBLIC LexReg* nextTok(){

    //auxilia a criação do registro lexico
    LexReg* lexReg = NULL;
    int tokType = IDENTIFIER;

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
                    ERROR_UNRECOGNIZED_SYMBOL;
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
                    ERROR_LEXEME_NOT_FOUND(buffchr);
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
                    tokType = NUMBER;
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
                    ERROR_INVALID_HEX_CONST(buffchr);
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
                    tokType = NUMBER;
                    state = F;
                }
                break;
            case Q6:
                fillBuff(*prog);
                if( *(++prog) == 'h' ){
                    fillBuff(*prog);
                    tokType = HEX;
                    ++prog;
                    state = F;
                } else{
                    fillBuff(*prog++);
                    while ( ! isspace(*prog) ) fillBuff(*prog++);
                    closeBuff();
                    ERROR_INVALID_HEX_CONST(buffchr);
                }
                break;
            case Q7:
                fillBuff(*prog);
                if( isdigit(*(++prog)) ){
                    state = Q8;
                } else if( *prog == 'h' ){
                    fillBuff(*prog);
                    tokType = HEX;
                    ++prog;
                    state = F;
                } else{
                    tokType = NUMBER;
                    state = F;
                }
                break;
            case Q8:
                do{
                    fillBuff(*prog);
                }while ( isdigit(*(++prog)) );
                tokType = NUMBER;
                state = F;
                break;
            case Q9:
                while ( isalnum(*(++prog)) || strChr("()[]%&@;,!?*/-+_-<>=:{}'^ ",*prog) ){
                    fillBuff(*prog );
                }
                if( *prog == '\"'){
                    state = Q10;
                }
                else if( *prog == '$' || *prog == '\n'  ){
                    ERROR_UNRECOGNIZED_SYMBOL;
                }
                else{
                    ERROR_UNRECOGNIZED_SYMBOL;
                }
                break;
            case Q10:
                if( *(++prog) == '\"' ){
                    ERROR_UNRECOGNIZED_SYMBOL;
                } else{
                    tokType = STRING;
                    state = F;
                }
                break;
            case Q11:
                if( isalnum(*(++prog)) || strChr("()[]%&@;,!?*/-+_-<>=:{}\'^\"\n$ ",*prog) ){
                    fillBuff(*prog);
                    state = Q12;
                }
                else{
                    ERROR_UNRECOGNIZED_SYMBOL;
                }
                break;
            case Q12:
                if( *(++prog) == '\'' ){
                    tokType = CHARACTER;
                    ++prog;
                    state = F;
                }
                else{
                    ERROR_UNRECOGNIZED_SYMBOL;
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
                    ERROR_EOF_NOT_EXPECTED;
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
                    tokType = KEYWORD;
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

                //Cria um registro lexico
                lexReg = lexRegAlloc();

                Tok* tok;
                //Verifica se o lexema reconhecido é esta presente na tabela de símbolos
                if( (tok = tokSearch(buffchr)) == NULL ){

                    //lexReg->tok = tokAlloc();
                    tok = tokAlloc();

                    if( tokType == IDENTIFIER ){
                        setTok(tok,buffchr,tokType);
                        tokAdd(tok);

                    } else {
                        setTok(tok,buffchr,tokType);
                    }
                }
                lexReg->pos = lineCounter;
                lexReg->tok = tok;

                state = END;
                break;
        }
    }

    return lexReg;
}

PUBLIC BOOL startLex( string fileName ){

    //Representação string dos tokens da linguagem
    string tokstr [] = {"final","int","char","for","if","else","do","and","or","not","to",
                        "begin","end","then","step","readln","write","writeln","<-","=","<>",">","<",">=","<=",
                        "+","-","*","/","%",";",",","(",")","[","]"};

    //Verifica a extensão do código-fonte
    if( !evalFileExt(fileName) || !fileExists(fileName) ){
        printf("lex: error: Arquivo %s nao encontrado!\n",fileName);
        exit(1);
    }

    //Reserva espaço para carregar o programa
    if( ( buffp = (char*) malloc(sizeof(char)*PROGRAM_LEN_MAX ) ) == NULL ){
        printf("lex: error: Não foi possível carregar o programa!\n");
        exit(1);
    }

    //carrega o programa para memória principal
    if( ! loadProgram(buffp,fileName) ){
        exit(1);
    }

    //cria a tabela de símbolos
    symbolTable = hashTableCreate(SYMBOL_TABLE_SIZE);

    //Carrega as palavras reservadas na tabela de símbolos.
    Tok* tok;
    int tok_id;
    for( tok_id = 0; tok_id < NUM_OF_TOKS; ++tok_id ){
        tok = tokAlloc();
        setTok(tok,tokstr[tok_id],tok_id);
        tokAdd(tok);
    }

    return TRUE;

}

PUBLIC void printTok(Tok* tok){
    if( tok != NULL )
        printf("\n\tTok( \n\t\taddr: %p\n\t\tlexeme: \"%s\" ; size: %d\n\t",tok,tok->lexeme,strlen(tok->lexeme));
    else
        printf("\n\tTok( \n\t\t null \n\t");
}

PUBLIC void printLexReg(LexReg* lexReg){

    if( lexReg != NULL ){

        printf("\nLex register{ \tLine: %d\n",lineCounter);
        printTok(lexReg->tok);
        printf("\ttype: %s\n\t);\n}\n",strtoktype[ lexReg->tok->tokId >= TOK_FINAL && lexReg->tok->tokId < NUM_OF_TOKS ? KEYWORD - NUM_OF_TOKS : lexReg->tok->tokId - NUM_OF_TOKS ] );
    }
}

PUBLIC void printSymTab(){

    printf("\n\n****** SHOW SYMBOL TABLE *******\n");

    printf("Number elements: %d\n",symbolTable->count);
    printf("hash: %p\n", symbolTable );
    printf("node**: %p\n", symbolTable->node );

    int i;
    struct node* sNode = NULL;
    for( i = 0; i < symbolTable->size; ++i ) {

        sNode = symbolTable->node[i];

        if( sNode != NULL ){

            printf("node*: %p { lexeme: %s }", sNode->obj, ((Tok*) sNode->obj)->lexeme );

            while ( sNode->prox != NULL ){
                printf(" -> node*: %p { lexeme: %s }", sNode->prox->obj, ((Tok*) sNode->prox->obj)->lexeme );
                sNode = sNode->prox;
            }
            printf("\n");
        } else{
            printf("node*: %p { lexeme: %s }\n", sNode, "" );
        }
    }
}

