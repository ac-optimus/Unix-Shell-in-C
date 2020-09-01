/*
search term is always passed with zero or more files to grep
should work well for even long lines
with no command line argument throw an error
in one approach we can tokenize each line an

*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h> //exit()
#include <string.h>

#define MAX_PATTERN_LENGTH 1024


int isPresent(char* line, char* pattern){
    /* return 1 if a substring else return 0*/
    int line_length = strlen(line);  //length os line
    int pattern_length = strlen(pattern); // length of the pattern
    int k;
    for (int i = 0; i< line_length; i++){
        k = 0;
        // check if pattern is a substring starting with ith index of line
        while ((i+k < line_length) && (k < pattern_length)){
            if (line[i + k] != pattern[k]){
                break;
            }
            k++;
        }
        if (k == pattern_length){
            return 1;
        }
    }
    return 0;
}


void grep(char* filename, char* pattern){
    FILE* fp;
    if (filename !=NULL){
        fp = fopen(filename, "r");
    }
    else{
        fp = stdin;
    }
    char* line = NULL;
    size_t len = 0; // what is this type all about
    ssize_t nread; // what is this, nread ?  its datatype?

    if (fp == NULL) {
        // handelling error
        // printf("wgrep: cannot open file %s\n"filename);
        fprintf(stderr, "wgrep: '%s': %s\n", filename, strerror(errno));
        exit(1);
    }

    int status;
    while ((nread = getline(&line, &len, fp)) != -1) {
        status = isPresent(line, pattern);
        if (status == 1){
            // print the line
            printf("%s", line);
        }
    }
    free(line);
    fclose(fp);
    // if (status == EOF){
    //     // handelling error
    //     fprintf(stderr, "cat: '%s': %s\n", filename, strerror(errno));
    //     exit(1);
    // }

}


int main(int argc, char* argv[]){
    char pattern[MAX_PATTERN_LENGTH];
    if (argc == 1){
        // what to do here
        // print the error -
        // "wgrep: searchterm [file ...]"
        exit(1);
    }
    if (argc == 2){
        // no filename passed
        printf("here??\n");
        strcpy(pattern, argv[1]);
        grep(NULL, pattern);
    }
    else{
        strcpy(pattern, argv[1]);
        for (int i =2; i<argc; i++){
            grep(argv[i], pattern);
        }
    }
    return 0;
}