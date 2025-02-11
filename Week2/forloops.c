#include <stdio.h>

int main() {    
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c <= r; c++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}