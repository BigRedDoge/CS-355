#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096


void mode_to_string(int mode, char str[]) {
    strcpy(str,"----------");
    if(S_ISDIR(mode)) str[0]='d'; // directory?
    if(S_ISCHR(mode)) str[0]='c'; // terminal?
    if(S_ISBLK(mode)) str[0]='b'; // disk?
    if(S_ISLNK(mode)) str[0]='l'; // link?

    if(mode & S_IRUSR) str[1]='r'; // bits for the user
    if(mode & S_IWUSR) str[2]='w';
    if(mode & S_IXUSR) str[3]='x';

    if(mode & S_IRGRP) str[4]='r'; // bits for the group
    if(mode & S_IWGRP) str[5]='w';
    if(mode & S_IXGRP) str[6]='x';

    if(mode & S_IROTH) str[7]='r'; // bits for the others
    if(mode & S_IWOTH) str[8]='w';
    if(mode & S_IXOTH) str[9]='x';
}

void do_ls(char* directory) {
    DIR *dir_ptr;
    struct dirent *dirent_ptr;

    dir_ptr = opendir(directory);
    if (dir_ptr == NULL) {
        perror(directory);
        return;
    }

    while ((dirent_ptr = readdir(dir_ptr)) != 0) {
        struct stat info;
        if (stat(dirent_ptr->d_name, &info) != -1) {
            char modestring[11];
            mode_to_string(info.st_mode, modestring);
            
            char* access_time = ctime(&info.st_atime);

            printf("%s %s %s\n", modestring, access_time, dirent_ptr->d_name);
        } else {
            perror(dirent_ptr->d_name);
        }
    }
}

int do_cp(char* source, char* destination, int offset) {
    char buffer[BUFFER_SIZE];
    
    int src = open(source, O_RDONLY);
    if (src < 0) {
        perror(source);
        return 1;
    }

    int dst = creat(destination, S_IRUSR | S_IWUSR);
    if (dst < 0) {
        perror(destination);
        return 1;
    }

    lseek(src, offset, SEEK_SET);

    int numBytes;
    while ((numBytes = read(src, buffer, BUFFER_SIZE)) > 0) {
        if (write(dst, buffer, numBytes) != numBytes) {
            perror("Write error");
            return 1;
        }
    }

    if (numBytes < 0) {
        perror("Read error");
        return 1;
    }

    if (close(src) < 0 || close(dst) < 0) {
        perror("Error closing files");
        return 1;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    char directory[1024] = ".";
    char source[1024];
    char destination[1024];
    int offset = 0;

    strcpy(directory, argv[1]);
    strcpy(source, argv[2]);
    strcpy(destination, argv[3]);
    offset = atoi(argv[4]);

    do_ls(directory);

    return do_cp(source, destination, offset);

    //return 0;
}