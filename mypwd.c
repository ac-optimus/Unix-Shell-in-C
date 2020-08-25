/*
pwd implementation
    prints name of current/ working directory
usage
    mypwd
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

#define MAX_SIZE 1024

void mypwd(char* dirname){  //is  this void return type good to go?
    DIR* dir = opendir(dirname); // open the directory location to read.

    if (dir == NULL){
        // Handelling error
        fprintf(stderr, "opendir: '%s': %s\n", dirname, strerror(errno));
        exit(EXIT_FAILURE);
    }
    struct dirent* dir_reader; // to read the directory

    if ((dir_reader = readdir(dir)) !=NULL){
        printf("%s  ", dir_reader->d_name); // replace tab by \n to print files in new lines
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
            printf("%s\n",dirname);
        }
    }
    return 0;
}