#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

/*
def is_prime_brute_force(number):
    if number <= 1:
        return False
    for i in range(2, int(number**0.5) + 1):
        if number % i == 0:
            return False
    return True

def find_primes_brute_force(limit):
    primes = []
    for number in range(2, limit + 1):
        if is_prime_brute_force(number):
            primes.append(number)
    return primes

*/

int current_prime = 0;

int is_prime(int num) {
    if (num <= 1) {
        return 0;
    }
    // check if divisible by any number between 2 and its square root
    for (int i = 2; i < pow(num, 0.5) + 1; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

void calculate_primes() {
    int n = 0;
    while (1) {
        if (is_prime(n)) {
            current_prime = n;
        }
        n++;
    }
}

void check_end(int signum) {
    char* quit;
    printf("%d     Quit [y/n]? ", current_prime);
    scanf("%s", quit);
    if ((strcmp(quit, "y") == 0) || (strcmp(quit, "Y") == 0)) {
        signal(SIGINT, SIG_DFL);
        raise(SIGINT);
    }
}

int main(){
    signal(SIGINT, check_end);
    calculate_primes();

    return 0;
}