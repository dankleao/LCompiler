//
// Created by Daniel on 28/02/2018.
//

#include "lex.h"
#include "tblerrors.h"

PRIVATE inline Tok* addTok( Tok* tok ){
    if( tok == NULL ){
        printf("Tok pointer is NULL!\n");
        exit(1);
    }
    return (Tok*) addHashTable(symbolTable,getKey(tok->lexeme),tok)->obj;
}

PRIVATE inline Tok* searchTok( string lexeme ){
    Node* node;
    if( (node = searchHashTable(symbolTable,lexeme,tokcmp) ) != NULL )
        return (Tok*) node->obj;
    else
        return NULL;
}

PRIVATE inline Tok* allocTok(){
    return (Tok*) malloc(sizeof(Tok));
}

PRIVATE inline LexReg* allocLexReg(){
    return (LexReg*) malloc(sizeof(LexReg));
}

PUBLIC BOOL evalFileExt(string file_name){

    if( strlen(file_name) < 3 )
        return FALSE;

    char* chr_p = file_name + (strlen(file_name) - 1);

    if(  *(chr_p) == 'l' && *( chr_p - 1) == '.' )
        return TRUE;
    else
        return FALSE;

}

PRIVATE void fillBuff(char chr){

    if( buffindex < VAR_LEN_MAX ){
        buffchr[buffindex++] = chr;
    } else{
        ERROR_VAR_LEN;
    }
    //return ( buffindex < VAR_LEN_MAX ? ( (buffchr[buffindex++] = chr),TRUE) : FALSE );
}

PRIVATE inline void closeBuff(){
    buffchr[buffindex] = '\0';
}

PRIVATE inline void ignoreWs(){
    while ( isspace(*prog) && *prog ){
        if( *prog == '\n' ) ++clin;
        ++prog;
    }
}

PRIVATE void setTok(Tok* tok, string lexeme, int tokId ){

    tok->lexeme = allocString(lexeme);
    tok->tokId = tokId;
}

PRIVATE inline BOOL tokcmp( Node* tok , string str ){
    //printf("before string%p\n", (Tok*) tok->obj );
    string lexeme = allocString( ((Tok*)tok->obj)->lexeme );
    //printf("after string!\n");
    return ( ! strcmp( lexeme ,str) ? TRUE : FALSE );
}

