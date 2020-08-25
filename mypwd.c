/*
way : 1
    open the directory
    read the directory
    print the name
    close the directory

*/







    while ((dir_reader = readdir(dir)) !=NULL){ // see the content in the directory.
        // pointer shifts to the new file/ directory.
            stpcpy(cur_file, src);
            strcat(cur_file, "/");
            strncat(cur_file, dir_reader->d_name, strlen(dir_reader->d_name));