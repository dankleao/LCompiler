//
// Created by Daniel on 01/03/2018.
//

#include <stdio.h>
#include "def.h"

<<<<<<< HEAD
PUBLIC string strAlloc( string str ){
=======
PUBLIC string allocString( string str ){
>>>>>>> master

    if(str == NULL)
        return NULL;

    int size = strlen(str);
    if( size < 1 )
        return NULL;

    string newStr = (string) malloc(sizeof(string)*size+1);
    int i = 0;
    while( i < size ){
        newStr[i] = str[i];
        ++i;
    }

    return (newStr[i] = '\0',newStr);

}

<<<<<<< HEAD
PUBLIC BOOL strChr( char*str, char chr ){
=======
PUBLIC BOOL iscontained( char*str, char chr ){
>>>>>>> master
    while( *str ){
        if( chr == *str++ )
            return TRUE;
    }
    return FALSE;
}