/*
chmod implementation

usage
    chmod mode file1 fil2 ...

NOTE:
only supports numerical format permission mode
*/

#include <stdio.h>
#include <sys/stat.h> // for chmod
#include <errno.h>
#include <stdlib.h>


void mychmod(char* filepath, char*new_mode){
    // get the mode to assign
    mode_t mode = (int)strtol(new_mode, NULL, 8);
    int status;
    status = chmod(filepath, mode);
    if (status == -1){
        fprintf( stderr,"chmod: cannot access '%s' No such file or directory \n", filepath);
        return; //ignore this file
    }
}


int main(int argc, char* argv[]){
    if (argc == 1){
        fprintf(stderr,"chmod: missing operand\n");
        exit(1);
    }
    else if (argc == 2){
        fprintf(stderr,"chmod: missing operand after '%s'\n", argv[1]);
    }
    else{
        // change the mode file by file
        for (int i=2;i<argc; i++){
            mychmod(argv[i], argv[1]);
        }
    }
    return 0;
}