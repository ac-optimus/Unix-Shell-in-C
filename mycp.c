/*
this cp facitilates
 - file to file copy   [X]
 - multiple files to a directory copy
 - directory to directory copy (subdirectories are not coppied just the files.)

usage
    cp src_file dst_file
    cp s1 s2 s3 s4 dst_dir
    cp -r src_dir dst_dir
// how to copy files with same permissions?
*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <stdbool.h>   // bool data type
#include "mymkdir.h"

#define READ_BUFFER 1025
#define PERMISSION 0666
#define MAX_FILE_NAME_LENGTH 100


void resolve_dir(char src[MAX_FILE_NAME_LENGTH], char dst[MAX_FILE_NAME_LENGTH]);
void file_to_file_n_dir(char src[MAX_FILE_NAME_LENGTH], char dst[MAX_FILE_NAME_LENGTH]);


int isDir(char PATH[MAX_FILE_NAME_LENGTH]){ // look at the return values seems locha
    /* Returns
            0 -- PATH is not presents
            1 -- PATH is a directory
            2 -- PATH is a regular file
    */
    struct stat check_file; // some other name please
    if (stat(PATH, &check_file)==-1){ // 0 when file exist
        // printf("cannot stat on %s location!\n", PATH);  //are you planning to print this?
        return 0;
    }
    if (S_ISDIR(check_file.st_mode)) return 1;
    if (S_ISREG(check_file.st_mode)) return 2;

}


void resolve_dir(char src[MAX_FILE_NAME_LENGTH], char dst[MAX_FILE_NAME_LENGTH]){

    DIR* dir = opendir(src); // open the directory location to read.
    printf("I was called\n");
    if (dir == NULL){
        // Handelling error
        fprintf(stderr, "opendir: '%s': %s\n", src, strerror(errno)); // maybe add a error that can not read the file
        return;
        // exit(EXIT_FAILURE);
    }


    // call file_to_file_n_dir(...)
    //  make a new directory and then process it
    // update the destination location
    char new_dst =




    // traverse src and pick all the files





    struct dirent* dir_reader; // to read the directory
    char cur_file[MAX_FILE_NAME_LENGTH] = "";
    while ((dir_reader = readdir(dir)) !=NULL){ // see the content in the directory.
        // pointer shifts to the new file/ directory.
            stpcpy(cur_file, src);
            strcat(cur_file, "/");
            strncat(cur_file, dir_reader->d_name, strlen(dir_reader->d_name));
            printf("About to process, %s\n", cur_file);
        if (isDir(cur_file) == 2){
            // stpcpy(cur_file, src);
            // strcat(cur_file, "/");
            // strncat(cur_file, dir_reader->d_name, strlen(dir_reader->d_name));
            // printf("asfasd `%s\n",cur_file);
            file_to_file_n_dir(cur_file, dst);
        }
        // printf("%s  ", dir_reader->d_name); // replace \n by tab aagar man kare


}
}

void file_to_file_n_dir(char src[MAX_FILE_NAME_LENGTH], char dst[MAX_FILE_NAME_LENGTH]){
    // check by changing the file permission.
    // resolve the source if it is file or a directory
    if (isDir(src) == 1){
        // call the directory
        printf ("src is a directory!\n");
        resolve_dir(src, dst);

        return;
        // exit(EXIT_FAILURE);
    }

    int fd = open(src, O_RDONLY); // open the file in read only mode
    if(fd == -1 ){
        printf("Unable to open the file %s\n", src);  //do we need to use frpint?
        exit(EXIT_FAILURE);
    }
    // reading the content of the file...
    char buffer[READ_BUFFER];
    read(fd, &buffer,READ_BUFFER);
    /*------reading ka kam khatam yaha tak-----*/



    char new_dst[MAX_FILE_NAME_LENGTH] = "";
    stpcpy(new_dst, dst);

    //befor that how about checking weather it is a file or directory and then updating the path
    int check_type = isDir(new_dst);
    // update destination path if a dst is a directory.
    if (check_type == 1){ // dst is dir
        strcat(new_dst, "/");

        strncat(new_dst, src, strlen(src));
        // have to look how to rever this as well, we have passed it by reference.
    }

    check_type = isDir(new_dst);
    // printf ("%s\n",new_dst);
    if (check_type == 2){ // no point in going ahead if the destination is a regualr file and already exist
        printf("this file is already present sir!\n");
        // return; // this seems better
        return;
        // exit(EXIT_FAILURE); // this can be ignored as the cp does the same, it also ignores.
    }
    printf("source -- %s, destination -- %s\n", src, new_dst);
    // new file descriptor to create a copy.
    int fd2 = open(new_dst, O_CREAT, PERMISSION);
    write(fd2, buffer, strlen(buffer));
    // close the descriptors.
    close(fd2);
    close(fd);
}

// have to resolve the source files



int main(int argc, char* argv[]){
    if (argc <3){
        // no path is passed
        fprintf(stderr,"cp: missing operand\n");
        exit(EXIT_FAILURE);
    }
    else{
        // char* src = argv[1]; // there can be multiple source, directories or files, we need to check them.
        char dst[MAX_FILE_NAME_LENGTH] = "";
        strncat(dst, argv[argc-1], strlen(argv[argc-1]));

        if ((argc > 3) && (isDir(dst) !=1)){
            fprintf(stderr,"cp: target %s is not a directory\n", dst);
            exit(EXIT_FAILURE);
        }
        char src[MAX_FILE_NAME_LENGTH] = "";

        for (int i=1; i< argc-1; i++){
            strcpy(src, argv[i]);
            printf ("%s\n", src);
            file_to_file_n_dir(src, dst);
        }
    }
    return 0;
}