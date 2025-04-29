#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>


struct flagOptions {
    int a;
    int s;
    int r;
};

int get_terminal_cols() {
    struct winsize wbuf;
    if (ioctl(0, TIOCGWINSZ, &wbuf) == -1) {
        return 0;
    } else {
        return wbuf.ws_col;
    }
}

int r_lex(const void *a, const void *b) {
    return strcmp((const char *)b, (const char *)a);
}

void ls(char *dir_name, struct flagOptions flags) {
    DIR *dir_ptr;               
    struct dirent *dirent_ptr; 
    char entries[1024][1024]; 
    int longestLen = 0;
    int entryCount = 0;

    dir_ptr = opendir(dir_name);
    if (dir_ptr == NULL) {       
        perror(dir_name);     
        return;
    }

    while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
        if (flags.a == 0 && dirent_ptr->d_name[0] == '.') {
            continue;
        }

        int entry_len = strlen(dirent_ptr->d_name);
        if (longestLen < entry_len) {
            longestLen = entry_len;
        }

        strcpy(entries[entryCount], dirent_ptr->d_name);
        entryCount++;
    }

    if (flags.r) {
        qsort(entries, entryCount, sizeof(entries[0]), r_lex);
    } else if (flags.s) {
        qsort(entries, entryCount, sizeof(entries[0]), strcmp);
    }

    int terminalCols = get_terminal_cols();
    int numCols = (int)(terminalCols / (longestLen + 4));
    int numRows = (int)entryCount/numCols + 1;
    int entry = 0;

    for (int x = 0; x < numRows; x++) {
        for (int y = 0; y < numCols; y++) {
            if (entry >= entryCount) {
                break;
            }
            printf("%s", entries[entry]);
            
            int entryLen = strlen(entries[entry]);
            int spaces = longestLen - entryLen + 4;

            if (entry < entryCount - 1) {
                for (int s = 0; s < spaces; s++) {
                    printf(" ");
                }
            }
            entry++;
        }

        if (x < numRows) {
            printf("\n");
        }
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
