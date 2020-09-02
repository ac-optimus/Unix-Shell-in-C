/*
have to make sure that if the input is just enter then simply do not run any process.
execute me problem aa rahe
problems:
    cding into another directory and then passing running some comman like ls, etc is creating problem.
    execute seem to be exact copy of the refference shared

// edit make file in such a way that
// want a home location for the project, cd without anyargument will bring at location.


left over
- how to run programs after doing cd
    - trailing effect in ls
- chmod
- cp
    - prob
    - dir to dir
- run processes in background []
- add binaries

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h> //fork an exec
#include <errno.h>
#include "mycd.h"


#define MAX_LINE_LENGTH 64 //same on the site
#define MAX_TOKEN_SIZE 64
#define MAX_FILE_NAME_LENGTH 64


char* pwd(){
    char* wd = malloc(MAX_FILE_NAME_LENGTH*sizeof(char));
    if (!wd) {
        fprintf(stderr, "termi: allocation error\n");
        exit(EXIT_FAILURE);
    }

    if (getcwd(wd, MAX_FILE_NAME_LENGTH) == NULL){
        fprintf(stderr, "chdir: %s\n",strerror(errno));
    }
    printf("%s\n", wd);
    return wd;
}

char* read_line(void){
    // get the input line
    // use getline instead, that seemed ot be better, here we have a limit based on max_line_length
    // fgets we fix he max size lenght of line, while getline looks for /n and read the line till there.
    // I would say try it.
    char* line = malloc(MAX_LINE_LENGTH*sizeof(char));

    if (!line) {
        fprintf(stderr, "termi: allocation error\n");
        exit(EXIT_FAILURE);
    }

    fgets(line, MAX_LINE_LENGTH, stdin); // i think a error handler should be here.
    return line;
}



char**  parse_line(char* line){

    char * token;
    int buffer_mem = MAX_TOKEN_SIZE;
    char** args = malloc(buffer_mem*sizeof(char)); // what happens if this does not holds.

    if (!args) {
        fprintf(stderr, "termi: allocation error\n");
        exit(EXIT_FAILURE);
    }

    char deli[] = " \t\r\n\a";
    token = strtok (line,deli);

    int i=0;
    while (token != 0){

        if (i >= buffer_mem) {
            buffer_mem += MAX_TOKEN_SIZE;
            args = realloc(args, buffer_mem * sizeof(char*));
            if (!args) {
                fprintf(stderr, "termi: allocation error\n");
                exit(1);
            }
        }
        if ((i == 0) && (strcmp(token, "cd")!=0) && (strcmp(token, "pwd"))){
            char* command = strdup(token);
            char* command2 = strdup(token);
            strcpy(command2, BINARIES); // location of all the binaries

            strcat(command2, "/my");
            strcat(command2, command);
            args[i] = command2;
        }
        else{
            args[i] = token;
        }
        token = strtok (0, deli);
        i++;
    }
    args[i] = NULL;
    return args;
}


int execute(char** args){

    if (strcmp(args[0], "cd")==0){
        cd(args);
        return 0;
    }
    if (strcmp(args[0], "pwd")==0){
        pwd();
        return 0;
    }
    //fork a child process
    int ret = fork();
    if (ret < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    //check if it is a child process

    if (ret == 0){
        //time to call another program --
        // printf("%s\n",args[0]);
        if (execvp(args[0], args) < 0){  //why args[0] not workings
            fprintf(stderr, "command not found\n");
            exit(1);
        }
        // printf("this shouldn't print out!\n");
    }
    else{
        //parnet process wait for child to finish execution.
        // if ( strcmp(args[argc-1],"&") !=0){
            wait(NULL);  //wait for child process to finish
    }

    return 0;
}


int main(void){

    char* line;
    char** args;
    int status;

    do {
        printf(">");
        line = read_line();
        args = parse_line(line);
        char** ptr = args;
        status = execute(args);
        printf("\n");
        // printf("%d",status);

        free(line);
        free(args);
    }while(1); // break if the last command could not be executed.

    return 0;
}