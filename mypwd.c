/*
pwd implementation
    prints name of current/ working directory
usage
    pwd
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAX_FILE_NAME_LENGTH 64


void pwd(){
    char pwd[MAX_FILE_NAME_LENGTH];
    if (getcwd(pwd, sizeof(pwd))){
        fprintf(stderr, "chdir: %s\n", strerror(errno));
    }
    printf("%s\n", pwd);
}



int main(int argc, char* argv[]){
    char dirname[MAX_SIZE] = ""; // initiailzation is so important, else you get garbage values appended at the end.
    // no argument
    if (argc == 1){
        if (getcwd(dirname, sizeof(dirname)) == NULL){
            fprintf(stderr, "getcwd: '%s': %s\n", dirname, strerror(errno));
            exit(EXIT_FAILURE);
        }
        else{
            printf("%s\n",dirname);
        }
    }
    return 0;
}