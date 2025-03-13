#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024


struct flagOptions {
    int e;
    int n;
    int s;
};

struct buffer {
    char data[BUFFER_SIZE];
    ssize_t size;
};

void printFile(char* fileName, struct flagOptions flags);

int main(int argc, char* argv[]) {
    struct flagOptions flags;
    char fileNames[25][256];
    int fileCount = 0;

    flags.e = 0;
    flags.n = 0;
    flags.s = 0;

    char option;
    while((option = getopt(argc, argv, "ens")) != -1) {
        switch(option) {
            case 'e':
                flags.e = 1;
                printf("flag E enabled\n");
                break;
            case 'n':
                flags.n = 1;
                printf("flag N enabled\n");
                break;
            case 's':
                flags.s = 1;
                printf("flag S enabled\n");
                break;  
        }
    }

    if (argc < 2) {
        printf("Incorrect number of arguments");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") != 0 && strcmp(argv[i], "-n") != 0 && strcmp(argv[i], "-s") != 0) {
            strcpy(fileNames[fileCount], argv[i]);
            fileCount++;
        }
    }

    for (int i = 0; i < fileCount; i++) {
        printf("Printing file: %s\n", fileNames[i]);
        printFile(fileNames[i], flags);
    }

    return 0;
}


void printFile(char* fileName, struct flagOptions flags) {
    struct buffer fileBuffer;
    int fileDesc;

    printf("Opening file: %s\n", fileName);

    if ((fileDesc = open(fileName, O_RDONLY)) == -1) {
        printf("Error opening file: %s", fileName);
        return;
    }

    printf("%d\n", flags.s);

    int line = 1;
    int newLine = 1;
    while ((fileBuffer.size = read(fileDesc, fileBuffer.data, BUFFER_SIZE)) > 0) {
        for (int i = 0; i < fileBuffer.size; i++) {
            if (newLine) {
                if (flags.n) {
                    printf("%d. ", line);
                }
                newLine = 0;
            }

            if (fileBuffer.data[i] != '\0') {
                if (fileBuffer.data[i+1] == '\n') {
                    if (flags.e) {
                        printf("$");
                    }
                }
            }

            if (fileBuffer.data[i] != '\n') {
                printf("%c", fileBuffer.data[i]);
            } else {
                if (!flags.s) {
                    printf("%c", fileBuffer.data[i]);
                }

                line++;
                newLine = 1;
            }
        }
    }

    if (close(fileDesc) == -1) {
        printf("Error closing file");
        return;
    }
}