//
// Created by Daniel on 13/03/2018.
//

#include "excpt.h"

PUBLIC void compilerror( int err_id, string arg ){

    if( arg == NULL )
        printf("\n%d: %s\n",lineCounter,err_list[err_id]);
    else
        printf("\n%d: %s [%s]\n",lineCounter,err_list[err_id],arg);
    exit(1);
}