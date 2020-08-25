
void mymkdir(char* pathname){  //void return is not good ??

    struct stat check_file; // some other name please
    // printf("%d\n", stat(pathname, &check_file)); // -1 if does not exist and 0 if exist
    if(stat(pathname, &check_file)==0) {
        printf("mkdir: cannot create directory '%s' : File exists\n",pathname);
        exit(EXIT_FAILURE);
    }
    else{
        int check = mkdir(pathname,0777); // what do do with this number ?
        // add a check if a directory with the same file name already exist
        // if not then call mkdir, what about the mode?
        if (check==-1){
            //can not create the directory
            fprintf(stderr, "mkdir: '%s': %s\n", pathname, strerror(errno)); // what is the point of adding this line?
            exit(EXIT_FAILURE);
        }
        // else{
        //     printf("directory created successfully\n");
        // }
    }
}