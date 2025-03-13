#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
/*
command line arguments
function prototypes
file open/close
file read
file write
file create
structs
pointers
*/

struct buffer {
    char data[BUFFER_SIZE];
    ssize_t size;
};

/*
get file name from command line arg
read from file
copy to new file 
*/
int main(int argc, char* argv[]) {
    int newFileDesc;
    int oldFileDesc;
    char oldFileName[256];
    char newFileName[256];
    struct buffer fileBuffer;

    if (argc != 3) {
        printf("Incorrect number of command line arguments");
        return 1;
    }

    strcpy(oldFileName, argv[1]);
    strcpy(newFileName, argv[2]);

    if ((oldFileDesc = open(oldFileName, O_RDONLY)) == -1) {
        perror("Error opening original file");
        return 1;
    }

    if ((newFileDesc = creat(newFileName,  S_IRUSR | S_IWUSR)) == -1) {
        perror("Error creating new file");
        return 1;
    }   

    while ((fileBuffer.size = read(oldFileDesc, fileBuffer.data, BUFFER_SIZE)) > 0) {
        if (write(newFileDesc, fileBuffer.data, fileBuffer.size) != fileBuffer.size) {
            perror("Error copying data to new file");
            return 1;
        }
    }

    if (close(oldFileDesc) == -1 || close(newFileDesc) == -1) {
        perror("Error closing files");
        return 1;
    }

    return 0;
}
