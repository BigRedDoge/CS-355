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
                break;
            case 'n':
                flags.n = 1;
                break;
            case 's':
                flags.s = 1;
                break;  
        }
    }

    if (argc < 2) {
        printf("Incorrect number of arguments");
        return 1;
    }
    
    int start_index = 1;
    if (flags.e || flags.n || flags.s) {
        start_index = 2;
    }
    for (int i = start_index; i < argc; i++) {
        strcpy(fileNames[fileCount], argv[i]);
        fileCount++;
    }

    for (int i = 0; i < fileCount; i++) {
        printFile(fileNames[i], flags);
    }

    return 0;
}


void printFile(char* fileName, struct flagOptions flags) {
    struct buffer fileBuffer;
    int fileDesc;

    if ((fileDesc = open(fileName, O_RDONLY)) == -1) {
        printf("Error opening file: %s", fileName);
        return;
    }

    int line = 1;
    int newLine = 1;
    while ((fileBuffer.size = read(fileDesc, fileBuffer.data, BUFFER_SIZE)) > 0) {
        int second_newline = 0;
        for (int i = 0; i < fileBuffer.size; i++) {
            if (newLine && !second_newline) {
                if (flags.s) {
                    int whitespace = 1;
                    int j = i;
                    while (fileBuffer.data[j] != '\n' && whitespace) {
                        if (fileBuffer.data[j] != ' ' && fileBuffer.data[j] != '\t' && fileBuffer.data[j] != '\n' && fileBuffer.data[j] != '\r') {
                            whitespace = 0;
                            break;
                        }
                        j++;
                    }
                    if (whitespace) {
                        i = j;
                        second_newline = 1;
                    }
                }
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
                if (!second_newline) {
                    printf("%c", fileBuffer.data[i]);
                    line++;
                    newLine = 1;
                    second_newline = 1;
                } else {
                    second_newline = 0;
                }
            }
        }
    }

    if (close(fileDesc) == -1) {
        printf("Error closing file");
        return;
    }
}