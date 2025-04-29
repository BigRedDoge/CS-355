#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 1024

int main(int ac, char* av[]) {
    if (ac != 2)   // the program requires one parameter: the target terminal name
                // you may need to add /dev before ttyname, e.g. /dev/pts/1
        fprintf(stderr, "usage: %s ttyname\n", av[0]);
    else {
        int fd = open(av[1], O_WRONLY);  // open the target terminal for writing
        if (fd == -1)                       // what if it could not be opened
            perror(av[1]);
        else {
            char buf[BUFSIZE];
            char hiMessage[]="Message from another terminal...\n";
            char byeMessage[]="EOF\n";

            char *fruits[] = {"apple", "pear", "banana", "orange", "plum"};
            int fruitLen = 5;

            write(fd, hiMessage, strlen(hiMessage));
            
            while (fgets(buf, BUFSIZE, stdin) != 0) {  // read a string from the current terminal
                int allowed = 1;
                for (int i = 0; i < fruitLen; i++) {
                    if (strstr(buf, fruits[i]) != NULL) {  // check for prohibited substring
                        printf("You entered a prohibited word: %s. Your message will not be sent.\n", fruits[i]); 
                        allowed = 0;
                    }
                }
                
                if (allowed) {
                    if (write(fd, buf, strlen(buf)) ==- 1) // write it to the target terminal
                        break;
                }
            }

            write(fd, byeMessage, strlen(byeMessage)); // print EOF at the very end of the session
            close(fd);
        }
    }
}