#include <signal.h>  // for signal
#include <stdio.h>   // for printf
#include <stdlib.h>  // for exit
#include <unistd.h>  // for sleep
#include <fcntl.h>   // for io
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <curses.h>


/*
What to study:
    - handling signals
    - terminal modes
    - curses library
    - alarms and timers
*/

/*
Program will:
[*] Take file name and chars to read as input
[*] Read k bottom characters from file
[*] Get stats about file
[*] Write those characters to a new file filename_concat.txt
[*] Display those characters in curses bouncing around
[*] Exit after hitting Ctrl-C 5 times
*/

#define BUFFER_SIZE 256

int count = 0;

char* charsFromFile(int k, char* filename);
void signal_handler(int signum);
char* thestrcat(char* dest, char* src);
void getStatsAboutFile(char* filename);
void bouncy_curses(char* string_to_move);


int main(int argc, char* argv[]) {
    signal(SIGINT, signal_handler);

    char* filename = argv[1];
    int k = atoi(argv[2]);

    char* chars_from_file = charsFromFile(k, filename);
    printf("%s\n", chars_from_file);

    getStatsAboutFile(filename);

    bouncy_curses(chars_from_file);
    
    return 0;
}


void bouncy_curses(char* string_to_move) {
    initscr();
    noecho();
    nodelay(stdscr, TRUE);

    int height, width;
    getmaxyx(stdscr, height, width);

    int len = strlen(string_to_move);
    int x_vel = 1;
    int y_vel = 1;
    int x = (int)(width / 2);
    int y = (int)(height / 2);

    while (1) {
        clear();
        for (int i = 0; i < len; i++) {
            mvaddch(y, x + i, string_to_move[i]);
        }
        x += x_vel;
        y += y_vel;

        if (x >= width - len || x <= 0) {
            x_vel = -1 * x_vel;
        }
        if (y >= height || y <= 0) {
            y_vel = -1 * y_vel;
        }
        refresh();
        usleep(35000);
    }

}

void signal_handler(int signum) {
    // SIG_IGN ignore the signal
    // SIG_DFL reset signal to its default action
    printf("Pressed Ctrl-C!\n");
    if (count >= 5) {
        printf("Goodbye!\n");
        endwin();
        signal(SIGINT, SIG_DFL);
        raise(SIGINT);
    }
    count++;
}


void getStatsAboutFile(char* filename) {
    struct stat info;
    if (stat(filename, &info) != -1) {
        char* access_time = ctime(&info.st_atime);
        printf("%s: Access time - %s\n", filename, access_time);
    } else {
        perror(filename);
    }
}


char* charsFromFile(int k, char* filename) {
    int fd, dst;
    char buffer[BUFFER_SIZE];
    static char chars[BUFFER_SIZE*10];

    char filename_concat[256] = "concat.txt";
    char new_file_name[256] = "concat.txt";

    //strcpy(new_file_name, filename);
    //thestrcat(new_file_name, filename_concat);

    if ((fd = open(filename, O_RDONLY)) > -1 && (dst = creat(new_file_name, S_IRUSR | S_IWUSR)) > -1) {
        int numBytes;

        lseek(fd, -k, SEEK_END);

        while ((numBytes = read(fd, buffer, BUFFER_SIZE)) > 0) {
            if (write(dst, buffer, numBytes) != numBytes) {
                perror("Write error");
                exit(1);
            }
            thestrcat(chars, buffer);

            if (numBytes < 0) {
                perror("Read error");
                exit(1);
            }
        }

        if (close(fd) < 0) {
            perror("Error closing file");
            exit(1);
        }

        if (close(dst) < 0) {
            perror("Error closing file");
            exit(1);
        }
        
        
    } else {
        perror(filename);
        exit(1);
    }

    return chars;
}

char* thestrcat(char* dest, char* src) {
    char* dest_ptr = dest;
    while (*dest_ptr != 0) {
        dest_ptr++;
    }
    
    while (*src != 0) {
        *dest_ptr = *src;
        dest_ptr++;
        src++;
    }

    *dest_ptr = '\0';

    return dest;
}