/*
mkdir implementation
support multiple direction creation
usage:
    mymkdir path_to_dir
    mymkdir dir1 dir2 dir3 ...

*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
// #include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include "mymkdir.h"


#define MAX_SIZE 1024

// void mymkdir(char* pathname){  //void return is not good ??

//     struct stat check_file; // some other name please
//     // printf("%d\n", stat(pathname, &check_file)); // -1 if does not exist and 0 if exist
//     if(stat(pathname, &check_file)==0) {
//         printf("cannot create directory '%s' : File exists\n",pathname);
//         exit(EXIT_FAILURE);
//     }
//     else{

//     int check = mkdir(pathname,0777); // what do do with this number ?
//     // add a check if a directory with the same file name already exist
//     // if not then call mkdir, what about the mode?
//     if (check==-1){
//         //can not create the directory
//         fprintf(stderr, "mkdir: '%s': %s\n", pathname, strerror(errno)); // what is the point of adding this line?
//         exit(EXIT_FAILURE);
//     }
//     else{
//         printf("directory created successfully\n");
//     }
//     }
// }


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
            printf("the directory -- %s\n", argv[i]);
            strncpy(pathname, argv[i], strlen(argv[i])); //do we need to check for bound MAX_SIZE
            // call mkdir
            mymkdir(pathname);
            // printf("%s\n", pathname);

        }
    }

    return 0;
}