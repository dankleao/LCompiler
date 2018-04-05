//
// Created by Daniel on 22/03/2018.
//

#include "symbol_table.h"

PRIVATE bool compareSymbol( Node* symbol , string str ){
    return ( ! strcmp( strAlloc( ((Symbol*)symbol->obj)->lexeme ) ,str) ? TRUE : FALSE );
}

PUBLIC Symbol* symbolAdd( Symbol* symbol ){
    return (Symbol*) hashTableAdd(symbolTable,getKey(symbol->lexeme),symbol)->obj;
}

PUBLIC Symbol* symbolAlloc(){
    return (Symbol*) malloc(sizeof(Symbol));
}

PUBLIC Symbol* symbolSearch(string lexeme){

    Node* node;
    if( (node = hashTableSearch(symbolTable,lexeme,compareSymbol) ) != NULL )
        return (Symbol*) node->obj;
    else
        return NULL;
}



