//
// Created by Daniel on 06/04/2018.
//

#ifndef LCOMPILER_HASH_TABLE_H
#define LCOMPILER_HASH_TABLE_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "def.h"
#include "config.h"

PRIVATE int* weights;

PRIVATE inline int fxHash( int key, int table_size );
PRIVATE void generateWeights();

/*
 * Nó da tabela hash
 */
typedef struct node{
    void* obj;          //objeto a ser armazenado na tabela
    struct node* prox;  //endereço do proximo elemento
}Node;

/*
 *  Tabela hash de tamanho N(tamanho fixo) apontadores do tipo Node com
 * cada Node representando uma lista encadeada.
 */
typedef struct hash_table{
    int count;              //armazena a quantidade de elementos da tabela hash
    int size;               //armazena o tamanho da tabela hash
    struct node** node;     //array de apontadores, tamanho fixo
}HashTable;

/*
 * Funções que manipulam os tipos de dados Node e HashTable
 */
PUBLIC Node* hashTableAdd(HashTable* hashTable, int key, void* obj);
PUBLIC HashTable* hashTableCreate(int size);
PUBLIC Node* hashTableSearch(HashTable* hash, string str, bool (*cmp) (Node*, string) );
PUBLIC int getKey(char* string);
PUBLIC void printHashTable( HashTable* hash );
PUBLIC void printWeights();


#endif //LCOMP_HASH_TABLE_H
