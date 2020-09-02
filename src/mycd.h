
// #include <stdio.h>
// #include <unistd.h> // chdir

void cd(char** args){
    if (args[2] !=NULL){
        fprintf(stderr, "cd: too many arguments\n");
        return;
    }

    char* path = args[1];

    if (path == NULL){
        path= HOME; // project home directory
    }
    int status = chdir(path);
    if (status == -1){
        fprintf(stderr, "cd: %s: No such file or directory\n", path);
        return;
    }
}
