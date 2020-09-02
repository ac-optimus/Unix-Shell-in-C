/*
grep implementation

usage
    grep searchterm file1 file2 file3 ...

NOTE:
    with no file as argument reads from stdin.
    searchterm is a string not regular expression.
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
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


void grep(char* filename, char* pattern, int flag){
    /* main function to look for pattern in filename*/
    FILE* fp;
    if (filename !=NULL){
        fp = fopen(filename, "r");
    }
    else{
        fp = stdin; // stdin file stream
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t nread;

    if (fp == NULL) {
        // handelling error
        fprintf(stderr, "grep: '%s': %s\n", filename, strerror(errno));
        return;
        // exit(1);
    }

    int status;
    while ((nread = getline(&line, &len, fp)) != -1) {
        status = isPresent(line, pattern);
        if (status == 1){
            // print filename if more than one file query
            if ((filename != NULL) && (flag != 0)){
                printf("%s:",filename);
            }
            // print the line
            printf("%s", line);
        }
    }
    free(line); // free the memory, add error handeller?
    fclose(fp);
    // if (status == EOF){
    //     // handelling error
    //     fprintf(stderr, "cat: '%s': %s\n", filename, strerror(errno));
    //     exit(1);
    // }

}


int main(int argc, char* argv[]){
    char pattern[MAX_PATTERN_LENGTH];
    int flag = 0; // to print filename incase of multiple file arguments
    if (argc == 1){
        printf("grep: searchterm [file ...]\n");
        exit(1);
    }
    else if (argc == 2){
        // no file as argument
        strcpy(pattern, argv[1]);
        grep(NULL, pattern, flag);
    }
    else{
        strcpy(pattern, argv[1]);
        if (argc >3)
            flag = 1;
        for (int i =2; i<argc; i++){
            grep(argv[i], pattern, flag);
        }
    }
    return 0;
}