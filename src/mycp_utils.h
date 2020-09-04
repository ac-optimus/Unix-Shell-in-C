/* utility functions for cp implementation (mycp.c)*/
#define MAX_FILE_NAME_LENGTH 64

void copy_file_to_file(char src[MAX_FILE_NAME_LENGTH], char dst[MAX_FILE_NAME_LENGTH], int flag);

void update_path(char* new_path, char* path, char* filename){
    /* update  new_path by appending filename at the end of path */
    stpcpy(new_path, path);
    strcat(new_path, "/");
    strncat(new_path, filename, strlen(filename));
}


void iterate_dir(char* src, char* dst, int flag){
    /* traverse src directory */
    DIR* dir = opendir(src);
    if (dir == NULL){
        // Handelling error
        fprintf(stderr, "opendir: '%s': %s\n", src, strerror(errno));
        return;
    }
    struct dirent* dir_iterator; // to read the directory
    int status;
    char new_src[MAX_FILE_NAME_LENGTH] = "";
    char new_dst[MAX_FILE_NAME_LENGTH] = "";

    while ((dir_iterator=readdir(dir))!=NULL){
         if ((strcmp(dir_iterator->d_name, ".") !=0) && (strcmp(dir_iterator->d_name, "..")!=0)){
            // ignore "." and ".." directories;

            update_path(new_src, src, dir_iterator->d_name);
            status = isDir(new_src);
            strcpy(new_dst, dst);
            // if new_source is a directory, create new dst and update old dst path to new_dst
            if (status == 1){ // a directory
                update_path(new_dst, dst, dir_iterator->d_name);
                mkdir_utility(new_dst); // make a new directory
            }
            //call copy_file_to_file recurssively with new source and dst path
            copy_file_to_file(new_src, new_dst, flag);
        }
    }
}
