/*
utility functions for shell.c
all the implemented binaries are present in MYbinaries.

NOTE:
    HOME -- project home directory
    BINARIES -- location of all the implemented binaries i.e $(HOME)/build/
*/

#define MAX_TOKEN_SIZE 64
// list of all the implemented binaries
char* MYbinaries[10] = {"ls","cd", "pwd", "grep", "cp", "mkdir", "mv", "cat", "chmod", NULL};

int useMyBinaries(char* utility_name){
    /* reutrn true if want to use my utility, else return False*/
    int indx=0;
    while (MYbinaries[indx]!=NULL){
        if (strcmp(utility_name, MYbinaries[indx])==0)
            break;
        indx+=1;
    }
    if (MYbinaries[indx] == NULL)
        return 0;
    return 1;
}


char* read_line(void){
    /* read line from input*/
    char* line = NULL;
    size_t len = 0;
    ssize_t nread;
    // get the input
    nread = getline(&line, &len, stdin);
    if (nread == -1){
        // handling error
        fprintf(stderr, "grep: %s\n", strerror(errno));
        exit(1);
    }
    return line;
}


char**  parse_line(char* line, int* background){
    /* parse line to tokenize it into commands and arguments */
    char * token;
    int buffer_mem = MAX_TOKEN_SIZE; // buffer memory
    char** args = malloc(buffer_mem*sizeof(char));

    if (!args){
        // handling error
        fprintf(stderr, "termi: allocation error\n");
        exit(1);
    }

    char deli[] = " \r\n"; // delimiter
    token = strtok (line,deli); // tokenization of read line

    int i=0;
    while (token != 0){

        if (i >= buffer_mem) {
            //reallocate memory if line lenght exceed buffersize
            buffer_mem += MAX_TOKEN_SIZE;
            args = realloc(args, buffer_mem * sizeof(char*));
            if (!args) {
                // handling error
                fprintf(stderr, "shell: allocation error\n");
                exit(1);
            }
        }
        // append ./my at the beginning of commands that are not imbuild(present in MYbinaries array)
        if ((i == 0) && (strcmp(token, "cd")!=0) && (strcmp(token, "pwd")) && (useMyBinaries(token)== 1)){ // and present in the array of binaries implemented
            char* command = strdup(token);
            char* command2 = strdup(token);
            strcpy(command2, BINARIES); // location of all the binaries
            strcat(command2, "/my");
            strcat(command2, command);
            args[i] = command2; // assign the path to args[i]
        }
        else{
            // do not update to use the inbuild binaries
            args[i] = token;
        }
        token = strtok (0, deli);
        i++;
    }
    // check if user wants to run the command in background
    if (strcmp(args[i-1], "&") ==0){
        *background = 1;
        i-=1;
    }
    args[i] = NULL;
    return args; // return the arguments
}


int execute(char** args, int* background){
    /* function to execute the command */

    // cd and pwd runs in the main process
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
    // if could not fork
    if (ret < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (ret == 0){
        // child process
        if (execvp(args[0], args) < 0){
            fprintf(stderr, "command not found\n");
            exit(1);
        }
    }
    else{
        if (*background==0){
            // wait for the last process/ command to finish execution
            int status;
            waitpid(ret, &status, WUNTRACED);
        }
    }
    return 0;
}
