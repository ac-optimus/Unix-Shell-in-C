/*
ls implementation
    - no arguments -- uses the current working directory
    - one or more arguments -- directories
usage
    myls
    myls dir1 dir2 dir3
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

#define MAX_SIZE 1024

void ls(char* dirname){  //is  this void return type good to go?
    DIR* dir = opendir(dirname); // open the directory location to read.

    if (dir == NULL){
        // Handelling error
        fprintf(stderr, "opendir: '%s': %s\n", dirname, strerror(errno));
        exit(EXIT_FAILURE);
    }
    struct dirent* dir_reader; // to read the directory

    // do not know who the below line is working?
    while ((dir_reader = readdir(dir)) !=NULL){
        if ((!strcmp(dir_reader->d_name, ".")) || (!strcmp(dir_reader->d_name, ".."))){
            // ignore "." and ".." directories;
        }
        else
            printf("%s\n", dir_reader->d_name); // replace tab by \n to print files in new lines
    }
    closedir(dir);
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
            ls(dirname);
        }
    }
    else{ // one or more arguments
        for (int i=1; i<argc; i++){
            strncpy(dirname, argv[i], strlen(argv[i]));
            if (argc!=2)
                printf("%s:\n", dirname);
            ls(dirname);
            printf("\n");
        }
    }
    return 0;
}