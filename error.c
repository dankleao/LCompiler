//
// Created by Daniel on 06/04/2018.
//

#include "error.h"

PUBLIC void compilerror( int err_id, string arg ){

    if( arg == NULL )
        printf("\n%d: %s\n",lineCounter,err_list[err_id]);
    else
        printf("\n%d: %s [%s]\n",lineCounter,err_list[err_id],arg);
    exit(1);
}
