/*
chmod implementation
usage:
    chmod permission_code filename

*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>


#define MAX_SIZE 1024

void mychmod(char* filename){  //void return is not good ??


}


int main(int argc, char* argv[]){
    if (argc == 1){
        // no path is passed
        fprintf(stderr,"mkdir: missing operand\n");
        exit(EXIT_FAILURE);
    }
    else{
        // we can have a list of args

        char pathname[MAX_SIZE] = "";
        for (int i=1; i<argc; i++){
            strncpy(pathname, argv[i], strlen(argv[i])); //do we need to check for bound MAX_SIZE
            // call mkdir
            mymkdir(pathname);
            // printf("%s\n", pathname);

        }
    }

    return 0;
}