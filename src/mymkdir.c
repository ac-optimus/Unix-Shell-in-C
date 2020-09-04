/*
mkdir implementation

usage:
    mkdir path_to_dir
    mkdir dir1 dir2 dir3 ...
*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include "mymkdir.h"


int main(int argc, char* argv[]){
    if (argc == 1){
        // no path is passed
        fprintf(stderr,"mkdir: missing operand\n");
        exit(EXIT_FAILURE);
    }
    else{
        // handling multiple directory creation
        for (int i=1; i<argc; i++){
            // call mkdir
            mymkdir(argv[i]);
        }
    }
    return 0;
}