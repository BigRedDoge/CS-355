#include <curses.h>
#include <stdio.h>
#include <unistd.h>     
#include <stdlib.h>     
#include "snake.h"



int main(int argc, char *argv[]) {
    int speed=1;            // speed of the animations
    if(argc==2)
        speed=atoi(argv[1]);  // convert a char* to an int
    initscr();              // initialize the curses library
    nodelay(stdscr, TRUE);  // do not wait for input when getch() is called
    keypad(stdscr, TRUE);   // enable special keys (arrow keys)
    noecho();               // do not echo input to the screen
    clear();                // clear the screen

    struct snake snake = initializeSnake();
    playSnake(snake, speed);

    free(snake.body);
    endwin();                // turn off curses
}


struct snake initializeSnake() {
    struct snake snake;
    //struct body body[100];  // array of body parts
    snake.body = malloc(sizeof(struct body) * MAX_SNAKE_LENGTH);

    snake.length = 1;
    snake.direction = 1;
    
    snake.body[0].x = (int)(LINES / 2);
    snake.body[0].y = (int)(COLS / 2);

    return snake;
}

void playSnake(struct snake snake, int speed) {
    int nextMove;
    int newMoveX;
    int newMoveY;
    
    struct food food;
    spawnFood(&food);

    // play snake game while alive and not hit quit
    while (1) {
        clear();
        // draw game
        //drawSnake(snake);
        drawFood(food);

        // move snake
        nextMove = getch();
        switch (nextMove) {
            case 'w':
            case KEY_UP:
                newMoveX = snake.body[0].x - 1;
                newMoveY = snake.body[0].y;
                snake.direction = 0;
                //moveSnake(&snake, newMoveX, newMoveY);   
                break;             
            case 'a':
            case KEY_LEFT: 
                newMoveX = snake.body[0].x;
                newMoveY = snake.body[0].y - 1;
                snake.direction = 3;
                //moveSnake(&snake, newMoveX, newMoveY);
                break;
            case 's':
            case KEY_DOWN:
                newMoveX = snake.body[0].x + 1;
                newMoveY = snake.body[0].y;
                snake.direction = 2;
                //moveSnake(&snake, newMoveX, newMoveY);
                break;
            case 'd':
            case KEY_RIGHT:
                newMoveX = snake.body[0].x;
                newMoveY = snake.body[0].y + 1;
                snake.direction = 1;
                //moveSnake(&snake, newMoveX, newMoveY);
                break;
            case 'q':
                return;
            default:
                if (snake.direction == 0) {
                    newMoveX = snake.body[0].x - 1;
                    newMoveY = snake.body[0].y;
                } else if (snake.direction == 1) {
                    newMoveX = snake.body[0].x;
                    newMoveY = snake.body[0].y + 1;
                } else if (snake.direction == 2) {
                    newMoveX = snake.body[0].x + 1;
                    newMoveY = snake.body[0].y;
                } else if (snake.direction == 3) {
                    newMoveX = snake.body[0].x;
                    newMoveY = snake.body[0].y - 1;
                }
        }
        moveSnake(&snake, newMoveX, newMoveY);

        if (!checkAlive(snake))
            break;

        checkIfEatFood(&snake, &food);
        drawSnake(&snake);

        // pause the process
        usleep(1000000 / speed);
        refresh();
    }

    // game over
    clear();
    move((int)(LINES / 2), (int)(COLS / 2));
    addstr("Game Over");
    move((int)(LINES / 2) + 2, (int)(COLS / 2));
    addstr("Score: ");
    char score[10];
    sprintf(score, "%d", snake.length);
    addstr(score);
    move((int)(LINES / 2) + 4, (int)(COLS / 2));
    addstr("Press any key to exit");
    refresh();
    usleep(1000000 / speed);
}

void spawnFood(struct food *food) {
    // spawn food
    food->x = rand() % LINES;
    food->y = rand() % COLS;
}

void checkIfEatFood(struct snake *snake, struct food *food) {
    // check if snake is eating food
    if (snake->body[0].x == food->x && snake->body[0].y == food->y) {
        // eat the food
        snake->length++;
        for (int i = snake->length - 1; i >= 0; i--) {
            snake->body[i + 1].x = snake->body[i].x;
            snake->body[i + 1].y = snake->body[i].y;
        }
        snake->body[0].x = food->x;
        snake->body[0].y = food->y;
        spawnFood(food);
    }
}

void drawFood(struct food food) {
    // draw food
    move(food.x, food.y);
    addch('*');
    refresh();
}

void drawSnake(struct snake *snake) {
    // draw snake
    for (int i = 0; i < snake->length; i++) {
        mvaddch(snake->body[i].x, snake->body[i].y, 'O');
    }
    refresh();
}

void moveSnake(struct snake *snake, int moveX, int moveY) {
    // move snake
    mvaddch(snake->body[snake->length - 1].x, snake->body[snake->length - 1].y, ' ');

    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i].x = snake->body[i - 1].x;
        snake->body[i].y = snake->body[i - 1].y;
    }
    snake->body[0].x = moveX;
    snake->body[0].y = moveY;
    refresh();
}

int checkAlive(struct snake snake) {
    // check if snake hit itself
    for (int i = 1; i < snake.length; i++) {
        if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
            return 0;
        }
    }
    
    // check if snake hit wall
    if (snake.body[0].x < 0 || snake.body[0].x >= LINES || snake.body[0].y < 0 || snake.body[0].y >= COLS) {
        return 0;
    }

    return 1;
}