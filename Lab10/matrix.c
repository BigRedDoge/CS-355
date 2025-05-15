#include <curses.h>
#include <stdio.h>
#include <unistd.h>     
#include <stdlib.h>     
#include <signal.h>


void matrix(int);
void shift_generate_row(int[COLS][LINES]);
void exit_program(int);
int x_size;
int y_size;

int main(int argc, char *argv[]) {
    int speed=1;           
    if(argc==2)
        speed=atoi(argv[1]); 

    initscr();              
    signal(SIGINT, exit_program);
    matrix(speed);
}

void matrix(int speed) {
    x_size = COLS;
    y_size = LINES;
    int matrix_array[x_size][y_size];
    // generate first row
    for (int i = 0; i < x_size; i++) {
        matrix_array[i][0] = rand() % 3;
        for (int j = 1; j < y_size; j++) {
            matrix_array[i][j] = 2;
        }
    }

    while (1) {
        clear();

        for (int i = 0; i < x_size; i++) {
            for (int j = 0; j < y_size; j++) {
                if (matrix_array[i][j] == 0) {
                    mvaddch(j, i, '0');
                } else if (matrix_array[i][j] == 1) {
                    mvaddch(j, i, '1');
                } else {
                    mvaddch(j, i, ' ');
                }
            }
        }
       


        usleep(250000 / speed);
        shift_generate_row(matrix_array);
        refresh();
    }
}

void shift_generate_row(int matrix_array[x_size][y_size]) {
    // shift rows down
    for (int i = 0; i < x_size; i++) {
        for (int j = y_size - 1; j > 0; j--) {
            matrix_array[i][j] = matrix_array[i][j - 1];
        }
    }
    //generate new row
    for (int i = 0; i < x_size; i++) {
        matrix_array[i][0] = rand() % 3;
    }
}

void exit_program(int sig) {
    clear();                
    endwin();
    signal(SIGINT, SIG_DFL);
}