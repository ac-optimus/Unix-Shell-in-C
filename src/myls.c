/*
ls implementation

usage
    myls
    myls dir1 dir2 dir3

NOTE:
    uses current directory when no argument is passed
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

#define MAX_FILE_NAME_LENGTH 64


void ls(char* dirname){
    // open the directory location to read
    DIR* dir = opendir(dirname);
    if (dir == NULL){
        // Handelling error
        fprintf(stderr, "ls: cannot access '%s': %s\n", dirname, strerror(errno));
        return;
    }
    struct dirent* dir_iterator; // to iterate over directory content

    while ((dir_iterator = readdir(dir)) !=NULL){
        if ((strcmp(dir_iterator->d_name, ".") !=0) && (strcmp(dir_iterator->d_name, "..")!=0)){
            // ignore "." and ".." directories
            printf("%s  ", dir_iterator->d_name);
        }
    }

    if (closedir(dir) == -1){// close directory
        // Handelling error
        fprintf(stderr, "ls: '%s': %s\n", dirname, strerror(errno));
        return;
    }
}


int main(int argc, char* argv[]){
    char dirname[MAX_FILE_NAME_LENGTH] = "";
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
                printf("%s:\n", argv[i]);
            ls(argv[i]);
            printf("\n");
        }
    }
    return 0;
}