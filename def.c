//
// Created by Daniel on 06/04/2018.
//

#include "def.h"

PUBLIC string strAlloc( string str ){

    int length;
    if( str == NULL || ( length = strlen(str) ) == 0 )
        return NULL;

    char* newStr = (char*) malloc( sizeof(char) * (strlen(str) + 1) );

    int i;
    for( i = 0; i < length; ++i )
        newStr[i] = str[i];
    newStr[i] = '\0';
    return newStr;
}

PUBLIC bool strChr( char*str, char chr ){
    while( *str ){
        if( chr == *str++ )
            return TRUE;
    }
    return FALSE;
}