PUBLIC LexReg* nextTok(){

    printf("\n >> Next Tok\n");

    //auxilia a criação do registro lexico
    static LexReg* lexReg = NULL;
    int tokType = IDENTIFIER;

    buffindex = 0;//zera contador do buffer do lexema

    if( *prog == '\0' ){
        return NULL;
    }

    int state = Q0;//inicia o automato sempre para o estado inicial na chamada da função

    while( state != END ){

        switch ( state ){

            case Q0:

                printf(" -> START");
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
                else if( iscontained("+-*%[](),;=",*prog) ){
                    fillBuff(*prog);
                    ++prog;
                    state = F;
                }//Fim de arquivo
                else if(*prog == '\0'){
                    printf("-> EOF");
                    return NULL;
                }//Estado de erro do automato
                else{
                    ERROR_UNRECOGNIZED_SYMBOL;
                }
                break;

            case Q1:
                do{
                    printf(" -> Q1");
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
                    printf(" -> Q2");
                    fillBuff(*prog);
                }while ( isalnum(*(++prog)) || *prog == '_' );
                state = F;
                break;
            case Q3:
                printf(" -> Q3");
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
                printf(" -> Q4");
                fillBuff(*prog);
                if( (*(++prog) >= 'A' && *prog <= 'F') || isdigit(*prog) ){
                    state = Q6;
                }else{
                    //state = F;
                    while ( ! isspace(*prog) ) fillBuff(*prog++);
                    closeBuff();
                    ERROR_INVALID_HEX_CONST(buffchr);
                }
                break;
            case Q5:
                printf(" ->Q5");
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
                printf(" ->Q6");
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
                printf(" ->Q7");
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
                    printf(" -> Q8");
                    fillBuff(*prog);
                }while ( isdigit(*(++prog)) );
                tokType = NUMBER;
                state = F;
                break;
            case Q9:
                while ( isalnum(*(++prog)) || iscontained("()[]%&@;,!?*/-+_-<>=:{}'^ ",*prog) ){
                    printf(" -> Q7");
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
                printf(" -> Q11");
                if( isalnum(*(++prog)) || iscontained("()[]%&@;,!?*/-+_-<>=:{}\'^\"\n$ ",*prog) ){
                    fillBuff(*prog);
                    state = Q12;
                }
                else{
                    ERROR_UNRECOGNIZED_SYMBOL;
                }
                break;
            case Q12:
                printf(" -> Q12");
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
                printf(" -> Q13");
                if( *(++prog) == '*' ){
                    state = Q14;
                } else{
                    // op.div
                    fillBuff(*(prog-1));
                    state = F;
                }
                break;
            case Q14:
                printf(" -> Q14");
                while( *(++prog) != '*' ) printf(" -> Q14");
                state = Q15;
                break;
            case Q15:
                do{
                    printf(" -> Q15");
                }while ( *(++prog) == '*' );

                if( *prog == '/' ){
                    printf(" -> START");
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
                printf(" -> Q16");
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
                printf(" -> Q17");
                if( *(++prog) == '=')
                    fillBuff(*prog++);
                state = F;
                break;
            case F:

                //Delimita o fim do lexema
                closeBuff();

                lexReg = allocLexReg();

                if( (lexReg->tok = searchTok(buffchr)) == NULL ){

                    lexReg->tok = allocTok();

                    if( tokType == IDENTIFIER ){
                        setTok(lexReg->tok,buffchr,tokType);
                        addTok(lexReg->tok);

                    } else {
                        setTok(lexReg->tok,buffchr,tokType);
                    }
                }

                lexReg->pos = clin;
                printf(" -> F");
                //printTok(lexReg->tok);

                printLexReg(lexReg);

                state = END;
                break;

            default:
                break;
        }
    }

    return lexReg;
}

PUBLIC BOOL loadProgram( string buff, string fileName ){

    static FILE * fp;

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

    return TRUE;
}

PUBLIC void printTok(Tok* tok){
    if( tok != NULL )
        printf("\n\tTok( \n\t\taddr: %p\n\t\tlexeme: \"%s\" ; size: %d\n\t",tok,tok->lexeme,strlen(tok->lexeme));
    else
        printf("\n\tTok( \n\t\t null \n\t");
}

PUBLIC void printLexReg(LexReg* lexReg){
    printf("\nLex register{\n");
    printf("\tline: %d",clin);
    printTok(lexReg->tok);
    printf("\ttype: %s\n\t);\n}\n",strtoktype[ lexReg->tok->tokId >= TOK_FINAL && lexReg->tok->tokId < NUM_OF_TOKS ? KEYWORD - NUM_OF_TOKS : lexReg->tok->tokId - NUM_OF_TOKS ] );
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

PUBLIC int main(int argc, char* argv[]){

    string fileName = argv[1];

    string tokstr [] = {"final","int","char","for","if","else","do","and","or","not","to",
    "begin","end","then","step","readln","write","writeln","<-","=","<>",">","<",">=","<=",
    "+","-","*","/","%",";",",","(",")","[","]"};

    //Verifica a extensão do arquivo fonte
    if( ! evalFileExt(fileName) ){
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
    symbolTable = createHashTable(SYMBOL_TABLE_SIZE);

    printHashTable(symbolTable);

    //Carrega as palavras reservadas na tabela de símbolos.

    Tok* tok;
    int tok_id;
    for( tok_id = 0; tok_id < NUM_OF_TOKS; ++tok_id ){
        tok = allocTok();
        setTok(tok,tokstr[tok_id],tok_id);
        addTok(tok);
    }

    printHashTable(symbolTable);

    /*
    int i;
    for( i = 0; i < SYMBOL_TABLE_SIZE; ++i ){
        printTok( searchTok(tokstr[i]) );
    }
    */

    while (nextTok() != NULL);

    printSymTab();

    return 0;
}



