//
// Created by Daniel on 06/04/2018.
//
#include "def.h"

PUBLIC string int2str(int value){

    char buffer[11];// 11 = max_value int com sinal

    return itoa(value,buffer,10), strAlloc(buffer);

}

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

    if( fileName == NULL )
        return FALSE;

    string fileNameBegin = fileName;

    enum states { Q0 = 0, Q1, Q2, F, DFA_ERROR };

    int state = Q0;

    while( state != F ) {

        if( state == Q0 ){

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

PUBLIC bool compareStrings(string strA, string strB){
    return ( ! strcmp(strA,strB) ? TRUE : FALSE );
}

PUBLIC int hex2int(string hex){

    int degree = strlen(hex);

    int decValue = 0;

    int i;
    for( i = 0 ; i < degree ; ++i ){
        if( isdigit(hex[i]) )
            decValue += ( hex[i] - 48 ) * pow(16,(degree-1)-i);
        else
            decValue += ( hex[i] - 55 ) * pow(16,(degree-1)-i);
    }

    return decValue;
}

PUBLIC string strInject( string source, string code, int pos ){

    int lenS = strlen(source);

    if( ( pos > lenS ) )
        return "\0";

    int lenC = strlen(code);

    string newSource = (string) malloc(sizeof(char) * (lenS + lenC + 1) );

    int i;
    for( i = 0 ; i < pos ; ++i )
        newSource[i] = source[i];

    for( ; i < pos + lenC ; ++i )
        newSource[i] = code[i - pos];

    for( ; i < lenS + lenC ; ++i )
        newSource[i] = source[ i - lenC ];

    newSource[i] = '\0';

    return newSource;
}

PUBLIC string substr(string str, int beginIndex, int endIndex){

    if( beginIndex > endIndex || endIndex > strlen(str) )
        return "\0";

    string newStr = (char*) malloc(sizeof(char) * (endIndex - beginIndex  + 1) );

    int i;
    for( i = 0; i < endIndex - beginIndex; ++i )
        newStr[i] = str[ beginIndex + i ];
    newStr[i] = '\0';

    return newStr;

}