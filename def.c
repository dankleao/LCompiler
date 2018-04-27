//
// Created by Daniel on 06/04/2018.
//

#include <io.h>
#include <ctype.h>
#include <stdio.h>
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

PUBLIC bool fileExists(string fileName){
    return (access( fileName, F_OK ) != -1 ? TRUE : FALSE);
}


PUBLIC bool evalFileExt(string fileName,string ext){

    printf("evalFileExt\n");

    if( fileName == NULL )
        return FALSE;

    string fileNameBegin = fileName;

    enum states { Q0 = 0, Q1, Q2, F, DFA_ERROR };

    int state = Q0;

    while( state != F ) {

        if( state == Q0 ){

            printf("%c",*fileNameBegin);
            if( isalnum(*fileNameBegin) || !strChr("\\/|<>*:\"",*fileNameBegin) ){
                ++fileNameBegin;
                state = Q1;
            }
            else{
                state = DFA_ERROR;
            }

        } else if ( state == Q1 ){

            while( isalnum(*fileNameBegin) )
                ++fileNameBegin;

            if( *fileNameBegin == '.' )
                state = Q2;
            else
                state = DFA_ERROR;

        } else if( state == Q2 ) {

            int extLength = strlen(ext);

            int i = 1;

            while ( i < extLength && *(++fileNameBegin) == ext[i]) ++i;

            if ( i == extLength && *(fileNameBegin + 1) == '\0')
                state = F;
            else
                state = DFA_ERROR;
        }
        else{
            break;
        }
    }

    return ( state == F ? TRUE: FALSE );

}