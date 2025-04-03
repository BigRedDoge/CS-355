#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
//#include <time.h>
#include <unistd.h>


struct flagOptions {
    int a;
    int s;
    int r;
};

int r_lex(const void *a, const void *b) {
    return strcmp((const char *)b, (const char *)a);
}

void ls(char *dir_name, struct flagOptions flags) {
    DIR *dir_ptr;               
    struct dirent *dirent_ptr; 
    char entries[1024][1024]; 

    dir_ptr = opendir(dir_name);
    if (dir_ptr == NULL) {       
        perror(dir_name);     
        return;
    }

    int entryCount = 0;
    while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
        if (flags.a == 0 && dirent_ptr->d_name[0] == '.') {
            continue;
        }
        strcpy(entries[entryCount], dirent_ptr->d_name);
        entryCount++;
    }

    if (flags.r) {
        qsort(entries, entryCount, sizeof(entries[0]), r_lex);
    } else if (flags.s) {
        qsort(entries, entryCount, sizeof(entries[0]), strcmp);
    }

    for (int i = 0; i < entryCount; i++) {
        printf("%s\n", entries[i]);
    }

    closedir(dir_ptr); 
}

int main(int argc, char* argv[]) {
    struct flagOptions flags = {0, 0, 0};
    int fileCount = 0;
    char directory[1024] = ".";

    flags.a = 0;
    flags.s = 0;
    flags.r = 0;

    char option;
    while((option = getopt(argc, argv, "ars")) != -1) {
        switch(option) {
            case 'a':
                flags.a = 1;
                break;
            case 's':
                flags.s = 1;
                break;
            case 'r':
                flags.r = 1;
                break;  
        }
    }
    

    int start_index = 1;
    if (flags.a) {
        start_index += 1;
    }
    if (flags.s) {
        start_index += 1;
    }
    if (flags.r) {
        start_index += 1;
    }

    if (flags.r && flags.s) {
        printf("Cannot use -r and -s flags together\n");
        return 1;
    }

    if (argc > start_index) {
        strcpy(directory, argv[start_index]);
    }

    ls(directory, flags);

    return 0;
}
