/*
mv implementation

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
#include <libgen.h>
#include "isDir.h"


#define MAX_FILE_NAME_LENGTH 1024

void mv(char oldpath[MAX_FILE_NAME_LENGTH], char dst[MAX_FILE_NAME_LENGTH]){
    /* moves oldpath to dst */
    if (isDir(oldpath) == 0){ //oldpath does not exist
        // handling error
        fprintf(stderr, "mv: '%s': %s\n", oldpath, strerror(errno));
        return;
    }

    int check_type = isDir(oldpath);
    char filename[MAX_FILE_NAME_LENGTH]="";
    // get the source filename
    if (check_type == 1){
        strcpy(filename, basename(oldpath));
    }
    else{
        strcpy(filename, oldpath);
    }

    // destination path
    char newPath[MAX_FILE_NAME_LENGTH] = "";
    strncpy(newPath, dst, strlen(dst));
    // update destination path if dst is a directory.
    if (isDir(newPath) == 1){
        // adds suffix "/filename" to the directory name
        strcat(newPath, "/");
        strcat(newPath, filename);
    }
    int ret = rename(oldpath, newPath);
    if (ret == -1){
        // handling error
        fprintf(stderr, "mv: %s\n", strerror(errno));
        return;
    }
}


int main(int argc, char* argv[]){
    if (argc <=2){
        // no path is passed
        fprintf(stderr,"mv: missing operand\n");
        exit(EXIT_FAILURE);
    }
    else{
        char* dst= argv[argc-1]; // dst_dir
        char pathname[MAX_FILE_NAME_LENGTH] = ""; // source path
        for (int i=1; i<argc-1; i++){
            strncpy(pathname, argv[i], strlen(argv[i]));
            // move from pathname to dst
            mv(pathname, dst);
        }
    }
    return 0;
}