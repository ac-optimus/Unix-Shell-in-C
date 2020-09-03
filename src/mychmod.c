/*
chmod implementation

usage
    chmod mode file1 fil2 ...
*/

#include <stdio.h>
#include <sys/stat.h> // for chmod
#include <errno.h>
#include <stdlib.h>


void mychmod(char* filepath, char*new_mode){
    mode_t mode = (int)strtol(new_mode, NULL, 8);
    printf("%d\n", mode);
    int status;
    status = chmod(filepath, mode);
    if (status == -1){
        printf( "chmod: cannot access '%s' No such file or directory \n", filepath);
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
        // add error handelling
        printf("%d\n", (int)strtol(argv[1], NULL, 8));
        for (int i=2;i<argc; i++){
            mychmod(argv[i], argv[1]);
        }
    }
    return 0;
}