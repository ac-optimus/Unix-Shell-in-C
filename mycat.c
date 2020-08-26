/*
cat implementation
concatenate files and print on the standard output
usage
    cat file1 file2 file3 file4
*/

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define MAX_FILE_NAME_LENGTH 64

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



void cat_file(char* filename){
    // read a file, print it line by line
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        // handelling error
        fprintf(stderr, "cat: '%s': %s\n", filename, strerror(errno));
        exit(1);
    }
    char character;
    character = fgetc(fp); // can we catch error in this?
    while (character != EOF){ //read character by character
        printf("%c",character);
        character = fgetc(fp);
    }
    int status = fclose(fp);
    if (status == EOF){
        // handelling error
        fprintf(stderr, "cat: '%s': %s\n", filename, strerror(errno));
        exit(1);
    }
}


int main(int argc, char* argv[]){
    int status;
    for (int i=1;i<argc; i++){
        status = isDir(argv[i]);
        if (status == 1){
            printf("cat: %s: Is a directory\n", argv[i]);
            exit(1);
        }
        else{
            cat_file(argv[i]);
        }
    }
    return 0;
}