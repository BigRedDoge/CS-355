#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096;

void printx(int argc, char** args);

struct buffer {
    void* buffer;
    ssize_t size;
};

/*
create
open
write
close
*/
int main(int argc, char* argv[]) {
    char fileName[256];
    int fd;
    struct buffer buf;

    strcpy(fileName, argv[1]);

    // create file
    if ((fd = creat(fileName, S_IRUSR | S_IWUSR)) == -1) {
        perror("Error creating new file");
    }

    for (int i = 0; i < argc; i++) {
        /*
        if (sizeof(argv[i]) < sizeof(buf.buffer)) {
            strcpy(buf.buffer, argv[i]);
        } else {
            perror("Argument too large");
        }
        */
            
        if (write(fd, argv[i], strlen(argv[i]) != strlen(argv[i]))) {
            perror("Error writing to file");
        }
        
        if (write(fd, " ", 1) != 1) {
            perror("Error writing to file");
        }
    }

    if (close(fd) == -1) {
        perror("Error closing file");
    }

    return 0;
}

void printx(int argc, char** args) {
    for (int i = 1; i < argc; i++) {
        int slen = strlen(args[i]);
    }
}