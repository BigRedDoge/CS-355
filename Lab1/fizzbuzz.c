/* 
Sean Clifford
CS 355
*/
#include <stdio.h>

void int_input(int* integer);
void fizzbuzz(int integer);
int abs(int integer);

int main() {
    int integer_input;

    // get integer input from user
    int_input(&integer_input);

    // do fizzbuzz
    fizzbuzz(integer_input);
    
    return 0;
}

/*
Execute fizzbuzz
*/
void fizzbuzz(int integer) {
    int integer_abs = abs(integer);

    int negative = integer < 0;

    // loop from 0 to inputted integer
    for (int i = 0; i <= integer_abs; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            // if i is divisible by both 3 and 5
            printf("FizzBuzz\n");
        } else if (i % 3 == 0) {
            // if i is divisible by 3
            printf("Fizz\n");
        } else if (i % 5 == 0) {
            // if i is divisible by 5
            printf("Buzz\n");
        } else {
            // if i is not divisible by 3 and 5
            if (negative) {
                printf("%d\n", -i);
            } else {
                printf("%d\n", i);
            }
        }
    }
}

/*
Get integer input from user
*/
void int_input(int* integer) {
    printf("Please enter an integer: ");
    scanf("%d", integer);
}

/*
Get absolute value of integer
*/
int abs(int integer) {
    if (integer < 0) {
        return -integer;
    } else {
        return integer;
    }
}