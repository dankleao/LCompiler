//
// Created by Daniel on 01/03/2018.
//

#include "def.h"

PUBLIC string strAlloc( string str ){

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

PUBLIC BOOL strChr( char*str, char chr ){
    while( *str ){
        if( chr == *str++ )
            return TRUE;
    }
    return FALSE;
}