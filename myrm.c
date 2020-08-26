/*
remove files and directories
usage
    rm file1 file2 file3 file4
    rm -r dir1 dir2
*/

#include <stdio.h> // removes
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define MAX_FILE_NAME_LENGTH 64


void rm(char* location, int* flag);


int isDir(char PATH[MAX_FILE_NAME_LENGTH]){ // look at the return values seems locha
    /* Returns
            0 -- PATH is not present
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

} // maybe have a .h file for this



void emptyDir(char* dirname, int* flag){  //is  this void return type good to go?
    /*
    removes all the files and directory of the passed dirname directory recurssively.
    */
    DIR* dir = opendir(dirname); // open the directory location to read.

    if (dir == NULL){
        // handelling error
        fprintf(stderr, "opendir: '%s': %s\n", dirname, strerror(errno));
        exit(EXIT_FAILURE);
    }

    struct dirent* dir_reader; // to read the directory
    char newlocation[MAX_FILE_NAME_LENGTH] = "";
    while ((dir_reader = readdir(dir)) !=NULL){
        if ((!strcmp(dir_reader->d_name, ".")) || (!strcmp(dir_reader->d_name, ".."))){
            // ignore "." and ".." directories
        }
        else{
            strcpy(newlocation, dirname);
            strcat(newlocation, "/");
            strncat(newlocation, dir_reader->d_name, strlen(dir_reader->d_name));
            // remove the directory file/ subdirectory
            rm(newlocation, flag);
        }
    }
    closedir(dir);
}



void rm(char* location, int* flag){
        /*
        checks  if location is file -- remove it
                if directory then first empty it and then recrussively remove its content
        */
        int status = isDir(location); // location is file or directory
        int check;

        if (status == 2){
            //location is file;
            check = remove(location);

            if (check == -1){
                // handelling error
                fprintf(stderr, "rm: '%s': %s\n", location, strerror(errno));
                exit(EXIT_FAILURE);
            }

        }
        else if (status == 1){
            // location is directory
                if (*flag != 1){
                    // handelling error
                    printf("rm: cannot remove '%s': Is a directory\n", location);
                    return;
                }

                emptyDir(location, flag);
                check = rmdir(location);

                if (check == -1){
                    // handelling error
                    fprintf(stderr, "rm: '%s': %s\n", location, strerror(errno));
                    exit(EXIT_FAILURE);
                }
        }
        else
            printf("rm: cannot remove '%s': No such file or directory\n",location);
}



int main(int argc, char* argv[]){
    if (argc == 1){
        // no path is passed
        fprintf(stderr,"rm: missing operand\n");
        exit(EXIT_FAILURE);
    }
    else{
        // we can have a list of args that to be delete
        char location[MAX_FILE_NAME_LENGTH] = "";
        int i = 1;
        int flag =0;
        if (strcmp(argv[1], "-r") == 0){
            // check flag to track  if -r is also passed
            i = 2;
            flag = 1;
        }
        for (;i<argc; i++){
            strcpy(location, argv[i]); // add a check for fileaname if too long?
            // call rm
            rm(location, &flag);
        }
    }
    return 0;
}