/*
unix shell implemented in c.
NOTE:
    utilities present in MYbinaries (in shell_utils.h) are used instead of inbuild binaries.
    char* MYbinaries[10] = {"ls","cd", "pwd", "grep", "cp", "mkdir", "mv", "cat", "chmod", NULL}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h> //fork an exec
#include <errno.h>
#include "mycd.h"
#include "mypwd.h"
#include "shell_utils.h"


void shellRun(void){
    /* read line--> parse and tokonize the line-->execute the command */
    char* line;
    char** args;
    int status;
    int background; // flag for background execution of commmand
    do {
        background = 0;
        printf(">");
        line = read_line(); //read the input line
        // ignore furhter operations if empty line
        if (strlen(line) == 1){
            continue;
        }
        args = parse_line(line, &background); // parse line
        // handle exit
        if (strcmp(args[0],"exit")==0)
            break;
        status = execute(args, &background); // execute commmand
        printf("\n");
        // printf("%d",status);
        //free memory allocated
        free(line);
        free(args);
    }while(1);
}


int main(void){
    // start the shell
    shellRun();
    return 0;
}