//
// Created by Daniel on 28/02/2018.
//

#ifndef COMPILERL_HASH_TABLE_H
#define COMPILERL_HASH_TABLE_H

#include <malloc.h>
#include <mem.h>
#include <time.h>
#include <stdio.h>
#include "def.h"

PRIVATE int* weights;

typedef struct node{
    void* obj;
    struct node* prox;
}Node;

typedef struct hash_table{

    int count,size;
    struct node** node;

}HashTable;

PUBLIC Node* addHashTable(HashTable* hashTable, int key, void* obj);
PUBLIC HashTable* createHashTable(int size);
PUBLIC Node* searchHashTable(HashTable* hash, string str, BOOL (*cmp) (Node*, string) );
PRIVATE inline int fxHash( int key, int table_size );
PRIVATE void generateWeights();
PUBLIC void printHashTable( HashTable* hash );

PUBLIC int getKey(char* string);
PRIVATE int getKey2(char* string, int weights[]);

PUBLIC void printWeights();


#endif //COMPILERL_HASH_TABLE_H
