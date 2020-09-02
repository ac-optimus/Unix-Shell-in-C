/*
mv implementations
    directory to directory (new or already exisiting)
    multiple files to a directory[directory must be existing]
    old file to old file
usage
    mv old_dir dst_dir
    mv file1 file2 file3 dst_dir
*/
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "isDir.h"


#define MAX_FILE_NAME_LENGTH 100

void mv(char oldpath[MAX_FILE_NAME_LENGTH], char dst[MAX_FILE_NAME_LENGTH]){
    // what if old file does not exist
    if (isDir(oldpath) == 0){ //oldpath does not exist
        fprintf(stderr, "mv: '%s': %s\n", oldpath, strerror(errno));
        return;
    }
    // strip the filename
    char filename[MAX_FILE_NAME_LENGTH] = "";

    char* pos = strrchr(oldpath, '/');
    if (pos == NULL){
        // oldpath is itself filename
        strncpy(filename, oldpath, strlen(oldpath));
    }
    else{
        strncpy(filename, &pos[1], strlen(&pos[1]));
    }

    // destination path
    char newPath[MAX_FILE_NAME_LENGTH] = "";
    strncpy(newPath, dst, strlen(dst));
    if (isDir(newPath) == 1){  //is a directory
        // adds "/filename" to the directory name
        strcat(newPath, "/");
        strcat(newPath, filename);
    }
    int ret = rename(oldpath, newPath);
}


int main(int argc, char* argv[]){
    if (argc <=2){
        // no path is passed
        fprintf(stderr,"mv: missing operand\n");
        exit(EXIT_FAILURE);
    }
    else{
        char* dst= argv[argc-1]; // dst_dir
        char pathname[MAX_FILE_NAME_LENGTH] = "";
        for (int i=1; i<argc-1; i++){
            strncpy(pathname, argv[i], strlen(argv[i])); //do we need to check for bound MAX_SIZE
            mv(pathname, dst);

        }
    }
    return 0;
}