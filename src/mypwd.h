/*
pwd implementation, used in shell.c

NOTE:
    changes directory to default, i.e HOME(project) directory when no argument is passed
*/

#define MAX_FILE_NAME_LENGTH 1024

char* pwd(){
    char* path = malloc(MAX_FILE_NAME_LENGTH*sizeof(char));
    if (!path) {
        // handling error
        fprintf(stderr, "shell: allocation error\n");
        exit(1);
    }
    //get the current working directory
    if (getcwd(path, MAX_FILE_NAME_LENGTH) == NULL){
        // handling error
        fprintf(stderr, "chdir: %s\n",strerror(errno));
    }
    //print the presents working directory
    printf("%s\n", path);
    return path;
}