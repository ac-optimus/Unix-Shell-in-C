/* utility function to create new directory */
#include "isDir.h"

void mkdir_utility(char* pathname){

    int check = mkdir(pathname,0755);
        if (check==-1){
            //can not create the directory
            fprintf(stderr, "mkdir: '%s': %s\n", pathname, strerror(errno));
            return;
        }
}

void mymkdir(char* path){
    int status = isDir(path);
    // check if path already exist
    if ((status == 1) || (status == 2)){
        printf("mkdir: cannot create directory '%s' : File exists\n",path);
        return;
    }
    else{
        //make directory
        mkdir_utility(path);
    }
}