#ifndef SNAKE_H
#define SNAKE_H

#include <ncurses.h>

struct body {
    int x;
    int y;
};

struct snake {
    int x;
    int y;
    int length;
    int direction;
    struct body *body;
};

struct food {
    int x;
    int y;
};

struct snake initializeSnake(int speed);
void playSnake(struct snake snake, int speed);
void drawSnake(struct snake snake);
void drawFood(struct food food);
void moveSnake(struct snake *snake, int moveX, int moveY);
void spawnFood(struct food *food);
void checkIfEatFood(struct snake *snake, struct food *food);
int checkAlive(struct snake snake);


#endif // SNAKE_H