//
// Created by Daniel on 28/02/2018.
//

#include "hash_table.h"

PUBLIC Node* addHashTable(HashTable* hash, int key, void* obj){

    /*
    if( hash->count >= hash->size )
        return NULL;
     */

    Node* newNode;
    if( ( newNode = (Node*) malloc(sizeof(Node)) ) == NULL )
        return NULL;

    newNode->obj = obj;
    newNode->prox = NULL;

    int pos = fxHash(key,hash->size);

    if( hash->node[pos] != NULL ){

        Node* sNode = hash->node[pos];

        while( sNode->prox != NULL ) sNode = sNode->prox;

        sNode->prox = newNode;

    } else{

        hash->node[pos] = newNode;
    }

    ++hash->count;

    return newNode;
}

PUBLIC Node* searchHashTable(HashTable* hash, string str, BOOL (*cmp) (Node*, string) ){

    int pos = fxHash(getKey(str),hash->size);

    if(  hash->node[pos] == NULL )
        return NULL;

    Node* sNode = hash->node[pos];

    do{

        if( (*cmp)( sNode ,str) ){
            return sNode;
        }

    }while( ( (sNode = sNode->prox), sNode != NULL ) );

    return NULL;
}

PUBLIC void printHashTable( HashTable* hash ){

    printf("\n****** SHOW HASH *******\n");

    printf("hash: %p\n", hash );
    printf("node**: %p\n", hash->node );

    int i;
    struct node* sNode = NULL;
    for( i = 0; i < hash->size; ++i ) {

        sNode = hash->node[i];

        if( sNode != NULL ){

            printf("node*: %p",sNode->obj );

            while ( sNode->prox != NULL ){
                printf(" -> node*: %p", sNode->prox->obj );
                sNode = sNode->prox;
            }
            printf("\n");
        } else{
            printf("node*: %p\n",sNode);
        }
    }
}

PUBLIC HashTable* createHashTable(int size){

    int i;

    HashTable* hashTable = (HashTable*) malloc(sizeof(hashTable));


    if(hashTable != NULL){

        hashTable->count = 0;
        hashTable->size = size;

        hashTable->node = (Node**) malloc( sizeof(Node*) * hashTable->size );

        if( hashTable->node == NULL ){
            free(hashTable);
            return NULL;
        }

        for ( i = 0; i < hashTable->size ; ++i)
            hashTable->node[i] = NULL;

        generateWeights();
    }

    return hashTable;
}

PRIVATE void generateWeights(){

    int i;
    weights = (int*) malloc( VAR_LEN_MAX * sizeof(int) );

    if( weights != NULL ){

        srand(time(NULL));

        for( i = 0; i < VAR_LEN_MAX; ++i)
            weights[i] = rand() % TAB_ASC2_SIZE;
    }
}

PUBLIC void printWeights( ){

    int i;
    for( i = 0; i < VAR_LEN_MAX; ++i ){
        if( i % 16 == 0 )
            printf("\n");
        printf("%d ", weights[i] );
    }
}

PUBLIC inline int fxHash( int key, int table_size ){
    //printf("h( %d ) = %d\n", key, key % table_size);
    return  key % (table_size);
}

PUBLIC int getKey(char* string){
    return getKey2(string,weights);
}

PUBLIC int getKey2(string str, int weights[]){

    //printf("string: %s\n",str);

    int key = 0;
    int length = strlen(str);

    int i;
    int j;
    for (i = 0; i < length ; ++i) {
        key += ((int) str[i]) * weights[i];
        j = ((int) str[i]) * weights[i];
        //printf("%d = %d * %d\n", j, (int)str[i], weights[i]);

    }
    return key;
}
