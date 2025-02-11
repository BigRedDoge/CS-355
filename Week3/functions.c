#include <stdio.h>

int product1(int, int);

int main() {
    int a, b;
    printf("Please enter 2 numbers: ");
    scanf("%d %d", &a, &b);
    
    int tmp1 = product1(a, b);
    printf("Product1: %d * %d = %d", a, b, tmp1);
}

int product1(int x, int y) {
    int result = x*y;
    return result;
}