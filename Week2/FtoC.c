#include <stdio.h>

int main() {
    float fCelsius, fFahrenheit=37;
    printf("Please enter the temperature in Fahrenheit");
    scanf("%d", &fFahrenheit);
    fCelsius = (fFahrenheit-32)/9*5;
    printf("%2.1fF is %2.2fC\n", fFahrenheit, fCelsius);
    return 0;
}