/*
cp implementation

usage
    cp  src_file dst_file
    cp file1 file2 file3 file4 dst_dir
    cp -r src_dir dst_dir

NOTE:
    for src_dir to dst_dir, dst_dir must already exit
    overwrite file if it alreay exist
*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include "mymkdir.h"
#include <libgen.h>
#include "mycp_utils.h"
// #include "isDir.h" // already included in mymkir.h


#define READ_BUFFER 1024
#define MAX_FILE_NAME_LENGTH 1024

void copy_file_to_file(char src[MAX_FILE_NAME_LENGTH], char dst[MAX_FILE_NAME_LENGTH], int flag){
    /*copy src file path to dst file path*/

    // check if src is a directory or regular file
    if (isDir(src) == 1){ // src is directory
        if (flag != 1){ // -r not passed as argument
            fprintf(stderr, "cp: -r not specified; omitting directory '%s'\n", src);
            exit(1);
        }
        iterate_dir(src, dst, flag); //traverse the src directory
        return;
    }

    char new_dst[MAX_FILE_NAME_LENGTH] = "";
    stpcpy(new_dst, dst);
    int check_type = isDir(new_dst);

    // update destination path if a dst is a directory.
    if (check_type == 1){ // dst is dir
        char* filename = basename(src); // get the filename
        update_path(new_dst, dst, filename); // update the dst path
    }

    int fd = open(src, O_RDONLY); // open src in read only mode
    if(fd == -1 ){
        fprintf(stderr, "cp: '%s': %s\n", src, strerror(errno));
        return;
    }
    // reading the content of the src file
    char buffer[READ_BUFFER];
    read(fd, &buffer,READ_BUFFER);
    struct stat file_stat;
    if (stat(src, &file_stat) == -1){
        // handling error
        fprintf(stderr, "stat: cannot stat '%s': %s\n", src,strerror(errno));
        exit(1);
    }
    // get the permissions of source files
    mode_t permission = file_stat.st_mode;
    // new file descriptor to create a copy
    int fd2 = creat(new_dst, permission);
    if(fd2 == -1 ){
        fprintf(stderr, "cp: '%s': %s\n", new_dst, strerror(errno));
        return;
    }
    write(fd2, buffer, strlen(buffer));
    // close the descriptors.
    close(fd2);
    close(fd);
    if(fd == -1 ){
        // handling error
        fprintf(stderr, "cp: '%s': %s\n", src, strerror(errno));
        return;
    }
}


int main(int argc, char* argv[]){

    if (argc <3){
        // less operands passed
        fprintf(stderr,"cp: missing operand\n");
        exit(1);
    }
    else{
        // path of destination -- argv[argc-1]
        // check if destination is present
        if ((argc >3) && (isDir(argv[argc-1]) !=1)){
            fprintf(stderr,"cp: target '%s' is not a directory\n", argv[argc-1]);
            exit(1);
        }
        int i = 1;
        int flag = 0;
        if (strcmp(argv[1], "-r")== 0){
            i = 2;
            flag = 1;
        }
        for (;i< argc-1; i++){
            copy_file_to_file(argv[i], argv[argc-1], flag);
        }
    }
    return 0;
}