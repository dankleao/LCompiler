//
// Created by Daniel on 28/02/2018.
//

#ifndef COMPILERL_HASH_TABLE_H
#define COMPILERL_HASH_TABLE_H

#include "def.h"

#ifdef HASH_TABLE_IMPL

#include <mem.h>
#include <time.h>

PRIVATE int* weights;

PRIVATE inline int fxHash( int key, int table_size );
PRIVATE void generateWeights();
PRIVATE int getKey2(char* string, int weights[]);

#endif

/*
 * Tipo de dados abstrato <b>Node</b> armazena o endereço do objeto a ser armazenado na tabela e
 * aponta para seu vizinho na mesma posição da tabela caso exista.
 */

typedef struct node{
    void* obj;          //objeto a ser armazenado na tabela
    struct node* prox;  //lista dinâmica que armazena os objetos que possuem a mesma chave
}Node;

/*
 * Tipo de dados abstrato <b>HashTable</b> representa uma tabela hash com n(tamanho fixo) apontadores do tipo Node.
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
PUBLIC Node* hashTableSearch(HashTable* hash, string str, BOOL (*cmp) (Node*, string) );
PUBLIC int getKey(char* string);
PUBLIC void printHashTable( HashTable* hash );
PUBLIC void printWeights();

#endif //COMPILERL_HASH_TABLE_H
