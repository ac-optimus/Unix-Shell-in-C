/*
cat implementation

usage
    cat file1 file2 file3 file4

NOTE
    when no files are passed as argument, program returns 0
*/

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "mymkdir.h"

#define MAX_FILE_NAME_LENGTH 1024


void cat_file(char* filename){
    /* read a file, print it line by line */
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        // handling error
        fprintf(stderr, "cat: '%s': %s\n", filename, strerror(errno));
        return; // we want to process other files
    }
    char character;
    character = fgetc(fp);
    while (character != EOF){ //read line char by char
        printf("%c",character);
        character = fgetc(fp);
    }
    int status = fclose(fp);
    if (status == EOF){
        // handling error
        fprintf(stderr, "cat: '%s': %s\n", filename, strerror(errno));
        return; // we want to process other files.
    }
}


int main(int argc, char* argv[]){

    int status;
    for (int i=1;i<argc; i++){
        status = isDir(argv[i]);
        if (status == 1){ // error if directory is given as argument
            fprintf(stderr,"cat: %s: Is a directory\n", argv[i]);
            exit(1);
        }
        else{
            cat_file(argv[i]);
        }
    }
    return 0;
}