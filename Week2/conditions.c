#include <stdio.h>

int main() {
    int iAge = 0;
    printf("How old are you? ");
    scanf("%d", &iAge);
    //printf("You told me that you are %d years old\n", iAge);

    if (iAge >= 0 && iAge <= 120) {
        printf("Hello! Your age is %d\n", iAge);
    } else {
        printf("You entered an invalid age %d", iAge);
    }

    return 0;
}