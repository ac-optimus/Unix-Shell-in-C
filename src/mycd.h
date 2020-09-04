/*
cd implementation, used in shell.c

NOTE:
    changes directory to default, i.e HOME(project) directory when no argument is passed
*/

void cd(char** args){
    if (args[2] !=NULL){
        fprintf(stderr, "cd: too many arguments\n");
        return;
    }
    char* path = args[1];
    // set path to HOME directory
    if (path == NULL){
        path= HOME; // project home directory
    }
    // change directory to path
    int status = chdir(path);
    if (status == -1){
        fprintf(stderr, "cd: %s: No such file or directory\n", path);
        return;
    }
}
