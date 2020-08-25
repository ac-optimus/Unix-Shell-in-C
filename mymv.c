/*

move only files not directories.
support multiple file moving to a directory
oldfilelocation to newfilelocation
usage
    mv file1 file2 file3 dst_dir

*/
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


#define MAX_FILE_NAME_LENGTH 100


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


void mv(char oldpath[MAX_FILE_NAME_LENGTH], char dst[MAX_FILE_NAME_LENGTH]){

    // strip the filename
    char filename[MAX_FILE_NAME_LENGTH] = "";

    char* pos = strrchr(oldpath, '/');
    if (pos == NULL){
        // oldpath is itself filename
        strncpy(filename, oldpath, strlen(oldpath));
    }
    else{
        strncpy(filename, &pos[1], strlen(&pos[1]));
    }

    // destination path
    char newPath[MAX_FILE_NAME_LENGTH] = "";
    strncpy(newPath, dst, strlen(dst));
    if (isDir(newPath) == 1){  //is a directory
        // add prefix "/filename" to the directory name
        strcat(newPath, "/");
        strcat(newPath, filename);
    }
    int ret = rename(oldpath, newPath);

}




int main(int argc, char* argv[]){
    if (argc <=2){
        // no path is passed
        fprintf(stderr,"mv: missing operand\n");
        exit(EXIT_FAILURE);
    }
    else{
        char* dst= argv[argc-1]; // destination dir/ filename
        char pathname[MAX_FILE_NAME_LENGTH] = "";
        for (int i=1; i<argc-1; i++){
            strncpy(pathname, argv[i], strlen(argv[i])); //do we need to check for bound MAX_SIZE
            mv(pathname, dst);

        }
    }
    return 0;
}